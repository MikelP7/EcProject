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
	int yDino;
	int xDino;
	int xCactus;

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



		//************INTRO************//

		if (ESTADO == INTRO) {

			// Escribe el Titulo y los creadores del juego en la pantalla de arriba	
			iprintf("\x1b[10;5HDino Run ");						
			iprintf("\x1b[13;5HBy: Telmo, Mikel & Sendoa ");
		
			visualizarIntro();

			// Los espacios despues de el nombre del estado sirven para evitar cualquier tipo
			// de error debido a la diferencia de longitud.
			//ELIMINAR EN VER. FINAL
			//iprintf("\x1b[21;1HESTADO= INTRO  ");		

		}




		//************MENU************//

		if (ESTADO == MENU) {

			visualizarMenu2();

			//Borra el sprite de choque para que no aparezca en el menú
			BorrarDino_choque(1,20,135);


			//Explica por pantalla los controles del juego.
			iprintf("\x1b[2;2HCONTROLES:   ");
			
			iprintf("\x1b[5;3HSaltar= Cruceta ARRIBA   ");
			iprintf("\x1b[7;3HAgacharse= Cruceta ABAJO   ");
			iprintf("\x1b[9;3HIzquierda= Cruceta IZQUIERDA   ");
			iprintf("\x1b[11;3HDerecha= Cruceta DERECHA   ");
			iprintf("\x1b[13;3HPLAY= Tocar PANTALLA   ");
			iprintf("\x1b[15;3HGAME OVER= 'B'   ");


			if(TactilTocada()==1){

				consoleClear();
				ESTADO=CORRER;
				//iprintf("\x1b[21;1HESTADO= CORRER  ");
			}
		
		}




		//************CORRER************//

		if (ESTADO == CORRER) {

			PonerEnMarchaTempo();
			//iprintf("\x1b[10;3HxDino: %d" xDino);						
			//iprintf("\x1b[13;3HyDino: %d" yDino);

			if (TeclaPulsada()==B){
				ESTADO = CHOQUE;

			iprintf("\x1b[5;10H*GAME OVER*");

			}

			if (TeclaPulsada()==ARRIBA)
			{
				ESTADO=SALTO;

			
			}


		}




		//************CHOQUE************//

		if (ESTADO == CHOQUE) {


		
		}




		//************SALTO************//

		if (ESTADO == SALTO)
		{
			if (TeclaPulsada()==B){
				ESTADO = CHOQUE;

				iprintf("\x1b[5;10H*GAME OVER*");

			}
			
			//ELIMINAR EN VER. FINAL
		}

	}
}
