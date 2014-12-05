/**
* Galactic 2D
* Source/EngineCore/Thread/threadTasks.cpp
* Defines classes to be used alongside or employed directly by the threading system in the engine
* (C) 2014 Phantom Games Development - All Rights Reserved
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
**/

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		WorkPoolBase *G_ThreadPool = NULL;

		/*
		TSCounter Class Definitions
		*/
		#if (!defined(GALACTIC_WINDOWS) || WINVER >= 0x0600)

			TSCounter::TSCounter(S64 initialValue) {
				tsCounter = initialValue;
			}

			TSCounter::TSCounter(const TSCounter &c) {
				//Note! This method is not 100% "thread-safe" because if the counter being copied is currently being used, then the value cannot be guarenteed.
				// ToDo? Consider some kind of mutex lock on the counter in question until the copy is complete.
				tsCounter = c.tsCounter;
			}

			S64 TSCounter::fetch() const {
				return tsCounter;
			}

			S32 TSCounter::toS32() const {
				//This type-cast "should" be safe, since we're downcasting.
				return (S32)tsCounter;
			}

			S64 TSCounter::inc() {
				return PlatformAtomics::increment(&tsCounter);
			}

			S64 TSCounter::dec() {
				return PlatformAtomics::decrement(&tsCounter);
			}

			S64 TSCounter::add(S64 amount) {
				return PlatformAtomics::add(&tsCounter, amount);
			}

			S64 TSCounter::sub(S64 amount) {
				return PlatformAtomics::add(&tsCounter, -(amount));
			}

			S64 TSCounter::set(S64 value) {
				return PlatformAtomics::exchange(&tsCounter, value);
			}

			S64 TSCounter::operator++() {
				return inc();
			}

			S64 TSCounter::operator--() {
				return dec();
			}

			S64 TSCounter::operator+=(S64 amount) {
				return add(amount);
			}

			S64 TSCounter::operator-=(S64 amount) {
				return sub(amount);
			}

			S64 TSCounter::operator=(S64 value) {
				return set(value);
			}

		#else

			TSCounter::TSCounter(S32 initialValue) {
				tsCounter = initialValue;
			}

			TSCounter::TSCounter(const TSCounter &c) {
				//Note! This method is not 100% "thread-safe" because if the counter being copied is currently being used, then the value cannot be guarenteed.
				// ToDo? Consider some kind of mutex lock on the counter in question until the copy is complete.
				tsCounter = c.tsCounter;
			}

			S32 TSCounter::fetch() const {
				return tsCounter;
			}

			S32 TSCounter::toS32() const {
				//We're on a windows platform below vista, hence there is no actual convert-to-S32 function, since, we're already S32, push a warn()
				#if !(GALACTIC_DONT_REPORT_INTERNAL_ERRORS)
					GC_Warn("TSCounter::toS32(): This version of windows does not support 64-bit thread-safe counters, you may safely use fetch() to obtain the requested value.");
				#endif
				return fetch();
			}

			S32 TSCounter::inc() {
				return PlatformAtomics::increment(&tsCounter);
			}

			S32 TSCounter::dec() {
				return PlatformAtomics::decrement(&tsCounter);
			}

			S32 TSCounter::add(S32 amount) {
				return PlatformAtomics::add(&tsCounter, amount);
			}

			S32 TSCounter::sub(S32 amount) {
				return PlatformAtomics::add(&tsCounter, -(amount));
			}

			S32 TSCounter::set(S32 value) {
				return PlatformAtomics::exchange(&tsCounter, value);
			}

			S32 TSCounter::operator++() {
				return inc();
			}

			S32 TSCounter::operator--() {
				return dec();
			}

			S32 TSCounter::operator+=(S32 amount) {
				return add(amount);
			}

			S32 TSCounter::operator-=(S32 amount) {
				return sub(amount);
			}

			S32 TSCounter::operator=(S32 value) {
				return set(value);
			}

		#endif

		/*
		WorkerThread Class Definitions	
		*/
		WorkerThread::WorkerThread() : killThreadFlag(0), poolInst(NULL), workEvent(NULL), threadWork(NULL) { }

		bool WorkerThread::create(WorkPoolBase *owningPool, ThreadBase::ThreadPriority p, U32 stackSize) {
			static S32 workerThreadID = 0;
			String threadName = String::ToStr("WorkerThread_%i", workerThreadID);
			poolInst = owningPool;
			workEvent = PlatformProcess::createEvent();
			threadInst = ContinualThread::init(threadName.c_str(), this, false, false, stackSize, p);
			workerThreadID++;
			if (!threadInst) {
				GC_Error("WorkerThread::create(): Failed To Create a Worker Thread Instance.");
				return false;
			}
			return true;
		}

		void WorkerThread::performWork(Work *workToDo) {
			if (threadWork != NULL) {
				GC_Error("WorkerThread::performWork(): Unable to initiate another work task while a job is in process.");
				return;
			}
			//Assign the task, Then apply a barrier call to prevent the work from overloading the memory.
			threadWork = workToDo;
			PlatformOperations::strictMemory();
			//Perform the task.
			workEvent->fire();
		}

		bool WorkerThread::kill() {
			//Recall that these threads are also part of a thread-safe manager instance, therefore the kill value is handled by an atomic-lock numeric.
			PlatformAtomics::increment(&killThreadFlag);
			//This process is a little more tricky, since the thread itself may still be "sleeping" we need to first wake it, and then kill it off.
			// The kill process must be absolute at the time, and therefore we could be in for a bit of memory trouble. This is just a little ToDo note
			// to investigate by trial-and-error the potential leak effect this may have.
			workEvent->fire();
			threadInst->waitForCompletion();
			//Clean up the instances.
			SendToHell(workEvent);
			SendToPitsOfHell(threadInst);
			//All finished!
			return true;
		}

		U32 WorkerThread::run() {
			//This method actually performs the thread execution, essentially, we keep cycling through until an event is detected, then do it.
			while (killThreadFlag < 1) {
				//Grab the work locally, then enforce a barrier call to prevent memory from leaking away endlessly.
				workEvent->wait();
				Work *job = threadWork;
				threadWork = NULL;
				PlatformOperations::strictMemory();
				if (!(job || killThreadFlag)) {
					//ToDo: Throw an assert here for invalid thread call...
					GC_Error("WorkerThread::run(): Invalid thread call operation blocked.");
				}
				//Do the work, and then keep doing work until there's nothing left to do...
				while (job != NULL) {
					job->perform();
					job = poolInst->fetchNextTask(this);
				}
			}
			return 0;
		}

		/*
		WorkPoolBase Class Definitions
		*/
		WorkPoolBase *WorkPoolBase::createInstance() {
			return new WorkPool;
		}

		/*
		MutexLock Class Definitions
		*/
		MutexLock::MutexLock(PlatformCriticalSection *cs) : cSec(cs) {
			if (!cSec) {
				GC_Error("MutexLock(): Unable to initialize instance, invalid critical section object sent to class.");
				return;
			}
			cs->lock();
		}

		MutexLock::~MutexLock() {
			if (!cSec) {
				//This is very... very.. bad.
				GC_CError("[PTL_CERR] ~MutexLock(): Unable to detect locking instance, there is a possibility of a function deadlock...");
				return;
			}
			cSec->unlock();
		}

		/*
		WorkPool Class Definitions
		*/
		WorkPool::WorkPool() : cSec(NULL), isBeingDeleted(false) { }

		WorkPool::~WorkPool() {
			cleanThreads();
		}

		bool WorkPool::createWithAmount(U32 amountOfThreads, ThreadBase::ThreadPriority p, U32 stackSize) {
			//We use this flag here to determine if we got the desired result, or not.
			bool success = true;
			if (cSec != NULL) {
				//The critical section object should not be initialized before this function, stop everything here.
				return false;
			}
			cSec = new PlatformCriticalSection();
			//At this point in time, we want to lock down this method to other thread instances...
			MutexLock lock(cSec);
			openWorkerThreads.reserve(amountOfThreads * sizeof(WorkerThread *));
			//Now actually add the threads.
			for (S32 i = 0; i < (S32)amountOfThreads; i++) {
				WorkerThread *newThread = new WorkerThread();
				//Attempt to initialize the thread
				if (newThread->create(this, p, stackSize)) {
					//Add the thread to the pool
					openWorkerThreads.pushToBack(newThread);
					allThreadObjects.pushToBack(newThread);
				}
				else {
					//The thread failed to init... break off..
					SendToPitsOfHell(newThread);
					success = false;
					break;
				}
			}
			//If we failed in some way or form, clean out everything...
			if (!success) {
				cleanThreads();
			}
			return success;
		}

		void WorkPool::cleanThreads() {
			//This is by far one of the most 'annoying' methods in the eninge. We essentially need to pull a list instance of all of the jobs of the
			// pool, while maintaining thread safety during deletion. Assuming that the whole method doesn't just explode with memory problems during 
			// the call, we need to kill off threads in terms of which ones can be 'safely' terminated. Lastly, we clean up the memory used by these threads.
			if (!cSec) {
				//If we don't have a critical section object, this class was never initialized, and therefore, this call is invalid, goodbye...
				GC_Error("WorkPool::cleanThreads(): Cannot call cleanThreads() on an uninitialized WorkPool class.");
				return;
			}
			//Lock down the call to other threads, then apply a memory barrier to other threads, we use the if() to scope the call to the specified area.
			if (true) {
				MutexLock lock(cSec);
				isBeingDeleted = true;
				PlatformOperations::strictMemory();
				for (Work *iter = jobsToDo.front(); iter != jobsToDo.back(); iter++) {
					iter->halt();
				}
				jobsToDo.clear();
			}
			jobsToDo.compact();
			//This is where things just get brutal in terms of work. We need to validate that the threads are 'completed' before they can be safely deleted.
			// We also need to ensure they are locked down so nothing new can get a hold of them while they're being deleted.
			while (true) {
				//Scope down the lock to the specified region
				if (true) {
					MutexLock lock(cSec);
					//If these sizes are equal, all threads are done...
					if (allThreadObjects.size() == openWorkerThreads.size()) {
						break;
					}
				}
				//Block infinite loop by sleeping the call with an infintesimally small number so values can be updated outside of the call.
				PlatformProcess::sleep(0.0);
			}
			//Now actually delete those threads, scope the lock...
			if (true) {
				MutexLock lock(cSec);
				for (WorkerThread *iter = allThreadObjects.front(); iter != allThreadObjects.back(); iter++) {
					iter->kill();
					SendToPitsOfHell(iter);
				}
			}
			//Last thing to do is "uninitialize" the class by eliminating the critical section, this also unlocks all of those mutex locks specified above.
			SendToHell(cSec);
		}

		void WorkPool::addWork(Work *w) {
			if (!w) {
				GC_Error("WorkPool::addWork(): Cannot add a NULL job to the work pool.");
				return;
			}
			if (!cSec) {
				//This class is uninitialized, stop...
				GC_Error("WorkPool::addWork(): Cannot call addWork() on an uninitialized WorkPool class.");
				return;
			}
			if (isBeingDeleted) {
				//Sorry, this pool is going bye bye, kill here.
				GC_Error("WorkPool::addWork(): Work pool is currently in the de-initialization process, cannot add job.");
				w->halt();
				return;
			}
			WorkerThread *worker = NULL;
			//At this point, the method is wide open to other threads, which is bad, lock the method down, and add the job.
			MutexLock lock(cSec);
			if (openWorkerThreads.size() > 0) {
				//If there's an open thread, give it something to do now, then take it from the list of open threads.
				worker = openWorkerThreads[openWorkerThreads.size() - 1];
				openWorkerThreads.erase(openWorkerThreads.size() - 1);
			}
			//Check if we were sent out...
			if (!worker) {
				//Unfortunately not, so add the job to the work pool.
				jobsToDo.pushToBack(w);
			}
			else {
				//Yep, wake up the thread.
				worker->performWork(w);
			}
		}

		Work *WorkPool::fetchNextTask(WorkerThread *toPool) {
			//This method is responsible for telling threads to either get another task to perform from jobsToDo, or return to openWorkerThreads.
			if (!toPool) {
				GC_Error("WorkPool::fetchNextTask(): Cannot send a NULL thread parameter to this method.");
				return NULL;
			}
			Work *nextJob = NULL;
			MutexLock lock(cSec);
			if (isBeingDeleted) {
				//If we're being deleted ,then we don't want this function being called at all. This is also a good validation point
				if (jobsToDo.size() > 0) {
					GC_Error("WorkPool::fetchNextTask(): Unable to pull a new job from a pool being deleted, %i jobs detected.", jobsToDo.size());
				}
				return NULL;
			}
			//Check for a job to do.
			if (jobsToDo.size() > 0) {
				//Grab the oldest job in the queue (the first one)
				nextJob = jobsToDo[0];
				jobsToDo.erase((U32)0);
				jobsToDo.compact();
			}
			//If nothing was given, then return the specified thread to the pool
			if (!nextJob) {
				openWorkerThreads.pushToBack(toPool);
			}
			return nextJob;
		}

		bool WorkPool::removeWork(Work *w) {
			if (!w) {
				GC_Error("WorkPool::removeWork(): Cannot remove a NULL job from the work pool.");
				return false;
			}
			if (!cSec) {
				//This class is uninitialized, stop...
				GC_Error("WorkPool::removeWork(): Cannot call removeWork() on an uninitialized WorkPool class.");
				return false;
			}
			if (isBeingDeleted) {
				//If the pool is being deleted, this job has likely been stopped already, no further action needed.
				GC_Warn("WorkPool::removeWork(): This work pool is being deleted, the job in question has already been stopped, no further action required.");
				return false;
			}
			MutexLock lock(cSec);
			//Find the first instance of the job in question, and delete it.
			S32 deleteIndex = jobsToDo.findNext(w, 0);
			if (deleteIndex != -1) {
				jobsToDo.erase(deleteIndex);
				return true;
			}
			return false;
		}

	};

};