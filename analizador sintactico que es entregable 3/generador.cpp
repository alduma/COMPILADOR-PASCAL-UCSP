#include "generador.h"
generador::generador(Arbol&& t_synt_tree) {
    try {
        synt_tree = &t_synt_tree;
        code.open(synt_tree->GetValue() + ".S", std::ios::out | std::ios::trunc);
        if (!code.is_open())
            throw;
    }
    catch (const std::exception& exp) {
        std::string what;
        std::string lel(exp.what());
        what = "<E> GenCode: Catch exception in constructor: ";
        throw std::runtime_error(what + lel);
    }
}

generador::~generador() {
    code.close();
    clearBuffer();
}

int generador::GenerateAsm() {
    try {
        if (synt_tree->GetLeftNode() == nullptr &&
            synt_tree->GetRightNode() == nullptr) {
            std::cerr << "<E> GenCode: Empty tree" << std::endl;
            return -EXIT_FAILURE;
        }

        if (synt_tree->GetLeftNode() != nullptr)
            generateDeclVars();

        if (synt_tree->GetRightNode() != nullptr) {
            generateTextPart();
        }

        generateEnd();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& exp) {
        std::cerr << "<E> GenCode: Catch exception in " << __func__ << ": "
            << exp.what();
        return -EXIT_FAILURE;
    }
}

void generador::addLine(std::string&& code_line) {
    code << code_line << std::endl;
}

void generador::buildLine(std::string&& code_line) {
    test_str << code_line << std::endl;
}

int generador::generateDeclVars() {
    auto ptr = synt_tree->GetLeftNode();//var

    if (ptr->GetValue() != "var") {
        std::cerr << "<E> GenCode: Can't find declaration of variables" << std::endl;
        return -EXIT_FAILURE;
    }

    if (ptr->GetRightNode()->GetLeftNode()->GetLeftNode() != nullptr)
        addLine(DATA_SECT);
    else
        addLine(BSS_SECT);

    while (ptr->GetRightNode() != nullptr) {
        if (ptr->GetLeftNode()->GetLeftNode() != nullptr) {
            generateDataVar(ptr->GetLeftNode());
            if (!test_str.str().empty()) {
                addLine(test_str.str());
                clearBuffer();
            }
        }
        else {
            generateBssVaar(ptr->GetLeftNode());
            if (!test_str.str().empty()) {
                addLine(test_str.str());
                clearBuffer();
            }
        }
        ptr = ptr->GetRightNode();
    }
    return EXIT_SUCCESS;
}

int generador::generateDataVar(Arbol* node) {
    if (node->GetRightNode() == nullptr) {
        std::cerr << "<E> GenCode: Variable doesn't have a type node" << std::endl;
        return -EXIT_FAILURE;
    }
    if (!checkType(getType(node)))
        return EXIT_SUCCESS;
    std::string val;
    if (node->GetLeftNode() != nullptr) {
        if ((node->GetLeftNode()->GetLeftNode() != nullptr) ||
            (node->GetLeftNode()->GetRightNode() != nullptr)) {
        }
        else {
            val = node->GetLeftNode()->GetValue();
            if (getType(node) == types.at(1)) {
                if (val == "false") val = "0";
                else val = "1";
            }
        }
        std::string type = (getType(node) == types.at(0)) ? LONG_TYPE : BYTE_TYPE;
        generateLabel(node->GetValue(), type, val);
    }
    return EXIT_SUCCESS;
}

int generador::generateBssVaar(Arbol* node) {
    if (node->GetRightNode() == nullptr) {
        std::cerr << "<E> GenCode: Variable doesn't have a type node" << std::endl;
        return -EXIT_FAILURE;
    }
    if (node->GetLeftNode() != nullptr && !checkSpec(getSpec(node)))
        return EXIT_SUCCESS;
    std::string val;
    std::string var;

    if (getType(node) == specif.at(0)) {
        var = node->GetValue();
        node = node->GetRightNode();
        val = getArraySize(node->GetLeftNode(), getType(node));
    }
    else {
        var = node->GetValue();
        val = (getType(node) == types.at(0)) ? LONG_SIZE : BYTE_SIZE;
    }
    std::string type = SPAC_TYPE;
    generateLabel(var, type, val);
    return EXIT_SUCCESS;
}

void generador::generateTextPart() {
    addLine(TEXT_SECT);
    addLine(GLOB_SECT);
    addLine(" ");
    addLine(MAIN_SECT);
    addLine(" ");
    addLine(EAX_ZERO);
    addLine(EBX_ZERO);
    addLine(" ");
    if (generateCompound(synt_tree->GetRightNode()->GetRightNode()))
        std::cerr << "<E> GenCode error in begin/end operation" << std::endl;
}

int generador::generateCompound(Arbol* node) {
    try {
        while (node->GetValue() != "end" && node->GetValue() != "end.") {

            if (node->GetValue() == "end" || node->GetValue() == "end.")
                return EXIT_SUCCESS;

            std::string st = node->GetValue();
            std::string st_end = st;
            st += ":";
            addLine(st.data());
            addLine(" ");

            st_end += "_end:";
            breakpoint = st_end;

            if (node->GetLeftNode() == nullptr) {
                node = node->GetRightNode();
                continue;
            }


            if (node->GetLeftNode()->GetValue() == "for") {
                num_for++;
                auto num = num_for;

                auto ptrNextOp = node->GetRightNode();
                if (ptrNextOp->GetValue() == "end.") ptrNextOp = nullptr;
                auto ptr = node->GetLeftNode();
                auto var = node->GetLeftNode()->GetLeftNode()->GetLeftNode()->GetLeftNode()->GetValue();
                auto value1 = ptr->GetLeftNode()->GetLeftNode()->GetRightNode()->GetValue();
                auto value2 = ptr->GetLeftNode()->GetRightNode()->GetValue();
                std::string str;
                std::string loop_label;
                addLine("xorl %eax, %eax");
                str = "movl $";
                str += value2;
                str += ", %ecx";
                addLine(str.data());
                addLine(" ");

                str = "loop_m_";
                str += std::to_string(num);
                loop_label = "loop ";
                loop_label += str;
                str += ":";
                addLine(str.data());

                addLine(" ");

                if (ptr->GetRightNode()->GetValue() == "begin" ||
                    ptr->GetRightNode()->GetValue() == "for" ||
                    ptr->GetRightNode()->GetValue() == "if") {

                    node = ptr->GetRightNode()->GetRightNode();
                    generateCompound(node);
                    addLine(" ");
                }

                if (ptr->GetRightNode()->GetValue() == ":=") {
                    if (ptr->GetRightNode()->GetRightNode()->GetLeftNode() == nullptr) {
                        str = "movl ";
                        (checkVariable(ptr->GetRightNode()->GetRightNode()->GetValue()) == nullptr) ? str += "$" : "";
                        str += ptr->GetRightNode()->GetRightNode()->GetValue() += ", ";
                        str += ptr->GetRightNode()->GetLeftNode()->GetValue();
                        addLine(str.data());
                        addLine(" ");
                    }
                    else {
                        generateExpressions(ptr->GetRightNode()->GetRightNode());
                        addLine("popl %eax");
                        str = "movl %eax, " + ptr->GetRightNode()->GetLeftNode()->GetValue();
                        addLine(str.data());
                        addLine(" ");
                    }
                }

                while (node->GetRightNode()->GetValue() != "end") {
                    if (ptrNextOp != nullptr) break;
                    if (node->GetValue() == "end.") break;
                    node = node->GetRightNode();
                }
                addLine(loop_label.data());
            }
            else if (node->GetLeftNode()->GetValue() == "if") {
                auto ptr = node->GetLeftNode();

                if (ptr->GetLeftNode() == nullptr) {
                    std::cerr << "<E> GenCode: need condition in if" << std::endl;
                    throw std::out_of_range("error in if");
                }

                if (ptr->GetRightNode()->GetValue() != "then") {
                    std::cerr << "<E> GenCode: need then" << std::endl;
                    throw std::out_of_range("error in if");
                }
                num_if++;
                auto num = num_if;
                std::string str;

                if (ptr->GetLeftNode()->GetValue() == "true" ||
                    ptr->GetLeftNode()->GetValue() == "false" ||
                    (checkVariable(ptr->GetLeftNode()->GetValue()) != nullptr)) {

                    if (ptr->GetLeftNode()->GetValue() == "true") addLine("movl $1, %eax");
                    else if (ptr->GetLeftNode()->GetValue() == "false") addLine("movl $0, %eax");
                    else {
                        str = "movl " + ptr->GetLeftNode()->GetValue() + ", %eax";
                        addLine(str.data());
                    }
                    addLine("movl $0, %ebx");
                    addLine("cmp %ebx, %eax");
                    str = "jle ";
                }
                else {
                    generateAfterCondition(ptr->GetLeftNode()->GetLeftNode());
                    generateAfterCondition(ptr->GetLeftNode()->GetRightNode());
                    addLine("popl %ebx");
                    addLine("popl %eax");
                    addLine("cmp %ebx, %eax");

                    if (ptr->GetLeftNode()->GetValue() == ">") str = "jle ";
                    else if (ptr->GetLeftNode()->GetValue() == "<") str = "jge";
                    else if (ptr->GetLeftNode()->GetValue() == "=") str = "jgl";
                    else if (ptr->GetLeftNode()->GetValue() == "<>") str = "je";
                    else if (ptr->GetLeftNode()->GetValue() == ">=") str = "jl";//
                    else if (ptr->GetLeftNode()->GetValue() == "<=") str = "jg";//

                    else {
                        std::cerr << "Undefined condition";
                        throw std::out_of_range("error in if");
                    }
                }

                str += " _nope" + std::to_string(num) + "_";
                addLine(str.data());
                if (ptr->GetRightNode()->GetLeftNode() != nullptr)
                    generateThenElseExpr(ptr->GetRightNode());
                if (ptr->GetRightNode()->GetRightNode() != nullptr) {
                    str = "jmp _end" + std::to_string(num) + "_";
                    addLine(str.data());
                }

                str = " _nope" + std::to_string(num) + "_:";
                addLine(str.data());

                if (ptr->GetRightNode()->GetRightNode() != nullptr) {
                    if (ptr->GetRightNode()->GetRightNode()->GetLeftNode() != nullptr) {
                        generateThenElseExpr(ptr->GetRightNode()->GetRightNode());
                    }
                    str = " _end" + std::to_string(num) + "_:";
                    addLine(str.data());
                }

            }
            else if (node->GetLeftNode()->GetValue() == ":=") {
                if (node->GetLeftNode()->GetRightNode()->GetLeftNode() ==
                    nullptr) {

                    std::string str = "movl ";
                    (checkVariable(node->GetLeftNode()->GetRightNode()->GetValue()) == nullptr) ? str +=
                        "$" : "";
                    if (node->GetLeftNode()->GetRightNode()->GetValue() == "true") str += "1";
                    else if (node->GetLeftNode()->GetRightNode()->GetValue() == "false") str += "0";
                    else str += node->GetLeftNode()->GetRightNode()->GetValue();

                    if (node->GetLeftNode()->GetLeftNode()->GetValue() == specif.at(0)) {
                        str += ", " + node->GetLeftNode()->GetLeftNode()->GetLeftNode()->GetValue();
                        stringstream memindex;
                        memindex << 4 * stoi(node->GetLeftNode()->GetLeftNode()->GetRightNode()->GetValue());
                        str += " + " + memindex.str();
                    }
                    else
                        str += ", " + node->GetLeftNode()->GetLeftNode()->GetValue();

                    addLine(str.data());
                }
                else {

                    generateExpressions(node->GetLeftNode()->GetRightNode());
                    addLine("popl %eax");
                    std::string str = "movl %eax, ";
                    if (node->GetLeftNode()->GetLeftNode()->GetValue() == specif.at(0)) {
                        str += node->GetLeftNode()->GetLeftNode()->GetLeftNode()->GetValue();
                        stringstream memindex;
                        memindex << 4 * stoi(node->GetLeftNode()->GetLeftNode()->GetRightNode()->GetValue());
                        str += " + " + memindex.str();
                    }
                    else
                        str += node->GetLeftNode()->GetLeftNode()->GetValue();
                    addLine(str.data());
                }
            }
            else if (node->GetLeftNode()->GetValue() == "begin") {

                if (generateCompound(node->GetLeftNode()->GetRightNode())) {
                    return -EXIT_FAILURE;
                }

            }
            else throw std::out_of_range("need some end for begin");
            addLine(" ");
            addLine(st_end.data());
            if (node->GetValue() == "end" || node->GetValue() == "end.")
                break;
            else
                node = node->GetRightNode();
        }
        return EXIT_SUCCESS;
    }
    catch (const std::exception& exp) {
        std::cerr << "<E> GenCode: Catch exception in " << __func__ << ": "
            << exp.what();
        return -EXIT_FAILURE;
    }
}

void generador::generateExpressions(Arbol* node) {

    if (node->GetRightNode() == nullptr && node->GetLeftNode() == nullptr) {
        if (node->GetParentNode()->GetLeftNode() == node) {
            std::string str = "pushl ";
            (checkVariable(node->GetValue()) == nullptr) ? str += "$" : "";
            if (node->GetValue() == "true") str += "1";
            else if (node->GetValue() == "false") str += "0";
            else str += node->GetValue();
            addLine(str.data());

        }
        else {
            std::string str = "movl ";
            (checkVariable(node->GetValue()) == nullptr) ? str += "$" : "";
            if (node->GetValue() == "true") str += "1";
            else if (node->GetValue() == "false") str += "0";
            else str += node->GetValue();
            str += ", %ebx";
            addLine(str.data());
        }

        return;
    }
    if (node->GetLeftNode()->GetValue() == specif.at(0)) {

        std::string str = "pushl ";
        str += node->GetLeftNode()->GetLeftNode()->GetValue();
        stringstream memindex;
        memindex << 4 * stoi(node->GetLeftNode()->GetRightNode()->GetValue());
        str += " + " + memindex.str();
        addLine(str.data());
    }
    else if (node->GetLeftNode() != nullptr)
        generateExpressions(node->GetLeftNode());
    if (node->GetRightNode()->GetValue() == specif.at(0)) {
        std::string str = "pushl ";
        str += node->GetRightNode()->GetLeftNode()->GetValue();
        stringstream memindex;
        memindex << 4 * stoi(node->GetRightNode()->GetRightNode()->GetValue());
        str += " + " + memindex.str();
        addLine(str.data());
    }
    else if (node->GetRightNode() != nullptr)
        generateExpressions(node->GetRightNode());

    if (node->GetRightNode() != nullptr) {
        if ((node->GetRightNode()->GetRightNode() != nullptr) &&
            (node->GetRightNode()->GetLeftNode() != nullptr))
            addLine("popl %ebx");
    }

    addLine("popl %eax");

    switch (GetOperation(node->GetValue())) {
    case 1:
        addLine("addl %ebx, %eax");
        break;
    case 2:
        addLine("subl  %ebx, %eax");
        break;
    case 3:
        addLine("xorl %edx, %edx");
        addLine("mull  %ebx");
        break;
    case 4:
        addLine("xorl %edx, %edx");
        addLine("divl  %ebx");
        break;
    case 5:
        addLine("andl %ebx, %eax");
        break;
    case 6:
        addLine("xorl %ebx, %eax");
        break;
    case 7:
        addLine("orl %ebx, %eax");
        break;
    default:
        throw std::out_of_range("invalid operation");
    }
    addLine("pushl %eax");
}

int generador::GetOperation(const std::string str) {
    if (str == "+") return 1;
    if (str == "-") return 2;
    if (str == "*") return 3;
    if (str == "div") return 4;
    if (str == "and") return 5;
    if (str == "xor") return 6;
    if (str == "or") return 7;
    else return -1;
}

Arbol* generador::checkVariable(std::string&& variable) {
    auto ptr = synt_tree->GetLeftNode();
    if (ptr == nullptr)
        return nullptr;

    while (ptr->GetRightNode() != nullptr) {
        if (ptr->GetLeftNode()->GetValue() == variable)
            return ptr->GetLeftNode();
        ptr = ptr->GetRightNode();
    }
    return nullptr;
}

void generador::generateLabel(const std::string& name, const std::string& type,
    const std::string& val) {
    std::string decl = name + ": " + type + val;
    buildLine(std::move(decl));
}

void generador::generateEnd() {
    addLine(" ");
    addLine("leave");
    addLine(RET_SECT);
    addLine("");
}

std::string generador::getType(Arbol* node) {
    if (node->GetRightNode() == nullptr)
        return "";
    else
        return node->GetRightNode()->GetValue();
}

std::string generador::getSpec(Arbol* node) {
    if (node->GetLeftNode() == nullptr)
        return "";
    else
        return node->GetLeftNode()->GetValue();
}

std::string generador::getArraySize(Arbol* spec_node, std::string type) {
    int max = std::stoi(spec_node->GetRightNode()->GetValue());
    int min = std::stoi(spec_node->GetLeftNode()->GetValue());

    int type_size = (type == "integer") ? 4 : 1;
    return std::to_string((max - min + 1) * type_size);
}

bool generador::checkType(const std::string& type) {
    auto res = std::find_if(types.begin(), types.end(), [&](const std::string& t) {
        return (t == type);
        });

    return res != types.end();
}

bool generador::checkSpec(const std::string& spec) {
    auto res = std::find_if(specif.begin(), specif.end(), [&](const std::string& t) {
        return (t == spec);
        });

    return res != specif.end();
}

void generador::clearBuffer() {
    test_str.str("");
    test_str.clear();
}

void generador::generateAfterCondition(Arbol* node) {
    if ((node->GetLeftNode() == nullptr) && //variable
        (node->GetRightNode() == nullptr)) {

        std::string str = "pushl ";
        (checkVariable(node->GetValue()) == nullptr) ? str += "$" : "";
        if (node->GetValue() == "true") str += "1";
        else if (node->GetValue() == "false") str += "0";
        else str += node->GetValue();
        addLine(str.data());
    }
    else {
        generateExpressions(node);
    }
}

void generador::generateThenElseExpr(Arbol* node) {
    if (node->GetLeftNode()->GetValue() == ":=") {

        if (checkVariable((node->GetLeftNode()->GetLeftNode()->GetValue())) ==
            nullptr) {
            throw std::out_of_range("undefined variable");
        }

        if (node->GetLeftNode()->GetRightNode()->GetLeftNode() ==
            nullptr) {
            std::string str = "movl ";
            (checkVariable(node->GetLeftNode()->GetRightNode()->GetValue()) == nullptr) ? str +=
                "$" : "";
            if (node->GetLeftNode()->GetRightNode()->GetValue() == "true") str += "1";
            else if (node->GetLeftNode()->GetRightNode()->GetValue() == "false") str += "0";
            else str += node->GetLeftNode()->GetRightNode()->GetValue();
            str += ", " + node->GetLeftNode()->GetLeftNode()->GetValue();
            addLine(str.data());

        }
        else {
            generateExpressions(node->GetLeftNode()->GetRightNode());
            addLine("popl %eax");
            std::string str = "movl %eax, " + node->GetLeftNode()->GetLeftNode()->GetValue();
            addLine(str.data());
        }
    }
    else if (node->GetLeftNode()->GetValue() == "if") {
        num_if++;
        auto num = num_if;
        auto ptr = node->GetLeftNode();

        if (ptr->GetLeftNode() == nullptr) {
            std::cerr << "<E> GenCode: need condition in if" << std::endl;
            throw std::out_of_range("error in if");
        }

        if (ptr->GetRightNode()->GetValue() != "then") {
            std::cerr << "<E> GenCode: need then" << std::endl;
            throw std::out_of_range("error in if");
        }

        std::string str;
        if (ptr->GetLeftNode()->GetValue() == "true" ||
            ptr->GetLeftNode()->GetValue() == "false" ||
            (checkVariable(ptr->GetLeftNode()->GetValue()) != nullptr)) {

            if (ptr->GetLeftNode()->GetValue() == "true") addLine("movl $1, %eax");
            else if (ptr->GetLeftNode()->GetValue() == "false") addLine("movl $0, %eax");
            else {
                str = "movl " + ptr->GetLeftNode()->GetValue() + ", %eax";
                addLine(str.data());
            }
            addLine("movl $0, %ebx");
            addLine("cmp %ebx, %eax");
            str = "jle ";

        }
        else {
            generateAfterCondition(ptr->GetLeftNode()->GetLeftNode());
            generateAfterCondition(ptr->GetLeftNode()->GetRightNode());
            addLine("popl %ebx");
            addLine("popl %eax");
            addLine("cmp %ebx, %eax");
            std::string str;

            if (ptr->GetLeftNode()->GetValue() == ">") str = "jle ";
            else if (ptr->GetLeftNode()->GetValue() == "<") str = "jge";
            else if (ptr->GetLeftNode()->GetValue() == "=") str = "jgl";
            else if (ptr->GetLeftNode()->GetValue() == "<>") str = "je";
            else if (ptr->GetLeftNode()->GetValue() == ">=") str = "jl";//
            else if (ptr->GetLeftNode()->GetValue() == "<=") str = "jg";//

            else {
                std::cerr << "Undefined condition";
                throw std::out_of_range("error in if");
            }
        }
        str += " _nope" + std::to_string(num) + "_";
        addLine(str.data());
        if (ptr->GetRightNode()->GetLeftNode() != nullptr)
            generateThenElseExpr(ptr->GetRightNode());
        if (ptr->GetRightNode()->GetRightNode() != nullptr) {
            str = "jmp _end" + std::to_string(num) + "_";
            addLine(str.data());
        }
        str = " _nope" + std::to_string(num) + "_:";
        addLine(str.data());

        if (ptr->GetRightNode()->GetRightNode() != nullptr) {
            if (ptr->GetRightNode()->GetRightNode()->GetLeftNode() != nullptr) {
                generateThenElseExpr(ptr->GetRightNode()->GetRightNode());
            }
            str = " _end" + std::to_string(num) + "_:";
            addLine(str.data());
        }

    }
    else if (node->GetLeftNode()->GetValue() == "break") {
        std::string str = "jmp " + breakpoint;
        addLine(str.data());
    }
    else if (node->GetLeftNode()->GetValue() == "begin") {
        generateCompound(node->GetLeftNode()->GetRightNode());
    }
    else {
        std::cerr << "<E> GenCode in if can be :=/if/goto or begin/end" << std::endl;
        throw std::out_of_range("");
    }
}