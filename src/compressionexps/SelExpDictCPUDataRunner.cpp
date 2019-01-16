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
 /**
 */
#include "SelExpDictCPUDataRunner.h"

SelExpDictCPUDataRunner::SelExpDictCPUDataRunner() {
}


SelExpDictCPUDataRunner::~SelExpDictCPUDataRunner() {
}

bool SelExpDictCPUDataRunner::run(Globals* g, const vector<string>& args) {
  if(args.size()<2){
    cout << "at least two arguments! " <<endl;
    return false;
  }
  _file = args[0].c_str();
  int testnum = atoi(args[1].c_str());

  int i=0;
  for (; i< 100; i++)
    if (strncmp(_file+i, "D1.data",7) == 0) {
      break;
    }

  char* temp = new char[30];
  sprintf(temp, "test1Int%s", (_file+i+8));
  char* temp2 = new char[30];
  sprintf(temp2, "test1DictC%sEntries", (_file+i+8));
  char* temp3 = new char[30];
  sprintf(temp3, "test1Type2%s", (_file+i+8));
  char* temp4 = new char[30];
  sprintf(temp4, "test1RLE%s", (_file+i+8));
  char* temp5 = new char[30];
  sprintf(temp5, "test1first%s", (_file+i+8));
  char* temp7 = new char[30];
  sprintf(temp7, "test1DictC%sTable", (_file+i+8));

  cout << "SelExpDictCPUDataRunner: Running file " << _file << endl;
    	bool success=true;
  
  StopWatch stopWatch;
  stopWatch.start();


  ROSAM* am4 = new ROSAM(temp5, 2);
    RLEDataSource* lreturn = new RLEDataSource(am4, true);


    /*ROSAM* am3 = new ROSAM(temp, 1);
      IntDataSource* suppvar=new IntDataSource(am3, false, true);*/

  /*ROSAM* am3 = new ROSAM(temp4, 1);
    RLEDataSource* suppvar=new RLEDataSource(am3, false);*/

    /*ROSAM* am3 = new ROSAM( "selexpquantvarVals", 1);
      Type2DataSource* suppvar=new Type2DataSource(am3, false);*/

    ROSAM* am3 = new ROSAM(temp2, 1);
    ROSAM* am5 = new ROSAM(temp7, 1);
    DictCPUDataSource* suppvar=new DictCPUDataSource(am5, am3, false);
    //suppvar->setDecodingType(0);
    //dict = generateDictTable(am5);


  Predicate* pred2 = new Predicate(Predicate::OP_EQUAL);
  lreturn->setPredicate(pred2);
  lreturn->changeRHSBinding(65);
  suppvar->setPositionFilter(lreturn, 0);

    /*  Predicate* pred2 = new Predicate(Predicate::OP_EQUAL);
  suppvar->setPredicate(pred2);
  suppvar->changeRHSBinding(dict);
  lreturn->setPositionFilter(suppvar, 0);*/

  //Dict2Int* di = new Dict2Int(suppvar, 0, am5);


  HashCount* hashAgg = new HashCount((Operator*) suppvar, 0, (Operator*) suppvar, 0);
  hashAgg->setHashFunction(new IdentityHashFunction(100001));
  hashAgg->setHashTableSize(100001);
  Operator* srcs[1]={hashAgg};
  //Operator* srcs[2]={suppvar2,suppkey2};
  int numCols[1]={2};
  //int numCols[2]={1,1};
  
  char* temp6 = new char[30];
  sprintf(temp6, "test1DictC");
  char* temp8 = new char[30];
  sprintf(temp8, "%s.out", temp6);
  BlockPrinter* bPrint=new BlockPrinter(srcs, numCols, 1, temp8);
  bPrint->printColumns();
  
  
  sprintf(temp8, "test%dDictC.dat", testnum);
  ofstream flStream;
  flStream.open(temp8, ios::out | ios::app);
  flStream.seekp(ios::end);
  flStream << "xval: " << (_file+i+8) << endl;
  stopWatch.stopToFile(temp8);
  flStream.close();
  
  cout << "Query took: " << stopWatch.stop() << " ms" <<  endl;
  
  return success;	
}
int SelExpDictCPUDataRunner::generateDictTable(AM* dictTableAM) {
  IntDataSource* ds = new IntDataSource(dictTableAM, false, true);
  ds->setSingles(true);
  //int reallastpos = ds->getLastPosition();
  BasicBlock* block=(BasicBlock*) ds->getNextValBlock(0);

  //dict = new unsigned int[reallastpos];

  unsigned int curpos = 0;
  while (block!=NULL) {
    ValPos* vp = block->getStartPair();
    //assume int type for now ... fix later
    assert(vp->type == ValPos::INTTYPE);
      unsigned int value=*(int*)vp->value;
      curpos = (block->getStartPair()->position)-1;
        //cout << "pos is: " << curpos << endl;
      if (value == 1)
	return curpos;
      //dict[curpos]=value;
      //Log::writeToLog("DictDataSource", 1, "initTable(): got Entry", curpos);					
      //Log::writeToLog("DictDataSource", 1, "initTable(): for value", value);
      
      block=(BasicBlock*) ds->getNextValBlock(0);
      //to fix strange bug where dictionary table page gets read in twice from the ROSAM (should probably fix for real at some point)
      //if (block->getStartPair()->position == 1)
      //block=NULL;
    //curpos++;
  }
  throw new UnexpectedException("should not get here");
}
