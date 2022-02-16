#include<string>
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////
extern FILE* F;
//numero de palabras reservadas
const int norw = 18;
//tamaño de mi tabla de indentificadores
const int max1 = 1000,max2 = 300,max3 = 200,max4 = 6000,max5 = 200,max6 = 300,max7 = 32767;
//nro de digitos permitidos
const int namx = 14;
//longitud maxima de un identificador
const int al = 100;
//numero maximo de niveles de anidado
const int max9 = 70;
//cantidad de lineas de codigo que puede tener
const int max8 = 2000,tamlinea = 5000,limitlinea = 2000;
//capacidad de pila de ejecucion
const int tam_sta = 14500;
typedef char alfa[al];
//último carácter leído
extern char ch;
//tipo de lectura
extern string palabra;
//leer cadena
extern string id;
//leer entero
extern int num_ent;
//leer numero real
extern double num_real;
//nro de linea
extern int nro_l;
//Subíndice de tabla de cadenas
extern int sub_ind;
//longitud de la cuerda
extern int tam_c;
//variable de espacio libre
extern int espacio;
//contador de errores
extern int cont_error;
//Almacene el carácter de lectura
extern alfa temporalC;		
/////////////////////////////////////////////////////////////////////////////////////
extern string simbolo[32];
extern string te(char ch);
extern string plabra[18];
extern string plabra1[18];
/////////////////////////////////////////////////////////////////////////////////////
typedef struct{string typ;int ref;}item;
typedef struct{int f,x,y;}Orden;
/////////////////////////////////////////////////////////////////////////////////////
//Declaración de Lexer
extern void limpiar_token();
extern void obtener_token();
extern void obtener();
extern void obtener_palabra();
/////////////////////////////////////////////////////////////////////////////////////
//Tabla de símbolos
/////////////////////////////////////////////////////////////////////////////////////
typedef struct{string name,obj,typ;int link,lev,adr,ref;bool normal;}Tabla;
typedef struct{string inxtpy,eltyp;int elref,high,elsize, size;}Tabla1;
typedef struct{int last,lastpar,psize,vsize;}Tabla2;
typedef struct{string tabla3;}Tabla3;
typedef struct{string tp;int i;double r;}conrec;
typedef struct{int i;double r;bool b;char c;}stack;
/////////////////////////////////////////////////////////////////////////////////////