#ifndef TREE_H
#define TREE_H
#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <string>
#include <queue>
#include <utility>
#include <iomanip>
using namespace std;

class Arbol {
public:
	Arbol();
	explicit Arbol(const string& val);
	virtual ~Arbol();
	void SetPriority(int priority_);
	int GetPriority();
	void AddLeftNode(const string& val);
	void AddRightNode(const string& val);
	void AddLeftNode(const string& val, int priority_);
	void AddRightNode(const string& val, int priority_);
	void AddLeftTree(Arbol* tree);
	void AddRightTree(Arbol* tree);
	void ChangeValue(const string& val);
	string GetValue();
	static Arbol* CreateNode(const string& val);
	static Arbol* CreateNode(Arbol* parent_tree, const string& val);
	static Arbol* CreateNode(Arbol* parent_tree, const string& val, int& priority_);
	Arbol* GetLeftNode();
	Arbol* GetRightNode();
	Arbol* GetParentNode();
	void FreeLeftNode();
	void FreeRightNode();
	static void FreeTree(Arbol*& t_tree);
	void PrintTree(int tab);
	void PrintTree_2();
private:
	Arbol* left;
	Arbol* right;
	Arbol* parent;
	string value;
	int priority;
	void FreeTree();
};
#endif