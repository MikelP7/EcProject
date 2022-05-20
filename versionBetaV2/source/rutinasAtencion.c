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

int xDino=20;	//Posicion Dino eje x
int yDino=131;	//Posicion Dino eje y

int xPajaro=255; //Posicion Pajaro eje x
int yPajaro=120;

int xCactus2=255; //Posicion ARBOL(cactus) eje x
int yCactus2=131;

int xCactus=255; //Posicion ARBOL(cactus) eje x
int yCactus=131;



int cambioFondo=0;  // esta variable indica el cambio de fondo
bool movIzda=false;
bool movDcha=false;


void RutAtencionTeclado()
{
	// Tecla A por interrupción --> (Si se pulsa finaliza la partida)
	if (TeclaPulsada()==A && (ESTADO == CORRER || ESTADO == SALTO || ESTADO == AGACHAR)){
	//	printf("fin");
	   	ESTADO=CHOQUE;
	}

	/* NOTA:  
	 *  Por conveniencia las interrupciones de las teclas ARRIBA/ABAJO (crucetas) se han realizado en la RutAtencionTempo(),
	 *   ya que estas no causan un cambio de ESTADO era más sencillo implementarlo directamente en la RutAtencionTempo() en las animaciones.
	 */

}




void RutAtencionTempo()
{
	static int tick=0;  	//Tick para las animaciones (para Mostrar/Borrar) de todos los sprites
	static int tickTemp=0;	//Tick para el tiempo (usado para calcular puntuación)
	static int tickMov=0;	//Tick para el movimiento de los sprites enemigos y el fondo


	static int seg3=0;		//Tiempo dentro del juego

	static int segSalto=0;	//Tiempo del salto
	static int segPajaro=0;	//Tiempo de aparicion del pajaro
	static int segCactus2=0; //Tiempo de aparicion del cactus


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
		


		// cada 5 ticks = 1segundo 

		//Aquí esperaría 3 segundos en el estado INTRO (simula la pantalla de carga)
		if (tick == 5*3 && ESTADO == INTRO ){
		    tick=0;
		    tickTemp=0;
		    tickMov=0;

		    consoleClear();
		    ESTADO=MENU;
		}


		// EN ESTE APARTADO CONGIFURAREMOS LAS ANIMACIONES y controlaremos el MOVIMIENTO de los Sprites del juego.
		/*
		 * Se comprobará el ESTADO del juego y CONFIGURA:
		 *       -> Puntuación y tiempo		 
		 *       -> Fondos
		 *		 -> Movimiento de sprites enemigos: Arboles y Pajaros
	 	 *       -> Posicion lateral del Dino (tecla DCHA/IZDA por interrupción)
		 *       -> Sistema de colisiones (choque=game over)
		 *       -> Animaciones de Sprites (Mostrar/Borrar en pantalla)
		 *  
		 */  



		/* ***CORRER/AGACHAR*** */

		// En ambos estados (CORRER y AGACHAR) ocurrirán aciones similares -> unificamos el codigo usando un || 
		if (ESTADO == CORRER || ESTADO == AGACHAR) {
			MostrarArbol_4(11,xCactus,yCactus);  // Muestra el Arbol4(cactus) en pantalla

			MostrarArbol_2(12,xCactus2,yCactus2);  // Muestra el Arbol4(cactus) en pantalla

		
		    /* Controla el tiempo real transcurrido y calcula la puntuación */
			if (tickTemp == 5) {

				//Suma +1 cada segundo al juego cuando se inicia
				seg3++;

				iprintf("\x1b[17;6HTiempo:%d  ", seg3);
				puntos= 10*seg3;
				iprintf("\x1b[19;6HPuntos:%d  ", puntos);
					
		  		//Cooldown del pajaro para que salga de nuevo (Cooldown es el tiempo de espera)
				if(xPajaro <= 0){
					BorrarPajaro_alas_abajo(6,xPajaro,yPajaro);
					BorrarPajaro_alas_arriba(5,xPajaro,yPajaro);
					segPajaro++;
					xPajaro=-20;

					if (segPajaro == 5){
						segPajaro=0;
						xPajaro=255;
						MostrarPajaro_alas_arriba(5,xPajaro,yPajaro);
					}	
				}


				//Cooldown del cactus2 para que salga de nuevo
				if(seg3 == 10){
					MostrarArbol_2(12,xCactus2,yCactus2);
				}

				if(xCactus2 <= 0){
					BorrarArbol_2(12,xCactus2,yCactus2);
					segCactus2++;
					xCactus2=-30;

					if(segCactus2 == 15){
						segCactus2=0;
						xCactus2=255;
						MostrarArbol_2(12,xCactus2,yCactus2);
					}	
				}


				//reinicia los ticks para entrar de nuevo al if
				tickTemp=0;
			}



			/* Movimiento de sprites enemigos y fondo */
			if (tickMov == 1) {
				
				cambioFondo++; //actualiza el fondo

				// Actualiza la posición de los Sprites enemigos
				if(seg3 >= 5) xPajaro=xPajaro-6;
		
				xCactus=xCactus-7;
				if(seg3 >= 3) xCactus2=xCactus2-5;
				
				//Comprueba si el Cactus (MuestraArbol_4, con id 11) se sale de la pantalla
				if (xCactus<=0)	xCactus=255;
				

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

				tickMov=0;
				
				
				
				
			   /* Control del MOVIMIENTO LATERAL del Dino (Izquierda / Derecha)  */
				if(TeclaPulsada()==DERECHA && xDino <=80){
					xDino= xDino+5;
				}
				if(TeclaPulsada()==IZQUIERDA && xDino >=20){
					xDino= xDino-5;
				}


				
				
			}


			/* Controlamos las animaciones del juego*/
			if (tick == 2) {
			
				/* **** SISTEMA de COLISIONES **** */

				//Si dino corriendo (colisiona con el pajaro y con el cactus)
				if (ESTADO==CORRER){
					if ( ((xPajaro-xDino)<= 10 && (xPajaro-xDino)>= -10) ||  ((xCactus2-xDino)<= 10 && (xCactus2-xDino)>= -10) ||((xCactus-xDino)<= 10 && (xCactus-xDino)>= -10) ) ESTADO=CHOQUE;
				}
				
				//Si dino AGACHADO (solo puede colisionar con el cactus)
				if (ESTADO==AGACHAR){
					if ( ((xCactus2-xDino)<= 10 && (xCactus2-xDino)>= -10) || ((xCactus-xDino)<= 10 && (xCactus-xDino)>= -10)  ) ESTADO=CHOQUE;
				} 

			

				//********ANIMACIÓN DE PAJARO********//  (animacion del aleteo del pajaro)
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

				

				//********ANIMACION DE DINO ********// (animación CORRIENDO)
				if(ESTADO==CORRER){
					segSalto=0;
					if (inicio){
						MostrarDino_izda(4,xDino,yDino);
						inicio = false;
					}

					// levanta pie derecho
					if (paso_derecho){ 
						MostrarDino(1,xDino,yDino);
						BorrarDino_izda(4,xDino,yDino);		

						MostrarDino_dcha(3,xDino,yDino);		
						BorrarDino(1,xDino,yDino);
						paso_derecho=false;
					}
			
					// levanta pie izquierdo
					else{
						MostrarDino(1,xDino,yDino);
						BorrarDino_dcha(3,xDino,yDino);		
						MostrarDino_izda(4,xDino,yDino);		
						BorrarDino(1,xDino,yDino);
						paso_derecho=true;
					}

				}


				/********Animación AGACHAR del Dinosaurio********/ // 

				if (ESTADO == AGACHAR)	{
					if (inicioAgachar){
						BorrarDino(1,xDino,yDino);
						BorrarDino_izda(4,xDino,yDino);
						BorrarDino_dcha(3,xDino,yDino);
						MostrarDino_agachar_izda(7,xDino,yDino);
						inicio = false;
					}

					// levanta pie derecho
					if (paso_derechoAgachar){ 
						MostrarDino_agachar(8,xDino,yDino);
						BorrarDino_agachar_izda(7,xDino,yDino);	

						MostrarDino_agachar_dcha(9,xDino,yDino);		
						BorrarDino_agachar(8,xDino,yDino);
						paso_derechoAgachar=false;
					}

					// levanta pie izquierdo
					else {
						MostrarDino_agachar(8,xDino,yDino);
						BorrarDino_agachar_dcha(9,xDino,yDino);	
						MostrarDino_agachar_izda(7,xDino,yDino);			
						BorrarDino_agachar(8,xDino,yDino);
						paso_derechoAgachar=true;

					}
					
					// Si ya no está siendo pulsada la tecla, Dino se levanta 
					if (TeclaPulsada()!=ABAJO){
						BorrarDino_agachar_dcha(9,xDino,yDino);	
						BorrarDino_agachar(8,xDino,yDino);
						BorrarDino_agachar_izda(7,xDino,yDino);	

						MostrarDino(1,xDino,yDino); //Para evitar bugs al terminar el salto...
						tick=2;

						ESTADO=CORRER;
					}
				}

				
				tick=0;
				}

		}
		 

		
		//********SALTO********//
		if(ESTADO == SALTO) {
			MostrarArbol_4(11,xCactus,yCactus);  // Muestra el Arbol4(cactus) en pantalla
			MostrarArbol_2(12,xCactus2,yCactus2);  // Muestra el Arbol4(cactus) en pantalla

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
				
				//Cooldown del pajaro para que salga de nuevo (Cooldown significa tiempo de espera)
				if(xPajaro <= 0){
					BorrarPajaro_alas_abajo(6,xPajaro,yPajaro);
					BorrarPajaro_alas_arriba(5,xPajaro,yPajaro);
					segPajaro++;
					xPajaro=-20;

					if (segPajaro == 5){
						segPajaro=0;
						xPajaro=255;
						MostrarPajaro_alas_arriba(5,xPajaro,yPajaro);
					}	
				}


				//Cooldown del cactus2 para que salga de nuevo
				if(seg3 == 10){
					MostrarArbol_2(12,xCactus2,yCactus2);
				}

				if(xCactus2 <= 0){
					BorrarArbol_2(12,xCactus2,yCactus2);
					segCactus2++;
					xCactus2=-30;

					if(segCactus2 == 15){
						segCactus2=0;
						xCactus2=255;
						MostrarArbol_2(12,xCactus2,yCactus2);
					}	
				}

				//reinicia los ticks para entrar de nuevo al if
				tickTemp=0;
			}


			/** Aquí controlamos todo el movimiento de los sprites **/
			if (tickMov == 1) {

				cambioFondo++; //actualiza el fondo

				// Actualiza la posición de los Sprites enemigos
				if(seg3 >= 5) xPajaro=xPajaro-6;
		
				xCactus=xCactus-7;
				if(seg3 >= 3) xCactus2=xCactus2-8;
				
				//Comprueba si el Cactus (MuestraArbol_4, con id 11) se sale de la pantalla
				if (xCactus<=0)	xCactus=255;
			

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
				
				/* Control del MOVIMIENTO LATERAL del Dino (Izquierda / Derecha)  */

				if(TeclaPulsada()==DERECHA && xDino <=80){
					xDino= xDino+5;
				}

				if(TeclaPulsada()==IZQUIERDA && xDino >=20){
					xDino= xDino-5;
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
				
				/** SISTEMA DE COLISIONES para el estado salto **/

				// Si Dino está saltando --> se PUEDE chocar con el PÁJARO
				if   ( ((xPajaro-xDino)<= 10 && (xPajaro-xDino)>= -10)  || (((xCactus2-xDino)<= 8 && (xCactus2-xDino)>= -8) && ((yCactus2-yDino)<=8 && (yCactus2-yDino)>=-8)) || (  (((xCactus-xDino)<= 8 && (xCactus-xDino)>= -8) && ((yCactus-yDino)<=8 && (yCactus-yDino)>=-8))  )  ) ESTADO=CHOQUE;



				//********ANIMACION DE PAJARO********// (aleteo del pajaro)
				if(iniPajaro){
					MostrarPajaro_alas_arriba(5,xPajaro,yPajaro);
					iniPajaro=false;
				}
				
				// alas abajo
				if (paso_abajoPajaro){ 
					BorrarPajaro_alas_arriba(5,xPajaro,yPajaro);
					MostrarPajaro_alas_abajo(6,xPajaro,yPajaro);		
					paso_abajoPajaro=false;

				}

                //alas arriba
				else{
					BorrarPajaro_alas_abajo(6,xPajaro,yPajaro);			
					MostrarPajaro_alas_arriba(5,xPajaro,yPajaro);		
					paso_abajoPajaro=true;

				}
	
				tick=0; //reset de ticks

			}

			// Termina el salto una vez realizado
			if(segSalto >= 10){
				ESTADO = CORRER;
			}

		}


		// ANIMACIÓN de choque (game over)
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

