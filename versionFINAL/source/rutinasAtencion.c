   
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
int xCactus=255; //Posicion Cactus eje x
int xCactus2=255;

int yPajaro=120;
int yCactus=131;
int yCactus2=131;

int cambioFondo=0;  // esta variable indica el cambio de fondo


//
	// Habilitar las interrupciones del teclado.

	// Establecer las rutinas de atención a interrupciones
//	EstablecerVectorInt();
//

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
	static int segPajaro=0;	//Tiempo de aparicion del pajaro
	static int segCactus2=0; //Tiempo de aparicion del cactus

	static int segSalto=0;	//Tiempo del salto
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

			MostrarArbol_2(12,xCactus2,131);
			MostrarArbol_4(11,xCactus,yCactus);


	
		    /* Controla el tiempo real transcurrido y calcula la puntuación */
			if (tickTemp == 5) {

				//Suma +1 cada segundo al juego cuando se inicia
				seg3++;

				iprintf("\x1b[17;6HTiempo:%d  ", seg3);
				puntos= 10*seg3;
				iprintf("\x1b[19;6HPuntos:%d  ", puntos);


							
				//Cooldown del pajaro para que salga de nuevo

				if(xPajaro <= 0){
					BorrarPajaro_alas_abajo(6,xPajaro,110);
					BorrarPajaro_alas_arriba(5,xPajaro,110);
					segPajaro++;
					xPajaro=-20;

					if (segPajaro == 10){
						segPajaro=0;
						xPajaro=255;
						MostrarPajaro_alas_arriba(5,xPajaro,110);

					}	
				}


				//Cooldown del cactus2 para que salga de nuevo

				if(seg3 == 10){
					MostrarArbol_2(12,xCactus2,131);
				}

				if(xCactus2 <= 0){
					BorrarArbol_2(12,xCactus2,131);
					segCactus2++;
					xCactus2=-20;

					if(segCactus2 == 20){
						segCactus2=0;
						xCactus2=255;
						MostrarArbol_2(12,xCactus2,131);
					}
					
				}


				//reinicia los ticks para entrar de nuevo al if
				tickTemp=0;
			}



			/* Movimiento de sprites enemigos y fondo */
			if (tickMov == 1) {
				
				cambioFondo++;
			
				if(seg3 >= 10){
				xPajaro=xPajaro-5;
				}

				xCactus=xCactus-7;

				if(seg3 >= 20){
					xCactus2=xCactus2-8;
				}


				if (xCactus<=0) {
					xCactus=255;
				}

				


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


				/* Aquí se produce el movimiento lateral del Dino (controlado mediante las flechas izda/dcha) */
				
				if(TeclaPulsada()==DERECHA && xDino <=100){
					xDino= xDino+5;
				}

				if(TeclaPulsada()==IZQUIERDA && xDino >=20){
					xDino= xDino-5;
				}
			}


			/* Controlamos las animaciones del juego*/
			if (tick == 2) {
			
				//SISTEMA COLISIONES//

				//si dino corriendo (se la pega con el pajaro y con el cactus)
				if (ESTADO==CORRER){
					if ( ((xPajaro-xDino)<= 10 && (xPajaro-xDino)>= -10) ||  ((xCactus-xDino)<= 10 && (xCactus-xDino)>= -10) ) ESTADO=CHOQUE;
				}

				if (ESTADO==CORRER){
					if ((xCactus2-xDino)<= 10 && (xCactus2-xDino)>= -10) ESTADO=CHOQUE;
				}
				
				//si dino AGACHADO (se la pega con el cactus)
				if (ESTADO==AGACHAR){
					if ((xCactus-xDino)<= 10 && (xCactus-xDino)>= -10) ESTADO=CHOQUE;
				} 

				if (ESTADO==AGACHAR){
					if ((xCactus2-xDino)<= 10 && (xCactus2-xDino)>= -10) ESTADO=CHOQUE;
				} 
			
			

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
				MostrarArbol_4(11,xCactus,yCactus);
			




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

			MostrarArbol_2(12,xCactus2,131);
			MostrarArbol_4(11,xCactus,yCactus);

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


				//Cooldown del pajaro para que salga de nuevo

				if(xPajaro <= 0){
					BorrarPajaro_alas_abajo(6,xPajaro,110);
					BorrarPajaro_alas_arriba(5,xPajaro,110);
					segPajaro++;
					xPajaro=-20;

					if (segPajaro == 10){
						segPajaro=0;
						xPajaro=255;
						MostrarPajaro_alas_arriba(5,xPajaro,110);

					}	

				}


				
				//Cooldown del cactus2 para que salga de nuevo

				if(seg3 == 10){
					MostrarArbol_2(12,xCactus2,131);
				}

				if(xCactus2 <= 0){
					BorrarArbol_2(12,xCactus2,131);
					segCactus2++;
					xCactus2=-20;

					if(segCactus2 == 20){
						segCactus2=0;
						xCactus2=255;
						MostrarArbol_2(12,xCactus2,131);
					}

				}


			}


			/** Aquí controlamos todo el movimiento de los sprites **/
			if (tickMov == 1) {
				cambioFondo++;

				if(seg3 >= 10){
				xPajaro=xPajaro-5;
				}

				xCactus=xCactus-7;

				if(seg3 >= 20){
				xCactus2=xCactus2-8;
				}


				if (xCactus<=0) {
					xCactus=255;
				}

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



				/* Aquí se produce el movimiento lateral del Dino (controlado mediante las flechas izda/dcha) */

				if(TeclaPulsada()==DERECHA && xDino <=100){
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
				
				/** Sistema de colisiones **/

				// Si el Dino está saltando se la pega con el pajaro
				if ( ((xPajaro-xDino)<= 10 && (xPajaro-xDino)>= -10)  || (((xCactus-xDino)<= 8 && (xCactus-xDino)>= -8) && ((yCactus-yDino)<=8 && (yCactus-yDino)>=-8)) || (((xCactus2-xDino)<= 8 && (xCactus2-xDino)>= -8) && ((yCactus2-yDino)<=8 && (yCactus2-yDino)>=-8))  ) ESTADO=CHOQUE;


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

				tick=0;

			}

			// Termina el salto una vez realizado
			if(segSalto >= 10){
				ESTADO = CORRER;
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
			MostrarArbol_4(11,xCactus,yCactus);


			//Para el tiempo cuando choca contra algo
			PararTempo();
			iprintf("\x1b[17;6HTiempo:%d      ", seg3);
			iprintf("\x1b[5;10H*GAME OVER*");
			iprintf("\x1b[8;8HRESTART THE GAME");
			iprintf("\x1b[10;9HTO PLAY AGAIN");


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
