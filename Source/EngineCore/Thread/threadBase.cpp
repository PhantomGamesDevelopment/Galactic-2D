/**
* Galactic 2D
* Source/EngineCore/Thread/threadBase.cpp
* Defines standardized threading classes used throughout the engine.
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
		EventPool Class Definitions
		*/
		EventPool &EventPool::fetchInstance() {
			if (managedSingleton<EventPool>::instance() == NULL) {
				managedSingleton<EventPool>::createInstance();
			}
			return *(managedSingleton<EventPool>::instance());
		}

		Event *EventPool::fetchFromPool() {
			if (ePool.size() < 1) {
				return PlatformProcess::createEvent();
			}
			Event *last = ePool[ePool.size() - 1];
			ePool.popBack();
			if (last == NULL) {
				last = PlatformProcess::createEvent();
			}
			return last;
		}

		void EventPool::returnToPool(Event *e) {
			if (e == NULL) {
				GC_Error("EventPool::returnToPool(): Cannot send NULL to the event pool.");
				return;
			}
			ePool.pushToBack(e);
		}

		/*
		SingleEvent Class Definitions
		*/
		SingleEvent::SingleEvent() : storedEvent(fetchFromPool()) { }

		SingleEvent::~SingleEvent() {
			storedEvent->wait();
			returnToPool(storedEvent);
			storedEvent = NULL;
		}

		Event *SingleEvent::fetch() {
			return storedEvent;
		}

		void SingleEvent::fire() {
			storedEvent->fire();
		}

		Event *SingleEvent::fetchFromPool() {
			return EventPool::fetchInstance().fetchFromPool();
		}

		void SingleEvent::returnToPool(Event *e) {
			EventPool::fetchInstance().returnToPool(e);
		}

		/*
		ObjectThread Class Definitions
		*/
		ObjectThread::~ObjectThread() {
			//Stub Function...
		}

		bool ObjectThread::init() {
			//Stub Function...
			return true;
		}

		void ObjectThread::hold() {
			//Stub Function...
		}

		void ObjectThread::stop() {
			//Stub Function...
		}

		SingleThreadedObjThread *ObjectThread::fetchNMT() {
			//Stub Function...
			return NULL;
		}
		
		/*
		ContinualThread Class Definitions
		*/
		ContinualThread *ContinualThread::init(UTF16 name, ObjectThread *refObjThrd, bool delObjThrd_exit, bool delSelf_exit, U64 stackSize, ThreadPriority p, U64 affinityMask) {
			if (refObjThrd == NULL) {
				GC_Error("ContinualThread::init(): Cannot send a NULL reference thread to this method.");
				return NULL;
			}
			ContinualThread *newInst = NULL;
			if (PlatformProcess::isMultithreaded()) {
				newInst = PlatformProcess::createContThread();
				if (newInst) {
					//If we passed an affinity, we need to fetch the proper overlay mask (This is mainly an android thing, but still, we need it here)
					if (affinityMask == 0) {
						affinityMask = PlatformProcess::fetchAffinityMask(name);
					}
					//Try to initialize the thread
					if (!newInst->create(name, refObjThrd, delObjThrd_exit, delSelf_exit, stackSize, p, affinityMask)) {
						GC_Error("ContinualThread::init(): Failed to initialize a thread object.");
						SendToHell(newInst);
					}
				}
			}
			else if (refObjThrd->fetchNMT()) {
				newInst = new SingleThreadedContinualThread();
				//Try to initialize the thread
				if (!newInst->create(name, refObjThrd, delObjThrd_exit, delSelf_exit, stackSize, p, affinityMask)) {
					GC_Error("ContinualThread::init(): Failed to initialize a thread object.");
					SendToHell(newInst);
				}
			}
			//Has this thread already been forked off and flagged for deletion?
			if (newInst && newInst->onCreated()) {
				newInst = NULL; 
			}
			//If it's still sitting there, then it's waiting to be thrown into the registry
			if (newInst) {
				threadRegistry::fetchInstance().add(newInst->getThreadID, newInst);
			}
			return newInst;
		}

		BasicMulticastDelegate &ContinualThread::onDestroyed() {
			return onThreadDestroyedDelegate;
		}

		/*
		threadRegistry Class Definitions
		*/
		threadRegistry &threadRegistry::fetchInstance() {
			if (managedSingleton<threadRegistry>::instance() == NULL) {
				managedSingleton<threadRegistry>::createInstance();
			}
			return *(managedSingleton<threadRegistry>::instance());
		}

		void threadRegistry::add(U32 id, ContinualThread *t) {
			//Whenever we manipulate the registry, we need to lock the threads first.
			lock();
			if (tRegistry.find(id) == NULL) {
				//We need to add it...
				tRegistry.insert(Pair<U32, ContinualThread *>(id, t));
			}
			else {
				tRegistry.at(id) = t;
			}
			updated = true;
			unlock();
		}

		void threadRegistry::remove(U32 id) {
			lock();
			tRegistry.erase(id);
			updated = true;
			unlock();
		}

		ContinualThread *threadRegistry::fetch(U32 id) {
			return tRegistry.at(id).second;
		}

		S32 threadRegistry::count() {
			lock();
			S32 number = tRegistry.size();
			unlock();
			return number;
		}

		void threadRegistry::lock() {
			cSec.lock();
		}

		void threadRegistry::unlock() {
			cSec.unlock();
		}

		void threadRegistry::reset() {
			updated = false;
		}

		bool threadRegistry::isUpdated() {
			return FBOOL(updated == true);
		}

	};

};