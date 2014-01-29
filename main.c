/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "nRF24L01.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

// Contador de pulsos
unsigned long contador=0;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    unsigned long contador_ant;

    /* Initialize I/O and Peripherals for application */
    InitApp();

    // TODO terminar de revisar nRF setup
    nRF_Setup();

    // TODO: hacemos un flush del buffer TX
    while(1)
    {
        // La cuenta de contador es incrementada/decrementada por la rutina
        // de atenci�n de interrupci�n por cambio de pines RB0/1

        // TODO: esperamos que buffer TX quede vac�o
        
        // Verificamos si la cuenta se ha modificado
        if(contador != contador_ant){
            // hubo movimiento del encoder
            // tenemos que trasmitir el valor de la cuenta
            // tomamos referencia del valor actual de la cuenta
            GIEH=0;     // desactivamos interrupciones de cuenta encoder para
                        // tener acceso seguro a contador
            contador_ant = contador;
            GIEH=1;
            // pasamos los 4 bytes al m�dulo wireless
            WritePayload(4,(char*)&contador_ant);
        }
    }
}

