#include "lexico.h"

lexico::lexico(const char* file_path) {
    try {
        code.open(file_path);
    }
    catch (const std::exception& exp) {
        std::string lel(exp.what());
        std::string what = "<E> Lexer: Catch exception in constructor:";
        throw std::runtime_error(what + lel);
    }
}

std::vector<Lexem> lexico::ScanCode() {
    try {
        if (!code.is_open()) {
            std::cerr << "<E> Can't open file" << std::endl;
            return lex_table;
        }

        while (!code.eof()) {
            lex_table.emplace_back(GetLex());
        }

        return lex_table;
    }
    catch (const std::exception& exp) {
        std::cerr << "<E> Catch exception in " << __func__ << ": " << exp.what() << std::endl;
        return lex_table;
    }
}

lexico::~lexico() { code.close(); }

Lexem lexico::GetLex() {
    try {
        auto ch = GetCurrentCurs();
        while (ch == -1 || ch == ' ' || ch == '\r' || ch == '\n' || ch == '\t') {
            if (ch == '\n') line++;
            ch = GetChar();
            if (code.eof()) return Lexem(std::move("EOF"), eof_tk, line);
        }
        auto isId = [](char ch) {
            return std::isalpha(static_cast<unsigned char>(ch)) ||
                std::isdigit(static_cast<unsigned char>(ch));
        };
        std::string lex;
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            while (std::isdigit(static_cast<unsigned char>(ch))) {
                lex += ch;
                ch = GetChar();
            }

            return Lexem(std::move(lex), constant_tk, line);
        }
        else if (std::isalpha(static_cast<unsigned char>(ch))) {
            while (isId(ch)) {
                lex += ch;
                ch = GetChar();
            }
            if (lex == "program") { return Lexem(std::move(lex), program_tk, line); }
            else if (lex == "var") { return Lexem(std::move(lex), var_tk, line); }
            else if (lex == "begin") { return Lexem(std::move(lex), begin_tk, line); }
            else if (lex == "integer") { return Lexem(std::move(lex), type_tk, line); }
            else if (lex == "boolean") { return Lexem(std::move(lex), type_tk, line); }
            else if (lex == "array") { return Lexem(std::move(lex), arr_tk, line); }
            else if (lex == "of") { return Lexem(std::move(lex), of_tk, line); }
            else if (lex == "end") { return Lexem(std::move(lex), end_tk, line); }
            else if (lex == "div") { return Lexem(std::move(lex), div_tk, line); }
            else if (lex == "and") { return Lexem(std::move(lex), and_tk, line); }
            else if (lex == "or") { return Lexem(std::move(lex), or_tk, line); }
            else if (lex == "xor") { return Lexem(std::move(lex), xor_tk, line); }
            else if (lex == "if") { return Lexem(std::move(lex), if_tk, line); }
            else if (lex == "for") { return Lexem(std::move(lex), for_tk, line); }
            else if (lex == "to") { return Lexem(std::move(lex), to_tk, line); }
            else if (lex == "downto") { return Lexem(std::move(lex), downto_tk, line); }
            else if (lex == "do") { return Lexem(std::move(lex), do_tk, line); }
            else if (lex == "false") { return Lexem(std::move(lex), bool_false_tk, line); }
            else if (lex == "true") { return Lexem(std::move(lex), bool_true_tk, line); }
            else if (lex == "break") { return Lexem(std::move(lex), break_tk, line); }
            else if (lex == "then") { return Lexem(std::move(lex), then_tk, line); }
            else if (lex == "else") { return Lexem(std::move(lex), else_tk, line); }
            else if (lex == "Write") { return Lexem(std::move(lex), write_tk, line); }
            else if (lex == "Writeln") { return Lexem(std::move(lex), writeln_tk, line); }
            else if (lex == "const") { return Lexem(std::move(lex), const_tk, line); }
            else {
                return Lexem(std::move(lex), id_tk, line);
            }
        }
        else if (std::ispunct(static_cast<unsigned char>(ch))) {
            tokens tok{ unknown_tk };
            switch (ch) {
            case ',': tok = comma_tk; break;
            case 39: tok = comma_tk; break;
            case '!': tok = comma_tk; break;
            case '.': tok = dot_tk; break;
            case ':': tok = ddt_tk; break;
            case ';': tok = semi_tk; break;
            case '=': tok = eqv_tk; break;
            case '+': tok = plus_tk; break;
            case '-': tok = minus_tk; break;
            case '*': tok = mul_tk; break;
            case '(': tok = opb_tk; break;
            case ')': tok = cpb_tk; break;
            case '[': tok = osb_tk; break;
            case ']': tok = csb_tk; break;
            case '>': tok = bool_bigger_tk; break;
            case '<': tok = bool_less_tk; break;
            case ':=': tok = bool_less_tk; break;
            default:
                std::cerr << "<E> desconocido token " << ch << std::endl;
                tok = unknown_tk;
                break;
            }
            lex += ch;
            if (tok == ddt_tk) {
                ch = GetChar();
                if (ch == '=') {
                    lex += ch;
                    tok = ass_tk;
                }
            }
            if (tok == dot_tk) {
                ch = GetChar();
                if (ch == '.') {
                    lex += ch;
                    tok = dots_arr_tk;
                }
            }
            if (tok == eqv_tk) {
                ch = GetChar();
                if (ch == '=') {
                    lex += ch;
                    tok = bool_eqv_tk;
                }
            }
            if (tok == bool_bigger_tk) {
                ch = GetChar();
                if (ch == '=') {
                    lex += ch;
                    tok = bool_bigeqv_tk;
                }
            }
            if (tok == bool_less_tk) {
                ch = GetChar();
                if (ch == '=') {
                    lex += ch;
                    tok = bool_leseqv_tk;
                }
            }
            if (tok == bool_less_tk) {
                ch = GetChar();
                if (ch == '>') {
                    lex += ch;
                    tok = bool_noneqv_tk;
                }
            }
            GetChar();
            return Lexem(std::move(lex), tok, line);
        }
        else {
            std::cerr << "<E> desconocido token " << ch << std::endl;
        }
        return Lexem(std::move(""), unknown_tk, line);
    }
    catch (const std::exception&) {
        return Lexem(std::move(""), unknown_tk, line);
    }
}

char lexico::GetChar() {
    if (code.fail()) {
        std::cerr << "<E> Can't read from the file" << std::endl;
        throw std::runtime_error("File doesn't available");
    }
    if (!code.eof()) {
        code >> std::noskipws >> cursor;
    }
    else {
        std::cerr << "<E> File is EOF early" << std::endl;
        throw std::runtime_error("File is EOF early");
    }
    return cursor;
}
