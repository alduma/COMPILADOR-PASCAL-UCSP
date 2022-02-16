#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include"define.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern int lc, t, a, b, c2;
extern int level;
extern void enterids();
extern int display[max9];
extern Tabla2 tabla2[max3];
extern void Block(bool isfun);
extern void error(int n);
extern void e(int fct);
extern void generador();
extern void interprete();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[]){
	char file[100];
	cout << "ingresa el nombre del archivo:";
	cin >> file;
	fopen_s(&F, file, "r+");
	nro_l = 1;lc = 0;cont_error = 0;t = -1;a = 0;b = 1;sub_ind = 0;c2 = 0;
	display[0] = 1;
	level = 1;
	enterids();
	tabla2[1].last = t;
	tabla2[1].lastpar = 1;
	tabla2[1].psize = 0;
	tabla2[1].vsize = 0;
	obtener_palabra();
	Block(false);
	if (palabra != "period")
		error(60);
	e(31);
	//Generat();
	cout << "------------------------------------" << endl;
	cout << "compilacion completa" << endl;
	cout << "------------------------------------" << endl;
	if (cont_error == 0){
		
		interprete();
		cout << endl;
		cout << "------------------------------------" << endl;
		cout << "\n" << "Interprete completo" << endl;
		
	}
	else
		cout << "\n" << "el programa tiene errores" << endl;
	fclose(F);
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
