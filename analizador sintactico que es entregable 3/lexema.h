#ifndef LEXEM_H
#define LEXEM_H
#include <string>
enum tokens {
    unknown_tk = -1, program_tk = 0, var_tk, begin_tk, end_tk, type_tk, id_tk = 8,
    constant_tk = 9, arr_tk, of_tk, if_tk, then_tk, else_tk, do_tk, for_tk, to_tk, downto_tk,
    bool_false_tk, bool_true_tk, break_tk, dot_tk, dots_arr_tk, comma_tk, ddt_tk, semi_tk,
    eqv_tk, ass_tk, plus_tk, minus_tk, mul_tk, div_tk, opb_tk, cpb_tk, osb_tk, csb_tk,
    or_tk, and_tk, xor_tk, bool_eqv_tk, bool_noneqv_tk, bool_bigger_tk, bool_less_tk,
    bool_bigeqv_tk, bool_leseqv_tk, comp_tk, eof_tk, write_tk, writeln_tk, const_tk
};

enum errors {
    UNKNOWN_LEXEM, EOF_ERR, MUST_BE_ID, MUST_BE_SEMI, MUST_BE_PROG, MUST_BE_COMMA, MUST_BE_CONST,
    MUST_BE_COMP, MUST_BE_TYPE, MUST_BE_DOT, MUST_BE_DOTS_ARR, MUST_BE_ASS, MUST_BE_BRACKET,
    MUST_BE_BRACKET_END, MUST_BE_ARRBRACKET, MUST_BE_ARRBRACKET_END, MUST_BE_DO, MUST_BE_TO,
    MUST_BE_THEN, MUST_BE_OF, DUPL_ID_ERR, UNKNOWN_ID, INCORRECT_TYPE, INCORRECT_RANGE,
};
class Lexem {
public:
    Lexem() = default;
    Lexem(const std::string& t_name, tokens token_tk, int t_line) : name(t_name), token(token_tk), line(t_line) {};
    int GetLine() { return line; }
    tokens GetToken() { return token; }
    const std::string& GetName() { return name; }

private:
    std::string name{ "" };
    tokens token{ unknown_tk };
    int line{ 0 };
};
#endif

