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





/// ESTO ESTÁ MAL --> (hay que buscar la manera de usar un timer para las animaciones)  //restauralo a la version de tu proyecto si quieres
//(me han comentado que LAS INTERRUPCIONES funcionan MAL en MelonDS u otros); mejor usar No$GBA...
void RutAtencionTiempo()
{
	static int tick=0;
	static int seg=0;
	static int seg3=0;

	static int segSalto=0;
	static bool paso_derecho=true;
	
	static bool inicio=true;


	if (ESTADO!=ESPERA)
	{
		tick++; 

		// cada 5 ticks=1segundo (en teoria)
		if (tick == 5*1 && ESTADO == INTRO ){
		    tick=0;
			consoleClear();
		    ESTADO=MENU;
		}

		if (ESTADO == CORRER && tick == 2) {

			//animacionDino();
			//Suma +1 cada segundo al juego cuando se inicia
			seg3++;
			if (inicio){
				MostrarDino_izda(4,10,131);
				inicio = false;
			}

			if (paso_derecho){ 
				MostrarDino(1,10,131);
				BorrarDino_izda(4,10,131);		

				MostrarDino_dcha(3,10,131);		
				BorrarDino(1,10,131);
				paso_derecho=false;
		

			} else{
				MostrarDino(1,10,131);
				BorrarDino_dcha(3,10,131);		
				MostrarDino_izda(4,10,131);		
				BorrarDino(1,10,131);
				paso_derecho=true;



			}
		 

			MostrarPajaro_alas_abajo(10,50,100);
			MostrarPajaro_alas_abajo(11,100,100);
			iprintf("\x1b[17;6HTiempo:%d  ", seg3);
			puntos= 10*seg3;
			iprintf("\x1b[19;6HPuntos:%d  ", puntos);
		    tick=0;

		}

		

	


	

		if (ESTADO == CHOQUE)
		{
			//Para el tiempo cuando choca contra algo
			PararTiempo();
			iprintf("\x1b[17;6HTiempo:%d      ", seg3);
			seg3=0;
		}

		if (ESTADO == MENU) {
			//Para el tiempo y lo resetea para volver a activarlo cuando inicie el juego
			seg3=0;
			PararTiempo();
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
	if (seg1 == 1 && ESTADO==CORRER)
	{
		//MostrarDino(3,70,131);
		iprintf("\x1b[17;13H DINO ANI");

		//animacionDino();
		seg1 = 0;
	}
}



//interrumpe 20ticks por seg
void EstablecerVectorInt()
{
// A COMPLETAR
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	irqSet(IRQ_TIMER0, RutAtencionTiempo);
	irqSet(IRQ_TIMER1, RutAtencionTempAnimaciones);

}



