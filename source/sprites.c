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
u16* gfxdino_dcha;  //Dino (pierna izquierda levantada)
u16* gfxdino_agachar;  //Dino (pierna izquierda levantada)
u16* gfxdino_choque;  //Dino (pierna izquierda levantada)


u16* gfxromboGrande;


/* Reservar memoria para cada sprite que se quiera mostrar en pantalla.*/
void memoriaReserba()
{
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxdino= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdino_izda= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdino_dcha= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdino_agachar= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdino_choque= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);

//	gfxromboGrande=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
}

/* A cada uno de los 256 valores que puede tomar un pixel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros. 
   MODIFICAR SEGÚN LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES*/
void EstablecerPaletaPrincipal() {

	SPRITE_PALETTE[1] = RGB15(31,0,0); // los píxeles con valor 1 serán de color rojo.
	SPRITE_PALETTE[2] = RGB15(0,31,0); // los píxeles con valor 2 serán verdes.
	SPRITE_PALETTE[3] = RGB15(0,0,31); // los píxeles con valor 3 serán azules.
}

/* definición de un sprite de 16x16 píxeles */
/* Por la forma que tienen de trabajar los bancos de memoria, la imagen del sprite se divide en bloques de 8x8 píxeles. Los primeros 64 (8x8) píxeles que indicamos
aparecerán en el cuadrante superior izquierdo de la imagen del sprite, los siguientes 64 en el cuadrante superior derecho, los siguientes en el cuadrante inferior izquierdo y los
últimos en el cuadrante inferior derecho. */




// Sprite de dinosaurio (con las dos piernas abajo)

u8 dino[256] = {0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	9	9	9	9	9	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	0	9	9	9	9
9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	0	9	9	9	9	0	0	0	0
0	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	9	9	9	9	9	9	9	9	0
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

u8 dino_izda[256] = { 0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	9	9	9	9	9	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	0	9	9	9	9
9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	0	9	9	9	9	0	0	0	0
0	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	9	9	9	9	9	9	9	9	0
9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	 // 	9	9	0	0	0	9	9	9	9	9	9	0	0	0	0	0
9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	 // 	9	9	9	9	9	9	9	9	9	9	9	9	9	0	0	0
0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	0	9	0	0	0
0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	 // 	0	9	9	9	9	9	9	9	9	9	9	0	0	0	0	0
0	,	0	,	0	,	0	,	9	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	 // 	0	0	0	9	9	9	9	9	9	9	9	0	0	0	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	9	9	9	9	0	0	0	0	0	0
9	,	9	,	9	,	0	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	0	0	9	9	0	0	0	0	0	0	0
9	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	9	9	0	0	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	0	0	0	0	0	0	0
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	9	0	0	0	0	0	
}

// Dino (pierna derecha levantada)
u8 dino_dcha[256] = { 0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	9	9	9	9	9	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	0	9	9	9	9
9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9
0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	0	9	9	9	9	0	0	0	0
0	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	9	0	0	0	0	0	0	9	9	9	9	9	9	9	9	0
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
}



// Dino agachado (dos piernas en el suelo)
u8 dino_agachar[256] = { 0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	0	9	9	9	9	9	9
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	0	0	9	9
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9	9
9	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	0	0
9	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	9	9	9	9	9	9	9	9
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
}




// Dino muerto (chocado) -> se le cambia el ojo
u8 dino_choque[256] =  {0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	0	9	9	9	9	9	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	 // 	0	0	0	0	0	0	0	0	0	9	6	6	6	6	9	9
9	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	6	0	6	6	9	9
9	,	9	,	0	,	0	,	0	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	9	,	 // 	0	0	0	0	0	0	0	0	0	9	6	6	6	6	9	9
0	,	0	,	9	,	9	,	9	,	9	,	9	,	0	,	0	,	9	,	6	,	6	,	6	,	6	,	9	,	9	,	 // 	9	0	0	0	0	0	0	0	9	9	9	9	9	9	9	0
0	,	9	,	6	,	0	,	6	,	6	,	9	,	9	,	0	,	9	,	6	,	6	,	6	,	6	,	9	,	9	,	 // 	9	0	0	0	0	0	0	9	9	9	9	9	9	9	9	0
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
}








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
		gfxdino_choque[i] = dino_choque[i*2] | (dino_choque[(i*2)+1]<<8);				
			
				
				
	}

	//sprite de 32x32 
	/*
	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxromboGrande[i] = romboGrande[i*2] | (romboGrande[(i*2)+1]<<8);				
	} */
}




//## FUNCIONES PARA MOSTRAR GRÁFICAMENTE LOS SPRITES



/* Esta función dibuja un DINO NORMAL en la posición x-y de pantalla. ( indice -> un valor entre 0 y 126.) */
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

/*Esta función borra de la pantalla el DINOSAURIO(pies abajo) con el índice indicado*/
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





/* Esta función dibuja el dino con PIERNA DERECHA LEVANTADA*/
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

/* Esta función BORRA el dino que ha sido dibujado con la PIERNA DERECHA LEVANTADA*/
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









/* Esta función dibuja el dino con la PIERNA IZQUIERDA LEVANTADA*/
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

/* Esta función BORRA el dino con PIERNA IZQUIERDA LEVANTADA*/
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







/* Esta función dibuja el dino AGACHADO*/
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

/* Esta función BORRA el dino el cuál ha sido dibujado AGACHADO*/
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



/* Esta función dibuja el dino cuando se HA CHOCADO (cuando "muere" el dinosaurio) */
void MostrarDino_coque(int indice, int x, int y)
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

/* Esta función BORRA el dino CHOCADO*/
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







// PARA SPRITES MÁS GRANDES...
/*
void MostrarRomboGrande(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxromboGrande,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void BorrarRomboGrande(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxromboGrande,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}
*/
