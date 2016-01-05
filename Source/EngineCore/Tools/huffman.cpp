/**
* Galactic 2D
* Source/EngineCore/Tools/huffman.cpp
* Defines a class instance for coding & decoding strings to BitStreams using Huffman Tables
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

#include "huffman.h"

namespace Galactic {

	namespace Core {

		//Declare the static reference
		HuffCoder HuffCoder::G_HuffCoder;

		bool HuffCoder::compressStringToBitStream(UTF16 string, Streams::BitStream *stream, S32 maxLength) {
			if(!string) {
				//We handle empty strings by sending a false flag (compressed), and the Huffman code for empty (0);
				stream->writeFlag(false);
				stream->writeS32(0, 8);
				return true;
			}
			//If the tables aren't built on this instance, do so now.
			if(!huffTablesBuilt) {
				buildHuffTable();
			}
			//Fetch the length.
			S32 stringLen = string ? (S32)strlen(string) : 0;
			if(stringLen > 255) {
				//The string is too long for BitStream::writeString, push a warning.
			}
			if(stringLen > maxLength) {
				stringLen = maxLength;
			}
			//While the String may exceed the writeString maxima, the compression algorithm is bitCount enforced
			// rather than string length enforced, so test this.
			S32 numBits = 0, index = 0;
			for(index = 0; index < stringLen; index++) {
				//Run through the length of the string and get a running bitCount based on leaf values.
				numBits += huffLeaves[(U8)string[index]].bitCount;
			}
			//Is the string too long for compression?
			if(numBits > (stringLen * 8)) {
				stream->writeFlag(false);
				stream->writeS32(stringLen, 8);
				stream->write(string, stringLen);
			}
			else {
				//Nope, we can safely compress.
				stream->writeFlag(true);
				stream->writeS32(stringLen, 8);
				for(index = 0; index < stringLen; index++) {
					HuffLeaf &refLeaf = huffLeaves[(U8)string[index]];
					stream->writeBits(&refLeaf.huffCode, refLeaf.bitCount);
				}
			}
		}

		bool HuffCoder::decompressStringFromBitStream(UTF8 string, Streams::BitStream *stream) {
			//If the tables aren't built on this instance, do so now.
			if(!huffTablesBuilt) {
				buildHuffTable();
			}
			S32 stringLen;
			if(stream->readFlag()) {
				//Compressed String
				S32 strIndx = 0;
				stringLen = stream->readS32(8);
				for(S32 i = 0; i < stringLen; i++) {
					while(true) {
						if(strIndx >= 0) {
							if(stream->readFlag()) {
								strIndx = huffNodes[strIndx].leafIndexRight;
							}
							else {
								strIndx = huffNodes[strIndx].leafIndexLeft;
							}
						}
						else {
							string[i] = huffLeaves[-(strIndx + 1)].letter;
							break;
						}
					}
				}
				string[stringLen] = '\0';
				return true;
			}
			else {
				//Uncompressed String
				stringLen = stream->readS32(8);
				stream->read(string, (U32)stringLen);
				string[stringLen] = '\0';
				return true;
			}
		}

		void HuffCoder::HuffTree::set(HuffNode *n) {
			node = n;
			leaf = NULL;
		}

		void HuffCoder::HuffTree::set(HuffLeaf *l) {
			node = NULL;
			leaf = l;
		}

		U32 HuffCoder::HuffTree::getValue() {
			if(node) {
				return node->value;
			}
			else {
				return leaf->value;
			}
		}

		void HuffCoder::buildHuffTable() {
			if(huffTablesBuilt) {
				//If the table has already been built, don't build a new one.
				return;
			}
			huffTablesBuilt = true;
			//Note: I should really look into alternate ways of this, however a constant frequency table seems to be the only viable option.
			// See the reference (http://en.wikipedia.org/wiki/Letter_frequency) for more details on how these values are obtained ~Phantom
			freqTable.insert(Pair<C8, U32>(0, 0));       /* ASCII 0: NULL */
			freqTable.insert(Pair<C8, U32>(1, 0));       /* ASCII 1: SOTT */
			freqTable.insert(Pair<C8, U32>(2, 0));       /* ASCII 2: STX */
			freqTable.insert(Pair<C8, U32>(3, 0));       /* ASCII 3: ETY */
			freqTable.insert(Pair<C8, U32>(4, 0));       /* ASCII 4: EOT */
			freqTable.insert(Pair<C8, U32>(5, 0));       /* ASCII 5: ENQ */
			freqTable.insert(Pair<C8, U32>(6, 0));       /* ASCII 6: ACK */
			freqTable.insert(Pair<C8, U32>(7, 0));       /* ASCII 7: BELL */
			freqTable.insert(Pair<C8, U32>(8, 0));       /* ASCII 8: BKSPC */
			freqTable.insert(Pair<C8, U32>(9, 329));     /* ASCII 9: HZTAB */
			freqTable.insert(Pair<C8, U32>(10, 21));     /* ASCII 10: NEWLN */
			freqTable.insert(Pair<C8, U32>(11, 0));      /* ASCII 11: VTAB */
			freqTable.insert(Pair<C8, U32>(12, 0));      /* ASCII 12: FF */
			freqTable.insert(Pair<C8, U32>(13, 0));      /* ASCII 13: CR */
			freqTable.insert(Pair<C8, U32>(14, 0));      /* ASCII 14: SO */
			freqTable.insert(Pair<C8, U32>(15, 0));      /* ASCII 15: SI */
			freqTable.insert(Pair<C8, U32>(16, 0));      /* ASCII 16: DLE */
			freqTable.insert(Pair<C8, U32>(17, 0));      /* ASCII 17: DC1 */
			freqTable.insert(Pair<C8, U32>(18, 0));      /* ASCII 18: DC2 */
			freqTable.insert(Pair<C8, U32>(19, 0));      /* ASCII 19: DC3 */
			freqTable.insert(Pair<C8, U32>(20, 0));      /* ASCII 20: DC4 */
			freqTable.insert(Pair<C8, U32>(21, 0));      /* ASCII 21: NAC */
			freqTable.insert(Pair<C8, U32>(22, 0));      /* ASCII 22: SYN */
			freqTable.insert(Pair<C8, U32>(23, 0));      /* ASCII 23: ETB */
			freqTable.insert(Pair<C8, U32>(24, 0));      /* ASCII 24: CAN */
			freqTable.insert(Pair<C8, U32>(25, 0));      /* ASCII 25: EM */
			freqTable.insert(Pair<C8, U32>(26, 0));      /* ASCII 26: SUB */
			freqTable.insert(Pair<C8, U32>(27, 0));      /* ASCII 27: ESC */
			freqTable.insert(Pair<C8, U32>(28, 0));      /* ASCII 28: FS */
			freqTable.insert(Pair<C8, U32>(29, 0));      /* ASCII 29: GS */
			freqTable.insert(Pair<C8, U32>(30, 0));      /* ASCII 30: RS */
			freqTable.insert(Pair<C8, U32>(31, 0));      /* ASCII 31: US */
			freqTable.insert(Pair<C8, U32>(32, 2809));   /* ASCII 32: (Space) */
			freqTable.insert(Pair<C8, U32>(33, 68));     /* ASCII 33: ! */
			freqTable.insert(Pair<C8, U32>(34, 0));      /* ASCII 34: " */
			freqTable.insert(Pair<C8, U32>(35, 27));     /* ASCII 35: # */
			freqTable.insert(Pair<C8, U32>(36, 0));      /* ASCII 36: $ */
			freqTable.insert(Pair<C8, U32>(37, 58));     /* ASCII 37: % */
			freqTable.insert(Pair<C8, U32>(38, 3));      /* ASCII 38: & */
			freqTable.insert(Pair<C8, U32>(39, 62));     /* ASCII 39: ' */
			freqTable.insert(Pair<C8, U32>(40, 4));      /* ASCII 40: ( */
			freqTable.insert(Pair<C8, U32>(41, 7));      /* ASCII 41: ) */
			freqTable.insert(Pair<C8, U32>(42, 0));      /* ASCII 42: * */
			freqTable.insert(Pair<C8, U32>(43, 0));      /* ASCII 43: + */
			freqTable.insert(Pair<C8, U32>(44, 15));     /* ASCII 44: , */
			freqTable.insert(Pair<C8, U32>(45, 65));     /* ASCII 45: - */
			freqTable.insert(Pair<C8, U32>(42, 554));    /* ASCII 46: . */
			freqTable.insert(Pair<C8, U32>(47, 3));      /* ASCII 47: / */
			freqTable.insert(Pair<C8, U32>(48, 394));    /* ASCII 48: 0 */
			freqTable.insert(Pair<C8, U32>(49, 404));    /* ASCII 49: 1 */
			freqTable.insert(Pair<C8, U32>(50, 189));    /* ASCII 50: 2 */
			freqTable.insert(Pair<C8, U32>(51, 117));    /* ASCII 51: 3 */
			freqTable.insert(Pair<C8, U32>(52, 30));     /* ASCII 52: 4 */
			freqTable.insert(Pair<C8, U32>(53, 51));     /* ASCII 53: 5 */
			freqTable.insert(Pair<C8, U32>(54, 27));     /* ASCII 54: 6 */
			freqTable.insert(Pair<C8, U32>(55, 15));     /* ASCII 55: 7 */
			freqTable.insert(Pair<C8, U32>(56, 34));     /* ASCII 56: 8 */
			freqTable.insert(Pair<C8, U32>(57, 32));     /* ASCII 57: 9 */
			freqTable.insert(Pair<C8, U32>(58, 80));     /* ASCII 58: : */
			freqTable.insert(Pair<C8, U32>(59, 1));      /* ASCII 59: ; */
			freqTable.insert(Pair<C8, U32>(60, 142));    /* ASCII 60: < */
			freqTable.insert(Pair<C8, U32>(61, 3));      /* ASCII 61: = */
			freqTable.insert(Pair<C8, U32>(62, 142));    /* ASCII 62: > */
			freqTable.insert(Pair<C8, U32>(63, 39));     /* ASCII 63: ? */
			freqTable.insert(Pair<C8, U32>(64, 0));      /* ASCII 64: @ */
			freqTable.insert(Pair<C8, U32>(65, 144));    /* ASCII 65: A */
			freqTable.insert(Pair<C8, U32>(66, 125));    /* ASCII 66: B */
			freqTable.insert(Pair<C8, U32>(67, 44));     /* ASCII 67: C */
			freqTable.insert(Pair<C8, U32>(68, 122));    /* ASCII 68: D */
			freqTable.insert(Pair<C8, U32>(69, 275));    /* ASCII 69: E */
			freqTable.insert(Pair<C8, U32>(70, 70));     /* ASCII 70: F */
			freqTable.insert(Pair<C8, U32>(71, 135));    /* ASCII 71: G */
			freqTable.insert(Pair<C8, U32>(72, 61));     /* ASCII 72: H */
			freqTable.insert(Pair<C8, U32>(73, 127));    /* ASCII 73: I */
			freqTable.insert(Pair<C8, U32>(74, 8));      /* ASCII 74: J */
			freqTable.insert(Pair<C8, U32>(75, 12));     /* ASCII 75: K */
			freqTable.insert(Pair<C8, U32>(76, 113));    /* ASCII 76: L */
			freqTable.insert(Pair<C8, U32>(77, 246));    /* ASCII 77: M */
			freqTable.insert(Pair<C8, U32>(78, 122));    /* ASCII 78: N */
			freqTable.insert(Pair<C8, U32>(79, 36));     /* ASCII 79: O */
			freqTable.insert(Pair<C8, U32>(80, 185));    /* ASCII 80: P */
			freqTable.insert(Pair<C8, U32>(81, 1));      /* ASCII 81: Q */
			freqTable.insert(Pair<C8, U32>(82, 149));    /* ASCII 82: R */
			freqTable.insert(Pair<C8, U32>(83, 309));    /* ASCII 83: S */
			freqTable.insert(Pair<C8, U32>(84, 335));    /* ASCII 84: T */
			freqTable.insert(Pair<C8, U32>(85, 12));     /* ASCII 85: U */
			freqTable.insert(Pair<C8, U32>(86, 11));     /* ASCII 86: V */
			freqTable.insert(Pair<C8, U32>(87, 14));     /* ASCII 87: W */
			freqTable.insert(Pair<C8, U32>(88, 54));     /* ASCII 88: X */
			freqTable.insert(Pair<C8, U32>(89, 151));    /* ASCII 89: Y */
			freqTable.insert(Pair<C8, U32>(90, 0));      /* ASCII 90: Z */
			freqTable.insert(Pair<C8, U32>(91, 0));      /* ASCII 91: [ */
			freqTable.insert(Pair<C8, U32>(92, 2));      /* ASCII 92: \ */
			freqTable.insert(Pair<C8, U32>(93, 0));      /* ASCII 93: ] */
			freqTable.insert(Pair<C8, U32>(94, 0));      /* ASCII 94: ^ */
			freqTable.insert(Pair<C8, U32>(95, 211));    /* ASCII 95: _ */
			freqTable.insert(Pair<C8, U32>(96, 0));      /* ASCII 96: ` */
			freqTable.insert(Pair<C8, U32>(97, 2090));   /* ASCII 97: a */
			freqTable.insert(Pair<C8, U32>(98, 344));    /* ASCII 98: b */
			freqTable.insert(Pair<C8, U32>(99, 736));    /* ASCII 99: c */
			freqTable.insert(Pair<C8, U32>(100, 993));   /* ASCII 100: d */
			freqTable.insert(Pair<C8, U32>(101, 2872));  /* ASCII 101: e */
			freqTable.insert(Pair<C8, U32>(102, 701));   /* ASCII 102: f */
			freqTable.insert(Pair<C8, U32>(103, 605));   /* ASCII 103: g */
			freqTable.insert(Pair<C8, U32>(104, 646));   /* ASCII 104: h */
			freqTable.insert(Pair<C8, U32>(105, 1552));  /* ASCII 105: i */
			freqTable.insert(Pair<C8, U32>(106, 328));   /* ASCII 106: j */
			freqTable.insert(Pair<C8, U32>(107, 305));   /* ASCII 107: k */
			freqTable.insert(Pair<C8, U32>(108, 1240));  /* ASCII 108: l */
			freqTable.insert(Pair<C8, U32>(109, 735));   /* ASCII 109: m */
			freqTable.insert(Pair<C8, U32>(110, 1533));  /* ASCII 110: n */
			freqTable.insert(Pair<C8, U32>(111, 1713));  /* ASCII 111: o */
			freqTable.insert(Pair<C8, U32>(112, 562));   /* ASCII 112: p */
			freqTable.insert(Pair<C8, U32>(113, 3));     /* ASCII 113: q */
			freqTable.insert(Pair<C8, U32>(114, 1775));  /* ASCII 114: r */
			freqTable.insert(Pair<C8, U32>(115, 1149));  /* ASCII 115: s */
			freqTable.insert(Pair<C8, U32>(116, 1469));  /* ASCII 116: t */
			freqTable.insert(Pair<C8, U32>(117, 979));   /* ASCII 117: u */
			freqTable.insert(Pair<C8, U32>(118, 407));   /* ASCII 118: v */
			freqTable.insert(Pair<C8, U32>(119, 553));   /* ASCII 119: w */
			freqTable.insert(Pair<C8, U32>(120, 59));    /* ASCII 120: x */
			freqTable.insert(Pair<C8, U32>(121, 279));   /* ASCII 121: y */
			freqTable.insert(Pair<C8, U32>(122, 31));    /* ASCII 122: z */
			freqTable.insert(Pair<C8, U32>(123, 0));     /* ASCII 123: { */
			freqTable.insert(Pair<C8, U32>(124, 0));     /* ASCII 124: | */
			freqTable.insert(Pair<C8, U32>(125, 0));     /* ASCII 125: } */
			freqTable.insert(Pair<C8, U32>(126, 68));    /* ASCII 126: ~ */
			freqTable.insert(Pair<C8, U32>(127, 0));     /* ASCII 127: DEL */
			//The Extended ASCII Table is also included in our Huffman Tables, However
			// by the standards of character frequency, these chars don't appear. Therefore
			// we set them all to 0 with a simple for loop.
			for(S32 i = 128; i < 256; i++) {
				freqTable.insert(Pair<C8, U32>(i, 0));
			}
			//Now, we construct the tables using these frequency values
			S32 Index, IndexL = -1, IndexR = -1, NodeCombIndex, DeleteIndex, NodeCt = 256;
			U32 v1 = 0xfffffffe, v2 = 0xffffffff, code = 0;
			//
			huffNodes.reserve(256);
			huffLeaves.setSize(256);
			huffLeaves.inc();
			//Construct the DynArrays & Tree
			HuffTree *tree = new HuffTree[256];
			for(Index = 0; Index < 256; Index++) {
				HuffLeaf &leaf = huffLeaves[Index];
				leaf.value = freqTable.at(Index)->second + 1;
				leaf.letter = (U8)Index;

				memset(&leaf.huffCode, 0, sizeof(leaf.huffCode));
				leaf.bitCount = 0;
				//Set the leaf for this tree index
				tree[Index].set(&leaf);
			}
			//Assemble the tree and set up the node indicies
			while(NodeCt != 1) {
				for(Index = 0; Index < NodeCt; Index++) {
					if(tree[Index].getValue() < v1) {
						v2 = v1;
						IndexR = IndexL;
						v1 = tree[Index].getValue();
						IndexL = Index;
					}
					else if(tree[Index].getValue() < v2) {
						v2 = tree[Index].getValue();
						IndexR = Index;
					}
				}
				//Check to ensure that the nodes are not sharing the same index, throw HUFFTABLEINDEXFAILURE if they are.
				if(!(IndexL != -1 && IndexR != -1 && IndexL != IndexR)) {
					//ToDo: Throw an assert error here
				}
				//Next, we need to construct the nodes for the Tree and assign the correct indicies to these nodes
				huffNodes.inc();
				HuffNode &refNode = huffNodes.last();
				refNode.value = tree[IndexL].getValue() + tree[IndexR].getValue();
				refNode.leafIndexLeft = determineTreeIndex(tree[IndexL]);
				refNode.leafIndexRight = determineTreeIndex(tree[IndexR]);
				//Merge & Delete?
				NodeCombIndex = IndexL > IndexR ? IndexR : IndexL;
				DeleteIndex = IndexL > IndexR ? IndexL : IndexR;
				tree[NodeCombIndex].set(&refNode);
				if(IndexR != (NodeCt - 1)) {
					//Delete the contents of the current node by copying the contents of the node we need to be on to it.
					tree[DeleteIndex] = tree[NodeCt - 1];
				}
				NodeCt--;
			}
			//Perform a few more tests to ensure we got the correct results
			if(NodeCt != 1) {
				//ToDo: Throw an assert error here
			}
			if(tree[0].node == NULL && tree[0].leaf != NULL) {
				//ToDo: Throw an assert error here
			}
			//The last thing we need to do is to run the newly constructed table through a BitStream to generate the codes, do this now.
			huffNodes[0] = *(tree[0].node);
			//Free up the memory used by the construction of the tree
			delete[] tree;

			Streams::BitStream ref(&code, 4);
			generateCodes(0, 0, ref);
		}

		S16 HuffCoder::determineTreeIndex(HuffTree &tree) {
			if(tree.leaf != NULL) {
				if(tree.node != NULL) {
					//We've got a node problem folks.
					//ToDo: Throw an assert error here
				}
				return (S16)(-((tree.leaf - huffLeaves.addr()) + 1));
			}
			else {
				if(tree.node == NULL) {
					//This only happens if there is a node and a leaf on the same index somewhere else, throw the same exception.
					//ToDo: Throw an assert error here
				}
				return (S16)(tree.node - huffNodes.addr());
			}
		}

		void HuffCoder::generateCodes(S32 treeIndex, S32 tableDepth, Streams::BitStream &ref) {
			if(treeIndex < 0) {
				//Leaf, grab the code from the leaf then back out to the root and proceed.
				HuffLeaf &refLeaf = huffLeaves[-(treeIndex + 1)];
				memcpy(&refLeaf.huffCode, ref.data, sizeof(refLeaf.huffCode));
				refLeaf.bitCount = tableDepth;
			}
			else {
				S64 cPos = ref.getCurrentPos();
				HuffNode &refNode = huffNodes[treeIndex];
				//Write the sequence to the Stream, then push to the two leaves (if they exist)
				// Write the left node
				ref.writeFlag(false);
				generateCodes(refNode.leafIndexLeft, tableDepth+1, ref);
				//Reset the bitstream position
				ref.setCurrentPos(cPos);
				// Write the right node
				ref.writeFlag(true);
				generateCodes(refNode.leafIndexRight, tableDepth+1, ref);
				//Reset the bitstream position
				ref.setCurrentPos(cPos);
			}
		}

	};

};