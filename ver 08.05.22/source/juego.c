/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/


#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"

int tiempo;

void juego()
{	
	// definiciones de variables
	int i=9;
	int tecla=0;
	int puntos=0;

	ESTADO=INTRO;
	

    // LLAMADAS A REALIZAR:

	// Configurar el teclado.
	int APorInt = 0x4001;
	ConfigurarTeclado(APorInt);

	// Configurar el temporizador.
	int Latch=39321;
	int Conf_Tempo=0x0002;
	ConfigurarTemporizador(Latch, Conf_Tempo);

	// Habilitar las interrupciones del teclado.
	HabilitarIntTeclado();

	// Habilitar las interrupciones del temporizador.
	PonerEnMarchaTempo();
	HabilitarIntTempo();

	// Establecer las rutinas de atención a interrupciones
	EstablecerVectorInt();
	



	//******************************************************************************//
	while(1)
	{	

		//***INTRO***//
		if (ESTADO == INTRO) {

			// Escribe el Titulo y los creadores del juego en la pantalla de arriba	
			iprintf("\x1b[10;5HDino Run ");						
			iprintf("\x1b[13;5HBy: Telmo, Mikel & Sendoa ");
		
			visualizarIntro();

			// Los espacios despues de el nombre del estado sirven para evitar cualquier tipo
			// de error debido a la diferencia de longitud.
			//ELIMINAR EN VER. FINAL
			iprintf("\x1b[21;1HESTADO= INTRO  ");		

		}


		//***MENU***//
		if (ESTADO == MENU) {

			visualizarMenu2();

			//Explica por pantalla los controles del juego.
			iprintf("\x1b[2;2HCONTROLES:   ");
			iprintf("\x1b[5;5HSaltar= Cruceta ARRIBA   ");
			iprintf("\x1b[7;5HAgacharse= Cruceta ABAJO   ");

			//ELIMINAR EN VER. FINAL
			iprintf("\x1b[21;1HESTADO= MENU   ");

			//ELIMINAR EN VER. FINAL
			if(TeclaPulsada()==A){

				consoleClear();
				ESTADO=CORRER;
				iprintf("\x1b[21;1HESTADO= CORRER  ");
			}	

			iprintf("\x1b[17;1HPANT_TOUCH= %d  ", TactilTocada());

			if(TactilTocada()==1){
				
				consoleClear();
				ESTADO=CORRER;
				iprintf("\x1b[21;1HESTADO= CORRER  ");
			}
		
		}


		//***CORRER***//
		if (ESTADO == CORRER) {

			PonerEnMarchaTempo();

			if (TeclaPulsada()==B){
				ESTADO = CHOQUE;

			iprintf("\x1b[5;10H*GAME OVER*");
			iprintf("\x1b[10;3HPulsa R para reiniciar.");						
			iprintf("\x1b[13;3HPulsa A para volver al menu.");

			//ELIMINAR EN VER. FINAL
			iprintf("\x1b[21;1HESTADO= CHOQUE  ");
			}

		}


		//***CHOQUE***//
		if (ESTADO == CHOQUE) {

			//ELIMINAR EN VER. FINAL
			iprintf("\x1b[21;1HESTADO= CHOQUE   ");

			if(TeclaPulsada()==ARRIBA){

				consoleClear();
				ESTADO=MENU;
			}	


			if(TeclaPulsada()==R){

				consoleClear();
				ESTADO=CORRER;

				//ELIMINAR EN VER. FINAL
				iprintf("\x1b[21;1HESTADO= CORRER   ");
			}	

		}


		//***SALTO***//
		if (ESTADO == SALTO)
		{

			//ELIMINAR EN VER. FINAL
			iprintf("\x1b[21;1HESTADO= SALTO  ");
		}

	}
}
