/**
 * Project kawa
 */


#include "KT_FactFinal.h"
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

/**
 * KT_FactFinal implementation
 */
 
 KT_FactFinal::KT_FactFinal() {}



Value* KT_FactFinal::acceptIRCompiler(IRCompiler *compiler) {
	return compiler->compileFactFinal(this);
}