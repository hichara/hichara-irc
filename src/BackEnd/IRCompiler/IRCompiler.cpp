
#include "IRCompiler.h"
#include "KT_includes.h"


void IRCompiler::compile(KT_Program *program) {
  
  // A completer
  std::string progName = program->getName();

  if(progName == "") {
    progName = "program";
  }

  IRmodule = new Module(progName, IRcontext);

  debug("program");

  std::vector<KT_Package*> pckgs = program->getPackages();

  int size = pckgs.size();

  for(int i = 0; i < size; i++) {
  	compile(pckgs[i]);
  }

  std::stringstream pName;

  pName << progName << ".ll";

  int fd = open(pName.str().c_str(), O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXG);

  raw_fd_ostream my_out(fd, true);

  getModule()->print(my_out, NULL);
}

void IRCompiler::compile(KT_Package *package) {
  debug("package");


  std::vector<KT_Class*> classes = package->getClasses(); 
  std::vector<KT_Interface*> interfaces = package->getInterfaces();

  int size_i = interfaces.size();
  int size_c = classes.size();  

  debug("debut compilation des interfaces");
  for(int i = 0; i < size_i; i++) {
  	compile(interfaces[i]);
  }

  debug("fin compilation des interfaces");


  debug("debut compilation des classes");

  for(int i = 0; i < size_c; i++) {
  	compile(classes[i]);
  }

  debug("fin compilation des classes");

  debug("debut creation table adHoc interfaces");

  for(int i = 0; i < size_i; i++) {
  	createAdHocTable(interfaces[i]);
  }

  debug("fin creation table adHoc interfaces");


  debug("debut creation table adHoc classes");

  for(int i = 0; i < size_c; i++) {
  	createAdHocTable(classes[i]);
  }

  debug("fin creation table adHoc classes");
}


void IRCompiler::compile(KT_Class *classe) {
  debug("class");

	std::vector<KT_SimpleMethod*> s_mehtodes = classe->getSimpleMethods();

	std::vector<KT_Constructor*> c_constructors = classe->getConstructors();

	int size_m = s_mehtodes.size();
	int size_c = c_constructors.size();

	for(int i = 0; i < size_m; i++) {
		compile(s_mehtodes[i]->getPrototype());
		compile(s_mehtodes[i]);
	}

	for(int i = 0; i < size_c; i++) {
		compile(c_constructors[i]);
	}
}

void IRCompiler::compile(KT_Interface *interface) {
  debug("interface");

  	createType(interface);

	std::vector<KT_Prototype *> prototypes = interface->getPrototypes();

	for(int i = 0; i < prototypes.size(); i++) {
		compile(prototypes[i]);
	}
}



Function* IRCompiler::compile(KT_Prototype *p) { 
	std::stringstream err, err2;
  debug("prototype");

	std::string className = p->getParentName();

	err << "parentName : " << className;

	KT_Modifier* modifier = p->getModifier();

	debug(err.str());

	std::string name = *(p->getName());

  debug(name);

	std::vector<KT_Param* > params = p->getParams();

  debug("params recuperes");

	std::string r_type  =  fqnType(p->getReturnType()->getTypeName()) ;

  debug("type de retour recuperes");

	bool istatic = modifier->isStatic();

	err2 << "rtype : " << r_type << " et " << istatic;

	//parametres
  	std::vector<std::string> params_names;
  	std::vector<std::string> params_types;

  //	debug("debut boucle");

  	for(int i = 0; i < params.size(); i++) {
  		params_names.push_back(*(params[i]->getName()));
  		params_types.push_back(fqnType(params[i]->getParamType()->getTypeName()));

  //		debug(*(params[i]->getName()));
//  		debug(fqnType(params[i]->getParamType()->getTypeName()));
  	}
    
    if(name == "main") {
      return FunctionGenerator::getOrCreateMainFunction(getModule(), "argc", "argv");
    }

  	debug("fin boucle");

  	debug("avant declaration");

  	Function *f =  FunctionGenerator::getOrCreateFunction(getModule(), istatic,
									className,
									name,
									r_type, 
									params_types,
									params_names);
  	debug("apres declaration");


 debug("prototype fin");

  return f;
}

Function* IRCompiler::compile(KT_SimpleMethod *methode) {
  	  debug("methode");

  	// A completer
 	KT_Prototype* proto = methode->getPrototype();
 	std::vector<KT_Param*> params = proto->getParams();
 	std::vector<std::string> param_names;
 	bool addThis = !proto->getModifier()->isStatic();

 	for(int i = 0; i < params.size(); i++){
 		param_names.push_back(*(params[i]->getName()));
 	}

  debug("Recuperation du prototype");

 	Function *f = compile(methode->getPrototype());

  f->dump();
  std::cerr << "\n";

  debug("Prototype recupere");

  currentFunction = f;
 	currentBloc = FunctionGenerator::initFunction(f, param_names, addThis);

  debug("Compilation bloc instructions");

  compileBlock(methode->getBlock());

  BasicInstructionGenerator::endFunction(f, currentBloc);

  debug("fin compilation methode");

  return f;
}

Function* IRCompiler::compile(KT_Constructor * constructor) {
	  debug("constructor");

  	std::string name = *(constructor->getName());
  	std::vector<KT_Param*> params = constructor->getParams();

  	std::vector<std::string> params_names;
  	std::vector<std::string> params_types;

  	for(int i = 0; i < params.size(); i++) {
  		params_names.push_back(*(params[i]->getName()));
  		params_types.push_back(fqnType(params[i]->getParamType()->getTypeName()));
  	}

  	Function *f =  FunctionGenerator::getOrCreateConstructor(getModule(),
								name,
								params_types,									
								params_names);

    currentBloc = FunctionGenerator::initFunction(f, params_names, true);
    currentFunction = f;

  	std::vector<KT_Statement*> stmnts;
  	stmnts = constructor->getBlock()->getStatements();

  	for(int i = 0; i < stmnts.size(); i++) {
      compileStatement(stmnts[i]);
  	}

    BasicInstructionGenerator::endFunction(f, currentBloc);

    debug("fin compilation constructor");

  	return FunctionGenerator::getConstructor(getModule(),
  		name, params_types, params_names);
}
