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
#include "EAggMin.h"

EAggMin::EAggMin(): EAgg()
{
	m_sOp = "min";
}


EAggMin::EAggMin(EColumn* lpRight) : EAgg(lpRight, "min")
{
}


EAggMin::~EAggMin()
{
}

// Translate the expression into a plan node
Node* EAggMin::translate(bool bNewSelectNode, Node* lpNode, Node* lpGroupNode, int* lpCopyIndex)
{
	Node* lpAgg = NULL;
	lpAgg = getAggNode(bNewSelectNode, lpNode, lpCopyIndex);

	if (lpGroupNode == NULL)
	{
		// without Group by
		m_lpNode = UAggMinNode::create(lpAgg, 0);
	}
	else
	{
		// with group by
		m_lpNode = BAggMinNode::create(lpAgg, 0, lpGroupNode, 0);
	}	 


	return m_lpNode;
}


//---------------------------------------------------------------
// Memory management functions

// New a node and put it in the m_lpList
EAggMin* EAggMin::create()
{
	Log::writeToLog("EAggMin", 0, "Create");
		
	EAggMin* lpPObject = new EAggMin();
	pushBack(lpPObject);
	return lpPObject;
}


// New a node and put it in the m_lpList
EAggMin* EAggMin::create(EColumn* lpRight)
{
	Log::writeToLog("EAggMin", 0, "Create with argeuments: EColumn* lpRight");
		
	EAggMin* lpPObject = new EAggMin(lpRight);
	pushBack(lpPObject);
	return lpPObject;
}
