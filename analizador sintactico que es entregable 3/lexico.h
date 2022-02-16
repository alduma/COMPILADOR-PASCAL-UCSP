#ifndef LEXER_H
#define LEXER_H
#include <fstream>
#include <iostream>
#include <vector>
#include "lexema.h"
class lexico {
public:
	explicit lexico(const char* file_path);
	std::vector<Lexem>	ScanCode();
	~lexico();
private:
	std::ifstream code;
	char cursor{ -1 };
	int	line{ 0 };
	std::vector<Lexem> lex_table;
	Lexem GetLex();
	char GetChar();
	inline char GetCurrentCurs() { return cursor; }
};
#endif 

