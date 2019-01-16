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
#ifndef _EARITHMETIC_H_
#define _EARITHMETIC_H_

#include <string>

#include "../constants.h"
#include "../Expression.h"

using namespace std;

// Variable
class EArithmetic : public Expression
{
	protected:
        Expression*	m_lpLeft;
        Expression*	m_lpRight;
        string		m_sOp;       


	 protected:
		// PObject's constructor is protected because they should not be new directly.
		// A node can be new by using static "create" function
		// This is for the purpose of memory management
        EArithmetic();
		EArithmetic(Expression* lpLeft, Expression* lpRight, string op);
		
	public:
        virtual ~EArithmetic();

		int getType( ListProjections* lp );
		void	setLeft(Expression* lpLeft);
		void	setRight(Expression* lpRight);
		void	set(Expression* lpLeft, Expression* lpRight, string op);
		Expression*	getLeft();
		Expression*	getRight();

        virtual string	toString();
		
		// Translate the expression into a plan node
		virtual Node* translate();	 
	
		// Translate the expression into a plan node
		virtual Node* translate(bool bNewSelectNode, Node* lpAggNode, Node* lpGroupNode, int* lpCopyIndex);

	//---------------------------------------------------------------
	// Memory management functions
		
	public:
		// New a PObject and put it in the m_lpList
		static EArithmetic* create();
		
		// New a PObject and put it in the m_lpList
		static EArithmetic* create(Expression* lpLeft, Expression* lpRight, string op);
};

#endif //  _EARITHMETIC_H_
