/**
* Galactic 2D - Delegate Types Header Generator
* (C) 2014 Phantom Games Development - All Rights Reserved
* Main.cpp
*
* This C++ Source file is responsible for generating the file for G2D/G3D: EngineCore/Delegates/delegateTypes.h. There are multiple options
*  and settings for this project. You are responsible for updating both this file & the delegate system located within the engine itself 
*  during operation.
*
* Side Note: This script has been tested on Windows & Linux platforms with success.
**/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//One Tab
#define T1 "\t"
//Two Tabs
#define T2 "\t\t"
//Three Tabs
#define T3 "\t\t\t"
//Four Tabs
#define T4 "\t\t\t\t"
//Five Tabs
#define T5 "\t\t\t\t\t"
//Six Tabs
#define T6 "\t\t\t\t\t\t"
//Seven Tabs
#define T7 "\t\t\t\t\t\t\t"
//Eight Tabs
#define T8 "\t\t\t\t\t\t\t\t"

//One Newline
#define NL "\n"
//Two Newlines
#define NL2 "\n\n"

//Forward Decs
typedef const string cstr;

/* You are responsible for updating these values */
/* This first category defines global settings for the delegate system */
cstr copywriteLine = "(C) 2014 Phantom Games Development - All Rights Reserved";           //Self Explanitory
cstr galacticEngineLine = "Galactic 2D";                                                   //Also Self Explanitory ;)
const int MaxParameters = 12;                                                              //The maximum number of standard C++ type params that are accepted
const int MaxArguments = 8;                                                                //The maximum number of coded class types that are accepted
cstr num2Text[MaxParameters + 1] = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", //Convert numerical values to string representations
									"Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve" }; //Convert numerical values to string representations
/* This second category defines engine settings, IE: you'll update this based on what's in the engine */
cstr EngineDelegateReturnType = "DelegateReturnType";                                      //The engine's template delegate return type, see engine files for this.
cstr EngineDelegateReturn = "ReturnType";                                                  //If the return's value flag is on, append this to the func name
cstr EngineDelegateType_ForOther = "DelegateReturnTypeAltCast";                            //This declares the type for the alternate (Multi->Single, Single->Multi) defs
cstr EngineDelegateArg = "Arg";                                                            //This is the prefix for a non-standard data type
cstr EngineDelegateParam = "Param";                                                        //This is the prefix for a standard data type
cstr EngineKeyword_Inline = "inline";                                                      //Engine keyword for declaring something to be inline...
cstr EngineKeyword_StaticInline = "static inline";                                         //Engine keyword for declaring something to be both static and inline...
//Macros, Check the C++ files for the current list.
cstr EngineMacro_HasArgs = "DELEGATE_HAS_ARGS";									           //Macro define to flag if this section has arguments
cstr EngineMacro_HasParams = "DELEGATE_HAS_PARAMS";                                        //Macro define to flag if this section has parameters
cstr EngineMacro_FSuffix = "DELEGATE_FUNCTION_SUFFIX";                                     //Macro for the string defining the function ending
cstr EngineMacro_ArgSuffix = "DELEGATE_FUNCTION_ARGUMENTS_SUFFIX";                         //Macro for defining the function suffix for arguments
cstr EngineMacro_TypeTemplateDec = "DELEGATE_FUNCTION_TYPENAME_TEMPLATE_DEC";              //Macro for typename declaration of function template
cstr EngineMacro_AltTemplateDec = "DELEGATE_FUNCTION_ALTERNATE_TEMPLATE_DEC";              //Macro for type of alternate function template
cstr EngineMacro_TemplateArguments = "DELEGATE_FUNCTION_TEMPLATE_ARGUMENTS";               //Macro for the argument list for function templates
cstr EngineMacro_ParamList = "DELEGATE_PARAM_LIST";                                        //Macro for the parameter list
cstr EngineMacro_ParamDef = "DELEGATE_PARAMETERS";                                         //Macro for the definition of parameters
cstr EngineMacro_ParamAssign = "DELEGATE_PARAM_ASSIGN";                                    //Macro for passing parameters through an assignment func.
cstr EngineMacro_ParamPassToFunc = "DELEGATE_PARAMETERS_PASSTOFUNC";                       //Macro used to break down to parameters.x, parameters.y, etc.
cstr EngineMacro_ParamInitializer = "DELEGATE_PARAM_INITIALIZER";                          //Macro used to definine the initializer list for the construtor.
cstr EngineMacro_ArgsTypeTemplateDec = "DELEGATE_FUNCTION_ARGUMENT_TEMPLATE_TYPENAME";     //Macro for typename declaration of function template
cstr EngineMacro_ArgsAltTemplateDec = "DELEGATE_FUNCTION_ARGUMENT_ALTERNATE_TEMPLATE_DEC"; //Macro for type of alternate function template
cstr EngineMacro_ArgsTemplateArguments = "DELEGATE_FUNCTION_ARGUMENT_TEMPLATE_ARGUMENTS";  //Macro for the argument list for function templates
cstr EngineMacro_ArgumentList = "DELEGATE_ARGS_LIST";                                      //Macro for the argument list
cstr EngineMacro_ArgumentDef = "DELEGATE_ARGUMENTS";                                       //Macro for the definition of arguments
cstr EngineMacro_ArgumentAssign = "DELEGATE_ARGS_ASSIGN";                                  //Macro for passing arguments through an assignment func.
cstr EngineMacro_ArgumentPassToFunc = "DELEGATE_ARGS_PASSTOFUNC";                          //Macro used to break down to argument.x, argument.y, etc.
cstr EngineMacro_ArgumentInitializer = "DELEGATE_ARGS_INITIALIZER";                        //Macro used to definine the initializer list for the construtor.
cstr EngineMacro_ConstFunc = "DELEGATE_IS_CONST";                                          //Macro used to flag if a function is const or not
cstr EngineMacro_VoidRetType = "DELEGATE_FUNCTION_IS_VOID";                                //Macro used to flag is the function type is void
cstr EngineMacro_DeclareSCDelegate = "GALACTIC_INIT_SC_DELEGATE";                          //Macro of the prefix of the command to init a single-cast delegate
cstr EngineMacro_DeclareMCDelegate = "GALACTIC_INIT_MC_DELEGATE";                          //Macro of the prefix of the command to init a multi-cast delegate
cstr EngineMacro_DeclareSCName = "DELEGATE_DECLARE";                                       //Function name to declare a single-cast delegate
cstr EngineMacro_DeclareMCName = "DELEGATE_DECLARE_MULTICAST";                             //Function name to declare a multi-cast delegate
/* Definitions for the inl file */
cstr EngineMacro_CombineAB = "COMBINEAB";                                                  //Macro to combine two instances together
cstr EngineMacro_CombineABC = "COMBINEABC";                                                //Macro to combine three instances together
cstr EngineMacro_TagConst = "_constant";                                                   //Macro tag result for Constant
cstr EngineMacro_SuffixConstant = "FUNCTION_SUFFIX_CONSTANT";                              //Engine macro for constant suffix
cstr EngineMacro_DelegateInstanceClass = "DELEGATE_INSTANCE_CLASS";                        //Macro to define for instancing class
cstr EngineMacro_DelegateSRPClass = "DELEGATE_STRONGPOINTER_BASECLASS";                    //Macro to define the strong ptr class
cstr EngineMacro_DelegateMemMthdClass = "DELEGATE_CPPMEMBER_BASECLASS";                    //Macro to define the member method class
cstr EngineMacro_DelegateGloMthdClass = "DELEGATE_CPPGLOBAL_BASECLASS";                    //Macro to define the global method class
cstr EngineMacro_DelegateSRPDef = "DELEGATE_STRONGPOINTER_CLASS";                          //Macro definition for creation of strong ptr class
cstr EngineMacro_DelegateMemMthdDef = "DELEGATE_CPP_CLASS_METHOD_CLASS";                   //Macro definition for creation of class method class
cstr EngineMacro_DelegateGloMthdDef = "DELEGATE_CPP_GLOBAL_METHOD_CLASS";                  //Macro definition for creation of global method class
cstr EngineMacro_SCBaseClass = "DELEGATE_BASE_SINGLECAST_CLASS";                           //Macro definition for determining the base sc class
cstr EngineMacro_MCBaseClass = "DELEGATE_BASE_MULTICAST_CLASS";                            //Macro definition for determining the base mc class
cstr EngineMacro_MCClass = "DELEGATE_MULTICAST_CLASS";                                     //Macro definition for determining the mc class
cstr EngineMacro_TArgDecl = "DELEGATE_TEMPLATE_ARGS_DECLARATION";                          //Macro definition for delegate argument template defs.
cstr EngineMacro_TArgList = "DELEGATE_TEMPLATE_ARGS_LIST";                                 //Macro definition for delegate argument list
cstr EngineMacro_TArgPass = "DELEGATE_TEMPLATE_ARGS_PASS";                                 //Macro definition for delegate argument passing.
cstr EngineMacro_TArgPTF = "DELEGATE_TEMPLATE_ARGS_PASSTOFUNC";                            //Macro definition for delegate argument pass to function.
cstr EngineClass_baseDelegate = "DelegateInstance_";                                       //The base delegate instance class
cstr EngineClass_strPtrDelegate = "StrongPointerDelegateInstance_";                        //The delegate class for StrongReferencePointers
cstr EngineClass_clsMtdDelegate = "CPPClassMethodDelegateInstance_";                       //The delegate class for C++ class methods
cstr EngineClass_glbMtdDelegate = "CPPGlobalMethodDelegateInstance_";                      //The delegate class for C++ global methods
cstr EngineClass_delegateCore = "DelegateCore";                                            //The base class for SC delegates
cstr EngineClass_multicastDelegateCore = "MulticastDelegateCore";                          //The base class for MC delegates
cstr EngineClass_bdelegateCore = "BaseDelegateCore";                                       //The base class for SC delegates
cstr EngineClass_bmulticastDelegateCore = "BaseMulticastDelegateCore";                     //The base class for MC delegates
cstr EngineClass_multicastDelegateCoreInst = "MulticastDelegateCoreInstance";              //The instance class for MC delegates
cstr EngineClass_delegateInterface = "DelegateInterface";                                  //The gateway instance class for instace->interface
cstr EngineClass_di = "DelegateClassInstance";                                             //Just a keyword to attach to class name
cstr EngineClass_gdi = "GlobalMethodDelegateClassInstance";                                //Shortcut access for global method decs.
cstr EngineClassName_SPNTS = "StrongReference";                                            //Prefix name for strong reference delegates (non-thread safe)
cstr EngineClassName_SPTS = "TSStrongReference";                                           //Prefix name for strong reference delegates (thread safe)
cstr EngineClassName_CLMTD = "ClassMethod";                                                //Prefix name for class method delegates
cstr EngineClassName_GLMTD = "GlobalMethod";                                               //Prefix name for global method delegates
cstr EngineClass_bscdi = "SingleCastDelegateInstance";                                     //Base class for typedef of multicast -> singlecast

/* Include Files */
cstr EngineInclude_DelegateInstace = "delegateInstance.inl";                               //Include file for delegate class defs
cstr EngineInclude_DelegateInterface = "delegateInterface.inl";                            //Include file for delegateInstance overrides
cstr EngineInclude_DelegateSignatureTypes = "delegateTypes.inl";                           //Include file for delegate signature definitions

/* Function Decs */

void addINL_MacroDef(fstream *f, cstr frontTag, cstr baseClass, bool hasConst = true);
void addINL_SPTemplateInstancing(fstream *f, bool hasConst, cstr className, cstr originalMacro, bool useT, cstr thrdSfty, cstr constructorFirstParam, cstr constPassParam, int startPos = 0);
cstr MacroPlus(cstr macro, cstr addWhat, int num);

//If the number is not 1, append an 's' to the string, otherwise, append nothing. Used for things like "One Arg", "Two Arg's'", Etc.
cstr addS(int num) {
	return (num == 1 ? "" : "s");
}

int main() {
	string tempStorage, tempStorage2;

	//Basic Welcome Message.
	std::cout << "*** GALACTIC ENGINE ***" << NL;
	std::cout << "* Delegate Type Generator *" << NL;
	std::cout << "* By: Phantom Games Development *" << NL;
	std::cout << "* (C) Phantom Games Development - 2014" << NL2;

	std::cout << "* System will generate signatures for " << MaxParameters << " parameters and " << MaxArguments << " arguments." << NL;
	std::cout << "* Creating delegateTypes.h" << NL2;
	//Create the fstream instace
	fstream fileStrm("delegateTypes.h", fstream::out);
	//Write the standard C++ copywrite line for G2D files
	fileStrm << "/**" << NL << "* " << galacticEngineLine << NL << "* " << copywriteLine << NL;
	//Write the remaining header
	fileStrm << "* delegateTypes.h" << NL << "* " << NL << "* This file defines macros and include symbols for every delegate signature." << NL << "* " << NL;
	fileStrm << "* This C++ header file has been automatically generated by the delegateTypesH_Generator program." << NL;
	fileStrm << "**/" << NL2;
	//Write out the header guard
	fileStrm << "//First though, ensure that only delegate.h loads this file." << NL;
	fileStrm << "#if !defined(GALACTIC_ONLYINCLUDEFROM_DELEGATECOMBONATIONS_H) || !defined(GALACTIC_INCLUDING_DELEGATETYPES_INL)" << NL;
	fileStrm << T1 << "#error \"delegateTypes.h is being loaded by a file that is not delegate.h, breaking\"" << NL << "#endif" << NL2; 
	fileStrm << "/* The following (mega) block of code handles the definitions of the delegate types */" << NL;
	//Now, the format of this system works very eaily.
	//First, for each instance (param, arg), define a single instance of arguments relating to function template settings
	string retStr; //Return String
	string retStr2; //Return String for macro defs
	//Loop #1: Parameters
	for (int i = 0; i <= MaxParameters; i++) {
		//Define the initial set.
		fileStrm << "/* Delegate Definitions For " << num2Text[i] << " Parameters */" << NL;
		//Loop #2: Returns a value versus void
		for (int r = 0; r <= 1; r++) {
			if (r == 0) {
				retStr = "";
				retStr2 = "";
			}
			else {
				retStr = EngineDelegateReturn + "_";
				retStr2 = EngineDelegateReturn;
			}
			//Now create the first block (for DelegateBase_X)
			fileStrm << "// Delegate Base Block Definition Begin (" << num2Text[i] << " params, " << (r == 0 ? "void" : "return") << ")" << NL;
			fileStrm << "#define " << EngineMacro_FSuffix << " " << retStr << num2Text[i] << EngineDelegateParam << addS(i) << NL;

			fileStrm << "#define " << EngineMacro_TypeTemplateDec << " typename " << EngineDelegateReturnType;
			//For each parameter, add a comma and their respective type.
			for (int x = 1; x <= i; x++) {
				fileStrm << ", typename " << EngineDelegateParam << x << "Type";
			}
			fileStrm << NL;

			fileStrm << "#define " << EngineMacro_AltTemplateDec << " typename " << EngineDelegateReturnType << "Alt";
			//For each parameter, add a comma and their respective type.
			for (int x = 1; x <= i; x++) {
				fileStrm << ", typename " << EngineDelegateParam << x << "TypeAlt";
			}
			fileStrm << NL;

			fileStrm << "#define " << EngineMacro_TemplateArguments << " " << EngineDelegateReturnType;
			//For each parameter, add a comma and their respective type.
			for (int x = 1; x <= i; x++) {
				fileStrm << ", " << EngineDelegateParam << x << "Type";
			}
			fileStrm << NL;

			fileStrm << "#define " << EngineMacro_HasParams << " " << (i > 0 ? "1" : "0") << NL;

			fileStrm << "#define " << EngineMacro_ParamList << " ";
			for (int x = 1; x <= i; x++) {
				fileStrm << EngineDelegateParam << x << "Type xParam" << x;
				if ((x + 1) <= i) {
					fileStrm << ", ";
				}
			}
			fileStrm << NL;

			fileStrm << "#define " << EngineMacro_ParamDef << " ";
			for (int x = 1; x <= i; x++) {
				fileStrm << EngineDelegateParam << x << "Type Param" << x << "; ";
			}
			fileStrm << NL;

			fileStrm << "#define " << EngineMacro_ParamAssign << " ";
			for (int x = 1; x <= i; x++) {
				fileStrm << "xParam" << x;
				if ((x + 1) <= i) {
					fileStrm << ", ";
				}
			}
			fileStrm << NL;

			fileStrm << "#define " << EngineMacro_ParamPassToFunc << " ";
			for (int x = 1; x <= i; x++) {
				fileStrm << "parameters.Param" << x;
				if ((x + 1) <= i) {
					fileStrm << ", ";
				}
			}
			fileStrm << NL;

			fileStrm << "#define " << EngineMacro_ParamInitializer << " ";
			for (int x = 1; x <= i; x++) {
				fileStrm << "Param" << x << "(xParam" << x << ")";
				if ((x + 1) <= i) {
					fileStrm << ", ";
				}
			}
			fileStrm << NL;

			fileStrm << "#define " << EngineMacro_VoidRetType << " " << (r == 0 ? "1" : "0") << NL;

			//Lastly, load up the delegateInterface inline header.
			fileStrm << "#include \"" << EngineInclude_DelegateInterface << "\"" << NL;
			fileStrm << "// End Delegate Base Block Definition" << NL2;
			//Loop #3: Arguments
			for (int k = 0; k <= MaxArguments; k++) {
				//Phantom139: V2.0: Remove a huge chunk of the file with some majik
				fileStrm << "/* Delegate Definitions For " << num2Text[i] << " Parameters, " << num2Text[k] << " Arguments, and " << (r == 0 ? "no" : "a variable") << " return type */" << NL;

				fileStrm << "#define " << EngineMacro_HasArgs << " " << (k > 0 ? "1" : "0") << NL;

				fileStrm << "#define " << EngineMacro_ArgSuffix << " " << retStr << num2Text[i] << EngineDelegateParam << addS(i) <<
					(k > 0 ? "_" + num2Text[k] + EngineDelegateArg + addS(k) : "") << NL;

				fileStrm << "#define " << EngineMacro_ArgsTypeTemplateDec << " typename " << EngineDelegateReturnType;
				//For each parameter, add a comma and their respective type.
				for (int x = 1; x <= i; x++) {
					fileStrm << ", typename " << EngineDelegateParam << x << "Type";
				}
				for (int y = 1; y <= k; y++) {
					fileStrm << ", typename " << EngineDelegateArg << y << "Type";
				}
				fileStrm << NL;

				fileStrm << "#define " << EngineMacro_ArgsAltTemplateDec << " typename " << EngineDelegateReturnType << "Alt";
				//For each parameter, add a comma and their respective type.
				for (int x = 1; x <= i; x++) {
					fileStrm << ", typename " << EngineDelegateParam << x << "TypeAlt";
				}
				for (int y = 1; y <= k; y++) {
					fileStrm << ", typename " << EngineDelegateArg << y << "TypeAlt";
				}
				fileStrm << NL;

				fileStrm << "#define " << EngineMacro_ArgsTemplateArguments << " " << EngineDelegateReturnType;
				//For each parameter, add a comma and their respective type.
				for (int x = 1; x <= i; x++) {
					fileStrm << ", " << EngineDelegateParam << x << "Type";
				}
				for (int y = 1; y <= k; y++) {
					fileStrm << ", " << EngineDelegateArg << y << "Type";
				}
				fileStrm << NL;

				fileStrm << "#define " << EngineMacro_ArgumentList << " ";
				for (int x = 1; x <= k; x++) {
					fileStrm << EngineDelegateArg << x << "Type xArg" << x;
					if ((x + 1) <= k) {
						fileStrm << ", ";
					}
				}
				fileStrm << NL;

				fileStrm << "#define " << EngineMacro_ArgumentDef << " ";
				for (int x = 1; x <= k; x++) {
					fileStrm << EngineDelegateArg << x << "Type Arg" << x << "; ";
				}
				fileStrm << NL;

				fileStrm << "#define " << EngineMacro_ArgumentAssign << " ";
				for (int x = 1; x <= k; x++) {
					fileStrm << "xArg" << x;
					if ((x + 1) <= k) {
						fileStrm << ", ";
					}
				}
				fileStrm << NL;

				fileStrm << "#define " << EngineMacro_ArgumentPassToFunc << " ";
				for (int x = 1; x <= k; x++) {
					fileStrm << "Arg" << x;
					if ((x + 1) <= k) {
						fileStrm << ", ";
					}
				}
				fileStrm << NL;

				fileStrm << "#define " << EngineMacro_ArgumentInitializer << " ";
				for (int x = 1; x <= k; x++) {
					fileStrm << "Arg" << x << "(xArg" << x << ")";
					if ((x + 1) <= k) {
						fileStrm << ", ";
					}
				}
				fileStrm << NL;

				fileStrm << "#define " << EngineMacro_ConstFunc << " 0" << NL;
				fileStrm << "#define " << EngineMacro_SuffixConstant << " " << NL;

				//Load the include.
				fileStrm << "#include \"" << EngineInclude_DelegateInstace << "\"" << NL;
				//Undef consts..
				fileStrm << "#undef " << EngineMacro_ConstFunc << NL;
				fileStrm << "#undef " << EngineMacro_SuffixConstant << NL;
				//Redef const
				fileStrm << "#define " << EngineMacro_ConstFunc << " 1" << NL;
				fileStrm << "#define " << EngineMacro_SuffixConstant << " " << EngineMacro_TagConst << NL;
				fileStrm << "#include \"" << EngineInclude_DelegateInstace << "\"" << NL;
				//Then undef everything.
				fileStrm << "//Undefine Everything Now..." << NL;
				fileStrm << "#undef " << EngineMacro_HasArgs << NL;
				fileStrm << "#undef " << EngineMacro_ArgSuffix << NL;
				fileStrm << "#undef " << EngineMacro_ArgsTypeTemplateDec << NL;
				fileStrm << "#undef " << EngineMacro_ArgsAltTemplateDec << NL;
				fileStrm << "#undef " << EngineMacro_ArgsTemplateArguments << NL;
				fileStrm << "#undef " << EngineMacro_ArgumentList << NL;
				fileStrm << "#undef " << EngineMacro_ArgumentDef << NL;
				fileStrm << "#undef " << EngineMacro_ArgumentAssign << NL;
				fileStrm << "#undef " << EngineMacro_ArgumentPassToFunc << NL;
				fileStrm << "#undef " << EngineMacro_ArgumentInitializer << NL;
				fileStrm << "#undef " << EngineMacro_SuffixConstant << NL;
				fileStrm << "#undef " << EngineMacro_ConstFunc << NL;
				fileStrm << "/* End of Delegate Definition */" << NL2;
			}
			//Post Loop #3: Undefine Func Templates
			fileStrm << "/* Delegate Definition For This Block Completed... Declare Signatures and global Delegate Define Macros */" << NL;
			fileStrm << "//Load in the signatures" << NL;
			fileStrm << "#include " << "\"" << EngineInclude_DelegateSignatureTypes << "\"" << NL;
			fileStrm << "//Declare Global Macros" << NL;
			if (r == 0) {
				//No return type means we can define both single-cast and multi-cast delegates.
				fileStrm << "#define " << EngineMacro_DeclareSCDelegate << (i == 0 ? "" : "_" + num2Text[i] + EngineDelegateParam + addS(i)) << "(DelegateName";
				if (i >= 1) {
					fileStrm << ", ";
					for (int x = 1; x <= i; x++) {
						fileStrm << EngineDelegateParam << x << "Type";
						if ((x + 1) <= i) {
							fileStrm << ", ";
						}
					}
				}
				fileStrm << ") " << EngineMacro_DeclareSCName << "(DelegateName, " << num2Text[i] + EngineDelegateParam + addS(i) << ", void";
				if (i >= 1) {
					fileStrm << ", ";
					for (int x = 1; x <= i; x++) {
						fileStrm << EngineDelegateParam << x << "Type";
						if ((x + 1) <= i) {
							fileStrm << ", ";
						}
					}
				}
				fileStrm << ")" << NL;

				fileStrm << "#define " << EngineMacro_DeclareMCDelegate << (i == 0 ? "" : "_" + num2Text[i] + EngineDelegateParam + addS(i)) << "(DelegateName";
				if (i >= 1) {
					fileStrm << ", ";
					for (int x = 1; x <= i; x++) {
						fileStrm << EngineDelegateParam << x << "Type";
						if ((x + 1) <= i) {
							fileStrm << ", ";
						}
					}
				}
				fileStrm << ") " << EngineMacro_DeclareMCName << "(DelegateName, " << num2Text[i] + EngineDelegateParam + addS(i) << ", void";
				if (i >= 1) {
					fileStrm << ", ";
					for (int x = 1; x <= i; x++) {
						fileStrm << EngineDelegateParam << x << "Type";
						if ((x + 1) <= i) {
							fileStrm << ", ";
						}
					}
				}
				fileStrm << ")" << NL;
			}
			else {
				//When there's a return type in play, we can't use the multi-cast delegate
				fileStrm << "#define " << EngineMacro_DeclareSCDelegate << "_" << retStr2 << (i == 0 ? "" : "_") << (i == 0 ? "" : num2Text[i] + EngineDelegateParam + addS(i)) <<
					"(DelegateName, " << EngineDelegateReturnType << "";
				if (i >= 1) {
					fileStrm << ", ";
					for (int x = 1; x <= i; x++) {
						fileStrm << EngineDelegateParam << x << "Type";
						if ((x + 1) <= i) {
							fileStrm << ", ";
						}
					}
				}
				fileStrm << ") " << EngineMacro_DeclareSCName << "(DelegateName, " << retStr + num2Text[i] + EngineDelegateParam + addS(i) << ", " << EngineDelegateReturnType;
				if (i >= 1) {
					fileStrm << ", ";
					for (int x = 1; x <= i; x++) {
						fileStrm << EngineDelegateParam << x << "Type";
						if ((x + 1) <= i) {
							fileStrm << ", ";
						}
					}
				}
				fileStrm << ")" << NL;
			}
			fileStrm << "//Undefine Symbols / Macros..." << NL;
			fileStrm << "#undef " << EngineMacro_FSuffix << NL;
			fileStrm << "#undef " << EngineMacro_TypeTemplateDec << NL;
			fileStrm << "#undef " << EngineMacro_AltTemplateDec << NL;
			fileStrm << "#undef " << EngineMacro_TemplateArguments << NL;
			fileStrm << "#undef " << EngineMacro_HasParams << NL;
			fileStrm << "#undef " << EngineMacro_ParamList << NL;
			fileStrm << "#undef " << EngineMacro_ParamDef << NL;
			fileStrm << "#undef " << EngineMacro_ParamAssign << NL;
			fileStrm << "#undef " << EngineMacro_ParamPassToFunc << NL;
			fileStrm << "#undef " << EngineMacro_ParamInitializer << NL;
			fileStrm << "#undef " << EngineMacro_VoidRetType << NL;

			fileStrm << "/* Definition Block Complete */ " << NL2;
		}
	}

	fileStrm << "//End Of File...";
	fileStrm.close();
	std::cout << "delegateTypes.h completed..." << NL;

	/*
	
	Part II: delegateTypes.inl
	Most of these are redundant, and thus forked off to methods below
	
	*/
	std::cout << "* Creating " << EngineInclude_DelegateSignatureTypes << NL2;

	fileStrm.open(EngineInclude_DelegateSignatureTypes.c_str(), ios::out);
	//Write the standard C++ copywrite line for G2D files
	fileStrm << "/**" << NL << "* " << galacticEngineLine << NL << "* " << copywriteLine << NL;
	//Write the remaining header
	fileStrm << "* " << EngineInclude_DelegateSignatureTypes << NL << "* " << NL << "* This file defines macros and include symbols for delegate function & class signatures." << NL << "* " << NL;
	fileStrm << "* This C++ inline-header file has been automatically generated by the delegateTypesH_Generator program." << NL;
	fileStrm << "**/" << NL2;
	//Write out the header guard
	fileStrm << "//First though, ensure that only delegate.h loads this file." << NL;
	fileStrm << "#if !defined(GALACTIC_ONLYINCLUDEFROM_DELEGATECOMBONATIONS_H) || !defined(GALACTIC_INCLUDING_DELEGATETYPES_INL)" << NL;
	fileStrm << T1 << "#error \"" << EngineInclude_DelegateSignatureTypes << " is being loaded by a file that is not delegate.h, breaking\"" << NL << "#endif" << NL2;
	//Create the file heading defines
	fileStrm << "//Define the base instances" << NL;
	fileStrm << "#define " << EngineMacro_DelegateInstanceClass << " " << EngineMacro_CombineAB << "(" << EngineClass_baseDelegate << ", " << EngineMacro_FSuffix << ")" << NL;
	
	fileStrm << "//Define Class Instances";
	fileStrm << NL << "/* Define Global Method Instances */" << NL;
	addINL_MacroDef(&fileStrm, EngineMacro_DelegateGloMthdDef, EngineClass_glbMtdDelegate, false);
	fileStrm << NL << "/* Define Class Method Instances */" << NL;
	addINL_MacroDef(&fileStrm, EngineMacro_DelegateMemMthdDef, EngineClass_clsMtdDelegate);
	fileStrm << NL << "/* Define Strong Pointer Instances */" << NL;
	addINL_MacroDef(&fileStrm, EngineMacro_DelegateSRPDef, EngineClass_strPtrDelegate);

	//Define base classes
	fileStrm << NL2 << "//Define base delegate classes" << NL;
	fileStrm << "#define " << EngineMacro_SCBaseClass << " " << EngineMacro_CombineAB << "(" << EngineClass_bdelegateCore << "_, " << EngineMacro_FSuffix << ")" << NL;
	fileStrm << "#define " << EngineMacro_MCBaseClass << " " << EngineMacro_CombineAB << "(" << EngineClass_bmulticastDelegateCore << "_, " << EngineMacro_FSuffix << ")" << NL;
	fileStrm << "#define " << EngineMacro_MCClass << " " << EngineMacro_CombineAB << "(" << EngineClass_multicastDelegateCoreInst << "_, " << EngineMacro_FSuffix << ")" << NL;
	//Define var # type defs for class instances
	fileStrm << NL << "//Define argument definitions for instance classes." << NL;
	for (int i = 1; i <= MaxArguments; i++) {
		fileStrm << "/* Argument definitions for " << num2Text[i] << " Argument" << addS(i) << " */" << NL;
		if (i == 1) {
			fileStrm << "#define " << EngineMacro_TArgPTF << "_" << num2Text[i] + EngineDelegateArg + addS(i) << " " << EngineDelegateArg << i << NL;
			fileStrm << "#define " << EngineMacro_TArgList << "_" << num2Text[i] + EngineDelegateArg + addS(i) << " " << EngineDelegateArg << i << "Type" << NL;
			fileStrm << "#define " << EngineMacro_TArgPass << "_" << num2Text[i] + EngineDelegateArg + addS(i) << " " << EngineDelegateArg << i << "Type " << EngineDelegateArg << i << NL;
			fileStrm << "#define " << EngineMacro_TArgDecl << "_" << num2Text[i] + EngineDelegateArg + addS(i) << " typename " << EngineDelegateArg << i << "Type" << NL;
		}
		else {
			fileStrm << "#define " << EngineMacro_TArgPTF << "_" << num2Text[i] + EngineDelegateArg + addS(i) << " ";
			for (int r = 1; r <= i; r++) {
				fileStrm << EngineDelegateArg << r;
				if (r != i) {
					fileStrm << ", ";
				}
			}
			fileStrm << NL << "#define " << EngineMacro_TArgList << "_" << num2Text[i] + EngineDelegateArg + addS(i) << " ";
			for (int r = 1; r <= i; r++) {
				fileStrm << EngineDelegateArg << r << "Type";
				if (r != i) {
					fileStrm << ", ";
				}
			}
			fileStrm << NL << "#define " << EngineMacro_TArgPass << "_" << num2Text[i] + EngineDelegateArg + addS(i) << " ";
			for (int r = 1; r <= i; r++) {
				fileStrm << EngineDelegateArg << r << "Type " << EngineDelegateArg << r;
				if (r != i) {
					fileStrm << ", ";
				}
			}
			fileStrm << NL << "#define " << EngineMacro_TArgDecl << "_" << num2Text[i] + EngineDelegateArg + addS(i) << " ";
			for (int r = 1; r <= i; r++) {
				fileStrm << "typename " << EngineDelegateArg << r << "Type";
				if (r != i) {
					fileStrm << ", ";
				}
			}
			fileStrm << NL;
		}
	}
	/* This next (and massive) code block handles the dirty work of defining the single-cast instance delegate. */
	fileStrm << NL << "/* Define Delegate Instancing Classes */" << NL << "namespace Galactic {" << NL2 << T1 << "namespace Core {" << NL2;
	//Write the class description block for the documentation.
	fileStrm << T2 << "/*" << NL << T2 << " Single-cast base delegate: Overrides and methods used by all instances of single-cast delegates" << NL << T2 << "*/" << NL;
	//Now write the class declaration line.
	fileStrm << T2 << "template <" << EngineMacro_TypeTemplateDec << "> class " << EngineMacro_SCBaseClass << " : public " << EngineClass_delegateCore << " /*<>*/ {" << NL;
	fileStrm << T3 << "public: " << NL << T4 << "/* Typedefs */" << NL << T4 << "//Type out a base-delegate instance" << NL;
	fileStrm << T4 << "typedef " << EngineMacro_DelegateInstanceClass << "<" << EngineMacro_TemplateArguments << "> " << EngineClass_delegateInterface << ";" << NL2;
	fileStrm << T4 << "/* Template Class Declarations */" << NL;
	//Write out class instance defs for each argument definition
	fileStrm << NL << T4 << "/* Instances for Global Method Delegates */" << NL;
	//The first one is special...
	fileStrm << T4 << "typedef " << EngineMacro_DelegateGloMthdDef + "_" + num2Text[0] + EngineDelegateArg + "s" << "<" << EngineMacro_TemplateArguments
		<< "> " << EngineClass_gdi << ";" << NL;
	//Then define normally...
	addINL_SPTemplateInstancing(&fileStrm, false, EngineClassName_GLMTD, EngineMacro_DelegateGloMthdDef, false, "", "", "", 1);
	fileStrm << NL << T4 << "/* Instances for Class Method Delegates */" << NL;
	addINL_SPTemplateInstancing(&fileStrm, true, EngineClassName_CLMTD, EngineMacro_DelegateMemMthdDef, true, "", "T *obj,", "obj,");
	fileStrm << NL << T4 << "/* Instances for Strong Pointer Delegate <X, PointerModes::Determine> */" << NL;
	addINL_SPTemplateInstancing(&fileStrm, true, EngineClassName_SPNTS, EngineMacro_DelegateSRPDef, true, ", PointerModes::Determine",
		"const StrongReference<T, PointerModes::Determine> &obj,", "obj,");
	fileStrm << NL << T4 << "/* Instances for Strong Pointer Delegate <X, PointerModes::ThreadSafe> */" << NL;
	addINL_SPTemplateInstancing(&fileStrm, true, EngineClassName_SPTS, EngineMacro_DelegateSRPDef, true, ", PointerModes::ThreadSafe",
		"const StrongReference<T, PointerModes::ThreadSafe> &obj,", "obj,");
	fileStrm << NL;

	//Write constructors
	fileStrm << T4 << "/* Constructor / Destructor */" << NL << T4 << "//Default Constructor" << NL;
	fileStrm << T4 << EngineKeyword_Inline << " " << EngineMacro_SCBaseClass << "() : " << EngineClass_delegateCore << "(NULL) { }" << NL;
	fileStrm << T4 << "//Copy Constructor (From any instance)" << NL;
	fileStrm << T4 << EngineKeyword_Inline << " " << EngineMacro_SCBaseClass << "(" << EngineClass_delegateInterface << " *delInterface) : " << EngineClass_delegateCore
		     << "(delInterface) { }" << NL;
	fileStrm << T4 << "//Copy Constructor (From similar instance)" << NL;
	fileStrm << T4 << EngineKeyword_Inline << " " << EngineMacro_SCBaseClass << "(const " << EngineMacro_SCBaseClass << " &c) : " << EngineClass_delegateCore
		<< "(NULL) {" << NL << T5 << "*this = c;" << NL << T4 << "}" << NL;
	fileStrm << T4 << "//Destructor" << NL;
	fileStrm << T4 << EngineKeyword_Inline << " ~" << EngineMacro_SCBaseClass << "() {" << NL << T5 << "unbindDelegate();" << NL << T4 << "}" << NL2;

	//Write Public Methods.
	fileStrm << T4 << "/* Public Class Methods */" << NL;
	/* NOTE!!! If you're in charge of updating the delegate system, make sure to include all instances here */
	fileStrm << T4 << "/* Create methods for C++ Global Method Declarations */" << NL;
	//First one is unique...
	fileStrm << T4 << EngineKeyword_StaticInline << " " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments << "> createGlobalMethodDelegate(typename "
		<< EngineClass_gdi << "::methodPointer mthd) {" << NL << T5 << "return " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments
		<< ">(" << EngineClass_gdi << "::createInstance(mthd));" << NL << T4 << "}" << NL;
	//The remainder use a common syntax.	
	for (int i = 1; i <= MaxArguments; i++) {
		tempStorage = EngineClassName_GLMTD + EngineClass_di + "_" + num2Text[i] + EngineDelegateArg + addS(i);
		fileStrm << T4 << "template <" << (i > 0 ? EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_StaticInline
			     << " " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments << "> createGlobalMethodDelegate(typename " << tempStorage << "<"
			     << MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) << ">::methodPointer mthd, " << MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) << ") {" << NL
			     << T5 << "return " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments << ">(" << tempStorage << "<" << MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i)
			     << ">::createInstance(mthd, " << MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) << "));" << NL << T4 << "}" << NL;
	} 
	//Next, C++ methods
	fileStrm << T4 << "/* Create methods for C++ Class Method Declarations */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_CLMTD + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T4 << "template<class T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgDecl, EngineDelegateArg, i) : "") << "> " << EngineKeyword_StaticInline
				<< " " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments << "> createMemberMethodDelegate" << (c == 1 ? "_const" : "") << "(T* trgObj, typename " << tempStorage
				<< "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T5 << "return " << EngineMacro_SCBaseClass << "<"
				<< EngineMacro_TemplateArguments << ">(" << tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "")
				<< ">::createInstance(trgObj, mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << "));" << NL << T4 << "}" << NL;
		}
	}
	//Next, StrongReferece Instances...
	//Start with StrongReference<X, PointerModes::Determine>
	fileStrm << T4 << "/* Create methods for StrongReference Instances */" << NL;
	fileStrm << T4 << "/* Methods For StrongReference<X, PointerModes::Determine> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPNTS + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T4 << "template<class T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgDecl, EngineDelegateArg, i) : "") << "> " << EngineKeyword_StaticInline
				<< " " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments << "> createStrongReferenceDelegate" << (c == 1 ? "_const" : "") << "(const StrongReference<T, PointerModes::Determine> &trgObj"
				<< ", typename " << tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T5 << "return " << EngineMacro_SCBaseClass << "<"
				<< EngineMacro_TemplateArguments << ">(" << tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "")
				<< ">::createInstance(trgObj, mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << "));" << NL << T4 << "}" << NL;
		}
	}
	//Next, StrongReference<X, PointerModes::ThreadSafe>
	fileStrm << T4 << "/* Methods For StrongReference<X, PointerModes::ThreadSafe> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPTS + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T4 << "template<class T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgDecl, EngineDelegateArg, i) : "") << "> " << EngineKeyword_StaticInline
				<< " " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments << "> createTSStrongReferenceDelegate" << (c == 1 ? "_const" : "") << "(const StrongReference<T, PointerModes::ThreadSafe> &trgObj"
				<< ", typename " << tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T5 << "return " << EngineMacro_SCBaseClass << "<"
				<< EngineMacro_TemplateArguments << ">(" << tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "")
				<< ">::createInstance(trgObj, mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << "));" << NL << T4 << "}" << NL;
		}
	}
	//Next, Object -> StrongReference<X, Determine>
	fileStrm << T4 << "/* Methods For Object- > StrongReference<X, PointerModes::Determine> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPNTS + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T4 << "template<class T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgDecl, EngineDelegateArg, i) : "") << "> " << EngineKeyword_StaticInline
				<< " " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments << "> createStrongReferenceDelegate" << (c == 1 ? "_const" : "") << "(T* trgObj, typename " << tempStorage
				<< "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T5 << "return createStrongReferenceDelegate" << (c == 1 ? "_const" : "") << "("
				<< "StaticCastStrongReference<T>(trgObj->becomeStrongRef()), mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "")
				<< ");" << NL << T4 << "}" << NL;
		}
	}
	//Lastly, Object -> StrongReference<X, ThreadSafe>
	fileStrm << T4 << "/* Methods For Object- > StrongReference<X, PointerModes::ThreadSafe> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPTS + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T4 << "template<class T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgDecl, EngineDelegateArg, i) : "") << "> " << EngineKeyword_StaticInline
				<< " " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments << "> createTSStrongReferenceDelegate" << (c == 1 ? "_const" : "") << "(T* trgObj, typename " << tempStorage
				<< "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T5 << "return createTSStrongReferenceDelegate" << (c == 1 ? "_const" : "") << "("
				<< "StaticCastStrongReference<T>(trgObj->becomeStrongRef()), mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "")
				<< ");" << NL << T4 << "}" << NL;
		}
	}

	fileStrm << NL << T4 << "/* This next block of methods are responsible for binding the delegate instance to the delegate class itself. You are responsible for "
		<< NL << T4 << "ensuring that these delegate instances are still valid at any given moment. It is recommended to use object validation checks prior to calls "
		<< NL << T4 <<"to the delegate's exec() method. */" << NL;
	//Next we need to write the bind methods that the delegate system uses...
	fileStrm << T4 << "/* Delegate Bind Methods for C++ Global Methods */" << NL;
	//Like all of the times before, global, 0 args is special...
	fileStrm << T4 << EngineKeyword_Inline << " void bindGlobalMethod(typename " << EngineClass_gdi << "::methodPointer mthd) {" << NL
		<< T5 << "*this = createGlobalMethodDelegate(mthd);" << NL << T4 << "}" << NL;
	for (int i = 1; i <= MaxArguments; i++) {
		tempStorage = EngineClassName_GLMTD + EngineClass_di + "_" + num2Text[i] + EngineDelegateArg + addS(i);
		fileStrm << T4 << "template <" << (i > 0 ? EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_Inline
			<< " void bindGlobalMethod(typename " << tempStorage << "<" << MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) << ">::methodPointer mthd, "
			<< MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) << ") {" << NL << T5 << "*this = createGlobalMethodDelegate(mthd"
			<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << ");" << NL << T4 << "}" << NL;
	}
	//Class Methods
	fileStrm << T4 << "/* Delegate Bind Methods for C++ Class Methods */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_CLMTD + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T4 << "template <class T" << (i > 0 ? ", " + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_Inline
				<< " void bindMemberMethod" << (c == 1 ? "_const" : "") << "(T* trgObj, typename " << tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T5 << "*this = createMemberMethodDelegate" << (c == 1 ? "_const" : "") << "(trgObj, mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << ");" << NL << T4 << "}" << NL;
		}
	}
	//StrongReference<X, PointerModes::Determine>
	fileStrm << T4 << "/* Delegate Bind Methods for StrongReference<X, PointerModes::Determine> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPNTS + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T4 << "template <class T" << (i > 0 ? ", " + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_Inline
				<< " void bindStrongReference" << (c == 1 ? "_const" : "") << "(const StrongReference<T, PointerModes::Determine> &trgObj, typename " << tempStorage << "<T"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "")  << ">::methodPointer mthd" 
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T5 << "*this = createStrongReferenceDelegate" << (c == 1 ? "_const" : "") << "(trgObj, mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << ");" << NL << T4 << "}" << NL;
		}
	}
	//StrongReference<X, PointerModes::ThreadSafe>
	fileStrm << T4 << "/* Delegate Bind Methods for StrongReference<X, PointerModes::ThreadSafe> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPTS + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T4 << "template <class T" << (i > 0 ? ", " + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_Inline
				<< " void bindTSStrongReference" << (c == 1 ? "_const" : "") << "(const StrongReference<T, PointerModes::ThreadSafe> &trgObj, typename " << tempStorage << "<T"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T5 << "*this = createTSStrongReferenceDelegate" << (c == 1 ? "_const" : "") << "(trgObj, mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << ");" << NL << T4 << "}" << NL;
		}
	}
	//Object -> StrongReference<X, PointerModes::Determine>
	fileStrm << T4 << "/* Delegate Bind Methods for Object -> StrongReference<X, PointerModes::Determine> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPNTS + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T4 << "template <class T" << (i > 0 ? ", " + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_Inline
				<< " void bindStrongReference" << (c == 1 ? "_const" : "") << "(T* trgObj, typename " << tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T5 << "*this = createStrongReferenceDelegate" << (c == 1 ? "_const" : "") << "(trgObj, mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << ");" << NL << T4 << "}" << NL;
		}
	}
	//Object -> StrongReference<X, PointerModes::ThreadSafe>
	fileStrm << T4 << "/* Delegate Bind Methods for Object -> StrongReference<X, PointerModes::ThreadSafe> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPTS + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T4 << "template <class T" << (i > 0 ? ", " + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_Inline
				<< " void bindTSStrongReference" << (c == 1 ? "_const" : "") << "(T* trgObj, typename " << tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T5 << "*this = createTSStrongReferenceDelegate" << (c == 1 ? "_const" : "") << "(trgObj, mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << ");" << NL << T4 << "}" << NL;
		}
	}

	//Write some useful functions & operators
	fileStrm << NL << T4 << "/* The remaining methods in this class are common delegate asset methods, define them here */" << NL;
	fileStrm << T4 << "//Execute the delegate, an error will occur if you call this on an unbound delegate, hence call bound() first." << NL
		<< T4 << EngineKeyword_Inline << " " << EngineDelegateReturnType << " exec(" << EngineMacro_ParamList << ") const {" << NL
		<< T5 << EngineClass_delegateInterface << " *dInterface = (" << EngineClass_delegateInterface << " *)fetchDInstance();" << NL
		<< T5 << "if(dInterface == NULL) {" << NL << T6 << "//ToDo: Insert an asset here for an invalid call. If support for blocking comes in C++11/14, insert it here."
		<< NL << T5 "}" << NL << T5 << "return dInterface->exec(" << EngineMacro_ParamAssign << ");" << NL << T4 << "}" << NL2;

	fileStrm << T4 << "#if " << EngineMacro_VoidRetType << NL << T5 << "//Safer version of exec() for void functions..." << NL
		<< T5 << EngineKeyword_Inline << " bool execIfDelegateBound() const {" << NL << T6 << "if(bound()) {" << NL << T7
		<< "return ((" << EngineClass_delegateInterface << " *)fetchDInstance())->execIfPoss(" << EngineMacro_ParamAssign << ");"
		<< NL << T6 << "}" << NL << T6 << "return false" << NL << T5 << "}" << NL << T4 << "#endif" << NL2;

	fileStrm << T4 << "/* Operators */" << NL;
	fileStrm << T4 << "//Assignment Operator" << NL << T4 << EngineKeyword_Inline << " " << EngineMacro_SCBaseClass << "& operator=(const "
		<< EngineMacro_SCBaseClass << " &c) {" << NL << T5 << "if(&c != this) {" << NL << T6 << EngineClass_delegateInterface
		<< " *dInterface = (" << EngineClass_delegateInterface << " *)c.fetchDInstance();" << NL << T6 << "if(dInterface != NULL) {" << NL
		<< T7 << "applyNewDInstance(dInterface);" << NL << T7 << "return *this;" << NL << T6 << "}" << NL << T6 << "applyNewDInstance(NULL);" << NL
	    << T5 << "}" << NL << T5 << "return *this;" << NL << T4 << "}" << NL2;

	fileStrm << T4 << "//Equality Operator" << NL << T4 << EngineKeyword_Inline << " bool operator==(const " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments 
		<< "> &c) {" << NL << T5 << EngineClass_delegateInterface << " *dInt1 = (" << EngineClass_delegateInterface << " *)fetchDInstance();" << NL << T5
		<< EngineClass_delegateInterface << " *dInt2 = (" << EngineClass_delegateInterface << " *)c.fetchDInstance();" << NL << T5
		<< "if(dInt1 == NULL && dInt2 == NULL) {" << NL << T6 << "return true;" << NL << T5 << "}" << NL << T5 << "else {" << NL << T6
		<< "if(dInt1 != NULL && dInt2 != NULL) {" << NL << T7 << "return dInt1->boundToSameFunc(*dInt2);" << NL << T6 << "}" << NL << T6
		<< "return false;" << NL << T5 << "}" << NL << T4 << "}" << NL2;

	//Write the end of the class...
	fileStrm << T3 << "private:" << NL << T4 << "/* Grant Friend Access To Multi-cast Base */" << NL << T4 << "template <"
		<< EngineMacro_AltTemplateDec << "> friend class " << EngineMacro_MCBaseClass << ";" << NL << T2 << "}; " << NL2;

	//Begin definition for Multicast Base, First though, begin a isVoid() block, since multicast delegates only are valid for void functions
	fileStrm << T2 << "#if " << EngineMacro_VoidRetType << NL << T3 << "/*" << NL << T3 << " Multi-cast base delegate: Overrides and methods used by all instances of multi-cast delegates"
		<< NL << T3 << "*/" << NL << T3 << "template <" << EngineMacro_TypeTemplateDec << "> class " << EngineMacro_MCBaseClass << " : public " << EngineClass_multicastDelegateCore << " /*<>*/ {"
		<< NL << T4 << "public:" << NL << T5 << "/* Typedefs */" << NL << T5 << "//Definition for single-cast instance to be inserted into the multi-cast array" << NL << T5
		<< "typedef " << EngineMacro_SCBaseClass << "<" << EngineMacro_TemplateArguments << "> " << EngineClass_bscdi << ";" << NL << T5 << "//Definition for delegate instance overloads"
		<< NL << T5 << "typedef " << EngineMacro_DelegateInstanceClass << "<" << EngineMacro_TemplateArguments << "> " << EngineClass_delegateInterface << ";" << NL2
		<< T5 << "/* Public Class Methods */" << NL << T5 << "/* Methods to add a single-cast delegate to the multi-cast list */" << NL << T5 << "/* Add methods for Global Methods */" << NL;

	//The multicast base works like the singlecast base. We define methods for each of the "types" of delegates, but the difference here, is we're basing the 
	// functioning directly off of the singlecast itself to make our lives so much easier...
	//This is used quite a bit here, so let's shortcut it.
	tempStorage2 = "typename " + EngineClass_bscdi + "::template ";
	//Like every single instance beforehand, global zero args is unique...
	fileStrm << T5 << EngineKeyword_Inline << " void addGlobalMethod(typename " << EngineClass_bscdi << "::" << EngineClass_gdi << "::methodPointer mthd) {" << NL
		<< T6 << "addDelegate(" << EngineClass_bscdi << "::createGlobalMethodDelegate(mthd)); " << NL << T5 << "}" << NL;
	for (int i = 1; i <= MaxArguments; i++) {
		tempStorage = EngineClassName_GLMTD + EngineClass_di + "_" + num2Text[i] + EngineDelegateArg + addS(i);
		fileStrm << T5 << "template <" << (i > 0 ? EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_StaticInline
			<< " void addGlobalMethod(" << tempStorage2 + tempStorage << "<" << MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) << ">::methodPointer mthd, "
			<< MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) << ") {" << NL << T6 << "addDelegate(" << EngineClass_bscdi << "::createGlobalMethodDelegate("
			<< "mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << "));" << NL << T5 << "}" << NL;
	}
	//Member Methods...
	fileStrm << T5 << "/* Add methods for Class Methods */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_CLMTD + EngineClass_di + "_" + num2Text[i] + EngineDelegateArg + addS(i) + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T5 << "template <class T" << (i > 0 ? ", " + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_StaticInline
				<< " void addClassMethod(T* trgObj, " << tempStorage2 + tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T6 << "addDelegate(" << EngineClass_bscdi << "::createMemberMethodDelegate("
				<< "trgObj, mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << "));" << NL << T5 << "}" << NL;
		}
	}
	//Strong Pointer <X, Determine>
	fileStrm << T5 << "/* Add methods for StrongReference<X, PointerModes::Determine> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPNTS + EngineClass_di + "_" + num2Text[i] + EngineDelegateArg + addS(i) + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T5 << "template <class T" << (i > 0 ? ", " + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_StaticInline
				<< " void addStrongPointer(const StrongReference<T, PointerModes::Determine> &trgObj, " << tempStorage2 + tempStorage << "<T" 
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {"
				<< NL << T6 << "addDelegate(" << EngineClass_bscdi << "::createStrongReferenceDelegate(trgObj, mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") 
				<< "));" << NL << T5 << "}" << NL;
		}
	}
	//Strong Pointer <X, ThreadSafe>
	fileStrm << T5 << "/* Add methods for StrongReference<X, PointerModes::ThreadSafe> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPTS + EngineClass_di + "_" + num2Text[i] + EngineDelegateArg + addS(i) + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T5 << "template <class T" << (i > 0 ? ", " + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_StaticInline
				<< " void addTSStrongPointer(const StrongReference<T, PointerModes::ThreadSafe> &trgObj, " << tempStorage2 + tempStorage << "<T"
				<< (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "") << ">::methodPointer mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {"
				<< NL << T6 << "addDelegate(" << EngineClass_bscdi << "::createTSStrongReferenceDelegate(trgObj, mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "")
				<< "));" << NL << T5 << "}" << NL;
		}
	}
	//Object -> Strong Pointer <X, Determine>
	fileStrm << T5 << "/* Add methods for Object -> StrongReference<X, PointerModes::Determine> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPNTS + EngineClass_di + "_" + num2Text[i] + EngineDelegateArg + addS(i) + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T5 << "template <class T" << (i > 0 ? ", " + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_StaticInline
				<< " void addStrongPointer(T *trgObj, " << tempStorage2 + tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "")
				<< ">::methodPointer mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T6 << "addDelegate(" << EngineClass_bscdi
				<< "::createStrongReferenceDelegate(trgObj, mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << "));" << NL << T5 << "}" << NL;
		}
	}
	//Object -> Strong Pointer <X, ThreadSafe>
	fileStrm << T5 << "/* Add methods for Object -> StrongReference<X, PointerModes::ThreadSafe> */" << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		for (int c = 0; c <= 1; c++) {
			tempStorage = EngineClassName_SPTS + EngineClass_di + "_" + num2Text[i] + EngineDelegateArg + addS(i) + (c == 1 ? EngineMacro_TagConst : "");
			fileStrm << T5 << "template <class T" << (i > 0 ? ", " + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << "> " << EngineKeyword_StaticInline
				<< " void addTSStrongPointer(T *trgObj, " << tempStorage2 + tempStorage << "<T" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgList, EngineDelegateArg, i) : "")
				<< ">::methodPointer mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPass, EngineDelegateArg, i) : "") << ") {" << NL << T6 << "addDelegate(" << EngineClass_bscdi
				<< "::createTSStrongReferenceDelegate(trgObj, mthd" << (i > 0 ? ", " + MacroPlus(EngineMacro_TArgPTF, EngineDelegateArg, i) : "") << "));" << NL << T5 << "}" << NL;
		}
	}
	//Remove Methods
	fileStrm << NL << T5 << "/* Methods to remove a single-cast delegate from the multi-cast list */" << NL << T5 << "/* Remove method for Global Method Delegates */" << NL;
	//Only one instance here...
	fileStrm << T5 << EngineKeyword_Inline << " void killGlobalMemberDelegate(typename " << EngineClass_bscdi << "::" << EngineClass_gdi << "::methodPointer mthd) {" << NL
		<< T6 << "killDelegate(" << EngineClass_bscdi << "::createGlobalMethodDelegate(mthd));" << NL << T5 << "}" << NL;
	//Remainder have two instances, one for const, and one for non-const
	fileStrm << T5 << "/* Remove methods for Class Method Delegates */" << NL;
	for (int c = 0; c <= 1; c++) {
		tempStorage = EngineClassName_CLMTD + EngineClass_di + (c == 1 ? EngineMacro_TagConst : "");
		fileStrm << T5 << "template <class T> " << EngineKeyword_Inline << " void killClassMethodDelegate(T* trgObj, " << tempStorage2 << tempStorage
			<< "<T>::methodPointer mthd) {" << NL << T6 << "killDelegate(" << EngineClass_bscdi << "::createMemberMethodDelegate(trgObj, mthd));" << NL << T5 << "}" << NL;
	}
	fileStrm << T5 << "/* Remove methods for Strong Reference Delegates */" << NL << T5 << "/* Remove methods for StrongReference<X, PointerModes::Determine> */" << NL;
	for (int c = 0; c <= 1; c++) {
		tempStorage = EngineClassName_SPNTS + EngineClass_di + (c == 1 ? EngineMacro_TagConst : "");
		fileStrm << T5 << "template <class T> " << EngineKeyword_Inline << " void killStrongReferenceDelegate(const StrongReference<T, PointerModes::Determine> &trgObj, " << tempStorage2 << tempStorage
			<< "<T>::methodPointer mthd) {" << NL << T6 << "killDelegate(" << EngineClass_bscdi << "::createStrongReferenceDelegate(trgObj, mthd));" << NL << T5 << "}" << NL;
	}
	fileStrm << T5 << "/* Remove methods for StrongReference<X, PointerModes::ThreadSafe> */" << NL;
	for (int c = 0; c <= 1; c++) {
		tempStorage = EngineClassName_SPTS + EngineClass_di + (c == 1 ? EngineMacro_TagConst : "");
		fileStrm << T5 << "template <class T> " << EngineKeyword_Inline << " void killTSStrongReferenceDelegate(const StrongReference<T, PointerModes::ThreadSafe> &trgObj, " << tempStorage2 << tempStorage
			<< "<T>::methodPointer mthd) {" << NL << T6 << "killDelegate(" << EngineClass_bscdi << "::createTSStrongReferenceDelegate(trgObj, mthd));" << NL << T5 << "}" << NL;
	}
	fileStrm << T5 << "/* Remove methods for Object -> StrongReference<X, PointerModes::Determine> */" << NL;
	for (int c = 0; c <= 1; c++) {
		tempStorage = EngineClassName_SPNTS + EngineClass_di + (c == 1 ? EngineMacro_TagConst : "");
		fileStrm << T5 << "template <class T> " << EngineKeyword_Inline << " void killStrongReferenceDelegate(T *trgObj, " << tempStorage2 << tempStorage
			<< "<T>::methodPointer mthd) {" << NL << T6 << "killDelegate(" << EngineClass_bscdi << "::createStrongReferenceDelegate(trgObj, mthd));" << NL << T5 << "}" << NL;
	}
	fileStrm << T5 << "/* Remove methods for Object -> StrongReference<X, PointerModes::ThreadSafe> */" << NL;
	for (int c = 0; c <= 1; c++) {
		tempStorage = EngineClassName_SPNTS + EngineClass_di + (c == 1 ? EngineMacro_TagConst : "");
		fileStrm << T5 << "template <class T> " << EngineKeyword_Inline << " void killTSStrongReferenceDelegate(T *trgObj, " << tempStorage2 << tempStorage
			<< "<T>::methodPointer mthd) {" << NL << T6 << "killDelegate(" << EngineClass_bscdi << "::createTSStrongReferenceDelegate(trgObj, mthd));" << NL << T5 << "}" << NL;
	}

	//Define the support and usable methods...
	fileStrm << NL << T5 << "/* Support Methods for Public Class Methods */" << NL;
	fileStrm << T5 << "//Generic Delegate Add Method..." << NL << T5 << "void addDelegate(" << EngineClass_delegateInterface << " *dInst) {" << NL << T6 <<
		"if(dInst != NULL) {" << NL << T7 << "addToMCList(dInst);" << NL << T6 << "}" << NL << T5 << "}" << NL;

	fileStrm << T5 << "//Generic Delegate Kill Method..." << NL << T5 << "void killDelegate(const " << EngineClass_delegateInterface << " &dInst) {" << NL << T6 <<
		"removeFromMCList(dInst);" << NL << T5 << "}" << NL;

	//Define the block of protected stuff
	fileStrm << NL << T4 << "protected:" << NL << T5 << "/* Protected Class Methods */" << NL << T5 << "//Add Delegate To List" << NL << T5
		<< "void addToMCList(" << EngineClass_delegateInterface << " *dInst) {" << NL << T6 << "//Note: It may be beneficial to add a test at some point to validate the method being added is unique, but for now, we're fine!"
		<< NL << T6 << "addDelegateInstance(dInst);" << NL << T5 << "}" << NL;

	fileStrm << T5 << "//Remove Delegate From List" << NL << T5 << "void removeFromMCList(const " << EngineClass_delegateInterface << " *dInst) {" << NL << T6
		<< "const DynArray<" << EngineClass_delegateInterface << " *> &mcList = fetchDelegateList();" << NL << T6 << "for (" << EngineClass_delegateInterface
		<< " *it = mcList.end(); it != mcList.begin(); it--) {" << NL << T7 << "//Check for the function of interest here..." << NL << T7
		<< "if(it != NULL && it->boundToSameFunc(*dInst)) {" << NL << T8 << "//There can only be one function of this type in the list, so delete, then break."
		<< NL << T8 << "SendToHell(it);" << NL << T8 << "break;" << NL << T7 << "}" << NL << T6 << "}" << NL << T5 << "}" << NL;

	fileStrm << T5 << "//Issue a broadcast command to order all delegates in the list to execute." << NL << T5 << "void broadcast() const {" << NL << T6
		<< "const DynArray<" << EngineClass_delegateInterface << " *> &mcList = fetchDelegateList();" << NL << T6 << "incLocks();" << NL << T6
		<< "for (" << EngineClass_delegateInterface << " *it = mcList.end(); it != mcList.begin(); it--) {" << NL << T7
		<< "if(it != NULL || !it->execIfPoss(" << EngineMacro_ParamAssign << ")) {" << NL << T8 << "const_cast<" << EngineMacro_MCBaseClass << " *>"
		<< "(this)->forceClean();" << NL << T7 << "}" << NL << T6 << "}" << NL << T6 << "decLocks();" << NL << T6 << "const_cast<" << EngineMacro_MCBaseClass
		<< " *>(this)->performCleaning();" << NL << T5 << "}" << NL2;


	//Finish up...
	fileStrm << T5 << "/* Hidden Constructors */" << NL << T5 << EngineKeyword_Inline << " " << EngineMacro_MCBaseClass << "() { }" << NL << T3 << "};" << NL2;

	//Begin definition for Multicast Implement
	fileStrm << T3 << "/*" << NL << T3 << " Multicast Delegate: Overrides and methods directly used by multicast instances" << NL << T3 << "*/" << NL << T3 "template <" <<
		EngineMacro_TypeTemplateDec << "> class " << EngineMacro_MCClass << " : public " << EngineMacro_MCBaseClass << "<" << EngineMacro_TemplateArguments << "> {" <<
		NL << T4 << "public:" << NL << T5 << "/* Public Class Methods */" << NL << T5 << "//Issue a broadcast to execute all delegates attached to this multicast instance" <<
		NL << T5 << EngineKeyword_Inline << " void broadcast(" << EngineMacro_ParamList << ") const {" << NL << T6 << "return Parent::broadcast(" << EngineMacro_ParamAssign
		<< ");" << NL << T5 << "}" << NL2;

	fileStrm << T5 << "//Check if this multicast instance is bound" << NL << T5 << EngineKeyword_Inline << " bool bound() const {" << NL << T6 << "return Parent::bound();"
		<< NL << T5 << "}" << NL2 << T5 << "//Empty the delegate list from this multicast instance" << NL << T5 << EngineKeyword_Inline << " void empty() {" << NL << T6
		<< "Parent::empty();" << NL << T5 << "}" << NL2 << T4 << "private:" << NL << T5 << "//Define the parent instance of this class, this is used to prevent invalid calls to existing methods." 
		<< NL << T5 << "typedef " << EngineMacro_MCBaseClass << "<" << EngineMacro_TemplateArguments << "> Parent;" << NL << T3 << "};" << NL2;

	//Close out the namespaces
	fileStrm << T2 << "#endif" << NL2 << T1 << "};" << NL2 << "};" << NL2;

	//Undefines
	fileStrm << "//Undefine Macros..." << NL;
	fileStrm << "//Undefine Template Lists" << NL;
	for (int i = 1; i <= MaxArguments; i++) {
		fileStrm << "#undef " << EngineMacro_TArgPTF << "_" << num2Text[i] + EngineDelegateArg + addS(i) << NL;
		fileStrm << "#undef " << EngineMacro_TArgList << "_" << num2Text[i] + EngineDelegateArg + addS(i) << NL;
		fileStrm << "#undef " << EngineMacro_TArgPass << "_" << num2Text[i] + EngineDelegateArg + addS(i) << NL;
		fileStrm << "#undef " << EngineMacro_TArgDecl << "_" << num2Text[i] + EngineDelegateArg + addS(i) << NL;
	}
	fileStrm << "//Undefine Base Instance Classes" << NL;
	fileStrm << "#undef " << EngineMacro_DelegateInstanceClass << NL;
	fileStrm << "#undef " << EngineMacro_SCBaseClass << NL;
	fileStrm << "#undef " << EngineMacro_MCBaseClass << NL;
	fileStrm << "#undef " << EngineMacro_MCClass << NL;
	fileStrm << "//Undefine Method Argument Lists..." << NL;
	for (int i = 0; i <= MaxArguments; i++) {
		fileStrm << "#undef " << EngineMacro_DelegateSRPDef << "_" << num2Text[i] + EngineDelegateArg + addS(i) << NL;
		fileStrm << "#undef " << EngineMacro_DelegateMemMthdDef << "_" << num2Text[i] + EngineDelegateArg + addS(i) << NL;
		fileStrm << "#undef " << EngineMacro_DelegateGloMthdDef << "_" << num2Text[i] + EngineDelegateArg + addS(i) << NL;
	}
	fileStrm << "//End Of File...";

	//All done!
	std::cout << "Generation Complete, Your files will be located in the .exe directory..." << NL2;
	std::cin.get();
	//All finished!
	return 0;
}

//Add Macro Def
void addINL_MacroDef(fstream *f, cstr frontTag, cstr baseClass, bool hasConst) {
	for (int i = 0; i <= MaxArguments; i++) {
		//Argument loop
		for (int c = 0; c <= 1; c++) {
			if (!hasConst && c == 1) {
				break;
			}
			//Const or not...
			if (c == 0) {
				//Not Constant
				if (i == 0) {
					*f << "#define " << frontTag + "_" + num2Text[i] + EngineDelegateArg + "s" << " " << EngineMacro_CombineAB << "(" << baseClass << ", " << EngineMacro_FSuffix << ")" << NL;
				}
				else {
					*f << "#define " << frontTag + "_" + num2Text[i] + EngineDelegateArg + addS(i) << " " << EngineMacro_CombineAB
						<< "(" << frontTag + "_" + num2Text[0] + EngineDelegateArg + "s" << ", _" << num2Text[i] + EngineDelegateArg + addS(i) << ")" << NL;
				}
			}
			else {
				//Constant
				*f << "#define " << frontTag + "_" + num2Text[i] + EngineDelegateArg + addS(i) + EngineMacro_TagConst << " " << EngineMacro_CombineAB
					<< "(" << frontTag + "_" + num2Text[i] + EngineDelegateArg + addS(i) << ", " << EngineMacro_TagConst << ")" << NL;
			}
		}
	}
}

//Add template classes of the specified to the list.
void addINL_SPTemplateInstancing(fstream *f, bool hasConst, cstr className, cstr originalMacro, bool useT, cstr thrdSfty, cstr constructorFirstParam, cstr constPassParam, int startPos) {
	for (int i = startPos; i <= MaxArguments; i++) {
		//Argument loop
		for (int c = 0; c <= 1; c++) {
			if (c == 1 && !hasConst) {
				//If we don't have a constant definition for this instance, move on.
				break;
			}
			//Const or not...
			if (c == 0) {
				*f << T4 << "template <" << (useT ? "class T" : "") << (i > 0 ? (useT ? ", " : "") + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "")
					<< "> class " << className + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << " : public "
					<< originalMacro + "_" + num2Text[i] + EngineDelegateArg + addS(i) << "<" << (useT ? "T, " : "") << EngineMacro_TemplateArguments
					<< (i > 0 ? ", " + EngineMacro_TArgList + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << thrdSfty << "> {"
					<< " public: ";
			}
			else {
				*f << T4 << "template <" << (useT ? "class T" : "") << (i > 0 ? (useT ? ", " : "") + EngineMacro_TArgDecl + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "")
					<< "> class " << className + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + EngineMacro_TagConst << " : public "
					<< originalMacro + "_" + num2Text[i] + EngineDelegateArg + addS(i) + EngineMacro_TagConst << "<" << (useT ? "T, " : "") << EngineMacro_TemplateArguments
					<< (i > 0 ? ", " + EngineMacro_TArgList + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << thrdSfty << "> {"
					<< " public: ";
			}
			//Write the constructor
			*f  << className + EngineClass_di + (i > 0 ? "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") + (c == 1 ? EngineMacro_TagConst : "")
				<< "(" << constructorFirstParam << " typename " << originalMacro + "_" + num2Text[i] + EngineDelegateArg + addS(i) + (c == 1 ? EngineMacro_TagConst : "")
				<< "<" << (useT ? "T, " : "") << EngineMacro_TemplateArguments << (i > 0 ? ", " + EngineMacro_TArgList + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "")
				<< thrdSfty << ">::methodPointer trgFunc " << (i > 0 ? ", " + EngineMacro_TArgPass + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "")
				<< ") : " << originalMacro + "_" + num2Text[i] + EngineDelegateArg + addS(i) + (c == 1 ? EngineMacro_TagConst : "") << "<" << (useT ? "T, " : "")
				<< EngineMacro_TemplateArguments << (i > 0 ? ", " + EngineMacro_TArgList + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "") << thrdSfty
				<< "> (" << constPassParam << " trgFunc" << (i > 0 ? ", " + EngineMacro_TArgPTF + "_" + num2Text[i] + EngineDelegateArg + addS(i) : "")
				<< ") { } " << "};" << NL;
		}

	}
}

cstr MacroPlus(cstr macro, cstr addWhat, int num) {
	return macro + "_" + num2Text[num] + addWhat + addS(num);
}