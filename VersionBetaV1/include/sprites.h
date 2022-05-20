extern u16* gfx;
extern u16* gfx2;
extern u16* gfx3;
extern u16* gfxSub;

extern void memoriaReserva();

/* Para cada uno de los 256 valores que puede tomar un Pixel le da un color en la pantalla principal. El valor 0 es transparente y los valores sin definir negros */
extern void EstablecerPaletaPrincipal();


/* Para cada uno de los 256 valores que puede tomar un Pixel le da un color en la pantalla secundaria. El valor 0 es transparente y los valores sin definir negros */
extern void EstablecerPaletaSecundaria();


/* Carga en memoria los Sprites dibujados.*/
extern void GuardarSpritesMemoria();




/**** ANIMACIONES DINOSAURIO ****/
//CORRIENDO
/* Mostrar-borrar Dino corriendo (ambas piernas tocando el suelo) */
extern void MostrarDino(int indice, int x, int y);
extern void BorrarDino(int indice, int x, int y);

/* Mostrar-borrar Dino (pierna derecha levantada) */
extern void MostrarDino_dcha(int indice, int x, int y);
extern void BorrarDino_dcha(int indice, int x, int y);


/* Mostrar-borrar Dino (pierna izquierda levantada) */
extern void MostrarDino_izda(int indice, int x, int y);
extern void BorrarDino_izda(int indice, int x, int y);



//AGACHADO
/* Mostrar-borrar Dino AGACHADO (ambas piernas en el suelo) */
extern void MostrarDino_agachar(int indice, int x, int y);
extern void BorrarDino_agachar(int indice, int x, int y);


/* Mostrar-borrar Dino AGACHADO (pierna derecha levantada) */
extern void MostrarDino_agachar_dcha(int indice, int x, int y);
extern void BorrarDino_agachar_dcha(int indice, int x, int y);


/* Mostrar-borrar Dino AGACHADO (pierna izquierda levantada) */
extern void MostrarDino_agachar_izda(int indice, int x, int y);
extern void BorrarDino_agachar_izda(int indice, int x, int y);


//CHOCADO (muerto)
/*Mostrar-borrar Dino CHOCADO  */
extern void MostrarDino_choque(int indice, int x, int y);
extern void BorrarDino_choque(int indice, int x, int y);




/**** ANIMACIONES ARBOL (cactus) ****/
extern void MostrarArbol_2(int indice, int x, int y);
extern void BorrarArbol_2(int indice, int x, int y);

extern void MostrarArbol_3(int indice, int x, int y);
extern void BorrarArbol_3(int indice, int x, int y);

extern void MostrarArbol_4(int indice, int x, int y);
extern void BorrarArbol_4(int indice, int x, int y);



/**** ANIMACIONES PÁJARO (terodactilo) ****/
extern void MostrarPajaro_alas_arriba(int indice, int x, int y);
extern void BorrarPajaro_alas_arriba(int indice, int x, int y);

extern void MostrarPajaro_alas_abajo(int indice, int x, int y);
extern void BorrarPajaro_alas_abajo(int indice, int x, int y);


