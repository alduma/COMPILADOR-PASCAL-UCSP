#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include "define.h"
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char ch;
string palabra,id;
int num_ent;
double num_real;
int nro_l,sub_ind,tam_c,espacio;
alfa temporalC;
Tabla3 tabla3[max4];
FILE* F;
extern void error(int n);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string simbolo[32] ={
	"nul", "ident", "number", "plus", "minus", "times", "ridv", "of.", "eql", "neq", "less",
	"leq", "gtr", "geq", "lapren", "rparen", "comma", "semicolon", "period", "becomes",
	"begin.", "end.", "if.", "then.", "whille.", "do.", "call.", "const.",
	"var.", "proc.", "read.", "write."};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string plabra[18] ={
	"","array","begin","const","do","downto","else","end","for",
	"function","if","of","procedure","then","to","var","while"," "};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string plabra1[18] ={
	" ","array.","begin.","const.","do.","downto.",
	"else.","end.","for.","funct.","if.","of.",
	"procs.","then.","to.","var.","while."," "};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string te(char ch){
	if (ch == '+')return "plus";
	else if (ch == '-')return "minus";
	else if (ch == '*')return "times";
	else if (ch == '/')return "ridv";
	else if (ch == '(')return "lparent";
	else if (ch == ')')return "rparent";
	else if (ch == '=')return "eql";
	else if (ch == ',')return "comma";
	else if (ch == '[')return "lbrack";
	else if (ch == ']')return "rbrack";
	else if (ch == '.')return "period";
	else if (ch == '<')return "lss";
	else if (ch == '>')return "gtr";
	else if (ch == ';')return "semicolon";
	else return "error";}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void limpiar_token(){
	int i = 0;ch = '\0';
	for (i = 0; i < al; i++){temporalC[i] = '\0';}id = "";}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void obtener_token(){cout << left << setw(4) << nro_l << setw(24) << id << setw(24) << palabra << endl;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void obtener(){
	ch = fgetc(F);
	if (ch == EOF && nro_l == 0){cout << "programa inconpleto" << endl;exit(0);}
	else if (ch == EOF && nro_l != 0){cout << "programa completo" << endl;exit(0);}}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void obtener_palabra(){
	limpiar_token();
	int i, j, k;
	obtener();
	while (ch == ' ' || ch == '\t' || ch == '\n'){if (ch == '\n')nro_l += 1;obtener();}
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')){
		int k = 0;
		do{if (k < al){temporalC[k] = ch;k = k + 1;}
			obtener();
		} while ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'));
		fseek(F, -1, SEEK_CUR);
		if (k >= espacio)espacio = k;
		else{do {temporalC[espacio] = ' ';espacio = espacio - 1;
			} while (espacio != k);
		}
		id = temporalC;
		i = 1;j = norw;
		do{k = (i + j) / 2;
			if (id <= plabra[k])j = k - 1;
			if (id >= plabra[k])i = k + 1;
		} while (i <= j);
		if (i - 1 > j)palabra = plabra1[k];
		else palabra = "ident";
	}
	else if (ch >= 48 && ch <= 57){
		k = 0;num_ent = 0;num_real = 0.0;palabra = "number";
		do{
			id = id + ch;k = k + 1;obtener();
			if (ch == '.'){
				palabra = "real";id = id + ch;obtener();
			}
		} while (ch >= 48 && ch <= 57);
		fseek(F, -1, SEEK_CUR);
		char* str = const_cast<char*>(id.c_str());
		int len = strlen(str);
		char* b;
		b = (str + len - 1);
		if (*b == '.')error(13);
		if (palabra == "number")sscanf_s(str, "%d", &num_ent);
		else sscanf_s(str, "%lf", &num_real);}
	else if (ch == ':'){obtener();
		if (ch == '='){palabra = "becomes";id = ":=";}
		else{id = ":";palabra = "colon";fseek(F, -1, SEEK_CUR);}}
	else if (ch == '<'){obtener();
		if (ch == '='){palabra = "leq";id = "<=";}
		else if (ch == '>'){palabra = "neq";id = "<>";}
		else{palabra = "lss";id = "<";fseek(F, -1, SEEK_CUR);}}
	else if (ch == '>'){
		obtener();
		if (ch == '='){palabra = "geq";id = ">=";}
		else{palabra = "gtr";id = ">";fseek(F, -1, SEEK_CUR);}}
	else if (ch == '\''){palabra = "char.";obtener();id = ch;num_ent = ch;obtener();
		if (ch != '\''){error(59);fseek(F, -1, SEEK_CUR);ch = '\'';}}
	else if (ch == '"'){palabra = "str";
		do{obtener();
			id = id + ch;
		} while (ch != '"');
		id.erase(id.end() - 1);
		tam_c = id.length();num_ent = sub_ind;tabla3[sub_ind].tabla3 = id;sub_ind += 1;}
	else{palabra = te(ch);id = ch;}}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////