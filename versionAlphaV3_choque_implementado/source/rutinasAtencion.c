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
int seg4=0;
int puntos=0;

int xDino=20;	//Posicion Dino eje x
int yDino=131;	//Posicion Dino eje y

int xPajaro=255; //Posicion Pajaro eje x
int xArbol2=255; //Posicion ARBOL eje x

int yPajaro=120;
int yArbol2=131;
//int xArbol=255; //Posicion Pajaro eje x

int cambioFondo=0;  // esta variable indica el cambio de fondo
bool movIzda=false;
bool movDcha=false;

//
	// Habilitar las interrupciones del teclado.

	// Establecer las rutinas de atención a interrupciones
//	EstablecerVectorInt();
//

void RutAtencionTeclado()
{

	 // Solo me interrumpe si pongo TeclaPulsada()==A  .....

	if (TeclaPulsada()==DERECHA && (ESTADO == CORRER || ESTADO == SALTO || ESTADO == AGACHAR)){
	    printf("flecha dcha");
		movDcha= true;
	}
	if (TeclaPulsada()==IZQUIERDA && (ESTADO == CORRER || ESTADO == SALTO || ESTADO == AGACHAR)){	
		printf("flecha izda");
		movIzda= true;
	}

	//LEER: Lo mejor sería hacer por interrupcion tmb la tecla ARRIBA --> prueba si te funciona
	/*
	if (TeclaPulsada()==ARRIBA && ESTADO == CORRER) {
				printf("arriba pulsado");
				ESTADO=SALTO;			
			}
    */

}




void RutAtencionTempo()
{
	static int tick=0;  	//Tick para las animaciones (para Mostrar/Borrar) de todos los sprites
	static int tickTemp=0;	//Tick para el tiempo (usado para calcular puntuación)
	static int tickMov=0;	//Tick para el movimiento de los sprites enemigos y el fondo


	static int seg3=0;		//Tiempo dentro del juego

	static int segSalto=0;	//Tiempo del salto
	//static int segSalto=1;
	static bool paso_derecho=true;	//Paso derecho de movimiento Dino (sirve para animar la pierna dcha o izda. del Dino)
	static bool inicio=true;		//Inicio de movimiento Dino

	static bool paso_derechoAgachar=true;	// Paso derecho de movimiento Dino Agachado
	static bool inicioAgachar=true;		// Inicio de movimiento Dino Agachado

	static bool iniPajaro=true;        // Inicia la animacion del pajaro
	static bool paso_abajoPajaro=true; // Marca el aleteo del pajaro(alas arriba/abajo)




	/* Mediante un timer vamos a manejar todo el flujo y animaciones del juego*/
	if (ESTADO!=ESPERA)
	{
		tick++; 
		tickTemp++;
		tickMov++;
		


		// cada 5 ticks = 1segundo (en teoria)

		//Aquí esperaría 3 segundos en el estado INTRO (simula la pantalla de carga)
		if (tick == 5*3 && ESTADO == INTRO ){
		    tick=0;
		    tickTemp=0;
		    tickMov=0;

		    consoleClear();
		    ESTADO=MENU;
		}

		// EN ESTE APARTADO CONGIFURAREMOS LAS ANIMACIONES "generales" 
		/*
		 * Se comprueba si hay una partida en curso (ESTADO es Correr, Salto o Agachar) y se configura:
		 *   	 -> Movimiento de sprites enemigos: Arboles y Pajaros
		 *       -> Posicion lateral del Dino
		 *       -> Puntuación y tiempo
		 *       -> Fondos
		 */  

		// En ambos estados ocurrirán aciones similares, por tanto, podemos unificar el codigo usando un ||
		if (ESTADO == CORRER || ESTADO == AGACHAR) {

			/* Aquí se produce el movimiento lateral del Dino (controlado mediante las flechas izda/dcha) */
			while(movDcha && xDino <=40){
				xDino=xDino+5;
				movDcha=false;
			}

			while(movIzda && xDino >=20){
				xDino=xDino-5;
				movIzda=false;
			} 
	
		    /* Controla el tiempo real transcurrido y calcula la puntuación */
			if (tickTemp == 5) {

				//Suma +1 cada segundo al juego cuando se inicia
				seg3++;

				iprintf("\x1b[17;6HTiempo:%d  ", seg3);
				puntos= 10*seg3;
				iprintf("\x1b[19;6HPuntos:%d  ", puntos);


				//reinicia los ticks para entrar de nuevo al if
				tickTemp=0;
			}



			/* Movimiento de sprites enemigos y fondo */
			if (tickMov == 1) {
				
				cambioFondo++;
			
				xPajaro=xPajaro-5;
				xArbol2=xArbol2-10;

				if(xArbol2<=0) xArbol2=255;
			
				if(xPajaro<=0) xPajaro=255;
				


				//********MOVIMIENTO DE FONDO********//
				if(cambioFondo == 0){
					visualizarFondo00();
				}

				if(cambioFondo == 1){
					visualizarFondo01();
				}

				if(cambioFondo == 2){
					visualizarFondo02();
				}

				if(cambioFondo == 3){
					visualizarFondo03();
				}

				if(cambioFondo == 4){
					visualizarFondo04();
					cambioFondo=0;
				}				
				tickMov=0;
				
			}


			/* Controlamos las animaciones del juego*/
			if (tick == 2) {
			
				//SISTEMA COLISIONES
				//si dino corriendo (se la pega con el pajaro y con el cactus)
				if (ESTADO==CORRER){
					if ( ((xPajaro-xDino)<= 10 && (xPajaro-xDino)>= -10) ||  ((xArbol2-xDino)<= 10 && (xArbol2-xDino)>= -10) ) ESTADO=CHOQUE;
				}
				
				//si dino AGACHADO (se la pega con el cactus)
				if (ESTADO==AGACHAR){
					if ((xArbol2-xDino)<= 10 && (xArbol2-xDino)>= -10) ESTADO=CHOQUE;
				} 
				//si dino SALTO (se la pega con el pajaro)			
			

				//********ANIMACIÓN DE PAJARO********//
				if(iniPajaro){
					MostrarPajaro_alas_arriba(5,xPajaro,yPajaro);
					iniPajaro=false;
				}
				
				if (paso_abajoPajaro){ 
					BorrarPajaro_alas_arriba(5,xPajaro,yPajaro);

					MostrarPajaro_alas_abajo(6,xPajaro,yPajaro);		
					paso_abajoPajaro=false;

				}

				else{
					BorrarPajaro_alas_abajo(6,xPajaro,yPajaro);			
					MostrarPajaro_alas_arriba(5,xPajaro,yPajaro);		
					paso_abajoPajaro=true;

				}

				//arbol
				MostrarArbol_4(11,xArbol2,yArbol2);
				//MostrarArbol2(11,xArbol2,110)


				//********MOVIMIENTO DE DINO (animación CORRIENDO)********/
				if(ESTADO==CORRER){
					segSalto=0;
					if (inicio){
						MostrarDino_izda(4,xDino,yDino);
						inicio = false;
					}

					if (paso_derecho){ 
						MostrarDino(1,xDino,yDino);
						BorrarDino_izda(4,xDino,yDino);		

						MostrarDino_dcha(3,xDino,yDino);		
						BorrarDino(1,xDino,yDino);
						paso_derecho=false;
					}
			
					else{
						MostrarDino(1,xDino,yDino);
						BorrarDino_dcha(3,xDino,yDino);		
						MostrarDino_izda(4,xDino,yDino);		
						BorrarDino(1,xDino,yDino);
						paso_derecho=true;
					}

				}


				/********Animación AGACHAR del Dinosaurio********/

				if (ESTADO == AGACHAR)	{
					if (inicioAgachar){
						BorrarDino(1,xDino,yDino);
						BorrarDino_izda(4,xDino,yDino);
						BorrarDino_dcha(3,xDino,yDino);
						MostrarDino_agachar_izda(7,xDino,yDino);
						inicio = false;
					}

					if (paso_derechoAgachar){ 
						MostrarDino_agachar(8,xDino,yDino);
						BorrarDino_agachar_izda(7,xDino,yDino);	

						MostrarDino_agachar_dcha(9,xDino,yDino);		
						BorrarDino_agachar(8,xDino,yDino);
						paso_derechoAgachar=false;
					}

					else {
						MostrarDino_agachar(8,xDino,yDino);
						BorrarDino_agachar_dcha(9,xDino,yDino);	
						MostrarDino_agachar_izda(7,xDino,yDino);			
						BorrarDino_agachar(8,xDino,yDino);
						paso_derechoAgachar=true;

					}
					
					if (TeclaPulsada()!=ABAJO){
						BorrarDino_agachar_dcha(9,xDino,yDino);	
						BorrarDino_agachar(8,xDino,yDino);
						BorrarDino_agachar_izda(7,xDino,yDino);	


						//Para evitar bugs...
						MostrarDino(1,xDino,yDino);
						tick=2;
					
						ESTADO=CORRER;
					}
				}

				
				tick=0;
				}

		}
		 

	    
		//********SALTO********//
		if(ESTADO == SALTO) {

			// Borra los Dinosaurios con la pierna izda/dcha levantada
			BorrarDino_izda(4,xDino,yDino);
			BorrarDino_dcha(3,xDino,yDino);

			// El salto se muestra
			MostrarDino(1,xDino,yDino);
			segSalto++;


            // NOTA: Parte del código se repite entre todos los estados.

			/* Contamos el tiempo(segs) transcurrido para calcular la puntuación */
			if (tickTemp == 5) {
				//Suma +1 cada segundo al juego cuando se inicia
				seg3++;

				iprintf("\x1b[17;6HTiempo:%d  ", seg3);
				puntos= 10*seg3;
				iprintf("\x1b[19;6HPuntos:%d  ", puntos);

				//reinicia los ticks para entrar de nuevo al if
				tickTemp=0;
			}


			/** Aquí controlamos todo el movimiento de los sprites **/
			if (tickMov == 1) {
				cambioFondo++;
				xPajaro=xPajaro-5;
				xArbol2=xArbol2-7;

				if(xArbol2<=0) xArbol2=255;
				if(xPajaro<=0) xPajaro=255;

				tickMov=0;

				//********MOVIMIENTO DE FONDO********//
				if(cambioFondo == 0){
					visualizarFondo00();
				}

				if(cambioFondo == 1){
					visualizarFondo01();
				}

				if(cambioFondo == 2){
					visualizarFondo02();
				}

				if(cambioFondo == 3){
					visualizarFondo03();
				}

				if(cambioFondo == 4){
					visualizarFondo04();
					cambioFondo=0;
				}


				//********MOVIMIENTO DE DINO********//


				//Izquierda / Derecha

				/* Aquí se produce el movimiento lateral del Dino (controlado mediante las flechas izda/dcha) */
				while(movDcha && xDino <=40){
					xDino=xDino+5;
					movDcha=false;
				}

				while(movIzda && xDino >=20){
					xDino=xDino-5;
					movIzda=false;
				} 



				//Movimiento de salto
				if(segSalto == 1){
					yDino = yDino-10;
				}

				if(segSalto == 2){
					yDino = yDino-10;
				}


				if(segSalto == 3){
					yDino = yDino-10;
				}

				if(segSalto == 4){
					yDino = yDino-4;
				}

				if(segSalto == 5){
					yDino = yDino-4;
				}

				if(segSalto == 6){
					yDino = yDino+4;
				}

				if(segSalto == 7){
					yDino = yDino+4;
				}

				if(segSalto == 8){
					yDino = yDino+10;
				}

				if(segSalto == 9){
					yDino = yDino+10;
				}

				if(segSalto == 10){
					yDino = yDino+10;
				}

			}


			/** Aquí se realizan las ANIMACIONES, se muestran (o borran) los Sprites según convenga.  **/
			if (tick == 2) {
				
				/** Sistema de colisiones **/

				// Si el Dino está saltando se la pega con el pajaro
				if ( ((xPajaro-xDino)<= 10 && (xPajaro-xDino)>= -10)  || (((xArbol2-xDino)<= 8 && (xArbol2-xDino)>= -8) && ((yArbol2-yDino)<=8 && (yArbol2-yDino)>=-8))  ) ESTADO=CHOQUE;


				//********ANIMACION DE PAJARO********//

				if(iniPajaro){
					MostrarPajaro_alas_arriba(5,xPajaro,yPajaro);
					iniPajaro=false;
				}
				
				if (paso_abajoPajaro){ 
					BorrarPajaro_alas_arriba(5,xPajaro,yPajaro);

					MostrarPajaro_alas_abajo(6,xPajaro,yPajaro);		
					paso_abajoPajaro=false;

				}

				else{
					BorrarPajaro_alas_abajo(6,xPajaro,yPajaro);			
					MostrarPajaro_alas_arriba(5,xPajaro,yPajaro);		
					paso_abajoPajaro=true;

				}

				//*******ANIMACION DEL ARBOL*****************//
				MostrarArbol_4(11,xArbol2,yArbol2);

				tick=0;

			}

			// Termina el salto una vez realizado
			if(segSalto >= 10){
				ESTADO = CORRER;
				iprintf("\x1b[21;1HESTADO= CORRER  ");
			}

		}

		// CONFIGURAMOS LAS ANIMACIONES como choque y menu
		if (ESTADO == CHOQUE)
		{
			BorrarDino_agachar_dcha(9,xDino,yDino);	
			BorrarDino_agachar(8,xDino,yDino);
			BorrarDino_agachar_izda(7,xDino,yDino);	
			BorrarDino_izda(4,xDino,yDino);
			BorrarDino_dcha(3,xDino,yDino);
			BorrarDino(1,xDino,yDino);

			MostrarDino_choque(12,xDino,yDino);
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
	}
}

	



void EstablecerVectorInt()
{
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	irqSet(IRQ_TIMER0, RutAtencionTempo);
}

