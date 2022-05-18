
#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación. */

#include "fondos.h"
#include "graficos.h"
#include "Puerta.h"
#include "PuertaAbierta.h"
#include "Intro.h"
#include "Menu.h"
#include "Menu2.h"
#include "Fondo00.h"
#include "Fondo01.h"
#include "Fondo02.h"
#include "Fondo03.h"
#include "Fondo04.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria.*/
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */

void visualizarPuerta() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     PuertaBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     PuertaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}


void visualizarPuertaAbierta() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     PuertaAbiertaBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     PuertaAbiertaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}


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


void visualizarMenu2() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     Menu2Bitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     Menu2BitmapLen);
}


void visualizarFondo01() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     Fondo01Bitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     Fondo01BitmapLen);
}


void visualizarFondo02() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     Fondo02Bitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     Fondo02BitmapLen);
}

void visualizarFondo04() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     Fondo04Bitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     Fondo04BitmapLen);
}

void visualizarFondo03() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     Fondo03Bitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     Fondo03BitmapLen);
}

void visualizarFondo00() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     Fondo00Bitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     Fondo00BitmapLen);
}