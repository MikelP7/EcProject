
#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación. */

#include "fondos.h"
#include "graficos.h"

#include "Intro.h"
#include "Menu.h"


#include "Fondo01.h"
#include "Fondo02.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria.*/
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */




void visualizarIntro() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     IntroBitmap, 
                     (uint16 *)BG_BMP_RAM(0),
                     IntroBitmapLen); 
}


void visualizarMenu() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     MenuBitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     MenuBitmapLen);
}



//fondos
void visualizarFondo01() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     Fondo01Bitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     Fondo01BitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}



void visualizarFondo02() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     Fondo02Bitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     Fondo02BitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}


