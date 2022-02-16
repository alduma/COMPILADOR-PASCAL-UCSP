#ifndef SYNTAX_H
#define SYNTAX_H
#include <algorithm>
#include <iostream>
#include <chrono>
#include <list>
#include <map>
#include <vector>
#include "lexema.h"
#include "Variable.h"
#include "Arbol.h"

class sintaxis {
public:
	explicit sintaxis(std::vector<Lexem>&& t_lex_table);
	Arbol* ParseCode();
	~sintaxis();
private:
	using lex_it = std::vector<Lexem>::iterator;
	lex_it cursor;
	std::vector<Lexem> lex_table;
	std::map<std::string, Variable> id_map;
	Arbol* root_tree;
	bool error{ false };
	std::string breakpoint;
	std::map<std::string, int> operations;
	lex_it getNextLex(lex_it& iter);
	lex_it getPrevLex(lex_it& iter);
	lex_it peekLex(int N, lex_it t_iter);
	lex_it peekPrevLex(int N, lex_it t_iter);
	int programParse(lex_it& t_iter);
	int	 blockParse(lex_it& t_iter);
	std::list<std::string> vardParse(lex_it& t_iter);
	int	vardpParse(lex_it& t_iter, Arbol* t_tree);
	Arbol* stateParse(lex_it& t_iter, int c_count);
	Arbol* compoundParse(lex_it& t_iter, int c_count);
	int expressionParse(lex_it& t_iter, Arbol* tree, int t_lvl);
	Arbol* simplExprParse(const lex_it& var_iter, lex_it& t_iter, Arbol* tree, int t_lvl);
	Arbol* simplExprParse(Arbol* var_tree, lex_it& t_iter, Arbol* tree, int t_lvl);
	void printError(errors t_err, Lexem lex);
	bool checkLexem(const lex_it& t_iter, const tokens& t_tok);
	bool isVarExist(const std::string& t_var_name);
	void updateVarTypes(const std::list<std::string>& t_var_list, const std::string& t_type_name);
	void updateVarTypes(const std::list<std::string>& t_var_list, const std::string& t_type_name, const std::pair<int, int>& range);
	void buildVarTree(const std::list<std::string>& t_var_list, Arbol* t_tree);
	void buildVarTree(const std::list<std::string>& t_var_list, Arbol* t_tree, Arbol* array_tree);
	void createVarTree(Arbol* t_tree, Arbol* t_donor_tree, int lvl);
	Arbol* createLowestOpTree(Arbol* t_parent_tree, std::string value, int priority);
};
#endif 

