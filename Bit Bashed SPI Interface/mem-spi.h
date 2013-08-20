/*
IBEX UK LTD http://www.ibexuk.com
Electronic Product Design Specialists
RELEASED SOFTWARE

The MIT License (MIT)

Copyright (c) 2013, IBEX UK Ltd, http://ibexuk.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
//Project Name:		FAT FILING SYSTEM FAT16 & FAT 32 DRIVER
//BIT BASHED SPI INTERFACE C CODE HEADER FILE




//################################################
//################################################
//########## USING MANUAL SPI INTERFACE ##########
//################################################
//################################################
//This bit based SPI interface may be used with devices that don't support SPI, or where you suspect there may
//be a problem with your devices SPI peripheral, say due to a silicon bug.

//###########################################
//##### IN YOUR PROJECTS INITIALISATION #####
//###########################################

//Ensure the CLK and SDO pins are configured as outputs and the SDI pin is configured as an input.
//If you are using this manual SPI interface instead of your devices built in SPI interface ensure
//your devices SPI module is disabled and not using the pins.


//##############################
//##### ADD TO MEM-MMCSD.C #####
//##############################

//ADD AT TOP OF FILE AFTER OTHER INCLUDES:-
/*
#include "mem-spi.h"				//Manual bit bashed SPI interface
*/

//##############################
//##### ADD TO MEM-MMCSD.H #####
//##############################
/*
//REPLACE THE EXISTING MATCHING DEFINES WITH THESE:-
#define	FFS_SPI_BUF_FULL				1
#define	FFS_SPI_TX_BYTE(data)			spi_tx_byte(data)
#define	FFS_SPI_RX_BYTE_BUFFER			spi_rx_data

#define	SPI_BUS_SET_TO_LOW_SPEED		spi_speed_fast = 0;
#define	SPI_BUS_SET_TO_FULL_SPEED_MMC	spi_speed_fast = 1;
#define	SPI_BUS_SET_TO_FULL_SPEED_SD	spi_speed_fast = 1;
*/






//*****************************
//*****************************
//********** DEFINES **********
//*****************************
//*****************************
#ifndef MEM_SPI_C_INIT		//Do only once the first time this file is used
#define	MEM_SPI_C_INIT


//----------------------------------------------
//----- DEFINE TARGET COMPILER & PROCESSOR -----
//----------------------------------------------
//(ONLY 1 SHOULD BE INCLUDED, COMMENT OUT OTHERS)
//#define	SPI_USING_MICROCHIP_C18_COMPILER
#define	SPI_USING_MICROCHIP_C30_COMPILER
//<< add other compiler types here



#ifdef SPI_USING_MICROCHIP_C18_COMPILER
//########################################
//##### USING MICROCHIP C18 COMPILER #####
//########################################


//SPI PINS
#define	SPI_CLK_PIN			LATCbits.LATC3			//PIC SPI clock out
#define	SPI_DO_PIN			LATCbits.LATC5			//PIC SPI data out, memory card data in
#define	SPI_DI_PIN			PORTCbits.RC4			//PIC SPI data in, memory card data out

//SPI CLOCK DELAYS
//DELAY NEEDS TO BE 50% OF TOTAL CLOCK PERIOD (DELAY IS USED FOR EACH CLOCK EDGE).
#define	SPI_400KHZ_CLOCK_DELAY			Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	//Min 1.25uS, Comment out define if not requried
#define	SPI_20MHZ_CLOCK_DELAY			Nop();		//Min 25nS, Comment out define if not requried

//###############################################
//##### END OF USING MICROCHIP C18 COMPILER #####
//###############################################
#endif		//#ifdef SPI_USING_MICROCHIP_C18_COMPILER



#ifdef SPI_USING_MICROCHIP_C30_COMPILER
//########################################
//##### USING MICROCHIP C30 COMPILER #####
//########################################


//SPI PINS
#define	SPI_CLK_PIN			_LATF6					//PIC SPI clock out
#define	SPI_DO_PIN			_LATF3					//PIC SPI data out, memory card data in
#define	SPI_DI_PIN			_RF2					//PIC SPI data in, memory card data out

//SPI CLOCK DELAYS
//DELAY NEEDS TO BE 50% OF TOTAL CLOCK PERIOD (DELAY IS USED FOR EACH CLOCK EDGE).
#define	SPI_400KHZ_CLOCK_DELAY			Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	Nop();	//Min 1.25uS, Comment out define if not requried
#define	SPI_20MHZ_CLOCK_DELAY			Nop(); Nop(); Nop(); Nop();		//Min 25nS, Comment out define if not requried


//###############################################
//##### END OF USING MICROCHIP C30 COMPILER #####
//###############################################
#endif		//#ifdef SPI_USING_MICROCHIP_C30_COMPILER





#endif




//*******************************
//*******************************
//********** FUNCTIONS **********
//*******************************
//*******************************
#ifdef MEM_SPI_C
//-----------------------------------
//----- INTERNAL ONLY FUNCTIONS -----
//-----------------------------------



//-----------------------------------------
//----- INTERNAL & EXTERNAL FUNCTIONS -----
//-----------------------------------------
//(Also defined below as extern)
void spi_tx_byte (BYTE data);



#else
//------------------------------
//----- EXTERNAL FUNCTIONS -----
//------------------------------
extern void spi_tx_byte (BYTE data);


#endif




//****************************
//****************************
//********** MEMORY **********
//****************************
//****************************
#ifdef MEM_SPI_C
//--------------------------------------------
//----- INTERNAL ONLY MEMORY DEFINITIONS -----
//--------------------------------------------





//--------------------------------------------------
//----- INTERNAL & EXTERNAL MEMORY DEFINITIONS -----
//--------------------------------------------------
//(Also defined below as extern)
BYTE spi_speed_fast = 0;
BYTE spi_rx_data;






#else
//---------------------------------------
//----- EXTERNAL MEMORY DEFINITIONS -----
//---------------------------------------
extern BYTE spi_speed_fast;
extern BYTE spi_rx_data;





#endif




