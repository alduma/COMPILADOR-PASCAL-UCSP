#include "proyecto.h"


int Compile(const std::string& file_path) {
	lexico lex(file_path.c_str());
	auto table = lex.ScanCode();
	sintaxis syntx(std::move(table));
	auto tree = syntx.ParseCode();
	if (tree == nullptr) {
		std::cerr << "Error: sintaxis invalida del arbol" << std::endl;
		return -EXIT_FAILURE;
	}
	generador gencod(std::move(*tree));
	gencod.GenerateAsm();
	return EXIT_SUCCESS;
}