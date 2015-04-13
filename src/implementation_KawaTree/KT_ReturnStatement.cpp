/**
 * Project Untitled
 */


#include "KT_ReturnStatement.h"

/**
 * KT_ReturnStatement implementation
 */

KT_ReturnStatement::KT_ReturnStatement(){}

/**
 * @return bool
 */
bool KT_ReturnStatement::isVoidReturn() {
    return VoidReturn;
}

/**
 * @return KT_Expression *
 */
KT_Expression * KT_ReturnStatement::getReturnExpression() {
    return returnExppression;
}

/**
 * @param bool
 */
void KT_ReturnStatement::setIsVoidReturn( bool var) {
	VoidReturn=var;
}

/**
 * @param Kt_Expression *
 */
void KT_ReturnStatement::setReturnExpression(Kt_Expression * var) {
	returnExppression=var;
}