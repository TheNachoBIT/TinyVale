#include <fstream>
#include "language/Lexer/Lexer.hpp"
#include "language/Parser/Parser.hpp"
#include "language/CodeGen/CodeGen.hpp"

int main(int argc, char const *argv[])
{
	if(argc <= 1) {
		return 0;
	}

	std::string cmd = argv[1];

	if(cmd == "build" || cmd == "emit") {

		std::ifstream t("main.vale");
		std::string str((std::istreambuf_iterator<char>(t)),
  		             std::istreambuf_iterator<char>());
	
		CodeGen::Initialize();
	
		Lexer::AddContent(str);
	
		Lexer::Start();
		
		bool canBuild = cmd == "build";

		Parser::MainLoop(canBuild);
	}

	return 0;
}