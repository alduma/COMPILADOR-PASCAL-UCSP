#ifndef GENCODE_H
#define GENCODE_H
#include <algorithm>
#include <fstream>
#include <sstream>
#include <array>
#include "sintaxis.h"

class generador {
public:
    generador(Arbol&& t_synt_tree);
    int GenerateAsm();
    virtual ~generador();
private:
    Arbol* synt_tree;
    std::ofstream code;
    std::ostringstream test_str;
    size_t num_if{ 0 };
    size_t num_for{ 0 };
    std::string breakpoint;
    const std::array<std::string, 2> types = { "integer", "boolean" };
    const std::array<std::string, 2> specif = { "array", "const" };
    static constexpr const char* DATA_SECT = ".data";
    static constexpr const char* BSS_SECT = ".bss";
    static constexpr const char* TEXT_SECT = ".text";
    static constexpr const char* GLOB_SECT = ".global _main";
    static constexpr const char* MAIN_SECT = "_main:";
    static constexpr const char* RET_SECT = "ret";
    static constexpr const char* EAX_ZERO = "xorl %eax, %eax";
    static constexpr const char* EBX_ZERO = "xorl %ebx, %ebx";
    static constexpr const char* BYTE_TYPE = ".byte ";
    static constexpr const char* LONG_TYPE = ".long ";
    static constexpr const char* SPAC_TYPE = ".space ";
    static constexpr const char* LONG_SIZE = "4";
    static constexpr const char* BYTE_SIZE = "1";
    int generateDeclVars();
    int generateBssVaar(Arbol* node);
    int generateDataVar(Arbol* node);
    int generateCompound(Arbol* node);
    int GetOperation(const std::string str);
    void generateAfterCondition(Arbol* node);
    void generateThenElseExpr(Arbol* node);
    void generateTextPart();
    void generateExpressions(Arbol* node);
    void addLine(std::string&& code_line);
    void buildLine(std::string&& code_line);
    void addSpace();
    void generateLabel(const std::string& name, const std::string& type, const std::string& val);
    void generateEnd();
    void clearBuffer();
    void generateConstVars(Arbol* var_root);
    std::string getType(Arbol* node);
    std::string getSpec(Arbol* node);
    std::string getArraySize(Arbol* spec_node, std::string type);
    bool checkType(const std::string& type);
    bool checkSpec(const std::string& spec);
    Arbol* checkVariable(std::string&& variable);
};
#endif
