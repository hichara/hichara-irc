/**
 * Project Untitled
 */


#ifndef _KT_STATEMENT_H
#define _KT_STATEMENT_H
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "SemanticVisitor.h"
using namespace std;

class KT_Statement {
public:
	KT_Statement();
  virtual ~KT_Statement();
	virtual void toString(){};
	virtual void accept(SemanticVisitor* visitor){};
};

#endif //_KT_STATEMENT_H
