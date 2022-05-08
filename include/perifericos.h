/*-------------------------------------
perifericos.h
-------------------------------------*/

extern int TeclaDetectada();
extern int TeclaPulsada();
extern void ConfigurarTeclado(int Conf_Tec);

extern void ConfigurarTemporizador0(int Latch, int Conf_Tempo);

void ConfigurarTemporizador1(int Latch, int Conf_Tempo); //el Cong_Tempo se es asignado directamente como valor de TIMER1_CNT


extern void HabilitarIntTeclado();
extern void InhibirIntTeclado();
extern void HabilitarIntTempo();
extern void InhibirIntTempo();
extern void PonerEnMarchaTempo();
extern void PararTempo();
extern void ClearScreen();

