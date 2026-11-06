//-----------------------------------------------------------------------------
// TP1_BSE.c
//-----------------------------------------------------------------------------
// AUTH: 
// DATE: 
//
// Target: C8051F02x
// Tool chain: KEIL Microvision5
//
//-----------------------------------------------------------------------------
// Déclarations Registres et Bits de l'espace SFR
#include "intrins.h"
#include<c8051F020.h>
#include<c8051F020_SFR16.h>
#include<TP1_BSE_Lib_Config_Globale.h>
#include<TP1_BSE_Lib_Divers.h>

#define LED_ON 1
#define LED_OFF 0

sbit LED = P1^6;  // LED
sbit BP = P3^7; 	// Bouton poussoir 

bit ACK_BP = 1; // vérif si bp relaché: 1 = attente 0 = déjà appuyé
bit ETAT_LED = 1; // si clignote(1) ou eteint(0)



//------------------------------------------------------------------------------------
// Function Prototypes

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
void main (void) {
	
	      Init_Device();
				P3MDOUT &= 0x7F; // masque pour bit 7 à 0
				BP = 1; // ouvre le drain 
				
				P3IF &= 0xF7; //masque bit 3 à 0
				P3IF &= 0x7F; //masque bit 7 à 0
	
	//configure un GPIO:
				EIE2 |= 0x20; // interupteur int7 au bit 5
				EA = 1;		// interupteur général
				
	
        while(1)
        {  
					/*if( BP == 1 && ACK_BP == 1 ){
						ACK_BP = 0;
						ETAT_LED = !ETAT_LED;
					}
					else if ( BP == 0 ){
						ACK_BP = 1;
					}*/

					if ( ETAT_LED == 1)
					{
					 LED = LED_ON;
					 Software_Delay(2); // Temporisation 20ms
					 LED = LED_OFF;
					 Software_Delay(10); // Temporisation 100ms		
					}
					if  ( ETAT_LED == 0)
					{
						LED = LED_OFF;
					}
        }						               	
			}

void Interruption_Bouton_INT7(void)interrupt 19
{
		P3IF &= 0x7F;
		ETAT_LED = !ETAT_LED;
}
		
//*****************************************************************************	 
