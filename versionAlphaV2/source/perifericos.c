/*-------------------------------------
perifericos.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"


int tecla; //variable para guardar la tecla pulsada



int TeclaDetectada() 
{
	//Devuelve TRUE si detecta que se ha pulsado alguna tecla.
	if ((~TECLAS_DAT & 0x03ff)!=0) return 1;
	else return 0;
}

int TeclaPulsada() 
{
	//Devuelve el código de la tecla pulsada utilizando para ello las constantes definidas en 
	//definiciones.h:  A=0;B=1;SELECT=2;START=3;IZQUIERDA=4;DERECHA=5;
	//ARRIBA=6;ABAJO=7;R=8;L=9;

	if (~(TECLAS_DAT) & 0X0001) return A; //0
	if (~(TECLAS_DAT) & 0X0002) return B; //1		

	if (~(TECLAS_DAT) & 0X0004) return SELECT; //2
	if (~(TECLAS_DAT) & 0X0008) return START; //3

	if (~(TECLAS_DAT) & 0X0010) return DERECHA; //4
	if (~(TECLAS_DAT) & 0X0020) return IZQUIERDA; //5
	if (~(TECLAS_DAT) & 0X0040) return ARRIBA; //6
	if (~(TECLAS_DAT) & 0X0080) return ABAJO; //7

	if (~(TECLAS_DAT) & 0X0100) return R; //8
	if (~(TECLAS_DAT) & 0X0200) return L; //9


}


//Devuelve 1 si la pantalla ha sido tocada, sino devuelve 0.
int TactilTocada() {

	touchPosition pos_pantalla;

	touchRead(&pos_pantalla);
 	return !(pos_pantalla.px==0 && pos_pantalla.py==0);
} 


void ConfigurarTeclado(int Conf_Tec)
{
	//Configuración del teclado. Modificar su registro de control en base a los bits
	//activados en el parametro Conf_Tec
	TECLAS_CNT |= Conf_Tec;
}


void ConfigurarTemporizador(int Latch, int Conf_Tempo)
{
	//Configuración del temporizador. El latch es el valor del registro de datos del temporizador
	//Activar los bits del registro de control necesarios en base a los bits activados en el parámetro Conf_Tempo
	TIMER0_DAT = Latch;
	TIMER0_CNT |= Conf_Tempo;
	
}


void HabilitarIntTeclado()
{
	//Habilitar las interrupciones del teclado
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;

	IE |= 0x1000;
	IME=1;
}


void InhibirIntTeclado()
{
	//Deshabilitar las interrupciones del teclado
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;

	IE &=0xefff;
	IME=1;
}  


void HabilitarIntTempo()
{
	//Habilitar las interrupciones del temporizador (timer0)
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;

	IE |=0x00000008;
	IME=1;
}


void InhibirIntTempo()
{
	//Deshabilitar las interrupciones del temporizado (timer0)
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;

	IE &= 0xfffffff7;
	IME=1;

}

void PonerEnMarchaTempo()
{
	TIMER0_CNT |= 0x00C0;
}

void PararTempo()
{
	TIMER0_CNT &= 0xff7f;
}


/* Codigo copiado de Internet para limpiar pantalla de arriba
void ClearScreen()
{
    int x;
    for ( x = 0; x < 10; x++ ) 
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
}

*/
