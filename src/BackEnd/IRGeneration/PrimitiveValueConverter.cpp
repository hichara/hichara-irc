#include "PrimitiveCreator.h"
#include "PrimitiveValueConverter.h"

/// Fonctions static public

 Value* PrimitiveValueConverter::convertFromTo(Type *t1, Type *t2, Value *v, BasicBlock *b) {
 	if(t1 == t2) {
 		return v;
 	}

 	LLVMContext &Context = b->getContext();

 	if(t1 == Type::getInt32Ty(Context)) {
 		if(t2 == Type::getFloatTy(Context))
 			return convertFromIntToFloat(v, b);

 		if(t2 == Type::getDoubleTy(Context))
 			return convertFromIntToDouble(v, b);

 		return NULL;
 	}

 	if(t1 == Type::getFloatTy(Context)) {
 		if(t2 == Type::getInt32Ty(Context))
 			return convertFromFloatToInt(v, b);

 		if(t2 == Type::getFloatTy(Context))
 			return convertFromFloatToDouble(v, b);

 		return NULL;
 	}

 	if(t1 == Type::getDoubleTy(Context)) {
 		if(t2 == Type::getInt32Ty(Context))
 			return convertFromDoubleToInt(v, b);

 		if(t2 == Type::getFloatTy(Context))
 			return convertFromDoubleToFloat(v, b);

 		return NULL;
 	}

 	return NULL;
 }

///// Fonctions private

 Value* PrimitiveValueConverter::convertFromIntToDouble(Value *v, BasicBlock *bb) {
 	LLVMContext &Context = bb->getContext();
 	IRBuilder<> b(Context);
 	b.SetInsertPoint(bb);

 	return b.CreateSIToFP(v, Type::getDoubleTy(Context));
 }

 Value* PrimitiveValueConverter::convertFromIntToFloat(Value *v, BasicBlock *bb) {
 	LLVMContext &Context = bb->getContext();
 	IRBuilder<> b(Context);
 	b.SetInsertPoint(bb);

 	return b.CreateSIToFP(v, Type::getInt32Ty(Context));
 }

 Value* PrimitiveValueConverter::convertFromFloatToInt(Value *v, BasicBlock *bb) {
 	LLVMContext &Context = bb->getContext();
 	IRBuilder<> b(Context);
 	b.SetInsertPoint(bb);

 	return b.CreateFPToSI(v, Type::getDoubleTy(Context));
 }

 Value* PrimitiveValueConverter::convertFromFloatToDouble(Value *v, BasicBlock *bb) {
 	LLVMContext &Context = bb->getContext();
 	IRBuilder<> b(Context);
 	b.SetInsertPoint(bb);

 	return b.CreateFPExt(v, Type::getDoubleTy(Context));
 }

 Value* PrimitiveValueConverter::convertFromDoubleToInt(Value *v, BasicBlock *bb) {
 	LLVMContext &Context = bb->getContext();
 	IRBuilder<> b(Context);
 	b.SetInsertPoint(bb);

 	return b.CreateSIToFP(v, Type::getInt32Ty(Context));
 }

 Value* PrimitiveValueConverter::convertFromDoubleToFloat(Value *v, BasicBlock *bb) {
 	LLVMContext &Context = bb->getContext();
 	IRBuilder<> b(Context);
 	b.SetInsertPoint(bb);

 	return b.CreateFPTrunc(v, Type::getDoubleTy(Context)); 	
 }


Value* PrimitiveValueConverter::convertToStr(Value *o1, BasicBlock *bb) {
	LLVMContext &context = bb->getContext();
	IRBuilder<> b(context);
	b.SetInsertPoint(bb);

	Type *type = o1->getType();

	if(type == Type::getInt32Ty(context))
		return PrimitiveValueConverter::convertIntToStr(o1, bb);

	if(type == Type::getInt8Ty(context))
		return PrimitiveValueConverter::convertCharToStr(o1, bb);

	if(type == Type::getInt8Ty(context)->getPointerTo())
		return o1;

	if(type == Type::getDoubleTy(context))
		return PrimitiveValueConverter::convertDoubleToStr(o1, bb);

	return PrimitiveCreator::create("[unknown]", context);
}


