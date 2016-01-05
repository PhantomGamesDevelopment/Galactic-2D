/**
* Galactic 2D
* Source/EngineCore/Containers/frameTicker.h
* Standard engine class for managing engine "ticks"
* (C) 2014-2016 Phantom Games Development - All Rights Reserved
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

#ifndef GALACTIC_CORE_TOOLS_FRAMETICKER
#define GALACTIC_CORE_TOOLS_FRAMETICKER

#include "../Delegates/easydelegate.hpp"

namespace Galactic {

	namespace Core {

		//Initialize the ticker delegate class instance. Returns a boolean value, and accepts F64 dT as a parameter.
		//GALACTIC_INIT_SC_DELEGATE_ReturnType_OneParam(GalacticFrameTickerDelegate, bool, F64);
		typedef StaticDelegate<bool, F64> GalacticFrameTickerDelegate;

		/*
		struct TickerInstance: Stores all of the information for the individual ticker.
		*/
		struct TickerInstance {
			/* Struct Constructor */
			//Default Constructor
			TickerInstance() : nextExecTime(0), deltaTime(0), tickerDelegate(NULL) { }
			//Copy Constructor
			TickerInstance(F64 net, F64 dt, const GalacticFrameTickerDelegate &c) : nextExecTime(net), deltaTime(dt), tickerDelegate(c) { }

			/* Stuct Methods */
			//Execute the event, returns true if the event was executed.
			bool exec(F64 dt) {
				//TODO: Update easydelegate.hpp to include a simple isBound() method for mProcAddress to ensure this is set.
				return tickerDelegate.invoke(dt);
			}

			/* Struct Members */
			//The next scheduled time this ticker element will execute.
			F64 nextExecTime;
			//The change in time (delay) between the fire.
			F64 deltaTime;
			//The delegate instance of this ticker.
			GalacticFrameTickerDelegate tickerDelegate;
		};

		/*
		FrameTicker: The main engine time class, has control over a delegate which fires an event each time the "tick" is called.
		*/
		class FrameTicker {
			public:
				/* Constructor / Destructor */
				//Default Constructor
				FrameTicker() : cTime(0.0) {

				}

				/* Public Class Methods */
				//Process all events for this frame, by doing it this way, we can save some performance by only pulling out the instances we need to
				// execute, and keeping the ones that aren't ready in the list until the next "tick"
				void tick(F64 dt) {
					if (tickerList.isEmpty()) {
						return;
					}
					F64 current = cTime + dt;
					Vector<TickerInstance> eventPriority;
					//Pull all of the events that are scheduled to execute from the ticker
					for (S32 i = tickerList.size(); i > 0; i++) {
						if (current >= tickerList[i].nextExecTime) {
							eventPriority.pushToBack(tickerList[i]);
							tickerList.erase((U32)i);
						}
					}
					//Adjust the current time...
					cTime = current;
					//Fire events that are ready to go.
					for (S32 i = 0; i < eventPriority.size(); i++) {
						TickerInstance &t = eventPriority[i];
						if (t.exec(dt)) {
							//Success! Re-add to the queue...
							t.nextExecTime = cTime + t.deltaTime;
							tickerList.pushToBack(t);
						}
 					}
				}

				//Add a TickerInstance to the list.
				void addTickerInstance(const GalacticFrameTickerDelegate &dele, F64 dt = 0.0f) {
					TickerInstance newInst(cTime + dt, dt, dele);
					tickerList.pushToBack(newInst);
				}

				//Remove a TickerInstance from the list.
				void removeTickerInstance(const GalacticFrameTickerDelegate &dele) {
					for (S32 i = 0; i < tickerList.size(); i++) {
						if (&tickerList[i].tickerDelegate == &dele) {
							tickerList.erase((U32)i);
						}
					}
				}

				//Fetch the main ticker object
				static FrameTicker &fetchMainTicker() {
					if (managedSingleton<FrameTicker>::instance() == NULL) {
						managedSingleton<FrameTicker>::createInstance();
					}
					return *(managedSingleton<FrameTicker>::instance());
				}

			private:
				/* Private Class Members */
				//The current time stored by the ticker instance.
				F64 cTime;
				//The Vector instance containing the TickerInstance objects
				Vector<TickerInstance> tickerList;
		};

	};

};

#endif //GALACTIC_CORE_TOOLS_FRAMETICKER