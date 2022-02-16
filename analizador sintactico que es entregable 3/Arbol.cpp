#include "Arbol.h"
Arbol::Arbol() {
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	value = "";
	priority = 0;
}
Arbol::Arbol(const string& val) {
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	value = val;
	priority = 0;
}
Arbol::~Arbol() { FreeTree(); }

void Arbol::SetPriority(int priority_) { priority = priority_; }
int	 Arbol::GetPriority() { return priority; }
void Arbol::AddLeftNode(const string& val) { this->left = CreateNode(this, val); }
void Arbol::AddRightNode(const string& val) { this->right = CreateNode(this, val); }
void Arbol::AddLeftNode(const string& val, int priority_) { this->left = CreateNode(this, val, priority_); }
void Arbol::AddRightNode(const string& val, int priority_) { this->right = CreateNode(this, val, priority_); }
void Arbol::AddLeftTree(Arbol* tree) {
	tree->parent = this;
	this->left = tree;
}
void Arbol::AddRightTree(Arbol* tree) {
	tree->parent = this;
	this->right = tree;
}
Arbol* Arbol::CreateNode(const string& val) {
	auto* node = new Arbol(val);
	return node;
}
Arbol* Arbol::CreateNode(Arbol* parent_tree, const string& val) {
	auto* node = new Arbol(val);
	node->parent = addressof(*parent_tree);
	return node;
}
Arbol* Arbol::CreateNode(Arbol* parent_tree, const string& val, int& priority_) {
	auto* node = new Arbol(val);
	node->parent = addressof(*parent_tree);
	node->SetPriority(priority_);
	return node;
}
void Arbol::ChangeValue(const string& val) { value = val; }
string Arbol::GetValue() { return this->value; }
Arbol* Arbol::GetLeftNode() { return this->left; }
Arbol* Arbol::GetRightNode() { return this->right; }
Arbol* Arbol::GetParentNode() { return this->parent; }
void Arbol::FreeLeftNode() { FreeTree(this->left); }
void Arbol::FreeRightNode() { FreeTree(this->right); }
void Arbol::FreeTree(Arbol*& t_tree) {
	try {
		if (t_tree->left != nullptr) FreeTree(t_tree->left);
		if (t_tree->right != nullptr) FreeTree(t_tree->right);
		delete t_tree;
		t_tree = nullptr;
	}
	catch (const std::exception& exp) {
		cerr << "<E> Tree: Catch exception in " << __func__ << ": "
			<< exp.what() << endl;
	}
}

void Arbol::FreeTree() {
	if (this->left != nullptr) this->left->FreeTree();
	if (this->right != nullptr) this->right->FreeTree();
	parent = nullptr;
	value = "";
}

void Arbol::PrintTree(int tab) {
	for (auto i = 0; i < tab; i++) {
		std::cout << "    ";
	}
	std::cout << this->value << std::endl;
	if (this->left != nullptr) { this->left->PrintTree(tab + 1); }
	else {
		for (auto i = 0; i < tab + 1; i++) {
			std::cout << "    ";
		}
		cout << endl;
	};
	if (this->right != nullptr) { this->right->PrintTree(tab + 1); }
	else {
		for (auto i = 0; i < tab + 1; i++) {
			std::cout << "    ";
		}
		cout << endl;
	}
}
void Arbol::PrintTree_2() {
	std::cout << this << "\t" << this->value
		<< ((this->value.size() >= 4) ? "\t " : "\t\t ")
		<< this->left
		<< ((this->left == nullptr) ? "\t\t\t " : "\t ")
		<< this->right << std::endl;
	if (this->left != nullptr) this->left->PrintTree_2();
	if (this->right != nullptr) this->right->PrintTree_2();
}