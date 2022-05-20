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

	HabilitarIntTeclado();


		//************INTRO************//
		if (ESTADO == INTRO) {

			// Escribe el Titulo y los creadores del juego en la pantalla de arriba	
			iprintf("\x1b[10;5HDino Run ");						
			iprintf("\x1b[13;5HBy: Telmo, Mikel & Sendoa ");
		
			visualizarIntro();

		}


		//************MENU************//
		if (ESTADO == MENU) {

			visualizarMenu2();  // Visualiza el menú de "Ayuda" (Tutorial) para jugar
		

			//Explica por pantalla los controles del juego.
			iprintf("\x1b[2;2HCONTROLES:   ");
			
			iprintf("\x1b[5;3HSaltar= Cruceta ARRIBA   ");
			iprintf("\x1b[7;3HAgacharse= Cruceta ABAJO   ");
			iprintf("\x1b[9;3HIzquierda= Cruceta IZQUIERDA   ");
			iprintf("\x1b[11;3HDerecha= Cruceta DERECHA   ");
			iprintf("\x1b[13;3HPLAY= Tocar PANTALLA   ");
			iprintf("\x1b[15;3HTERMINAR PARTIDA= 'A'   ");


			// Si se pulsa cualquier parte del Táctil comienza la partida (tactil por encuesta)
			if(TactilTocada()==1){
				consoleClear();
				ESTADO=CORRER;
			}
		
		}




		//************CORRER************//   (Estado en el que corre normal el dinosaurio)
		if (ESTADO == CORRER) {

			PonerEnMarchaTempo();
			
			// Tecla cruceta abajo (arrow down) por encuesta --> Agacha el dino
			if (TeclaPulsada()==ABAJO) {
				ESTADO=AGACHAR;			
			}

			// Tecla cruceta arriba (arrow up) por encuesta --> El dino salta
			if (TeclaPulsada()==ARRIBA) {
				ESTADO=SALTO;			
			}	

		}


		//************CHOQUE************//
		if (ESTADO == CHOQUE) {
			iprintf("\x1b[5;10H*GAME OVER*");
	
		}

		


		// Vblank sincroniza los frames
		swiWaitForVBlank();
	}
}