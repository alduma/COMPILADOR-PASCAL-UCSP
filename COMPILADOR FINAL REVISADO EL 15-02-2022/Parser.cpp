#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include "define.h"
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void error(int n);
extern void mal(int n);
extern void salto(int n);
extern void Tpuntoycoma();
extern void interprete();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int t, a, b, c1, c2, lc;
int level, dx, start = 1, i;
double constantee[max5];
int display[max9];
Orden codigo[max8];
Tabla tabl[max1];
Tabla1 tabla1[max2];
Tabla2 tabla2[max3];
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Block(bool isfun);
void declarar_variableC();
void Vconstante(conrec& c);
void declarar_variable();
void tipo_variable(string& tp, int& rf, int& x);
void tipo_arreglo(int& aref, int& arse);
void declarar_funcion();
void lista_de_parametros();
void declaracion();
void asignacion(int lv, int ad);
void expresion(item& x);
void expresionS(item& x);
void termino(item& x);
void factor(item& x);
void Selector(item& v);
void llamar(int i);
string Tresultado(string a, string b);
void declaracion_comp();
void declaracion_if();
void declaracion_while();
void declaracion_for();
void proceso(int n);
bool proceso1(string sy);
bool proceso2(string sy);
void enter(string x0, string x1, string x2, int x3);
void enter(string id, string k);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ord(bool flag){if (flag)return 1;else return 0;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ord(string s){
	if (s == "notyp")return 0;
	else if (s == "number")return 1;
	else if (s == "real")return 2;
	else if (s == "char")return 4;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool proceso1(string sy){
	if (sy == "notyp" || sy == "number" || sy == "real" || sy == "char")return true;
	else return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool proceso2(string sy){
	if (sy == "begin." || sy == "if." || sy == "while." || sy == "for.")return true;
	else return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Fun(string sy){
	if (sy == "number" || palabra == "real" || palabra == "char" || sy == "ident" || sy == "lparent" || sy == "notyp") return true;
	else return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void enter(string x0, string x1, string x2, int x3){
	t = t + 1;tabl[t].name = x0;tabl[t].link = t - 1;tabl[t].obj = x1;
	tabl[t].typ = x2;tabl[t].normal = true;tabl[t].lev = 0;tabl[t].adr = x3;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void enter(string id, string k){
	int j, l;
	if (t == max1)mal(1);
	else{
		tabl[0].name = id;j = tabla2[display[level]].last;l = j;
		while (tabl[j].name != id)j = tabl[j].link;
		if (j != 0)error(1);
		else{
			t = t + 1;tabl[t].name = id;tabl[t].link = l;tabl[t].obj = k;tabl[t].typ = "notyp";
			tabl[t].ref = 0;tabl[t].lev = level;tabl[t].adr = 0;tabl[t].normal = false;}
		tabla2[display[level]].last = t;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void enterarray(int h){
	if (h<0 || h>max7)error(27);
	if (a == max2)mal(4);
	else{a = a + 1;tabla1[a].high = h;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void enterblock(){
	if (b == max3)mal(2);
	else{b = b + 1;tabla2[b].last = 0;tabla2[b].lastpar = 0;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void enterreal(double x){
	if (c2 == max5 - 1)mal(3);
	else{constantee[c2 + 1] = x;c1 = 1;
		while (constantee[c1] != x){c1 += 1;}
		if (c1 > c2)c2 = c1;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void e(int fct){
	if (lc == max8)mal(6);
	codigo[lc].f = fct;lc = lc + 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void emit1(int fct, int b){
	if (lc == max8)mal(6);
	codigo[lc].f = fct;codigo[lc].y = b;lc = lc + 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void emit2(int fct, int a, int b){
	if (lc == max8)mal(6);
	codigo[lc].f = fct;codigo[lc].x = a;codigo[lc].y = b;lc = lc + 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int loc(string id){
	int i, j;
	i = level;
	tabl[0].name = id;
	do{
		j = tabla2[display[i]].last;
		while (tabl[j].name != id){j = tabl[j].link;}
		i = i - 1;
	} while (i >= 0 && j == 0);
	if (j == 0)error(0);
	return j;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void entervariable(){
	if (palabra == "ident"){enter(id, "vvariable");obtener_palabra();}
	else error(2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Block(bool isfun){
	int tempdx, templev;tempdx = dx;
	templev = level;int prt, prb, x;dx = 5;prt = t;
	if (level > max9)mal(5);
	enterblock();
	prb = b;display[level] = b;
	tabl[prt].typ = "notyp";tabl[prt].ref = prb;
	if (palabra == "lparent" && level > 1){lista_de_parametros();}
	tabla2[prb].lastpar = t;tabla2[prb].psize = dx;
	if (isfun){
		if (palabra == "colon"){obtener_palabra();
			if (palabra == "ident"){x = loc(id);obtener_palabra();
				if (x != 0){if (proceso1(tabl[x].typ))tabl[prt].typ = tabl[x].typ;
					else error(15);}
				else salto(2);}}
		else error(5);
	}
	if (palabra == "semicolon")obtener_palabra();
	else if (start == 1)start = start - 1;
	else error(14);
	do{
		if (palabra == "const."){declarar_variableC();}
		if (palabra == "var."){declarar_variable();}
		tabla2[prb].vsize = dx;
		if (palabra == "procs." || palabra == "funct.")declarar_funcion();
	} while (!proceso2(palabra));
	tabl[prt].adr = lc;obtener_palabra();declaracion();
	while (palabra == "semicolon" || proceso2(palabra)){
		if (palabra == "semicolon")obtener_palabra();
		else error(14);declaracion();}
	if (palabra == "end.")obtener_palabra();
	else error(57);
	dx = tempdx;level = templev;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void declarar_variableC(){
	conrec c;
	obtener_palabra();
	while (palabra == "ident"){
		enter(id, "constant");obtener_palabra();
		if (palabra == "eql")obtener_palabra();
		else{error(16);
			if (palabra == "becomes")obtener_palabra();}
		Vconstante(c);
		tabl[t].typ = c.tp;tabl[t].ref = 0;
		if (c.tp == "real"){enterreal(c.r);tabl[t].adr = c1;}
		else tabl[t].adr = c.i;
		if (palabra == "comma")obtener_palabra();
		else{Tpuntoycoma();
			if (palabra == "ident"){error(62);salto(62);}
			break;}}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Vconstante(conrec& c){
	int x, sign;
	c.tp = "notyp";
	c.i = 0;
	if (palabra == "char."){c.tp = "char";c.i = num_ent;obtener_palabra();}
	else{sign = 1;
		if (palabra == "plus" || palabra == "minus"){if (palabra == "minus"){sign = -1;}
			obtener_palabra();
		}
		if (palabra == "ident"){x = loc(id);if (x != 0){if (tabl[x].obj != "constant")error(25);
				else{c.tp = tabl[x].typ;
					if (c.tp == "real")c.r = sign * constantee[tabl[x].adr];
					else c.i = sign * tabl[x].adr;}}
			obtener_palabra();
		}
		else if (palabra == "number"){c.tp = "number";c.i = sign * num_ent;obtener_palabra();}
		else if (palabra == "real"){c.tp = "real";c.r = sign * num_real;obtener_palabra();}
		else salto(50);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void declarar_variable(){
	string tp;
	int t0, t1, rf = 0, sz = 0;
	obtener_palabra();
	while (palabra == "ident"){t0 = t;
		entervariable();
		while (palabra == "comma"){obtener_palabra();entervariable();}
		if (palabra == "colon")obtener_palabra();
		else error(5);
		t1 = t;
		tipo_variable(tp, rf, sz);
		while (t0 < t1){
			t0 = t0 + 1;tabl[t0].typ = tp;tabl[t0].ref = rf;tabl[t0].lev = level;
			tabl[t0].adr = dx;tabl[t0].normal = true;dx = dx + sz;}
		if (palabra != "semicolon"){error(63);obtener_palabra();}
		else{Tpuntoycoma();}}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tipo_variable(string& tp, int& rf, int& sz){
	string eltp;
	int elrf, x, t0, t1;
	tp = "notyp";rf = 0;sz = 0;
	if (palabra == "ident"){
		x = loc(id);
		if (x != 0){if (tabl[x].obj != "typel")error(29);
			else{tp = tabl[x].typ;rf = tabl[x].ref;sz = tabl[x].adr;
				if (tp == "notyp")error(30);}}
		obtener_palabra();
	}
	else if (palabra == "array."){obtener_palabra();
		if (palabra == "lbrack")obtener_palabra();
		else{error(11);
			if (palabra == "lparent")obtener_palabra();
		}
		tp = "array";tipo_arreglo(rf, sz);}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tipo_arreglo(int& aref, int& arse){
	string eltp;conrec high;
	int elrf, elsz;
	Vconstante(high);
	if (high.tp == "real"){error(27);high.tp = "number";high.i = 0;}
	enterarray(high.i);
	tabla1[a].inxtpy = "number";aref = a;
	if (palabra == "rbrack")obtener_palabra();
	else error(12);
	if (palabra == "of.")obtener_palabra();
	else error(8);
	string tempstr = "notyp";
	tipo_variable(eltp, elrf, elsz);
	arse = (tabla1[aref].high) * elsz;
	tabla1[aref].size = high.i;tabla1[aref].eltyp = eltp;tabla1[aref].elref = elrf;tabla1[aref].elsize = elsz;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void declarar_funcion(){
	int templev;bool isfun;
	isfun = (palabra == "funct.");
	obtener_palabra();
	if (palabra != "ident"){error(2);id = "";}
	if (isfun)enter(id, "function");
	else enter(id, "procedure");
	tabl[t].normal = true;
	obtener_palabra();
	templev = level;level += 1;Block(isfun);level = templev;
	if (palabra == "semicolon")obtener_palabra();
	else error(14);
	e(32 + ord(isfun));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lista_de_parametros(){
	string tp;
	bool valpar;int rf, sz, x, t0;
	obtener_palabra();
	tp = "notyp";rf = 0;sz = 0;
	if (palabra == "rparent")error(64);
	while (palabra == "ident" || palabra == "var."){
		if (palabra != "var.")valpar = true;
		else{obtener_palabra();valpar = false;}
		t0 = t;
		entervariable();
		while (palabra == "comma"){obtener_palabra();entervariable();}
		if (palabra == "colon"){obtener_palabra();
			if (palabra != "ident")error(2);
			else{x = loc(id);
				obtener_palabra();
				if (x != 0){if (tabl[x].obj != "typel")error(29);
					else{tp = tabl[x].typ;rf = tabl[x].ref;
						if (valpar)sz = tabl[x].adr;
						else sz = 1;}}}}
		else error(5);
		while (t0 < t){
			t0 = t0 + 1;tabl[t0].typ = tp;tabl[t0].ref = rf;
			tabl[t0].adr = dx;tabl[t0].normal = valpar;dx = dx + sz;}
		if (palabra != "rparent"){if (palabra == "semicolon")obtener_palabra();
			else{error(14);
				if (palabra == "comma")obtener_palabra();}}}
	if (palabra == "rparent"){obtener_palabra();}
	else error(4);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void declaracion(){
	if (palabra == "ident" || proceso2(palabra)){
		if (palabra == "ident"){
			i = loc(id);obtener_palabra();
			if (i != 0){if (tabl[i].obj == "constant" || tabl[i].obj == "typel")error(45);
				else if (tabl[i].obj == "vvariable")asignacion(tabl[i].lev, tabl[i].adr);
				else if (tabl[i].obj == "procedure"){if (tabl[i].lev != 0)llamar(i);
					else proceso(tabl[i].adr);}
				else if (tabl[i].obj == "function"){if (tabl[i].ref == display[level])asignacion(tabl[i].lev + 1, 0);
					else error(45);}}}
		else if (palabra == "begin.")declaracion_comp();
		else if (palabra == "if.")declaracion_if();
		else if (palabra == "while.")declaracion_while();
		else if (palabra == "for.")declaracion_for();}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void asignacion(int lv, int ad){
	item x, y;
	int f;
	x.typ = tabl[i].typ;x.ref = tabl[i].ref;
	if (tabl[i].normal)f = 0;
	else f = 1;
	emit2(f, lv, ad);
	if (palabra == "lbrack" || palabra == "lparent")Selector(x);
	if (palabra == "becomes")obtener_palabra();
	else{error(51);if (palabra == "eql")obtener_palabra();}
	expresion(y);
	if (x.typ == y.typ){if (proceso1(x.typ))e(38);else{
			if (x.ref != y.ref)error(46);else{
				if (x.typ == "array")emit1(23, tabla1[x.ref].size);
				else emit1(23, tabla2[x.ref].vsize);}}}
	else if (x.typ == "number" && y.typ == "char"){if (proceso1(x.typ))e(38);}
	else if (x.typ == "real" && (y.typ == "number" || y.typ == "char")){emit1(26, 0);e(38);}
	else if (x.typ != "notyp" && y.typ != "notyp")error(46);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void expresion(item& x){
	item y;string op;
	expresionS(x);
	if (palabra == "eql" || palabra == "neq" || palabra == "lss" || palabra == "leq" || palabra == "gtr" || palabra == "geq"){
		op = palabra;
		obtener_palabra();
		expresionS(y);
		if ((x.typ == "notyp" || x.typ == "number") && (x.typ == y.typ)){if (op == "eql")e(45);
			else if (op == "neq")e(46);
			else if (op == "lss")e(47);
			else if (op == "leq")e(48);
			else if (op == "gtr")e(49);
			else if (op == "geq")e(50);}
		else if ((x.typ == "char") && (x.typ == y.typ)){if (op == "eql")e(64);
			else if (op == "neq")e(65);
			else if (op == "lss")e(66);
			else if (op == "leq")e(67);
			else if (op == "gtr")e(68);
			else if (op == "geq")e(69);}
		else{if (x.typ == "number" || x.typ == "char"){x.typ == "real";emit1(26, 1);}
			else if (y.typ == "number" || y.typ == "char"){y.typ == "real";emit1(26, 0);}
			if (x.typ == "real" && y.typ == "real"){if (op == "eql")e(39);
				else if (op == "neq")e(40);
				else if (op == "lss")e(41);
				else if (op == "leq")e(42);
				else if (op == "gtr")e(43);
				else if (op == "geq")e(44);}
			else error(35);}
		x.typ = "bool";}
	else if (palabra == "char.")error(61);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void expresionS(item& x){
	item y;string op;
	if (palabra == "plus" || palabra == "minus"){op = palabra;obtener_palabra();termino(x);
		if (x.typ == "array")error(33);
		else if (op == "minus")e(36);}
	else termino(x);
	while (palabra == "plus" || palabra == "minus"){
		op = palabra;obtener_palabra();termino(y);
		x.typ = Tresultado(x.typ, y.typ);
		if (x.typ == "notyp");
		else if (x.typ == "number" || x.typ == "char"){if (op == "plus")e(52);
			else e(53);}
		else if (x.typ == "real"){if (op == "plus")e(54);
			else e(55);}}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void termino(item& x){
	item y;string op;
	factor(x);
	while (palabra == "times" || palabra == "ridv"){
		op = palabra;obtener_palabra();factor(y);
		if (op == "times"){x.typ = Tresultado(x.typ, y.typ);
			if (x.typ == "notyp");
			else if (x.typ == "number" || x.typ == "char")e(57);
			else if (x.typ == "real")e(60);}
		else if (op == "ridv" && (x.typ == "number" || x.typ == "char") && (y.typ == "number" || y.typ == "char")){
			if (op == "ridv")e(58);
			else{if (x.typ != "notyp" && y.typ != "notyp")error(34);x.typ = "notyp";}}
		else if (op == "ridv"){
			if (x.typ == "number" || x.typ == "char"){emit1(26, 1);x.typ = "real";}
			if (y.typ == "number" || y.typ == "char"){
				emit1(26, 0);y.typ = "real";}
			if (x.typ == "real" && y.typ == "real"){e(61);}
			else{if (x.typ != "notyp" && y.typ != "notyp")error(33);x.typ = "notyp";}}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void factor(item& x){
	int i, f;
	x.typ = "notyp";x.ref = 0;
	while (Fun(palabra)){if (palabra == "ident"){i = loc(id);obtener_palabra();
			if (tabl[i].obj == "constant"){x.typ = tabl[i].typ;x.ref = 0;
				if (x.typ == "real")emit1(25, tabl[i].adr);
				else if (x.typ == "char"){emit1(70, tabl[i].adr);}
				else emit1(24, tabl[i].adr);}
			else if (tabl[i].obj == "vvariable"){
				x.typ = tabl[i].typ;x.ref = tabl[i].ref;
				if (palabra == "lbrack" || palabra == "lparent"){if (tabl[i].normal)f = 0;
					else f = 1;
					emit2(f, tabl[i].lev, tabl[i].adr);
					Selector(x);
					if (proceso1(x.typ))e(34);}
				else{if (proceso1(x.typ)){if (tabl[i].normal)f = 1;
						else f = 2;}
					else{if (tabl[i].normal)f = 0;
						else f = 1;}
					emit2(f, tabl[i].lev, tabl[i].adr);}}
			else if (tabl[i].obj == "typel" || tabl[i].obj == "procedure")error(44);
			else if (tabl[i].obj == "function"){x.typ = tabl[i].typ;
				if (tabl[i].lev != 0)llamar(i);else error(0);}}
		else if (palabra == "char" || palabra == "number" || palabra == "real"){
			if (palabra == "real"){x.typ = "real";enterreal(num_real);emit1(25, c1);}
			else{if (palabra == "char"){x.typ = "char";emit1(70, num_ent);}
				else{x.typ = "number";emit1(24, num_ent);}}
			x.ref = 0;
			obtener_palabra();}
		else{if (palabra == "lparent"){obtener_palabra();expresion(x);
				if (palabra == "rparent")obtener_palabra();
				else error(4);}
			else error(9);}}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Selector(item& v){
	item x;int a, j;
	if (palabra != "lbrack")error(11);
	obtener_palabra();expresion(x);
	if (v.typ != "array")error(28);
	else{a = v.ref;
		if (tabla1[a].inxtpy != x.typ)error(26);
		else{if (tabla1[a].elsize == 1)emit1(20, a);
			else emit1(21, a);
			v.typ = tabla1[a].eltyp;v.ref = tabla1[a].elref;}}
	if (palabra == "rbrack")obtener_palabra();
	else{error(12);
		if (palabra == "rparent")obtener_palabra();}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void llamar(int i){
	item x;int lastp, cp, k;
	emit1(18, i);
	lastp = tabla2[tabl[i].ref].lastpar;cp = i;
	if (palabra == "lparent"){do{
			obtener_palabra();
			if (cp >= lastp)error(39);
			else{cp = cp + 1;
				if (tabl[cp].normal){expresion(x);
					if (x.typ == tabl[cp].typ){if (x.ref != tabl[cp].ref)error(36);
						else{if (x.typ == "array")emit1(22, tabla2[x.ref].vsize);}}
					else{if ((x.typ == "number" || x.typ == "char") && tabl[cp].typ == "real"){emit1(26, 0);}
						else if (x.typ != "notyp")error(36);}}
				else{if (palabra != "ident")error(2);
					else{k = loc(id);
						obtener_palabra();
						if (k != 0){if (tabl[k].obj != "vvariable")error(37);
							x.typ = tabl[k].typ;x.ref = tabl[k].ref;
							if (tabl[k].normal)emit2(0, tabl[k].lev, tabl[k].adr);
							else emit2(1, tabl[k].lev, tabl[k].adr);
							if (palabra == "lbrack" || palabra == "lparent"){Selector(x);}
							if (x.typ != tabl[cp].typ || x.ref != tabl[cp].ref)error(36);}}}}
		} while (palabra == "comma");
		if (palabra == "rparent")obtener_palabra();
		else error(4);}
	if (cp < lastp) error(39);emit1(19, tabla2[tabl[i].ref].psize - 1);
	if (tabl[i].lev < level)emit2(3, tabl[i].lev, level);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Tresultado(string a, string b){
	if (a == "array" || b == "array"){error(33);return "notyp";}
	else{if (a == "notyp" || b == "notyp")return "notyp";
		else{if (a == "number"){if (b == "number" || b == "char")return "number";
				else{emit1(26, 1);return "real";}}
			else if (a == "char"){if (b == "number" || b == "char")return "char";
				else{emit1(26, 1);return "real";}}
			else{if (b == "number" || b == "char")emit1(26, 0);return "real";}}}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void declaracion_comp(){
	obtener_palabra();declaracion();
	while (proceso2(palabra) || palabra == "semicolon"){
		if (palabra == "semicolon")obtener_palabra();
		else error(14);declaracion();}
	if (palabra == "end.")obtener_palabra();
	else error(57);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void declaracion_if(){
	item x;int lc1, lc2;
	obtener_palabra();expresion(x);
	if (x.typ != "notyp" && x.typ != "bool")error(17);
	lc1 = lc;e(11);
	if (palabra == "then.")obtener_palabra();
	else{error(52);
		if (palabra == "do.")obtener_palabra();}
	declaracion();
	if (palabra == "else."){obtener_palabra();
		lc2 = lc;e(10);codigo[lc1].y = lc;declaracion();codigo[lc2].y = lc;}
	else codigo[lc1].y = lc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void declaracion_while(){
	item x;int lc1, lc2;
	obtener_palabra();
	lc1 = lc;expresion(x);
	if (x.typ != "notyp" && x.typ != "bool")error(17);
	lc2 = lc;e(11);
	if (palabra == "do.")obtener_palabra();
	else error(54);
	declaracion();emit1(10, lc1);codigo[lc2].y = lc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void declaracion_for(){
	string cvt;item x;
	int i, f, lc1, lc2;
	obtener_palabra();
	if (palabra == "ident"){i = loc(id);
		obtener_palabra();
		if (i == 0)cvt == "number";
		else{if (tabl[i].obj == "vvariable"){cvt = tabl[i].typ;
				if (!tabl[i].normal)error(37);
				else emit2(0, tabl[i].lev, tabl[i].adr);
				if (cvt != "notyp" && cvt != "number" && cvt != "char")error(18);}
			else{error(37);cvt = "number";}}}
	else salto(2);
	if (palabra == "becomes"){obtener_palabra();expresion(x);
		if (x.typ != cvt)error(19);}
	else salto(51);
	f = 14;
	if (palabra == "to." || palabra == "downto."){if (palabra == "downto.")f = 16;
		obtener_palabra();expresion(x);
		if (x.typ != cvt)error(19);}
	else salto(55);
	lc1 = lc;e(f);
	if (palabra == "do.")obtener_palabra();
	else error(54);
	lc2 = lc;
	declaracion();emit1(f + 1, lc2);codigo[lc1].y = lc;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void proceso(int n){
	int i, f;item  x, y;
	if (n == 1){if (palabra == "lparent"){
			do{obtener_palabra();
				if (palabra != "ident")error(2);
				else{i = loc(id);
					obtener_palabra();
					if (i != 0){if (tabl[i].obj != "vvariable")error(37);
						else{x.typ = tabl[i].typ;x.ref = tabl[i].ref;
							if (tabl[i].normal)f = 0;
							else f = 1;
							emit2(f, tabl[i].lev, tabl[i].adr);
							if (palabra == "lbrack" || palabra == "lparent")Selector(x);
							if (x.typ == "number" || x.typ == "real" || x.typ == "char" || x.typ == "notyp")emit1(27, ord(x.typ));
							else error(41);}}}
			} while (palabra == "comma");
			if (palabra == "rparent")obtener_palabra();else error(4);}}
	else if (n == 3){if (palabra == "lparent"){
			obtener_palabra();
			if (palabra == "str"){emit1(28, num_ent);obtener_palabra();
				if (palabra == "comma"){obtener_palabra();expresion(x);
					if (!proceso1(x.typ))error(41);
					emit1(29, ord(x.typ));}}
			else{
				expresion(x);
				if (!proceso1(x.typ)){error(41);}
				emit1(29, ord(x.typ));}}
		if (palabra == "rparent")obtener_palabra();
		else error(4);}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void enterids(){
	enter("", "vvariable", "notyp", 0);
	enter("real", "typel", "real", 1);
	enter("char", "typel", "char", 1);
	enter("integer", "typel", "number", 1);
	enter("read", "procedure", "notyp", 1);
	enter("write", "procedure", "notyp", 3);
	enter("", "procedure", "notyp", 0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void generador(){
	int temp = 0;
	cout << "lc\t" << "f\t" << "x\t" << "y\t" << endl;
	do{
		cout << temp << "\t" << codigo[temp].f << "\t" << codigo[temp].x << "\t" << codigo[temp].y << endl;
		temp += 1;
	} while (temp != lc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////