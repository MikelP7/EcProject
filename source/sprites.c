/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

#include "sprites.h"
#include "definiciones.h"

u16* gfxdino; // Dinosaurio de pies (ambas piernas tocando el suelo)
u16* gfxdino_izda; //Dino (pierna izquierda levantada)
u16* gfxdino_dcha;  //Dino (pierna derecha levantada)

u16* gfxdino_agachar;  //Dino agachado (pierna ambas en el suelo)
u16* gfxdino_agachar_dcha;  //Dino agachado (pierna derecha levantada)
u16* gfxdino_agachar_izda;  //Dino agachado (pierna izquierda levantada)

u16* gfxdino_choque;  //Dino chocado (muerto)




u16* gfxarbol_2;  //arbol 2
u16* gfxarbol_3;  //arbol 3
u16* gfxarbol_4;  // arbol4


u16* gfxpajaro_abajo;
u16* gfxpajaro_arriba;



/* Reservar memoria para cada sprite que se quiera mostrar en pantalla.*/
void memoriaReserva()
{
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxdino= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdino_izda= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdino_dcha= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdino_agachar= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdino_agachar_dcha= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdino_agachar_izda= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdino_choque= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);


	gfxarbol_2= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxarbol_3= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxarbol_4= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);

	gfxpajaro_abajo= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxpajaro_arriba= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);

}

/* A cada uno de los 256 valores que puede tomar un pixel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros. 
   MODIFICAR SEG??N LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES*/
void EstablecerPaletaPrincipal() {

	SPRITE_PALETTE[1] = RGB15(31,0,0); // los p??xeles con valor 3 ser??n ROJO.

    SPRITE_PALETTE[3] = RGB15(31,31,31); // los p??xeles con valor 3 ser??n BLANCO.
    SPRITE_PALETTE[6] = RGB15(0,0,0); // los p??xeles con valor 6 ser??n NEGRO.
	SPRITE_PALETTE[9] = RGB15(16,16,16); // los p??xeles con valor 9 GRIS NORMAL
	SPRITE_PALETTE[11] = RGB15(8,8,8); // los p??xeles con valor 3 ser??n GRIS OSCURO.


}

/* definici??n de un sprite de 16x16 p??xeles */
/* Por la forma que tienen de trabajar los bancos de memoria, la imagen del sprite se divide en bloques de 8x8 p??xeles. Los primeros 64 (8x8) p??xeles que indicamos
aparecer??n en el cuadrante superior izquierdo de la imagen del sprite, los siguientes 64 en el cuadrante superior derecho, los siguientes en el cuadrante inferior izquierdo y los
??ltimos en el cuadrante inferior derecho. */




// Sprite de dinosaurio (con las dos piernas abajo)

u8 dino[256] = {
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	9	9	9	9	9	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	3	9	9	9	9
9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	0	9	9	9	9	0	0	0	0
0	,	9	,	9	,	3	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	9	9	9	9	9	9	9	9	0
9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	 // 	9	9	0	0	0	9	9	9	9	9	9	0	0	0	0	0
9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	 // 	9	9	9	9	9	9	9	9	9	9	9	9	9	0	0	0
0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	0	9	0	0	0
0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	0	0	0	0	0
0	,	0	,	0	,	0	,	9	,	9	,	0	,	9	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	 // 	0	0	0	9	9	9	9	9	9	9	9	0	0	0	0	0
0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	 // 	0	0	0	0	9	9	9	9	9	9	0	0	0	0	0	0
9	,	9	,	9	,	0	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	9	9	0	0	0	0	0	0	0
9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	0	0	0	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	0	0	0	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	0	9	9	0	0	0	0	0	0
};



//Dino (pierna izquierda levantada)

u8 dino_izda[256] = { 
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	9	9	9	9	9	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	3	9	9	9	9
9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	0	9	9	9	9	0	0	0	0
0	,	9	,	9	,	3	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	9	9	9	9	9	9	9	9	0
9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	 // 	9	9	0	0	0	9	9	9	9	9	9	0	0	0	0	0
9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	 // 	9	9	9	9	9	9	9	9	9	9	9	9	9	0	0	0
0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	0	9	0	0	0
0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	0	0	0	0	0
0	,	0	,	0	,	0	,	9	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	 // 	0	0	0	9	9	9	9	9	9	9	9	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	9	9	9	9	0	0	0	0	0	0
9	,	9	,	9	,	0	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	0	0	9	9	0	0	0	0	0	0	0
9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	0	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	9	0	0	0	0	0	0
};

// Dino (pierna derecha levantada)
u8 dino_dcha[256] = {
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	9	9	9	9	9	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	3	9	9	9	9
9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	0	9	9	9	9	0	0	0	0
0	,	9	,	9	,	3	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	9	9	9	9	9	9	9	9	0
9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	 // 	9	9	0	0	0	9	9	9	9	9	9	0	0	0	0	0
9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	 // 	9	9	9	9	9	9	9	9	9	9	9	9	9	0	0	0
0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	0	9	0	0	0
0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	0	0	0	0	0
0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	 // 	0	0	0	9	9	9	9	9	9	9	9	0	0	0	0	0
0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	 // 	0	0	0	0	9	9	9	9	9	9	0	0	0	0	0	0
9	,	9	,	9	,	0	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	0	9	0	0	0	0	0	0	0
9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	0	0	0	9	9	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	0	0	0	0	0	0	0	0	0
};



// Dino agachado (dos piernas en el suelo)
u8 dino_agachar[256] ={
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	0	9	9	9	9	9	9
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	3	3	9	9
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9	9
9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	0	0
9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	3	,	3	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9	9
9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	 // 	9	0	0	0	0	0	0	9	9	0	9	9	0	0	0	0
9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	9	9	0	0	0	0	0	9	9	9	9	9	9	9	9	9
9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	9	9	9	9	9	9	9	9	9	0	9	9	0	0	0	0
0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	0	9	9	0	0	0	0
0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	9	9	9	9	9
0	,	0	,	0	,	0	,	9	,	9	,	0	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	9	,	 // 	0	0	0	9	9	9	9	9	9	0	9	9	0	0	0	0
0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	 // 	0	0	0	0	9	9	9	9	9	9	9	9	9	9	9	9
9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	9	9	0	9	9	0	9	9	0	0	0	0
9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	9	9	0	9	9	0	9	9	0	0	0	0
9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	0	0	0	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	0	9	9	0	0	0	0	0	0
};


//Dino agachado (pierna izda levantada)   
u8 dino_agachar_izda[256] = {
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	0	9	9	9	9	9	9
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	0!	0!	9	9
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9	9
9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	0	0
9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	3/**/,	3/**/,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9	9
9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	 // 	9	0	0	0	0	0	0	9	9	0	9	9	0	0	0	0
9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	9	9	0	0	0	0	0	9	9	9	9	9	9	9	9	9
9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	9	9	9	9	9	9	9	9	0	0	9	9	0	0	0	0
0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	0	0	9	9	0	0	0	0
0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	9	9	9	9	9
0	,	0	,	0	,	0	,	9	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	9	,	 // 	0	0	0	9	9	9	9	9	9	0	9	9	0	0	0	0
0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	9	9	9	9	9	9	9	9	9	9
0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	9	0	0	9	0	0	9	9	0	0	0	0
9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	9	0	0	9	0	0	9	9	0	0	0	0
0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	0	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	9	0	0	0	0	0	0
};


//Dino agachado (pierna dcha levantada)
u8 dino_agachar_dcha[256] = {
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	0	9	9	9	9	9	9
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	0!	0!	9	9
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9	9
9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	0	0
9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,   3/**/,	3/**/,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9	9
9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	 // 	9	0	0	0	0	0	0	9	9	0	9	9	0	0	0	0
9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	9	9	0	0	0	0	0	9	9	9	9	9	9	9	9	9
9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	9	9	9	9	9	9	9	9	0	0	9	9	0	0	0	0
0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	0	0	9	9	0	0	0	0
0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	9	9	9	9	9
0	,	0	,	0	,	0	,	9	,	9	,	0	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	9	,	 // 	0	0	0	9	9	9	9	9	9	0	9	9	0	0	0	0
0	,	0	,	0	,	0	,	9	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	 // 	0	0	0	0	9	9	9	9	9	9	9	9	9	9	9	9
0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	9	9	0	9	0	0	9	9	0	0	0	0
9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	9	9	0	9	0	0	9	9	0	0	0	0
0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	0	0	9	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	0	0	0	0	0	0	0	0	0
};






// Dino muerto (chocado) -> se le cambia el ojo
u8 dino_choque[256] =  {
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	9	9	9	9	9	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	9	6	6	6	6	9	9
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	6	3	6	6	9	9
9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	6	6	6	6	9	9
0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	6	,	6	,	6	,	6	,	9	,	9	,	 // 	9	0	0	0	0	0	0	0	9	9	9	9	9	9	9	0
0	,	9	,	6	,	3	,	6	,	6	,	9	,	9	,	0	,	9	,	6	,	6	,	6	,	6	,	9	,	9	,	 // 	9	0	0	0	0	0	0	9	9	9	9	9	9	9	9	0
9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	 // 	9	9	0	0	0	9	9	9	9	9	9	0	0	0	0	0
9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	 // 	9	9	9	9	9	9	9	9	9	9	9	9	9	0	0	0
0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	0	9	0	0	0
0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	0	0	0	0	0
0	,	0	,	0	,	0	,	9	,	9	,	0	,	9	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	 // 	0	0	0	9	9	9	9	9	9	9	9	0	0	0	0	0
0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	 // 	0	0	0	0	9	9	9	9	9	9	0	0	0	0	0	0
9	,	9	,	9	,	0	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	9	9	0	0	0	0	0	0	0
9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	0	0	0	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	0	0	0	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	0	9	9	0	0	0	0	0	0
};






// 3 tipos de arbol (CACTUS)
u8 arbol_2[256] = 
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	11	,	0	,	0	,	11	,	9	,	 // 	0	0	0	0	0	0	0	9	0	0	0	0	0	0	0	0
0	,	0	,	0	,	9	,	9	,	0	,	9	,	9	,	0	,	0	,	0	,	9	,	9	,	0	,	9	,	11	,	 // 	0	0	0	11	0	0	11	9	9	0	0	0	0	0	0	0
0	,	0	,	0	,	11	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	9	9	0	9	9	9	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	11	,	0	,	11	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	9	9	0	9	11	11	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	11	9	9	9	9	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	9	9	9	9	9	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	11	0	11	9	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	9	,	11	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	0	9	11	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	11	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	11	9	9	0	9	9	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	11	,	9	,	9	,	 // 	0	0	0	0	0	0	9	9	9	9	9	9	11	0	0	0
0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	9	9	11	9	11	9	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	11	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	0	11	9	9	9	0	0	0	0	0	0	0
9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	11	,	0	,	0	,	0	,	 // 	0	0	0	0	0	9	9	9	9	0	0	0	0	0	0	0
11	,	9	,	11	,	9	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	11	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	11	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	11	9	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	0	0	0	0	0	0	0
};


u8 arbol_3[256] = 
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	9	,	 // 	0	0	0	0	0	0	0	9	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	11	,	 // 	0	0	0	0	0	0	11	9	9	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	9	9	9	0	0	0	0	0	0	0
0	,	0	,	0	,	11	,	9	,	0	,	11	,	9	,	0	,	0	,	0	,	9	,	9	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	9	11	9	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	0	0	9	9	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	 // 	0	0	0	11	9	0	11	9	9	9	9	9	11	0	0	0
9	,	9	,	9	,	9	,	11	,	0	,	0	,	0	,	9	,	9	,	11	,	9	,	9	,	0	,	0	,	0	,	 // 	0	0	0	9	9	0	9	9	9	9	11	9	9	0	0	0
0	,	0	,	11	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	11	,	 // 	0	0	11	9	9	9	9	9	9	9	9	9	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	9	9	9	11	9	0	0	11	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	9	9	9	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	9	9	9	0	0	0	0	0	0	0
9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	11	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	11	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	0	0	0	0	0	0	0
};

u8 arbol_4[256] = 
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	0	9	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	11	,	 // 	0	0	0	0	0	0	9	9	11	0	0	11	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	9	9	9	0	9	9	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	11	,	9	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	11	11	9	0	9	9	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	0	,	0	,	11	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	9	9	11	0	0	0	0
9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	9	9	9	0	0	0	0
9	,	9	,	9	,	11	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	11	0	11	0	0	0	0	0
11	,	0	,	11	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	11	9	0	9	9	9	0	0	0	0	0	0	0
0	,	0	,	0	,	9	,	9	,	0	,	9	,	9	,	0	,	0	,	11	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	9	9	0	9	9	11	0	0	0	0	0	0	0
0	,	0	,	0	,	9	,	11	,	9	,	11	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	11	9	9	9	9	9	9	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	11	,	9	,	9	,	 // 	0	0	0	9	11	9	11	9	9	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	9	9	9	11	0	0	0	0	0	0
11	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	9	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	11	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	11	9	9	9	0	0	0	0	0	0	0
9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	11	0	0	0	0	0	0	0
11	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	9	9	9	0	0	0	0	0	0	0
};




//Pajaro alas ABAJO (terodactilo)
u8 pajaro_abajo[256] = 
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	9	,	1	,	9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	11	,	 // 	0	0	0	0	9	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	9	9	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	9	9	9	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	9	1	9	9	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	11	,	11	,	9	,	9	,	9	,	9	,	9	,	 // 	9	9	9	9	9	9	9	11	11	11	11	9	9	9	9	9
0	,	0	,	9	,	9	,	0	,	0	,	9	,	11	,	9	,	9	,	9	,	0	,	0	,	0	,	9	,	11	,	 // 	0	0	9	9	0	0	9	11	11	11	11	9	9	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	 // 	9	9	9	0	0	0	9	11	11	11	9	9	9	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	11	11	11	9	9	9	9	9	9
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	11	11	11	0	0	0	0	0	0
11	,	11	,	11	,	9	,	9	,	0	,	0	,	0	,	11	,	11	,	9	,	9	,	9	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	11	0	0	0	0	0	0	0	0
11	,	11	,	9	,	9	,	9	,	9	,	9	,	9	,	11	,	11	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
};



//Pajaro alas ARRIBA (terodactilo)
u8 pajaro_arriba[256] = 
{
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	11	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	9	,	9	,	0	,	0	,	11	,	0	,	0	,	9	,	9	,	9	,	0	,	0	,	11	,	 // 	0	0	0	0	0	0	0	11	0	0	0	0	0	0	0	0
0	,	9	,	1	,	9	,	9	,	0	,	0	,	11	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	9	0	0	11	11	11	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	9	9	0	0	11	11	11	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	11	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	9	9	9	0	0	11	11	11	11	0	0	0	0	0
11	,	11	,	0	,	0	,	0	,	0	,	0	,	0	,	11	,	11	,	11	,	0	,	0	,	0	,	0	,	0	,	 // 	0	9	1	9	9	0	0	11	11	11	11	0	0	0	0	0
11	,	11	,	11	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	9	9	9	9	9	9	9	9	9	9	9	9	9	9	9
0	,	0	,	9	,	9	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	9	,	9	,	 // 	0	0	9	9	0	0	9	9	9	9	9	9	9	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	9	9	9	0	0	0	9	9	9	9	9	9	9	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	9	9	9	9	9	9	9	9	9
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
};



/* Carga en memoria cada uno de los sprites que hemos dibujado. */
void GuardarSpritesMemoria(){ 
	
int i;
	//sprite de 16*16
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxdino[i] = dino[i*2] | (dino[(i*2)+1]<<8);
	    gfxdino_izda[i] = dino_izda[i*2] | (dino_izda[(i*2)+1]<<8);
		gfxdino_dcha[i] = dino_dcha[i*2] | (dino_dcha[(i*2)+1]<<8);				
		gfxdino_agachar[i] = dino_agachar[i*2] | (dino_agachar[(i*2)+1]<<8);	
	    gfxdino_agachar_izda[i] = dino_agachar_izda[i*2] | (dino_agachar_izda[(i*2)+1]<<8);	
		gfxdino_agachar_dcha[i] = dino_agachar_dcha[i*2] | (dino_agachar_dcha[(i*2)+1]<<8);	
		gfxdino_choque[i] = dino_choque[i*2] | (dino_choque[(i*2)+1]<<8);				
			

		gfxarbol_2[i] = gfxarbol_2[i*2] | (gfxarbol_2[(i*2)+1]<<8);				
		gfxarbol_3[i] = gfxarbol_3[i*2] | (gfxarbol_3[(i*2)+1]<<8);				
		gfxarbol_4[i] = gfxarbol_4[i*2] | (gfxarbol_4[(i*2)+1]<<8);		

		gfxpajaro_abajo[i] = pajaro_abajo[i*2] | (pajaro_abajo[(i*2)+1]<<8);		
		gfxpajaro_arriba[i] = pajaro_arriba[i*2] | (pajaro_arriba[(i*2)+1]<<8);		



	}

}




/* -- FUNCIONES PARA MOSTRAR GR??FICAMENTE LOS SPRITES -- */



//DINO CORRIENDO
/* Esta funci??n dibuja un DINO NORMAL en la posici??n x-y de pantalla. ( indice -> un valor entre 0 y 126.) */
void MostrarDino(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}


/*Esta funci??n borra de la pantalla el DINOSAURIO(pies abajo) con el ??ndice indicado*/
void BorrarDino(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}




/* Esta funci??n dibuja el dino con PIERNA DERECHA LEVANTADA*/
void MostrarDino_dcha(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_dcha,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta funci??n BORRA el dino que ha sido dibujado con la PIERNA DERECHA LEVANTADA*/
void BorrarDino_dcha(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_dcha,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}




/* Esta funci??n dibuja el dino con la PIERNA IZQUIERDA LEVANTADA*/
void MostrarDino_izda(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_izda,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta funci??n BORRA el dino con PIERNA IZQUIERDA LEVANTADA*/
void BorrarDino_izda(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_izda,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 
}




// DINO AGACHADO
/* Esta funci??n dibuja el dino AGACHADO*/
void MostrarDino_agachar(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_agachar,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}


/* Esta funci??n BORRA el dino el cu??l ha sido dibujado AGACHADO*/
void BorrarDino_agachar(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_agachar,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 
}





/* Esta funci??n dibuja el dino AGACHAD (pierna izda levantada) O*/
void MostrarDino_agachar_izda(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_agachar_izda,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta funci??n BORRA el dino el cu??l ha sido dibujado AGACHADO*/
void BorrarDino_agachar_izda(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_agachar_izda,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 
}







/* Esta funci??n dibuja el dino AGACHADO (pierna derecha levantada)*/
void MostrarDino_agachar_dcha(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_agachar_dcha,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta funci??n BORRA el dino el cu??l ha sido dibujado AGACHADO*/
void BorrarDino_agachar_dcha(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_agachar_dcha,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 
}






//DINO CHOCADO (muerto)
/* Esta funci??n dibuja el dino cuando se HA CHOCADO (cuando "muere" el dinosaurio) */
void MostrarDino_choque(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_choque,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Esta funci??n BORRA el dino CHOCADO*/
void BorrarDino_choque(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdino_choque,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 
}







//FUNCIONES PARA MOSTRAR-BORRAR LOS 3 tipos de arboles

/*mostrar-borrar arbol 42*/
void MostrarArbol_2(int indice, int x, int y)
{ 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxarbol_2,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}
void BorrarArbol_2(int indice, int x, int y)
{
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxarbol_2,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 
}


/*mostrar-borrar arbol 3*/
void MostrarArbol_3(int indice, int x, int y)
{ 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxarbol_3,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}
void BorrarArbol_3(int indice, int x, int y)
{
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxarbol_3,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 
}


/*mostrar-borrar arbol 4*/
void MostrarArbol_4(int indice, int x, int y)
{ 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxarbol_4,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}
void BorrarArbol_4(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxarbol_4,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 
}









//FUNCIONES PARA MOSTRAR-BORRAR sprite del pajaro

/*mostrar-borrar pajaro alas arriba*/
void MostrarPajaro_alas_arriba(int indice, int x, int y)
{ 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpajaro_arriba,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}
void BorrarPajaro_alas_arriba(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpajaro_arriba,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 
}


/*mostrar-borrar pajaro alas abajo*/
void MostrarPajaro_alas_abajo(int indice, int x, int y)
{ 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpajaro_abajo,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}
void BorrarPajaro_alas_abajo(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpajaro_abajo,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 
}




void animacionDino(){
	int cont=0;
	while (cont<6){  //6 veces
		MostrarDino(1,10,131);
		BorrarDino(1,10,131);

		MostrarDino_dcha(1,10,131);
		BorrarDino_dcha(1,10,131);

		MostrarDino_izda(1,10,131);
		BorrarDino_izda(1,10,131);
		cont++;
	}


}

/*
void dinoCorriendo(){
	int x=10;
	while (x<240){
	   MostrarDino(1,x,131);
	   BorrarDino(1,x,131);
	   x++;

	}
	

}
*/

