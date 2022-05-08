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
int puntos=0;
int seg1=0 ;//  seg1 para animaciones

void RutAtencionTeclado ()
{
	// INTERRUPCION → iniciar jeugo
	if(TeclaPulsada()==A && ESTADO == MENU){

		consoleClear();
		ESTADO=CORRER;
	}	



	// Por INTERRUPCION (realizar salto)
	if(TeclaPulsada()==ARRIBA && ESTADO == CORRER){

		consoleClear();
		ESTADO=SALTO;
	}	

	// salir
	if (TeclaPulsada()==B){
		consoleClear();
		ESTADO = CHOQUE;

		iprintf("\x1b[5;10H*GAME OVER*");
		iprintf("\x1b[10;3HPulsa R para reiniciar.");						
		iprintf("\x1b[13;3HPulsa A para volver al menu.");

		//ELIMINAR EN VER. FINAL
		iprintf("\x1b[21;1HESTADO= CHOQUE  ");
	}

}





/// ESTO ESTÁ MAL --> (hay que buscar la manera de usar un timer para las animaciones)
void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	static int seg3=0;

	static int segSalto=0;
	

	if (ESTADO!=ESPERA)
	{
		tick++; 

		// cada 5 ticks=1segundo (en teoria)
		if (tick == 5*2 && ESTADO == INTRO ){
		    tick=0;
			consoleClear();
		    ESTADO=MENU;

		}

		if (ESTADO == CORRER && tick == 5*1){

			animacionDino();
			//Suma +1 cada segundo al juego cuando se inicia
			seg3++;
		//	MostrarDino(1,10,131);
			iprintf("\x1b[17;6HTiempo:%d  ", seg3);
			puntos= 10*seg3;
			iprintf("\x1b[19;6HPuntos:%d  ", puntos);
		    tick=0;

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

			if (segSalto == 2)	ESTADO=CORRER;
			}

		}
				
}



void RutAtencionTempAnimaciones()
{
	seg1 ++;
	if (seg1 == 10 && ESTADO==CORRER)
	{
		MostrarDino(1,10,131);
		iprintf("\x1b[17;13H DINO ANI");

		animacionDino();
		seg1 = 0;
	}
}



//interrumpe 20ticks por seg
void EstablecerVectorInt()
{
// A COMPLETAR
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	irqSet(IRQ_TIMER0, RutAtencionTempo);
	irqSet(IRQ_TIMER1, RutAtencionTempAnimaciones);

}



