/* Copyright (c) 2005, Regents of Massachusetts Institute of Technology, 
 * Brandeis University, Brown University, and University of Massachusetts 
 * Boston. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright 
 *     notice, this list of conditions and the following disclaimer in the 
 *     documentation and/or other materials provided with the distribution.
 *   - Neither the name of Massachusetts Institute of Technology, 
 *     Brandeis University, Brown University, or University of 
 *     Massachusetts Boston nor the names of its contributors may be used 
 *     to endorse or promote products derived from this software without 
 *     specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
// Encodes String Pages

#ifndef _STRINGENCODER_H_
#define _STRINGENCODER_H_

#include "Encoder.h"
#include "../Util/StringWriter.h"
#include "../SBasicBlock.h"
//#include "../../Writers/SBasicBlockWriter.h"
// StringEncoder encodes a page of strings
// The first int indicates the number of strings encoded
// The second int indicates the startPos of this page
// The third int indicates the string size of strings in this page
// Lastly, the rest of the page is a sequence of strings
class StringEncoder : public Encoder
{
public:
	StringEncoder(Operator* dataSrc_, int colIndex_, int stringSize, int bfrSizeInBits_);
	virtual ~StringEncoder();
	virtual byte* getPage();
	virtual void resetPair();
	//virtual bool writeVal(char* val_, unsigned int pos_);
protected:
	int totalNum;
	int totalLength;
	StringWriter* writer;
	//SBasicBlockWriter* blockWriter;
	byte* buffer;
	int* lengthPtr;
	int* startPosPtr;
	int* ssizePtr;
	SBlock* currBlock;
	bool init;
	SPair* currPair;
};

#endif //_STRINGENCODER_H_
