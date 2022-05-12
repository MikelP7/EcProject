/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/


#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos
#include <nds/ndstypes.h> // para el VBLANK
//librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"

int tiempo;

void juego()
{	
	// definiciones de variables
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
	ConfigurarTemporizador0(Latch, Conf_Tempo);


	int Latch1=39322;
	int Conf_Tempo1=0x00C1;
	ConfigurarTemporizador1(Latch1, Conf_Tempo1);

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

			visualizarMenu();

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
		
		}


		//***CORRER***//
		if (ESTADO == CORRER) {
			visualizarFondo01();
	    		
		    //animacionDino();

			PonerEnMarchaTempo();
	//	MostrarDino(1,10,131);

	//	animacionDino();

			// agachar sprite
			if(TeclaPulsada()==ABAJO){

				consoleClear();
				ESTADO=AGACHADO;
				iprintf("\x1b[21;1HESTADO= AGACHADO  ");
			}	

		

		}


		//***CHOQUE***//
		if (ESTADO == CHOQUE) {

			//ELIMINAR EN VER. FINAL
			iprintf("\x1b[21;1HESTADO= CHOQUE   ");

/*
  		if(TeclaPulsada()==ARRIBA){
				consoleClear();
				ESTADO=MENU;
			}	
*/ 
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
			//saltar()
			// ESTADO=CORRER


			//ELIMINAR EN VER. FINAL
			iprintf("\x1b[21;1HESTADO= SALTO  ");
		}
	swiWaitForVBlank();
	}
}
