/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"

int ESTADO;
int seg3;
int puntos=0;

void RutAtencionTeclado ()
{



		if (ESTADO == MENU)
		{		
			if(TeclaPulsada()==A){

				consoleClear();
				ESTADO=CORRER;
			}	
		}

		if (ESTADO == CHOQUE)
		{		
			if(TeclaPulsada()==ARRIBA){

				consoleClear();
				ESTADO=MENU;
			}	

			if(TeclaPulsada()==R){

				consoleClear();
				ESTADO=CORRER;
			}	
		}

}




void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	static int segSalto=0;
	

if (ESTADO!=ESPERA)
{
	tick++; 
	if (tick == 5)
	{
		seg++;
		tick=0;

		if (ESTADO == INTRO)
		{
			seg3++;
			if (seg3 == 5)
			{
				ESTADO=MENU;
				consoleClear();
			}
		}

		if (ESTADO == CORRER)
		{
			//Suma +1 cada segundo al juego cuando se inicia
			seg3++;
			iprintf("\x1b[17;6HTiempo:%d  ", seg3);
			puntos= 10*seg3;
			iprintf("\x1b[19;6HPuntos:%d  ", puntos);


		}

		if (ESTADO == CHOQUE)
		{
			//Para el tiempo cuando choca contra algo
			PararTempo();
			iprintf("\x1b[17;6HTiempo:%d      ", seg3);
			seg3=0;
		}

		if (ESTADO == MENU) {

			//Para el tiempo y lo resetea para volver a activarlo cuando inicie el juego
			seg3=0;
			PararTempo();
		}

		if (ESTADO == SALTO) 
		{
			segSalto++;

			if (segSalto == 2)
			{
				ESTADO=CORRER;
			}

		}
				
	}
}
	
}

void EstablecerVectorInt()
{
// A COMPLETAR
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	irqSet(IRQ_TIMER0, RutAtencionTempo);
}



