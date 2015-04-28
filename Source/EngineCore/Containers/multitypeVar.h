/**
* Galactic 2D
* Source/EngineCore/Containers/multitypeVar.h
* Defines template classes for using multiple type variable instances
* (C) 2014-2015 Phantom Games Development - All Rights Reserved
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

#ifndef GALACTIC_INTERNAL_MULTITYPE
#define GALACTIC_INTERNAL_MULTITYPE

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		//TwoVarCont is an abstract template class instance allowing you to define a simple container with two variable types.
		template <typename T1, typename T2> class TwoVarCont {
			typedef TwoVarCont<T1, T2> ref;

			public:
				/* Public Class Methods */
				//Default (empty) Constructor
				TwoVarCont() : x(), y() { }
				//Assignment Constructor
				TwoVarCont(T1 x1, T2 x2) : x(x1), y(x2) { }
				//Default Destructor
				virtual ~TwoVarCont() { }
				//Fetch method, for variable one
				T1 fetchX() { return x; }
				//Fetch method, for variable two
				T2 fetchY() { return y; }
				//Set method, defined as pure virtual for individual implementation
				virtual void set(T1 x1, T2 x2) = 0;
				//Swap elements of TwoVarCont
				void swap(ref &r) {
					if (this != r) {
						ref tmp = r;
						r.x = x;
						r.y = y;
						x = tmp.x;
						y = tmp.y;
					}
				}
				//Assignment Operator
				ref& operator=(const ref& r) {
					x = r.x;
					y = r.y;
					return (*this);
				}
				//Equality Operator
				bool operator==(const ref& r) {
					return ((x == r.x) && (y == r.y));
				}
				//Inequality Operator
				bool operator!=(const ref& r) {
					return ((x != r.x) || (y != r.y));
				}

				/* Public class members */
				//The variable contained in type one
				T1 x;
				//The variable contained in type two
				T2 y;
		};

		//ThreeVarCont is an abstract template class instance allowing you to define a simple container with three variable types.
		template <class T1, class T2, class T3> class ThreeVarCont {
			typedef ThreeVarCont<T1, T2, T3> ref;

		public:
			/* Public Class Methods */
			//Default (empty) Constructor
			ThreeVarCont() : x(), y(), z() { }
			//Assignment Constructor
			ThreeVarCont(T1 x1, T2 x2, T3 x3) : x(x1), y(x2), z(x3) { }
			//Default Destructor
			virtual ~ThreeVarCont() { }
			//Fetch method, for variable one
			T1 fetchX() { return x; }
			//Fetch method, for variable two
			T2 fetchY() { return y; }
			//Fetch method, for variable three
			T3 fetchZ() { return z; }
			//Set method, defined as pure virtual for individual implementation
			virtual void set(T1 x1, T2 x2, T3 x3) = 0;
			//Swap elements of ThreeVarCont
			void swap(ref &r) {
				if (this != r) {
					ref tmp = r;
					r.x = x;
					r.y = y;
					r.z = z;
					x = tmp.x;
					y = tmp.y;
					z = tmp.z;
				}
			}
			//Assignment Operator
			ref& operator=(const ref& r) {
				x = r.x;
				y = r.y;
				z = r.z;
				return (*this);
			}
			//Equality Operator
			bool operator==(const ref& r) {
				return ((x == r.x) && (y == r.y) && (z == r.z));
			}
			//Inequality Operator
			bool operator!=(const ref& r) {
				return ((x != r.x) || (y != r.y) || (z != r.z));
			}

			/* Public class members */
			//The variable contained in type one
			T1 x;
			//The variable contained in type two
			T2 y;
			//The variable contained in type three
			T3 z;
		};

		//FourVarCont is an abstract template class instance allowing you to define a simple container with four variable types.
		template <class T1, class T2, class T3, class T4> class FourVarCont {
			typedef FourVarCont<T1, T2, T3, T4> ref;

		public:
			/* Public Class Methods */
			//Default (empty) Constructor
			FourVarCont() : w(), x(), y(), z() { }
			//Assignment Constructor
			FourVarCont(T1 x1, T2 x2, T3 x3, T4 x4) : w(x1), x(x2), y(x3), z(x4) { }
			//Default Destructor
			virtual ~FourVarCont() { }
			//Fetch method, for variable one
			T1 fetchW() { return w; }
			//Fetch method, for variable two
			T2 fetchX() { return x; }
			//Fetch method, for variable three
			T3 fetchY() { return y; }
			//Fetch method, for variable four
			T4 fetchZ() { return z; }
			//Set method, defined as pure virtual for individual implementation
			virtual void set(T1 x1, T2 x2, T3 x3, T4 x4) = 0;
			//Swap elements of FourVarCont
			void swap(ref &r) {
				if (this != r) {
					ref tmp = r;
					r.w = w;
					r.x = x;
					r.y = y;
					r.z = z;
					w = tmp.w;
					x = tmp.x;
					y = tmp.y;
					z = tmp.z;
				}
			}
			//Assignment Operator
			ref& operator=(const ref& r) {
				w = r.w;
				x = r.x;
				y = r.y;
				z = r.z;
				return (*this);
			}
			//Equality Operator
			bool operator==(const ref& r) {
				return ((w == r.w) && (x == r.x) && (y == r.y) && (z == r.z));
			}
			//Inequality Operator
			bool operator!=(const ref& r) {
				return ((w != r.w) || (x != r.x) || (y != r.y) || (z != r.z));
			}

			/* Public class members */
			//The variable contained in type one
			T1 w;
			//The variable contained in type two
			T2 x;
			//The variable contained in type three
			T3 y;
			//The variable contained in type four
			T4 z;
		};

	};

};

#endif //GALACTIC_INTERNAL_MULTITYPE