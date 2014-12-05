/**
* Galactic 2D
* Source/EngineCore/Thread/singleThreadBase.cpp
* Defines engine threading classes to be used in single-threaded mode
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

		/*
		SingleThreadedEvent Class Definitions
		*/
		SingleThreadedEvent::SingleThreadedEvent() : hasFired(false), shouldResetManually(false) { }

		bool SingleThreadedEvent::init(bool manualReset) {
			shouldResetManually = manualReset;
			return true;
		}

		void SingleThreadedEvent::reset() {
			hasFired = false;
		}

		void SingleThreadedEvent::fire() {
			//This method should be named ::postFire() but is kept for compatibility purposes.
			hasFired = true;
		}

		bool SingleThreadedEvent::wait(U32 timeInMS) {
			//This is a single-threaded event, therefore we technically cannot wait unless we risk a deadlock, so to prevent this, this method
			// serves as a block-point by forcing a manual event reset.
			if (!hasFired) {
				GC_Warn("SingleThreadedEvent::wait(): Cannot apply wait to an event that has not fired.");
				return false;
			}
			//If there is no manual reset, then reset the event automatically... otherwise, we'll need a reset.
			hasFired = shouldResetManually;
			return true;
		}

		/*
		SingleThreadedContinualThread Class Definitions
		*/
		//Numerical starting value of startIDAt
		U32 SingleThreadedContinualThread::startIDAt = 65535;

		SingleThreadedContinualThread::SingleThreadedContinualThread() : objThread(NULL), onHold(false), shouldDeleteSelf(false), shouldDeleteObjThread(false) {
			threadID = startIDAt++;
			SingleThreadedThreadManager::fetchInstance().add(this);
		}

		SingleThreadedContinualThread::~SingleThreadedContinualThread() {
			SingleThreadedThreadManager::fetchInstance().remove(this);
		}

		bool SingleThreadedContinualThread::create(UTF16 name, ObjectThread *refObjThrd, bool delObjThrd_exit, bool delSelf_exit, U64 stackSize, ThreadPriority p, U64 affinityMask) {
			objThread = refObjThrd->fetchNMT();
			if (objThread != NULL) {
				refObjThrd->init();
			}
			return FBOOL(objThread != NULL);
		}

		void SingleThreadedContinualThread::run() {
			if (objThread != NULL && !onHold) {
				objThread->run();
			}
		}

		void SingleThreadedContinualThread::hold() {
			onHold = true;
		}

		void SingleThreadedContinualThread::resume() {
			onHold = false;
		}

		bool SingleThreadedContinualThread::kill(bool waitForCompletion) {
			//In single-threaded mode, this is an absolute kill command, regardless of the setting of waitForCompletion.
			SingleThreadedThreadManager::fetchInstance().remove(this);
			//Clean some things up...
			if (shouldDeleteObjThread) {
				SendToHell(objThread);
			}
			if (shouldDeleteSelf) {
				SendToPitsOfHell(this);
			}
			return true;
		}

		U32 SingleThreadedContinualThread::getThreadID() {
			return threadID;
		}

		String SingleThreadedContinualThread::getThreadName() {
			return threadName;
		}

		void SingleThreadedContinualThread::setPriority(ThreadPriority newPriority) {
			//In Single-Threaded mode, all threads share a universal priority level, therefore this function is ignored.
			GC_Warn("SingleThreadedContinualThread::setPriority(): There are no thread priorities in single-threaded mode, call ignored.");
		}

		void SingleThreadedContinualThread::setAffinityMask(U64 newMask) {
			//See above...
			GC_Warn("SingleThreadedContinualThread::setAffinityMask(): There are no thread affinity masks in single-threaded mode, call ignored.");
		}

		void SingleThreadedContinualThread::waitForCompletion() {
			//Remove the thread from the manager so it can complete it's task without being deleted by the manager.
			SingleThreadedThreadManager::fetchInstance().remove(this);
		}

		bool SingleThreadedContinualThread::onCreated() {
			//Do nothing else...
			return false;
		}

		/*
		SingleThreadedThreadManager Class Definitions
		*/
		SingleThreadedThreadManager &SingleThreadedThreadManager::fetchInstance() {
			if (managedSingleton<SingleThreadedThreadManager>::instance() == NULL) {
				managedSingleton<SingleThreadedThreadManager>::createInstance();
			}
			return *(managedSingleton<SingleThreadedThreadManager>::instance());
		}

		void SingleThreadedThreadManager::run() {
			for (SingleThreadedContinualThread *it = threadInstances.front(); it != threadInstances.back(); it++) {
				it->run();
			}
		}

		void SingleThreadedThreadManager::add(SingleThreadedContinualThread *t) {
			if (t == NULL) {
				GC_Error("ThreadManager::add(): Cannot add a NULL thread to the list.");
				return;
			}
			threadInstances.pushToBack(t);
		}

		void SingleThreadedThreadManager::remove(SingleThreadedContinualThread *t) {
			if (t == NULL) {
				GC_Error("ThreadManager::remove(): Cannot remove a NULL thread from the list.");
				return;
			}
			threadInstances.eraseSpecific(t);
		}

	};

};