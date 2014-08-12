/**
* Galactic 2D
* (C) 2014 Phantom Games Development - All Rights Reserved
* map.h
*
* Defines a Data Map class similar to the one defined in the Standard Template Library (std::map). This class
*  allows you to define a list of elements with a key and a element associated with it (Double Associated Array).
*  This header file also includes a basic form of the std::pair class (Pair) to be used alongside the Map class.
**/

#ifndef GALACTIC_INTERNAL_MAP
#define GALACTIC_INTERNAL_MAP

#include "../engineCore.h"

namespace Galactic {

	namespace Core {

		/*
		Pair is a dual reference template (tuple) style class that works by allowing the programmer to input two different classes
		 or data types into a single reference point (object) to be used by other tuple style classes. For the references used by 
		 ::get, see the Pair_Data class below.
		*/
		template <class T1, class T2> class Pair {
			public:
				typedef Pair<T1, T2> _pRef;

				T1 first;
				T2 second;

				//Default Constructor
				Pair() : first(), second() { }
				//Assign Constructor
				Pair(const T1 &t1, const T2 &t2) : first(t1), second(t2) { }

				//Swap Elements
				void swap(_pRef &ref) {
					if(this != ref) {
						_pRef tmp = ref;
						//Swap the elements now.
						ref.first = first;
						ref.second = second;
						//And bring over the other side.
						first = tmp.first;
						second = tmp.second;
					}
				}

				//Assign operator
				_pRef& operator=(const _pRef& ref) {
					first = ref.first;
					second = ref.second;
					return (*this);
				}

				//Assign from existing pair
				template <class X1, class X2> _pRef& operator=(const Pair<X1, X2>& ref) {
					first = ref.first;
					second = ref.second;
					return (*this);					
				}
		};

		/*
		The following is the definition of Pair_Data, which is used in the definition of ::get. This works pretty much in an exact fashion
		 as the one defined in the STL <utility.h>, so we use that as a base point. This deals with some very dicey C++ code, so you probably
		 shouldn't touch anything in here unless you absolutely know what you're doing.
		*/
		//Forward Declaration of Pair Data, so we can define the structs for indicies 0 and 1 below.
		template <S32 index, class type> struct Pair_Data;
		//Define the Pair_Data struct for index 0
		template <class T1, class T2> struct Pair_Data <0, Pair<T1, T2>> {
			public:
				typedef typename const T1 constType;
				typedef typename T1& refType;

				static constType value(const Pair<T1, T2> &pairRef) {
					return (pairRef.first);
				}

				static refType value(Pair<T1, T2> &pairRef) {
					return (pairRef.first);
				}
		};
		//Define the Pair_Data struct for index 1
		template <class T1, class T2> struct Pair_Data <1, Pair<T1, T2>> {
			public:
				typedef typename const T2 constType;
				typedef typename T2& refType;

				static constType value(const Pair<T1, T2> &pairRef) {
					return (pairRef.second);
				}

				static refType value(Pair<T1, T2> &pairRef) {
					return (pairRef.second);
				}
		};

		/*
		And after that lovely bit of a mess there, we can define the following two functions to allow us to do
		 Pair::get<0>(pair) and Pair::get<1>(pair) to obtain the values of the pair in reference or constant form.
		*/

		template <S32 index, class T1, class T2> typename Pair_Data<index, Pair<T1, T2>>::refType get(Pair<T1, T2> &ref) {
			return (Pair_Data<index, Pair<T1, T2>>::value(ref));
		}

		template <S32 index, class T1, class T2> typename Pair_Data<index, Pair<T1, T2>>::constType get(const Pair<T1, T2> &ref) {
			return (Pair_Data<index, Pair<T1, T2>>::value(ref));
		}


		/* MapNode contains each element stored in the Map. Each node contains a _keyType value and a _mapType value */
		template <class Key, class T> struct MapNode {
			typedef Pair<Key, T> _pRef;

			Key first;
			T second;

			//Functions
			//Default (Empty) Constructor
			MapNode() : first(), second() { }
			//Create Constructor, Two Values
			MapNode(Key &f, T &s) : first(f), second(s) { }
			//Create Constructor, Pair
			MapNode(_pRef p) : first(p.first), second(p.second) { }
			//Destructor
			~MapNode() { }
			//Operators
			//Setting Operator (Key Type).
			MapNode &operator=(Key &src) {
				first = src;
				return this;
			}
			//Setting Operator (Map Type).
			MapNode &operator=(T &src) {
				second = src;
				return this;
			}
		};

		/*
		Map is a class that is based off of the functioning used by the STL's map class. The map is a double associated array where each value
		 in the array has an associated key to go with the value
		*/
		template <class Key, class T> class Map {
			public:
				//This typedef is a shortcut to using Pair<Key, T> in the numerous functions here, instead, use _pRef.
				typedef Pair<Key, T> _pRef;
				typedef Key _keyType;
				typedef T _mapType;
				typedef MapNode<Key, T>* iterator;
				typedef const MapNode<Key, T>* const_iterator;

				//Standard Constructor
				Map();
				//Standard Destructor
				~Map();

				//Get the first element in the Map
				iterator begin();
				//Get the last element in the Map
				iterator end();
				//Constant definition of begin()
				const_iterator begin() const;
				//Constant definition of end()
				const_iterator end() const;

				//Test if the map is empty or not
				bool empty();
				//Return the size of the Map (amount of Nodes)
				U32 size();
				//Returns the maximum space of the Map in it's current state
				U32 maxSize();

				//Returns the first MapNode based on a key, see find()
				MapNode<Key, T> &at(const _keyType &src);

				//Access operator
				MapNode<Key, T> &operator[](U32 index);
				//S32 definition of the Access operator
				MapNode<Key, T> &operator[](S32 index) { return operator[]((U32)index); }
				//Assignment Operator
				Map &operator=(const Map &c);

				//Insert a pair to the Map
				void insert(_pRef &src);
				//Insert a pair at a specified location
				void insert(iterator pos, _pRef &src);
				//Erase a single element
				void erase(iterator pos);
				//Erase every element with a specific key
				void erase(const _keyType &ref);
				//Empty the map
				void clear();
				//Find the first MapNode based on a key at a given position
				iterator find(const _keyType &ref, U32 startPosition = 0);
				//Returns the number of MapNodes that are using a specifiec key
				U32 count(const _keyType &ref);

			protected:
				//The Dynamic Array containing the MapNodes for this object
				DynArray<MapNode<Key, T> *> container;
		};

		/* Map Functions */
		//
		template <class Key, class T> Map<Key, T>::Map() {
			container = NULL;
		}

		template <class Key, class T> Map<Key, T>::~Map() {

		}

		template <class Key, class T> MapNode<Key, T> *Map<Key, T>::begin() {
			//Note: We need this type-cast otherwise the compiler thinks this is DynArray::Y (iterator) instead of Map::iterator
			return (MapNode<Key, T> *)container.begin();
		}

		template <class Key, class T> MapNode<Key, T> *Map<Key, T>::end() {
			//Note: We need this type-cast otherwise the compiler thinks this is DynArray::Y (iterator) instead of Map::iterator
			return (MapNode<Key, T> *)container.end();
		}

		template <class Key, class T> const MapNode<Key, T> *Map<Key, T>::begin() const {
			//Note: We need this type-cast otherwise the compiler thinks this is DynArray::Y (iterator) instead of Map::iterator
			return (const MapNode<Key, T> *)container.begin();
		}

		template <class Key, class T> const MapNode<Key, T> *Map<Key, T>::end() const {
			//Note: We need this type-cast otherwise the compiler thinks this is DynArray::Y (iterator) instead of Map::iterator
			return (const MapNode<Key, T> *)container.end();
		}

		template <class Key, class T> bool Map<Key, T>::empty() {
			return container.isEmpty();
		}

		template <class Key, class T> U32 Map<Key, T>::size() {
			return container.size();
		}

		template <class Key, class T> U32 Map<Key, T>::maxSize() {
			return container.capacity();
		}

		template <class Key, class T> MapNode<Key, T> &Map<Key, T>::at(const Key &src) {
			for(iterator it = begin(); it != end(); it++) {
				if(it->first == src) {
					return it;
				}
			}
			return NULL;
		}

		template <class Key, class T> MapNode<Key, T> &Map<Key, T>::operator[](U32 index) {
			return container[index];
		}

		template <class Key, class T> Map<Key, T> &Map<Key, T>::operator=(const Map<Key, T> &c) {
			container = c.container;

			return this;
		}

		template <class Key, class T> void Map<Key, T>::insert(Pair<Key, T> &src) {
			MapNode<Key, T> newNode(src);
			container.pushToBack(&newNode);
		}

		template <class Key, class T> void Map<Key, T>::insert(MapNode<Key, T>* pos, Pair<Key, T> &src) {
			MapNode newNode(src);
			container.insert(pos, src);
		}

		template <class Key, class T> void Map<Key, T>::erase(MapNode<Key, T>* pos) {
			container.erase(pos);
		}

		template <class Key, class T> void Map<Key, T>::erase(const Key &src) {
			while(find(src) != NULL) {
				container.erase(find(src));
			}
		}

		template <class Key, class T> void Map<Key, T>::clear() {
			container.clear();
		}

		template <class Key, class T> MapNode<Key, T> *Map<Key, T>::find(const Key &ref, U32 startPosition) {
			if(startPosition >= size()) {
				return NULL;
			}
			for(U32 i = startPosition; i < size(); i++) {
				if(container[i]->first == ref) {
					return container[i];
				}
			}
			return NULL;
		}

		template <class Key, class T> U32 Map<Key, T>::count(const Key &ref) {
			U32 elements = 0;
			for(iterator it = begin(); it != end(); it++) {
				if(it->first == ref) {
					elements++;
				}
			}
			return elements;
		}

	};

};

#endif //GALACTIC_INTERNAL_MAP