#include <string>
#include<iostream>
#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void obtener_palabra();
extern string palabra;
extern int nro_l;
int cont_error = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string lista_de_errores[100] ={
	"0.Por favor, compruebe si el identificador está definido",
	"1.Compruebe si hay definiciones de identificadores duplicados.",
	"2.Compruebe si faltan identificadores.",
	"3.El programa debe comenzar con el programa",
	"4.Compruebe si falta ')'",
	"5.Compruebe si falta ':', estos dos puntos deben estar presentes al especificar el tipo",
	"6.Símbolo ilegal, la compilación omitirá la lectura de este símbolo y algunos símbolos posteriores.",
	"7.debe comenzar con un identificador o var",
	"8.Compruebe si falta 'of'",
	"9.Compruebe si falta '('",
	"10.Las definiciones de tipo deben comenzar con un identificador o una matriz",
	"11.Compruebe si falta '['",
	"12.Compruebe si falta ']'",
	"13.Compruebe si falta '.'",
	"14.Compruebe si falta ';'",
	"15.El resultado de la función debe ser de tipo entero, real o char",
	"16.Verifique si falta '=', ':=' solo se puede usar en declaraciones de asignación, no en declaraciones",
	"17.La expresión después de (if,while) o (until) debe ser de tipo (booleano)",
	"18.La variable de bucle después de (for) solo puede ser de tipo (integer) o (char)",
	"19.La expresión de valor inicial o final en la instrucción (for) debe ser del mismo tipo que la variable de bucle",
	"20.El encabezado del programa no contiene parámetros (output) o (input)",
	"21.El número es demasiado grande, como máximo 14 dígitos",
	"22.El final del programa es '.', marque el correspondiente (begin) y (end)",
	"23.La expresión que sigue a (case) debe ser (integer) o (char) (para este último, se recomienda una declaración if)",
	"24.símbolo inválido",
	"25.En definiciones constantes, el signo igual debe ir seguido de una constante o identificador constante",
	"26.El tipo de expresión de subíndice debe ser el mismo que el tipo de subíndice en la especificación de matriz",
	"27.En una especificación de matriz, el límite inferior no puede exceder el límite superior y deben ser del mismo tipo .",
	"28.no hay tal matriz",
	"29.Compruebe si faltan identificadores de tipo",
	"30.El tipo no está definido (no se permiten tipos de definición recursiva)",
	"31.no hay tal registro",
	"32.(not,and,or) los operandos deben ser de tipo (booleano)",
	"33.El tipo de expresión aritmética no es válido.",
	"34.Los operandos de las operaciones (div) y (mod) deben ser de tipo (entero)",
	"35.Los tipos de objetos que se comparan deben ser los mismos. Los arreglos solo pueden comparar sus elementos.",
	"36.El tipo del parámetro actual y el parámetro correspondiente será el mismo.",
	"37.debería ser una variable",
	"38.La cadena tiene al menos un carácter",
	"39.El número de parámetros reales no es igual al número de parámetros formales",
	"40.sin dígitos después del punto decimal",
	"41.Tipo de argumento incorrecto para (read) o (write)",
	"42.La expresión debe ser real.",
	"43.El ancho de campo de la declaración (write) debe ser un número entero",
	"44.Los identificadores de tipo o procedimiento no pueden aparecer en expresiones",
	"45.Debe ser un identificador de variable o procedimiento/función",
	"46.La variable a asignar en una declaración de asignación debe ser del mismo tipo que la expresión.",
	"47.Una etiqueta en una declaración (case) debe ser una constante del mismo tipo que la expresión de la cláusula (case)",
	"48.El tipo de expresión de argumento para esta función estándar es incorrecto",
	"49.desbordamiento de memoria",
	"50.Compruebe si faltan constantes",
	"51.Compruebe si falta (:=)",
	"52.Compruebe si (then) falta en la instrucción (if)",
	"53.Compruebe si falta (until)",
	"54.Por favor, compruebe si falta el (do) en la declaración (para)",
	"55.Por favor marque si (to) o (downto) faltan en la declaración (for)",
	"56.Compruebe si falta (begin)",
	"57.Compruebe si falta (end)",
	"58.Los factores deben comenzar con un identificador, constante o ')'",
	"59.Compruebe si falta “'” ",
	"60.El programa debe terminar con '.'",
	"61.Las operaciones directas sobre caracteres no están permitidas en las operaciones.",
	"62.Compruebe si la declaración constante es (var,produce,function,begin)",
	"63.Las declaraciones de variables deben terminar con (;)",
	"64.Los parámetros entre paréntesis en declaraciones de procedimientos y funciones no pueden estar vacíos"
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string	lista_de_mensajes[10] ={"","1.identificador","2.procedimiento","3.nroreal","4.arreglo","5.nivel","6.codigo","7.letras"};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void salto(int n){
	while (palabra != "semicolon")obtener_palabra();
	cout << "salto : " << lista_de_errores[n] << " en " << nro_l << endl;obtener_palabra();}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void error(int n){cout << "error: " << lista_de_errores[n] << " en " << nro_l << endl;cont_error += 1;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mal(int n){cout << " mal :" << lista_de_mensajes[n] << " en " << nro_l << endl;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tpuntoycoma(){
	if (palabra == "semicolon")obtener_palabra();
	else{error(14);if (palabra == "camma" || palabra == "colon")obtener_palabra();}}
