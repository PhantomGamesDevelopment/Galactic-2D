/**
* Galactic 2D
* Source/EngineCore/Tools/huffman.h
* Defines a class instance for coding & decoding strings to BitStreams using Huffman Tables
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

#ifndef GALACTIC_INTERNAL_HUFFMAN
#define GALACTIC_INTERNAL_HUFFMAN

#include "../engineCore.h"
#include "../Containers/map.h"
#include "../Stream/bitStream.h"

namespace Galactic {

	namespace Core {

		namespace Streams {
			//Forward Dec. For The BitStream Class
			class BitStream;
		};

		/*
		HuffNode: The individual node classes. Note: This is a very small object class, consider converting to a Struct?
		 This class serves as the root indicies in the Huffman Tree
		*/
		class HuffNode {
			public:
				/* Class Methods */
				// Default Constructor
				HuffNode() : value(0), leafIndexLeft(-1), leafIndexRight(-1) { }
				/* Class Values */
				//U32 value of the stored character
				U32 value;
				//Index of the node to the left
				S32 leafIndexLeft;
				//Index of the node to the right
				S32 leafIndexRight;
		};

		/*
		HuffLeaf: See HuffNode, This class contains the individual leaves in the Huffman Tree. It contains a value, leaf indicies
		 and a variable containing the bit code for the respective value
		*/
		class HuffLeaf {
			public:
				/* Class Methods */
				// Default Constructor
				HuffLeaf(): value(0), bitCount(0), letter(0), huffCode(0) { }
				/* Class Values */
				//U32 value of the stored character
				U32 value;
				//The amount of bits used by the leaf
				U8 bitCount;
				//The character stored (stored in unsigned format, no such thing as negative ASCII values)
				U8 letter;
				//The Huffman Code for this individual value (While no code should ever exceed 32 bits, this may be safely converted to a U64 if needed)
				U32 huffCode;
		};

		/*
		HuffCoder: Declares a class to compress and decompress String data into Streams using the Huffman Compression Algorithm
		*/
		class HuffCoder {
			public:
				//Class Constructor
				HuffCoder() : huffTablesBuilt(false) { }
				//Write a String to a BitStream by Compressing it
				bool compressStringToBitStream(UTF16 string, Streams::BitStream *stream, S32 maxLength);
				//Read a String from a BitStream by Decompressing it
				bool decompressStringFromBitStream(UTF8 string, Streams::BitStream *stream);

				//Static HuffCoder class reference
				static HuffCoder G_HuffCoder;

			private:
				/* Huffman Tree */
				struct HuffTree {
					public:
						//Default Constructor
						HuffTree() : node(NULL), leaf(NULL) { }
						//Set the active node
						void set(HuffNode *n);
						//Set the active leaf
						void set(HuffLeaf *l);
						//Get the character value
						U32 getValue();
						//The node assigned at this point in the Tree
						HuffNode *node;
						//The leaf assigned at this point in the Tree
						HuffLeaf *leaf;
				};

				/* Private Class Methods */
				//Build the Huffman Table
				void buildHuffTable();
				//Obtain the index relating to the current level of the tree
				S16 determineTreeIndex(HuffTree &tree);
				//Generate the Huffman codes for a given BitStream
				void generateCodes(S32 treeIndex, S32 tableDepth, Streams::BitStream &ref);

				/* Private Class Values */
				//Boolean to test if the tables have been built yet
				bool huffTablesBuilt;
				//A static constant table of values containing standard english letter frequencies.
				Map<C8, U32> freqTable;
				//Dynamic Array containing the list of Nodes.
				DynArray<HuffNode> huffNodes;
				//Dynamic Array containing the list of Leaves.
				DynArray<HuffLeaf> huffLeaves;
		};

	};

};

#endif //GALACTIC_INTERNAL_HUFFMAN