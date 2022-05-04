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
	//definiciones de variables
	int i=9;
	int tecla=0;;

	ESTADO=MENU;
	
	//Escribe el Titulo y los creadores del juego en la pantalla de arriba	
	iprintf("\x1b[10;5HDino Run");						
	iprintf("\x1b[13;5HBy: Telmo, Mikel & Sendoa");
	visualizarIntro();



    // LLAMADAS A REALIZAR:

	// Configurar el teclado.
	int APorInt = 0x4001;
	ConfigurarTeclado(APorInt);

	// Configurar el temporizador.
	int Latch=65536 - ((1/5) * (33554432/256));
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
      /*******************************EN LA 1.ACTIVIDAD*****************************************/
		/*Si el estado es ESPERA: codificar aquí la encuesta del teclado, sacar por pantalla la tecla que se ha pulsado, y si se pulsa ta la tecla START cambiar de estado*/
		if(ESTADO == MENU){
			iprintf("\x1b[1;1HLa tecla que se ha pulsado es. Valor=%d",TeclaPulsada());
			if(TeclaPulsada()==ARRIBA){
				ESTADO = SALTO;
				visualizarPuerta();
				iprintf("\x1b[21;1HESTADO=%d" ,ESTADO);
			}
		}
		else if(ESTADO== MENU){
				MostrarRombo(2, 10, 10);
				iprintf("\x1b[21;1HESTADO=%d" ,ESTADO);
		}
		else{
			if(tiempo == 3){
				ESTADO=MENU;
				visualizarPuerta();
				tiempo = 0;
				BorrarRombo();
				BorrarRomboGrande();
				iprintf("\x1b[21;1HESTADO=%d" ,ESTADO);
			}

		}
	}
}
