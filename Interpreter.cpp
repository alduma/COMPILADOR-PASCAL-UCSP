#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include"define.h"
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern Tabla1 tabla1[max2];
extern Tabla2 tabla2[max3];
extern Tabla3 tabla3[max4];
extern Orden codigo[max8];
extern Tabla tabl[max1];
extern double constantee[max5];
Orden ir;
int tr,tt,bb,hh, hh1, hh2,aa4, aa3, aa2, aa1;
//varias banderas de mensajes de error
string ps;
int FF[4];
int tabla_Ver[max9];
stack s[tam_sta];
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void F1(){
	if (ir.f == 0){tt = tt + 1;
		if (tt > tam_sta)ps = "desbordamiento";
		else s[tt].i = tabla_Ver[ir.x] + ir.y;}
	else if (ir.f == 1){tt = tt + 1;
		if (tt > tam_sta)ps = "desbordamiento";
		else s[tt] = s[tabla_Ver[ir.x] + ir.y];}
	else if (ir.f == 2){tt = tt + 1;
		if (tt > tam_sta)ps = "desbordamiento";
		else s[tt] = s[s[tabla_Ver[ir.x] + ir.y].i];}
	else if (ir.f == 3){hh = ir.y,hh1 = ir.x,hh2 = bb;
		do{tabla_Ver[hh] = hh2,hh = hh - 1,hh2 = s[hh2 + 2].i;}
		while (hh != hh1);
	}
	else if (ir.f == 8){cout << "no esperado : 8" << endl;}
	else if (ir.f == 9){s[tt].i = s[tt].i + ir.y;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void F2(){
	int  hh2, h4;
	if (ir.f == 10){tr = ir.y;}
	else if (ir.f == 11){
		if (!s[tt].b)tr = ir.y;tt = tt - 1;}
	else if (ir.f == 12){
		hh = s[tt].i,tt = tt - 1,hh1 = ir.y,hh2 = 0;
		do{if (codigo[hh1].f != 13){hh2 = 1,ps = "indefinido";}
			else{if (codigo[hh1].y == hh){hh2 = 1,tr = codigo[hh1 + 1].y;}
				else hh1 = hh1 + 2;}
		} while (hh2 == 0);}
	else if (ir.f == 14){hh = s[tt - 1].i;
		if (hh <= s[tt].i){s[s[tt - 2].i].i = hh;}
		else{tt = tt - 3,tr = ir.y;}}
	else if (ir.f == 15){
		hh1 = s[tt - 2].i;hh = s[hh1].i + 1;
		if (hh <= s[tt].i){s[hh1].i = hh;tr = ir.y;}
		else tt = tt - 3;}
	else if (ir.f == 16){
		hh = s[tt - 1].i;
		if (hh >= s[tt].i)s[s[tt - 2].i].i = hh;
		else{tr = ir.y;tt = tt - 3;}}
	else if (ir.f == 17){
		hh1 = s[tt - 2].i;hh = s[hh1].i - 1;
		if (hh >= s[tt].i){s[hh1].i = hh;tr = ir.y;}
		else tt = tt - 3;}
	else if (ir.f == 18){hh = tabla2[tabl[ir.y].ref].vsize;
		if ((tt + hh) > tam_sta)ps = "desbordamiento";
		else{tt = tt + 5;s[tt - 1].i = hh - 1;s[tt].i = ir.y;}}
	else if (ir.f == 19){
		hh = tt - ir.y;hh1 = s[hh + 4].i;hh2 = tabl[hh1].lev;
		tabla_Ver[hh2 + 1] = hh;h4 = s[hh + 3].i + hh;
		s[hh + 1].i = tr;s[hh + 2].i = tabla_Ver[hh2];s[hh + 3].i = bb;
		for (hh2 = tt + 1; hh2 <= h4; hh2++)s[hh2].i = 0;
		bb = hh;tt = h4;tr = tabl[hh1].adr;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void F3(){
	if (ir.f == 20){hh = ir.y;hh1 = 0;hh2 = s[tt].i;
		if (hh2 < hh1)ps = "invalido";
		else{if (hh2 > tabla1[hh].high)ps = "invalido";
			else{tt = tt - 1;s[tt].i = s[tt].i + (hh2 - hh1);}}}
	else if (ir.f == 21){hh = ir.y;hh1 = 0;hh2 = s[tt].i;
		if (hh2 < hh1)ps = "invalido";
		else{if (hh2 > tabla1[hh].high)ps = "invalido";
			else{tt = tt - 1;s[tt].i = s[tt].i + (hh2 - hh1) * tabla1[hh].elsize;}}}
	else if (ir.f == 22){hh = s[tt].i;tt = tt - 1;hh1 = ir.y + tt;
		if (hh1 > tam_sta)ps = "desbordamiento";
		else{while (tt < hh1){tt = tt + 1;s[tt] = s[hh];hh = hh + 1;}}}
	else if (ir.f == 23){hh = s[tt - 1].i;hh1 = s[tt].i;hh2 = hh + ir.y;
		while (hh < hh2){s[hh] = s[hh1];hh = hh + 1;hh1 = hh1 + 1;}
		tt = tt - 2;
	}
	else if (ir.f == 24){tt = tt + 1;
		if (tt > tam_sta)ps = "desbordamiento";
		else s[tt].i = ir.y;}
	else if (ir.f == 25){tt = tt + 1;
		if (tt > tam_sta)ps = "desbordamiento";
		else s[tt].r = constantee[ir.y];}
	else if (ir.f == 26){hh = tt - ir.y;s[hh].r = s[hh].i;}
	else if (ir.f == 27){
		if (ir.y == 1)cin >> s[s[tt].i].i;
		else if (ir.y == 2)cin >> s[s[tt].i].r;
		else if (ir.y == 4){
			char ch;
			cin >> ch;
			s[s[tt].i].c = ch;s[s[tt].i].i = ch;}
		tt = tt - 1;}
	else if (ir.f == 28){
		hh1 = ir.y;aa1 = aa1 + tabla3[hh1].tabla3.length();
		if (aa1 > tamlinea)ps = "muylargo";
		cout << tabla3[hh1].tabla3;
		hh1 = tabla3[hh1].tabla3.length();}
	else if (ir.f == 29){aa1 = aa1 + FF[ir.y];
		if (aa1 > tamlinea)ps = "muylargo";
		else{if (ir.y == 1)cout << s[tt].i;
			else if (ir.y == 2)cout << s[tt].r;
			else if (ir.y == 3){if (s[tt].b)cout << "true";
				else cout << "false";}
			else if (ir.y == 4){cout << (char)s[tt].i;}}
		tt = tt - 1;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void F4(){
	if (ir.f == 30){
		aa1 = aa1 + s[tt].i;
		if (aa1 > tamlinea)ps = "muylargo";
		else{if (ir.y == 1)cout << s[tt - 1].i;
			else if (ir.y == 2)cout << s[tt - 1].r;
			else if (ir.y == 3)cout << "no esperado : 30" << endl;
		}
		tt = tt - 2;}
	else if (ir.f == 31){ps = "fin";}
	else if (ir.f == 32){tt = bb - 1;tr = s[bb + 1].i;bb = s[bb + 3].i;}
	else if (ir.f == 33){tt = bb;tr = s[bb + 1].i;bb = s[bb + 3].i;}
	else if (ir.f == 34){s[tt] = s[s[tt].i];}
	else if (ir.f == 35){s[tt].b = !s[tt].b;}
	else if (ir.f == 36){s[tt].i = -s[tt].i;}
	else if (ir.f == 37){aa1 = aa1 + s[tt - 1].i;
		if (aa1 > tamlinea)ps = "muylargo";
		else cout << s[tt - 2].r;tt = tt - 3;
	}
	else if (ir.f == 38){s[s[tt - 1].i] = s[tt];tt = tt - 2;}
	else if (ir.f == 39){tt = tt - 1;s[tt].b = (s[tt].r == s[tt + 1].r);}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void F5(){
	if (ir.f == 40){tt = tt - 1;s[tt].b = (s[tt].r != s[tt + 1].r);}
	else if (ir.f == 41){tt = tt - 1;s[tt].b = (s[tt].r < s[tt + 1].r);}
	else if (ir.f == 42){tt = tt - 1;s[tt].b = (s[tt].r <= s[tt + 1].r);}
	else if (ir.f == 43){tt = tt - 1;s[tt].b = (s[tt].r > s[tt + 1].r);}
	else if (ir.f == 44){tt = tt - 1;s[tt].b = (s[tt].r >= s[tt + 1].r);}
	else if (ir.f == 45){tt = tt - 1;s[tt].b = (s[tt].i == s[tt + 1].i);}
	else if (ir.f == 46){tt = tt - 1;s[tt].b = (s[tt].i != s[tt + 1].i);}
	else if (ir.f == 47){tt = tt - 1;s[tt].b = (s[tt].i < s[tt + 1].i);}
	else if (ir.f == 48){tt = tt - 1;s[tt].b = (s[tt].i <= s[tt + 1].i);}
	else if (ir.f == 49){tt = tt - 1;s[tt].b = s[tt].i > s[tt + 1].i;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void F6(){
	if (ir.f == 50){tt = tt - 1;s[tt].b = s[tt].i >= s[tt + 1].i;}
	else if (ir.f == 51){tt = tt - 1;s[tt].b = s[tt].b || s[tt + 1].b;}
	else if (ir.f == 52){tt = tt - 1;s[tt].i = s[tt].i + s[tt + 1].i;}
	else if (ir.f == 53){tt = tt - 1;s[tt].i = s[tt].i - s[tt + 1].i;}
	else if (ir.f == 54){tt = tt - 1;s[tt].r = s[tt].r + s[tt + 1].r;}
	else if (ir.f == 55){tt = tt - 1;s[tt].r = s[tt].r - s[tt + 1].r;}
	else if (ir.f == 56){tt = tt - 1;s[tt].b = s[tt].b && s[tt + 1].b;}
	else if (ir.f == 57){tt = tt - 1;s[tt].i = s[tt].i * s[tt + 1].i;}
	else if (ir.f == 58){tt = tt - 1;
		if (s[tt + 1].i == 0)ps = "indefinido";
		else s[tt].i = s[tt].i / s[tt + 1].i;}
	else if (ir.f == 59){tt = tt - 1;
		if (s[tt + 1].r == 0)ps = "indefinido";
		else s[tt].i = s[tt].i - (s[tt].i / s[tt + 1].i) * s[tt].i;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void F7(){
	if (ir.f == 60){tt = tt - 1;s[tt].r = s[tt].r * s[tt + 1].r;}
	else if (ir.f == 61){tt = tt - 1;s[tt].r = s[tt].r / s[tt + 1].r;}
	else if (ir.f == 62){cout << "no esperado : 62" << endl;}
	else if (ir.f == 63){
		cout << endl;
		aa4 = aa4 + 1;aa1 = 0;
		if (aa4 > limitlinea)ps = "demasiado";}
	else if (ir.f == 64){tt = tt - 1;s[tt].b = (s[tt].c == s[tt + 1].c);}
	if (ir.f == 65){tt = tt - 1;s[tt].b = (s[tt].c != s[tt + 1].c);}
	else if (ir.f == 66){tt = tt - 1;s[tt].b = (s[tt].c < s[tt + 1].c);}
	else if (ir.f == 67){tt = tt - 1;s[tt].b = (s[tt].c <= s[tt + 1].c);}
	else if (ir.f == 68){tt = tt - 1;s[tt].b = (s[tt].c > s[tt + 1].c);}
	else if (ir.f == 69){tt = tt - 1;s[tt].b = (s[tt].c >= s[tt + 1].c);}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void F8(){
	if (ir.f == 70){tt = tt + 1;
		if (tt > tam_sta)ps = "desbordamiento";
		else{s[tt].i = ir.y;s[tt].c = (char)ir.y;}}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void interprete(){
	s[1].i = 0;s[2].i = 0;s[3].i = -1;s[4].i = tabla2[1].last;
	tabla_Ver[0] = 0;tabla_Ver[1] = 0;
	tt = tabla2[2].vsize - 1;bb = 0;tr = tabl[s[4].i].adr;
	aa4 = 0;aa3 = 0;aa1 = 0;ps = "bien";
	FF[1] = 10;FF[2] = 22;FF[3] = 10;FF[4] = 1;
	do{
		ir = codigo[tr];
		tr = tr + 1;
		aa3 = aa3 + 1;
		switch (ir.f / 10){
		case 0:F1();
		case 1:F2();
		case 2:F3();
		case 3:F4();
		case 4:F5();
		case 5:F6();
		case 6:F7();
		case 7:F8();
		}
	} while (ps == "bien");
	if (ps != "fin"){
		cout << "detenerse en : " << tr << " , por : " << ps;
		getchar();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////