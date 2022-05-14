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

int cambioFondo=0;

void RutAtencionTeclado ()
{

	if (ESTADO == CORRER && TeclaPulsada()==ARRIBA){
		ESTADO=SALTO;
	}


		if (ESTADO == CHOQUE)
		{		
			if(TeclaPulsada()==A){

				consoleClear();
				ESTADO=MENU;
			}	

			if(TeclaPulsada()==R){

				consoleClear();
				ESTADO=CORRER;
			}	
		}

}




void RutAtencionTempo()
{
	static int tick=0;  	//Tick para las animaciones
	static int tickTemp=0;	//Tick para el tiempo
	static int tickMov=0;	//Tick para el movimiento
	static int seg=0;
	static int seg3=0;		//Tiempo dentro del juego

	static int segSalto=0;	//Tiempo del salto

	static bool paso_derecho=true;	//Paso deecho de movimiento Dino
	static bool inicio=true;		//Inicio de movimiento Dino

	static bool paso_derechoAgachar=true;	//Paso deecho de movimiento Dino Agachado
	static bool inicioAgachar=true;		//Inicio de movimiento Dino Agachado

	static bool iniPajaro=true;
	static bool paso_abajoPajaro=true;





	if (ESTADO!=ESPERA)
	{
		tick++; 
		tickTemp++;
		tickMov++;

		// cada 5 ticks = 1segundo (en teoria)
		if (tick == 5*3 && ESTADO == INTRO ){
		    tick=0;
			tickTemp=0;
			tickMov=0;
			consoleClear();
		    ESTADO=MENU;
		}






		//********CORRER********//

		if (ESTADO == CORRER) {

			segSalto = 0;

				while(TeclaPulsada()==DERECHA && xDino <=50){
					xDino=xDino+1;
				}

				while(TeclaPulsada()==IZQUIERDA && xDino >=20){
					xDino=xDino-1;
				}
		
			if (tickTemp == 5) {

				//Suma +1 cada segundo al juego cuando se inicia
				seg3++;

				iprintf("\x1b[17;6HTiempo:%d  ", seg3);
				puntos= 10*seg3;
				iprintf("\x1b[19;6HPuntos:%d  ", puntos);




				//reinicia los ticks para entrar de nuevo al if
				tickTemp=0;


			}


			if (tickMov == 1) {

				cambioFondo++;

				xPajaro=xPajaro-5;

				if(xPajaro<=0) {
					xPajaro=255;
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


			}


			if (tick == 2) {

				


				//********MOVIMIENTO DE PAJARO********//

				if(iniPajaro){
					MostrarPajaro_alas_arriba(5,xPajaro,110);
					iniPajaro=false;
				}
				
				if (paso_abajoPajaro){ 
					BorrarPajaro_alas_arriba(5,xPajaro,110);

					MostrarPajaro_alas_abajo(6,xPajaro,110);		
					paso_abajoPajaro=false;

				}

				else{
					BorrarPajaro_alas_abajo(6,xPajaro,110);			
					MostrarPajaro_alas_arriba(5,xPajaro,110);		
					paso_abajoPajaro=true;

				}



				//********MOVIMIENTO DE DINO********//


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


				tick=0;

			}
			//***************************//



	

		}






		//********AGACHAR********//

		if (ESTADO == AGACHAR) {
		
		
			if (tickTemp == 5) {

				//Suma +1 cada segundo al juego cuando se inicia
				seg3++;

				iprintf("\x1b[17;6HTiempo:%d  ", seg3);
				puntos= 10*seg3;
				iprintf("\x1b[19;6HPuntos:%d  ", puntos);




				//reinicia los ticks para entrar de nuevo al if
				tickTemp=0;


			}



			if (tickMov == 1) {

				cambioFondo++;

				xPajaro=xPajaro-5;

				if(xPajaro<=0) {
					xPajaro=255;
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


			}


			if (tick == 2) {


				//********MOVIMIENTO DE PAJARO********//

				if(iniPajaro){
					MostrarPajaro_alas_arriba(5,xPajaro,110);
					iniPajaro=false;
				}
				
				if (paso_abajoPajaro){ 
					BorrarPajaro_alas_arriba(5,xPajaro,110);

					MostrarPajaro_alas_abajo(6,xPajaro,110);		
					paso_abajoPajaro=false;

				}

				else{
					BorrarPajaro_alas_abajo(6,xPajaro,110);			
					MostrarPajaro_alas_arriba(5,xPajaro,110);		
					paso_abajoPajaro=true;

				}



				//********MOVIMIENTO DE DINO********//

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
		
				else{
					MostrarDino_agachar(8,xDino,yDino);
					BorrarDino_agachar_dcha(9,xDino,yDino);	
					MostrarDino_agachar_izda(7,xDino,yDino);			
					BorrarDino_agachar(8,xDino,yDino);
					paso_derechoAgachar=true;

				}

				tick=0;

			}
			//***************************//

			if (TeclaPulsada()!=ABAJO){
				BorrarDino_agachar_dcha(9,xDino,yDino);	
				BorrarDino_agachar(8,xDino,yDino);
				BorrarDino_agachar_izda(7,xDino,yDino);	

				ESTADO=CORRER;
			}

	

		}








		//********SALTO********//

		if(ESTADO == SALTO) {

			BorrarDino_izda(4,xDino,yDino);
			BorrarDino_dcha(3,xDino,yDino);
			MostrarDino(1,xDino,yDino);
			segSalto++;




			
			if (tickTemp == 5) {

				//Suma +1 cada segundo al juego cuando se inicia
				seg3++;

				iprintf("\x1b[17;6HTiempo:%d  ", seg3);
				puntos= 10*seg3;
				iprintf("\x1b[19;6HPuntos:%d  ", puntos);




				//reinicia los ticks para entrar de nuevo al if
				tickTemp=0;


			}



			if (tickMov == 1) {


				cambioFondo++;

				xPajaro=xPajaro-5;

				if(xPajaro<=0) {
					xPajaro=255;
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

				while(TeclaPulsada()==DERECHA && xDino <=50){
					xDino++;
				}

				while(TeclaPulsada()==IZQUIERDA && xDino >=20){
					xDino--;
				}


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
					yDino = yDino-10;
				}

				if(segSalto == 5){
					yDino = yDino-4;
				}

				if(segSalto == 6){
					yDino = yDino-4;
				}

				if(segSalto == 7){
					yDino = yDino+4;
				}

				if(segSalto == 8){
					yDino = yDino+4;
				}

				if(segSalto == 9){
					yDino = yDino+10;
				}

				if(segSalto == 10){
					yDino = yDino+10;
				}

				if(segSalto == 11){
					yDino = yDino+10;
				}

				if(segSalto == 12){
					yDino = yDino+10;
				}

			}


			if (tick == 2) {

				


				//********MOVIMIENTO DE PAJARO********//

				if(iniPajaro){
					MostrarPajaro_alas_arriba(5,xPajaro,110);
					iniPajaro=false;
				}
				
				if (paso_abajoPajaro){ 
					BorrarPajaro_alas_arriba(5,xPajaro,110);

					MostrarPajaro_alas_abajo(6,xPajaro,110);		
					paso_abajoPajaro=false;

				}

				else{
					BorrarPajaro_alas_abajo(6,xPajaro,110);			
					MostrarPajaro_alas_arriba(5,xPajaro,110);		
					paso_abajoPajaro=true;

				}

				tick=0;

			}


			if(segSalto >= 12){
				ESTADO = CORRER;
				iprintf("\x1b[21;1HESTADO= CORRER  ");
			}

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

				
	}
}
	


void EstablecerVectorInt()
{
// A COMPLETAR
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	irqSet(IRQ_TIMER0, RutAtencionTempo);
}

