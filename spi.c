/* 
 * File:   spi.c
 * Author: jon
 *
 * Created on 14 November 2013
 */

#include <xc.h>
#include <GenericTypeDefs.h>
#include <stdio.h>
#include <stdlib.h>
#include "spi.h"

void SPI_init()
{
    // Configuración de pines y módulo SSP para 18f252
    SSPEN = 0;
    TRISC3 = 0;     //SCK
    //ANSC1 = 0;      //SDI
    TRISC5 = 0;     //SDO
    CKE = 1;
    SSPCON1 = 0x01;
    SMP = 1;
    SSPEN = 1;
}

BYTE SPI_transfer(BYTE data)
{
    SSPBUF = data;       // Put command into SPI buffer
    while (!BF);         // Wait for the transfer to finish
    return SSPBUF;       // Save the read value
}
