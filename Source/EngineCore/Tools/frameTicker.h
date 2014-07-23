/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* frameTicker.h
*
* Defines the engine's ticker module, which tracks engine time
**/

#ifndef GALACTIC_CORE_TOOLS_FRAMETICKER
#define GALACTIC_CORE_TOOLS_FRAMETICKER

#include "../Delegates/delegate.h"

namespace Galactic {

	namespace Core {

		//Initialize the ticker delegate class instance. Returns a boolean value, and accepts F32 dT as a parameter.
		GALACTIC_INIT_SC_DELEGATE_ReturnType_OneParam(GalacticFrameTickerDelegate, bool, F32);

		/*
		struct TickerInstance: Stores all of the information for the individual ticker.
		*/
		struct TickerInstance {
			/* Struct Constructor */
			//Default Constructor
			TickerInstance() {}
			//Copy Constructor
			TickerInstance(F64 net, F32 dt, const GalacticFrameTickerDelegate &c) : nextExecTime(net), deltaTime(dt), tickerDelegate(c) { }

			/* Stuct Methods */
			//Execute the event, returns true if the event was executed.
			bool exec(F32 dt) {
				if (tickerDelegate.bound()) {
					return tickerDelegate.exec(dt);
				}
				return false;
			}

			/* Struct Members */
			//The next scheduled time this ticker element will execute.
			F64 nextExecTime;
			//The change in time (delay) between the fire.
			F32 deltaTime;
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
				void tick(F32 dt) {
					if (tickerList.isEmpty()) {
						return;
					}
					F64 current = cTime + dt;
					DynArray<TickerInstance> eventPriority;
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
				void addTickerInstance(const GalacticFrameTickerDelegate &dele, F32 dt = 0.0f) {
					TickerInstance newInst(cTime + dt, dt, dele);
					tickerList.pushToBack(newInst);
				}

				//Remove a TickerInstance from the list.
				void removeTickerInstance(const GalacticFrameTickerDelegate &dele) {
					for (S32 i = 0; i < tickerList.size(); i++) {
						if (tickerList[i].tickerDelegate == dele) {
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
				//The DynArray instance containing the TickerInstance objects
				DynArray<TickerInstance> tickerList;
		};

	};

};

#endif //GALACTIC_CORE_TOOLS_FRAMETICKER