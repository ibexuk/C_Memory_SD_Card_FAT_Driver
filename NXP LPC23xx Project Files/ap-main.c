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
//NXP LPC2365 SAMPLE PROJECT C CODE FILE




//----- INCLUDE FILES FOR THIS SOURCE CODE FILE -----
#include "main.h"					//Global data type definitions (see https://github.com/ibexuk/C_Generic_Header_File )
#define	MAIN_C						//(Define used for following header file to flag that it is the header file for this source file)
#include "ap-main.h"				//(Include header file for this source file)

//----- OTHER PROJECT FILES REQUIRED BY THIS SOURCE CODE FILE -----
#include "mem-ffs.h"

//----- COMPILER LIBRARY FILES REQUIRED BY THIS SOURCE CODE FILE -----
#include <stdio.h>					//(Needed for printf)
//#include <stdlib.h>
#include <string.h>					//Used in the example project code



//*************************************************************************************************************************************
//*************************************************************************************************************************************
//*************************************************************************************************************************************
//*************************************************************************************************************************************
//*************************************************************************************************************************************
//*************************************************************************************************************************************
//*************************************************************************************************************************************

//********************************
//********************************
//********** INITIALISE **********
//********************************
//********************************
void initialise (void)
{
	BYTE b_temp;

	//------------------------------------------------------
	//----- ENABLE THE MEMORY ACCELERATOR MODULE (MAM) -----
	//------------------------------------------------------
	//If the application is run from on-chip Flash. It provides accelerated execution at higher frequencies and also helps in reducing power consumption
	//The MAM is only available in devices with on-chip Flash.
	//- Done in Philips_LPC230X_Startup.s

	//------------------------------------------------------
	//----- SET THE SYSTEM CLOCK AND PERIPHERAL CLOCKS -----
	//------------------------------------------------------
	//System clock CCLK done in Philips_LPC230X_Startup.s

	//0x0 PCLK_xyz = CCLK/4 [reset default]
	//0x1 PCLK_xyz = CCLK
	//0x2 PCLK_xyz = CCLK/2
	//0x3 PCLK_xyz = CCLK/8 except for CAN1, CAN2, and CAN filtering where 0x03 selects PCLK_xyz = CCLK/6.

	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_WDT_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_TIMER0_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_TIMER1_BIT);
	PCLKSEL0 |= (0x1 << PCLKSEL0_PCLK_UART0_BIT);
	PCLKSEL0 |= (0x1 << PCLKSEL0_PCLK_UART1_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_PWM0_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_PWM1_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_I2C0_BIT);
	//PCLKSEL0 |= (0x1 << PCLKSEL0_PCLK_SPI_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_RTC_BIT);
	//PCLKSEL0 |= (0x1 << PCLKSEL0_PCLK_SSP1_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_DAC_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_ADC_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_CAN1_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_CAN2_BIT);
	//PCLKSEL0 |= (0x0 << PCLKSEL0_PCLK_ACF_BIT);
	//PCLKSEL1 |= (0x0 << PCLKSEL1_PCLK_BAT_RAM_BIT);
	PCLKSEL1 |= (0x1 << PCLKSEL1_PCLK_GPIO_BIT);
	//PCLKSEL1 |= (0x0 << PCLKSEL1_PCLK_PCB_BIT);
	//PCLKSEL1 |= (0x0 << PCLKSEL1_PCLK_I2C1_BIT);
	PCLKSEL1 |= (0x1 << PCLKSEL1_PCLK_SSP0_BIT);
	//PCLKSEL1 |= (0x0 << PCLKSEL1_PCLK_TIMER2_BIT);
	//PCLKSEL1 |= (0x0 << PCLKSEL1_PCLK_TIMER3_BIT);
	//PCLKSEL1 |= (0x0 << PCLKSEL1_PCLK_UART2_BIT);
	//PCLKSEL1 |= (0x1 << PCLKSEL1_PCLK_UART3_BIT);
	//PCLKSEL1 |= (0x0 << PCLKSEL1_PCLK_I2C2_BIT);
	//PCLKSEL1 |= (0x0 << PCLKSEL1_PCLK_I2S_BIT);
	//PCLKSEL1 |= (0x0 << PCLKSEL1_PCLK_MCI_BIT);
	//PCLKSEL1 |= (0x0 << PCLKSEL1_PCLK_SYSCON_BIT);


	//---------------------------------------------------
	//----- SET THE MEMORY MAPPING CONTROL REGISTER -----	
	//---------------------------------------------------
	//(MEMMAP at address 0xE01F C040) accordingly. The MEMMAP register gives the application the flexibility of executing interrupts from different memory
	//regions. For instance, if MEMAP is set to 0x2, the interrupt vectors would be mapped to 0x4000 0000 (bottom of on-chip SRAM).
	//- Done in Philips_LPC230X_Startup.s


	//-------------------------
	//----- CONFIGURE WDT -----
	//-------------------------
	WDCLKSEL = 0;							//Clk Source = Internal RC oscillator (default).  The nominal IRC frequency is 4 MHz.
	WDTC =	1000000;						//32bit the time-out value (/4 prescaller) (min 0x000000ff - thus the minimum time-out interval is TWDCLK × 256 × 4.
	WDMOD = (WDMOD_WDEN | WDMOD_WDRESET);	//Watchdog enabled and will cause reset.
    ClrWdt;									//Start the Watchdog timer



	//-------------------------------------------------
	//----- ENABLE / DISABLE POWER TO PERIPHERALS -----
	//-------------------------------------------------
	PCONP = (
			PCONP_PCTIM0 |			//Timer/Counter 0
			//PCONP_PCTIM1 |		//Timer/Counter 1
			PCONP_PCUART0 |			//UART0
			//PCONP_PCUART1 |		//UART1
			//PCONP_PCPWM0 |		//PWM0
			//PCONP_PCPWM1 |		//PWM1
			//PCONP_PCI2C0 |		//The I2C0 interface
			//PCONP_PCSPI |			//The SPI interface
			PCONP_PCRTC |			//The RTC power/clock
			//PCONP_PCSSP1 |		//The SSP1 interface
			//PCONP_PCEMC |			//External Memory Controller 1
			//PCONP_PCAD |			//A/D converter (ADC) (Note: Clear the PDN bit in the AD0CR before clearing this bit, and set this bit before setting PDN) (reset value = 0)
			//PCONP_PCAN1 |			//CAN Controller 1
			//PCONP_PCAN2 |			//CAN Controller 2
			//PCONP_PCI2C1 |		//The I2C1 interface
			PCONP_PCSSP0 |			//The SSP0 interface
			//PCONP_PCTIM2 |		//Timer 2
			//PCONP_PCTIM3 |		//Timer 3
			//PCONP_PCUART2 |		//UART 2
			//PCONP_PCUART3 |		//UART 3
			//PCONP_PCI2C2 |		//I2C interface 2
			//PCONP_PCI2CS |		//I2S interface
			//PCONP_PCSDC |			//SD card interface
			//PCONP_PCGPDMA |		//GP DMA function
			//PCONP_PCENET |		//Ethernet block
			//PCONP_PUSB |			//USB interface
			0x00000000
			);

	
	//--------------------------
	//----- CONFIGURE GPIO -----
	//--------------------------
	//(Device will powerup with all IO pins as inputs)

	SCS |= SCS_GPIOM_MASK;		//High speed GPIO mode for ports 0 and 1 (not slower legacy mode)

	FIO0SET = 0x48008004;		//1 = set pin high
	FIO0CLR = 0x10000000;		//1 = set pin low
	FIO0DIR = 0x78048004;		//0 = input, 1 = output.  (GPIO pins P0.29 and P0.30 are shared with the USB D+/? pins and must be configured to be the same direction (input or output)
	//FIO0MASK = 0x00000000;	//1 = pin is not affected by writes into the port's FIOSET, FIOCLR and FIOPIN registers.
	//FIO0PIN					//Read port state.  Write port state if all pins must be set at once to 1's & 0's


	FIO1SET = 0x80000000;		//1 = set pin high
	FIO1CLR = 0x00780000;		//1 = set pin low
	FIO1DIR = 0x80780000;		//0 = input, 1 = output
	//FIO1MASK = 0x00000000;	//1 = pin is not affected by writes into the port's FIOSET, FIOCLR and FIOPIN registers.
	//FIO1PIN					//Read port state.  Write port state if all pins must be set at once to 1's & 0's

	FIO2SET = 0x000003fd;		//1 = set pin high
	FIO2CLR = 0x00000000;		//1 = set pin low
	FIO2DIR = 0x000023fd;		//0 = input, 1 = output
	//FIO2MASK = 0x00000000;	//1 = pin is not affected by writes into the port's FIOSET, FIOCLR and FIOPIN registers.
	//FIO2PIN					//Read port state.  Write port state if all pins must be set at once to 1's & 0's

	FIO3SET = 0x06000000;		//1 = set pin high
	FIO3CLR = 0x00000000;		//1 = set pin low
	FIO3DIR = 0x06000000;		//0 = input, 1 = output
	//FIO3MASK = 0x00000000;	//1 = pin is not affected by writes into the port's FIOSET, FIOCLR and FIOPIN registers.
	//FIO3PIN					//Read port state.  Write port state if all pins must be set at once to 1's & 0's

	FIO4SET = 0x10000000;		//1 = set pin high
	FIO4CLR = 0x00000000;		//1 = set pin low
	FIO4DIR = 0x10000000;		//0 = input, 1 = output
	//FIO4MASK = 0x00000000;	//1 = pin is not affected by writes into the port's FIOSET, FIOCLR and FIOPIN registers.
	//FIO4PIN					//Read port state.  Write port state if all pins must be set at once to 1's & 0's



  	//------------------------------------------
	//----- CONFIGURE PIN PULL UPS / DOWNS -----
	//------------------------------------------
	//0x0 pull-up resistor enabled [reset default]
	//0x2 neither pull-up nor pull-down.
	//0x3 pull-down resistor enabled.

	//PORT 0
	//PINMODE0 |= (0x0 << PINSEL0_P0_0_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_1_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_2_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_3_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_4_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_5_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_6_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_7_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_8_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_9_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_10_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_11_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_12_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_13_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_14_BIT);
	//PINMODE0 |= (0x0 << PINSEL0_P0_15_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_16_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_17_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_18_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_19_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_20_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_21_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_22_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_23_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_24_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_25_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_26_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_27_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_28_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_29_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_30_BIT);
	//PINMODE1 |= (0x0 << PINSEL1_P0_31_BIT);

	//PORT 1
	//PINMODE2 |= (0x0 << PINSEL2_P1_0_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_1_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_2_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_3_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_4_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_5_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_6_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_7_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_8_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_9_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_10_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_11_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_12_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_13_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_14_BIT);
	//PINMODE2 |= (0x0 << PINSEL2_P1_15_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_16_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_17_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_18_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_19_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_20_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_21_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_22_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_23_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_24_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_25_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_26_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_27_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_28_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_29_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_30_BIT);
	//PINMODE3 |= (0x0 << PINSEL3_P1_31_BIT);

	//PORT 2
	//PINMODE4 |= (0x0 << PINSEL4_P2_0_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_1_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_2_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_3_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_4_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_5_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_6_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_7_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_8_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_9_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_10_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_11_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_12_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_13_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_14_BIT);
	//PINMODE4 |= (0x0 << PINSEL4_P2_15_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_16_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_17_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_18_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_19_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_20_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_21_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_22_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_23_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_24_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_25_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_26_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_27_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_28_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_29_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_30_BIT);
	//PINMODE5 |= (0x0 << PINSEL5_P2_31_BIT);

	//PORT 3
	//PINMODE6 |= (0x0 << PINSEL6_P3_0_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_1_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_2_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_3_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_4_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_5_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_6_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_7_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_8_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_9_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_10_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_11_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_12_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_13_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_14_BIT);
	//PINMODE6 |= (0x0 << PINSEL6_P3_15_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_16_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_17_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_18_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_19_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_20_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_21_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_22_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_23_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_24_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_25_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_26_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_27_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_28_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_29_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_30_BIT);
	//PINMODE7 |= (0x0 << PINSEL7_P3_31_BIT);

	//PORT 4
	//PINMODE8 |= (0x0 << PINSEL8_P4_0_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_1_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_2_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_3_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_4_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_5_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_6_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_7_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_8_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_9_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_10_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_11_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_12_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_13_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_14_BIT);
	//PINMODE8 |= (0x0 << PINSEL8_P4_15_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_16_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_17_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_18_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_19_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_20_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_21_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_22_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_23_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_24_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_25_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_26_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_27_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_28_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_29_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_30_BIT);
	//PINMODE9 |= (0x0 << PINSEL9_P4_31_BIT);


  	//-------------------------------------------
	//----- CONFIGURE PIN SPECIAL FUNCTIONS -----
	//-------------------------------------------
    //0x0 Primary function, typically GPIO port [reset default]
	//0x1 First alternate function
	//0x2 Second alternate function
	//0x3 Third alternate function

	//PORT 0
	//PINSEL0 |= (0x0 << PINSEL0_P0_0_BIT);
	//PINSEL0 |= (0x0 << PINSEL0_P0_1_BIT);
	PINSEL0 |= (0x1 << PINSEL0_P0_2_BIT);			//UART0
	PINSEL0 |= (0x1 << PINSEL0_P0_3_BIT);			//UART0
	//PINSEL0 |= (0x1 << PINSEL0_P0_4_BIT);
	//PINSEL0 |= (0x1 << PINSEL0_P0_5_BIT);
	//PINSEL0 |= (0x1 << PINSEL0_P0_6_BIT);
	//PINSEL0 |= (0x2 << PINSEL0_P0_7_BIT);
	//PINSEL0 |= (0x2 << PINSEL0_P0_8_BIT);
	//PINSEL0 |= (0x2 << PINSEL0_P0_9_BIT);
	//PINSEL0 |= (0x2 << PINSEL0_P0_10_BIT);
	//PINSEL0 |= (0x2 << PINSEL0_P0_11_BIT);
	//PINSEL0 |= (0x0 << PINSEL0_P0_12_BIT);
	//PINSEL0 |= (0x0 << PINSEL0_P0_13_BIT);
	//PINSEL0 |= (0x0 << PINSEL0_P0_14_BIT);
	PINSEL0 |= (0x2 << PINSEL0_P0_15_BIT);			//SSP0 SCK
	//PINSEL1 |= (0x0 << PINSEL1_P0_16_BIT);
	PINSEL1 |= (0x2 << PINSEL1_P0_17_BIT);			//SSP0 MISO
	PINSEL1 |= (0x2 << PINSEL1_P0_18_BIT);			//SSP0 MOSI
	//PINSEL1 |= (0x0 << PINSEL1_P0_19_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_20_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_21_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_22_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_23_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_24_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_25_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_26_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_27_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_28_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_29_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_30_BIT);
	//PINSEL1 |= (0x0 << PINSEL1_P0_31_BIT);

	//PORT 1
	//PINSEL2 |= (0x1 << PINSEL2_P1_0_BIT);
	//PINSEL2 |= (0x1 << PINSEL2_P1_1_BIT);
	//PINSEL2 |= (0x0 << PINSEL2_P1_2_BIT);
	//PINSEL2 |= (0x0 << PINSEL2_P1_3_BIT);
	//PINSEL2 |= (0x1 << PINSEL2_P1_4_BIT);
	//PINSEL2 |= (0x0 << PINSEL2_P1_5_BIT);
	//PINSEL2 |= (0x0 << PINSEL2_P1_6_BIT);
	//PINSEL2 |= (0x0 << PINSEL2_P1_7_BIT);
	//PINSEL2 |= (0x1 << PINSEL2_P1_8_BIT);
	//PINSEL2 |= (0x1 << PINSEL2_P1_9_BIT);
	//PINSEL2 |= (0x1 << PINSEL2_P1_10_BIT);
	//PINSEL2 |= (0x0 << PINSEL2_P1_11_BIT);
	//PINSEL2 |= (0x0 << PINSEL2_P1_12_BIT);
	//PINSEL2 |= (0x0 << PINSEL2_P1_13_BIT);
	//PINSEL2 |= (0x1 << PINSEL2_P1_14_BIT);
	//PINSEL2 |= (0x1 << PINSEL2_P1_15_BIT);
	//PINSEL3 |= (0x1 << PINSEL3_P1_16_BIT);
	//PINSEL3 |= (0x1 << PINSEL3_P1_17_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_18_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_19_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_20_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_21_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_22_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_23_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_24_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_25_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_26_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_27_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_28_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_29_BIT);
	//PINSEL3 |= (0x3 << PINSEL3_P1_30_BIT);
	//PINSEL3 |= (0x0 << PINSEL3_P1_31_BIT);

	//PORT 2
	//PINSEL4 |= (0x2 << PINSEL4_P2_0_BIT);
	//PINSEL4 |= (0x2 << PINSEL4_P2_1_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_2_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_3_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_4_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_5_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_6_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_7_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_8_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_9_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_10_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_11_BIT);
	//PINSEL4 |= (0x1 << PINSEL4_P2_12_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_13_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_14_BIT);
	//PINSEL4 |= (0x0 << PINSEL4_P2_15_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_16_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_17_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_18_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_19_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_20_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_21_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_22_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_23_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_24_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_25_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_26_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_27_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_28_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_29_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_30_BIT);
	//PINSEL5 |= (0x0 << PINSEL5_P2_31_BIT);

	//PORT 3
	//PINSEL6 |= (0x0 << PINSEL6_P3_0_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_1_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_2_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_3_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_4_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_5_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_6_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_7_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_8_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_9_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_10_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_11_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_12_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_13_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_14_BIT);
	//PINSEL6 |= (0x0 << PINSEL6_P3_15_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_16_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_17_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_18_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_19_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_20_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_21_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_22_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_23_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_24_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_25_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_26_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_27_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_28_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_29_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_30_BIT);
	//PINSEL7 |= (0x0 << PINSEL7_P3_31_BIT);

	//PORT 4
	//PINSEL8 |= (0x0 << PINSEL8_P4_0_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_1_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_2_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_3_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_4_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_5_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_6_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_7_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_8_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_9_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_10_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_11_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_12_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_13_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_14_BIT);
	//PINSEL8 |= (0x0 << PINSEL8_P4_15_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_16_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_17_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_18_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_19_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_20_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_21_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_22_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_23_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_24_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_25_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_26_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_27_BIT);
	//PINSEL9 |= (0x3 << PINSEL9_P4_28_BIT);
	//PINSEL9 |= (0x3 << PINSEL9_P4_29_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_30_BIT);
	//PINSEL9 |= (0x0 << PINSEL9_P4_31_BIT);


	//--------------------------------
	//----- SETUP AtoD CONVERTER -----
	//--------------------------------
	/*
	AD0CR = (
			(0x10 << AD0CR_SEL_BIT) |			//AD bit to sample
			(3 << AD0CR_CLKDIV_BIT) |			//PCLK is divided by (this value + 1) to produce the clock for the A/D converter, which should be less than or equal to 4.5 MHz.
			(AD0CR_BURST) |						//Continuous burst sample (we are only using 1 input)
			(0 << AD0CR_CLKS_BIT) |				//Defines number of clocks used for each conversion in Burst mode (0 = 10 bit max resolution)
			(AD0CR_PDN));						//AtoD enabled
	*/



	//------------------------
	//----- SETUP TIMERS -----
	//------------------------
	//(INCLUDE THE USAGE OF ALL TIMERS HERE EVEN IF NOT SETUP HERE SO THIS IS THE ONE POINT OF
	//REFERENCE TO KNOW WHICH TIMERS ARE IN USE AND FOR WHAT).


	//----- SETUP TIMER 0 (32bit) -----
	//Used for: Heartbeat
	T0CTCR = (											//Count Control Register
			(0x0 << T0CTCR_Counter_Timer_Mode_BIT) |	//0x0 = Timer Mode: every rising PCLK edge, 0x1 = Counter Mode: TC incremented on rising edges on the CAP input, 0x2 = Counter Mode: TC incremented on falling edges on the CAP input, 0x3 = Counter Mode: TC is incremented on both edges on the CAP input
			(0x0 << T0CTCR_Count_Input_Select_BIT));	//When bits 1:0 in this register are not 00, these bits select which CAP pin is sampled for clocking
	T0PR = 0;								//Prescale register.  Prescale Counter increments on every PCLK. When it reaches the TxPR value the Timer incremented and the Prescale Counter is reset on the next PCLK. Timer will increment on every PCLK when PR = 0, every 2 PCLKs when PR = 1, etc.
	T0MCR = (T0MCR_MR0I | T0MCR_MR0R);		//Interrupt on MR0, Reset on MR0
    T0MR0 =	15000;							//Match register
    //T0CCR = 0;							//Capture Control Register
    //T0EMR = 0;							//External Match Register
	T0TCR =	T0TCR_Counter_Enable;			//Timer Control Register (T0TCR_Counter_Enable, T0TCR_Counter_Reset)
    //IRQ enabled in interrupts section below


	//----- SETUP TIMER 1 (32bit) -----
	//Used for: Available
	/*
	T1CTCR = (											//Count Control Register
			(0x0 << T1CTCR_Counter_Timer_Mode_BIT) |	//0x0 = Timer Mode: every rising PCLK edge, 0x1 = Counter Mode: TC incremented on rising edges on the CAP input, 0x2 = Counter Mode: TC incremented on falling edges on the CAP input, 0x3 = Counter Mode: TC is incremented on both edges on the CAP input
			(0x0 << T1CTCR_Count_Input_Select_BIT));	//When bits 1:0 in this register are not 00, these bits select which CAP pin is sampled for clocking
	T1PR = 0;								//Prescale register.  Prescale Counter increments on every PCLK. When it reaches the TxPR value the Timer incremented and the Prescale Counter is reset on the next PCLK. Timer will increment on every PCLK when PR = 0, every 2 PCLKs when PR = 1, etc.
	T1MCR = (T1MCR_MR0I | T1MCR_MR0R);		//Interrupt on MR0, Reset on MR0
    T1MR0 =									//Match register
    //T1CCR = 0;							//Capture Control Register
    //T1EMR = 0;							//External Match Register
	T1TCR =	T1TCR_Counter_Enable;			//Timer Control Register (T0TCR_Counter_Enable, T0TCR_Counter_Reset)
	*/

	//----- SETUP TIMER 2 (32bit) -----
	//Used for: Available
	/*
	T2CTCR = (											//Count Control Register
			(0x0 << T2CTCR_Counter_Timer_Mode_BIT) |	//0x0 = Timer Mode: every rising PCLK edge, 0x1 = Counter Mode: TC incremented on rising edges on the CAP input, 0x2 = Counter Mode: TC incremented on falling edges on the CAP input, 0x3 = Counter Mode: TC is incremented on both edges on the CAP input
			(0x0 << T2CTCR_Count_Input_Select_BIT));	//When bits 1:0 in this register are not 00, these bits select which CAP pin is sampled for clocking
	T2PR = 0;								//Prescale register.  Prescale Counter increments on every PCLK. When it reaches the TxPR value the Timer incremented and the Prescale Counter is reset on the next PCLK. Timer will increment on every PCLK when PR = 0, every 2 PCLKs when PR = 1, etc.
	T2MCR = (T2MCR_MR0I | T2MCR_MR0R);		//Interrupt on MR0, Reset on MR0
    T2MR0 =									//Match register
    //T2CCR = 0;							//Capture Control Register
    //T2EMR = 0;							//External Match Register
	T2TCR =	T2TCR_Counter_Enable;			//Timer Control Register (T0TCR_Counter_Enable, T0TCR_Counter_Reset)
	*/


	//----- SETUP TIMER 3 (32bit) -----
	//Used for: Available
	/*
	T3CTCR = (											//Count Control Register
			(0x0 << T3CTCR_Counter_Timer_Mode_BIT) |	//0x0 = Timer Mode: every rising PCLK edge, 0x1 = Counter Mode: TC incremented on rising edges on the CAP input, 0x2 = Counter Mode: TC incremented on falling edges on the CAP input, 0x3 = Counter Mode: TC is incremented on both edges on the CAP input
			(0x0 << T3CTCR_Count_Input_Select_BIT));	//When bits 1:0 in this register are not 00, these bits select which CAP pin is sampled for clocking
	T3PR = 0;								//Prescale register.  Prescale Counter increments on every PCLK. When it reaches the TxPR value the Timer incremented and the Prescale Counter is reset on the next PCLK. Timer will increment on every PCLK when PR = 0, every 2 PCLKs when PR = 1, etc.
	T3MCR = (T3MCR_MR0I | T3MCR_MR0R);		//Interrupt on MR0, Reset on MR0
    T3MR0 =									//Match register
    //T3CCR = 0;							//Capture Control Register
    //T3EMR = 0;							//External Match Register
	T3TCR =	T3TCR_Counter_Enable;			//Timer Control Register (T0TCR_Counter_Enable, T0TCR_Counter_Reset)
	*/




	//---------------------
	//----- SETUP SSP -----
	//---------------------

	//----- SETUP SPI -----
	//Used for: SD Memory Card
	//We don't use the SPI port because its slower than SSP0
	SSP0CPSR = 150;							//CPSDVSR.  Even value between 2 and 254 by which SSPPCLK is divided before being used by SCR
	SSP0CR0 = (((1 - 1) << SSP0CR0_SCR_BIT) | 0x07);	//8 bit, idle low, input data valid on the rising edge of the clock (Our transmit transistion occurs on transition from active (high) to Idle (low) clock state)
											//SCR (Serial clock rate) is required value - 1
											//SD Card max SPI clock = 20MHz.
											//SSP0CPSR = 150, SCR = 0 gives 400KHz @ SSPPCLK 60MHz
                                            //SSP0CPSR = 4, SCR = 0 gives 15MHz @ SSPPCLK 60MHz

    SSP0CR1 = SSP0CR1_SSE;					//Enable SSP port (after setting up other registers)
											//Input data is valid on the rising edge of the clock (Our transmit transistion occurs on transition from active (high) to Idle (low) clock state)
	
	//SSP0DR								//SPI Data Register. Write data to tx, read data received
	//SSP0SR								//SPI Status Register - shows the status of the SPI. (RO)
	//SSP0INT								//SPI Interrupt Flag. This register contains the interrupt flag for the SPI interface.

	//RX has an 8 frame fifo so ensure its empty
    while (SSP0SR & SSP0SR_RNE)
		b_temp = SSP0DR;


	//----- SETUP SSP 1 -----
	//Used for: Available
	/*
	SSP1CPSR = 2;							//CPSDVSR.  Even value between 2 and 254 by which SSPPCLK is divided before being used by SCR
	SSP1CR0 = (((18 - 1) << SSP1CR0_SCR_BIT) | 0x07);	//8 bit, idle low, input data valid on the rising edge of the clock (Our transmit transistion occurs on transition from active (high) to Idle (low) clock state)
											//SCR (Serial clock rate) is required value - 1
											//VS1053b max SPI clock for reads = CLKI / 7 = 12MHz / 7 = 1.714MHz
											//SSP1CPSR = 2, SCR = 18 gives 1.6666MHz @ SSPPCLK 60MHz
											//We need to be faster than the 1.536MHz I2S bitrate from the DSP incoming audio

    SSP1CR1 = SSP1CR1_SSE;					//Enable SSP port (after setting up other registers)
											//Input data is valid on the rising edge of the clock (Our transmit transistion occurs on transition from active (high) to Idle (low) clock state)
	
	//SSP1DR								//SPI Data Register. Write data to tx, read data received
	//SSP1SR								//SPI Status Register - shows the status of the SPI. (RO)
	//SSP1INT								//SPI Interrupt Flag. This register contains the interrupt flag for the SPI interface.
	*/


	//---------------------
	//----- SETUP I2C -----
	//---------------------

	//----- SETUP I2C 2 -----
	//Used for: Available
	//Mode: Master
	//Bit Frequency = pclk / (I2CSCLH + I2CSCLL)
	//100kHz = 15MHz / (I2CSCLH + I2CSCLL)
	//Therefore I2CSCLH + I2CSCLL = 150
	//Split it between the high and low bit time registers so: I2CSCLH = 75 and I2CSCLL = 75
	/*
	I2C2CONCLR = (I2C2CONCLR_I2ENC | I2C2CONCLR_STAC | I2C2CONCLR_SIC | I2C2CONCLR_AAC);		//AA not set means I2C will not enter slave mode if addressed
	I2C2CONSET = I2C2CONSET_I2EN;
    I2C2SCLH = 75;
	I2C2SCLL = 75;
	*/


	//-----------------------
	//----- SETUP USART -----
	//-----------------------
	//On reset UART0 is enabled, other UART's are disabled
	//Ensure UART receive pins do no have pull down resistors enabled

	//----- SETUP UART 0 -----
	//Used for: Available
	U0LCR = 0x03;								//Line control register (8 bit) (8 bit, no parity)
	U0FCR = 0;									//FIFO control register (8 bit)
	
	//Set BAUD rate to 9600 @ PCLK = CCLK/0
    U0LCR |= U0LCR_Divisor_Latch_Access_Bit;
	U0DLL = 135;								//Divisor latch (baud rate) LSB (8 bit) (DLAB = 1)
	U0DLM = 1;									//Divisor latch (baud rate) MSB (8 bit) (DLAB = 1)
	//U0FDR = ((0x01 << U0FDR_MULVAL_BIT) | (0x00 << U0FDR_DIVADDVAL_BIT));	//Fractional divider register (8 bit)

	U0TER = 0x80;								//Transmit enable register (8 bit)

	//Setup interrupts
	U0LCR &= ~U0LCR_Divisor_Latch_Access_Bit;
	U0IER = U0IER_RBR_Interrupt_Enable;			//Interrupt enable register (8 bit) (DLAB = 0)
	//IRQ enabled in interrupts section below


	//----- SETUP UART 1 -----
	//Used for:Available
	/*
	//(N.B. UART1 has additional modem control function, but this can be ignored unless enabled)
	U1LCR = 0x03;								//Line control register (8 bit) (8 bit, no parity)
	U1FCR = 0;									//FIFO control register (8 bit)
	
	//Set BAUD rate to 9600 @ PCLK = CCLK/0
    U1LCR |= U1LCR_Divisor_Latch_Access_Bit;
	U1DLL = 135;								//Divisor latch (baud rate) LSB (8 bit) (DLAB = 1)
	U1DLM = 1;									//Divisor latch (baud rate) MSB (8 bit) (DLAB = 1)
	//U1FDR = ((0x01 << U1FDR_MULVAL_BIT) | (0x00 << U1FDR_DIVADDVAL_BIT));	//Fractional divider register (8 bit)

	U1TER = 0x80;								//Transmit enable register (8 bit)

	//Setup interrupts
	U1LCR &= ~U1LCR_Divisor_Latch_Access_Bit;
	U1IER = U1IER_RBR_Interrupt_Enable;			//Interrupt enable register (8 bit) (DLAB = 0)
	//IRQ enabled in interrupts section below
	*/

    


	//----- SETUP UART 3 -----
	//Used for: Available
	/*
	U3LCR = 0x03;								//Line control register (8 bit) (8 bit, no parity)
	U3FCR = 0;									//FIFO control register (8 bit)
	
	//Set BAUD rate to 17857.1 @ PCLK = CCLK/0
    U3LCR |= U3LCR_Divisor_Latch_Access_Bit;
	U3DLL = 210;								//Divisor latch (baud rate) LSB (8 bit) (DLAB = 1)
	U3DLM = 0;									//Divisor latch (baud rate) MSB (8 bit) (DLAB = 1)
	//U3FDR = ((0x01 << U3FDR_MULVAL_BIT) | (0x00 << U3FDR_DIVADDVAL_BIT));	//Fractional divider register (8 bit)

	U3TER = 0x80;								//Transmit enable register (8 bit)

	//Setup interrupts
	U3LCR &= ~U3LCR_Divisor_Latch_Access_Bit;
	U3IER = U3IER_RBR_Interrupt_Enable;			//Interrupt enable register (8 bit) (DLAB = 0)
	//IRQ enabled in interrupts section below
	*/




	//---------------------
	//----- SETUP DMA -----
	//---------------------
	//DMA0 used for: Available
	//DMA1 used for: Available
	//DMACConfiguration = DMACConfiguration_E;	//Enable DMA, little endian mode (include DMACConfiguration_M for big endian)

	//Defining ram to be used for DMA example:
	//BYTE dma_mp3_tx_buffer[512] __attribute__ ((section(".usb_ram")));		//Must use DMA accessible ram area

	//---------------------------------------
	//----- SETUP RTC (REAL TIME CLOCK) -----
	//---------------------------------------
	//Leap year:
    //The RTC does a simple bit comparison to see if the two lowest order bits of the year counter are zero. If true, then the RTC considers
	//that year a leap year. The RTC considers all years evenly divisible by 4 as leap years. This algorithm is accurate from the year 1901
	//through the year 2099, but fails for the year 2100, which is not a leap year. The only effect of leap year on the RTC is to alter the
	//length of the month of February for the month, day of month, and year counters
	CCR = CCR_CLKSRC;							//Take clock from 32.768kHz oscillator
	CCR |= CCR_CLKEN;							//Enable clock

	/*Examples of usage
	//----- SET THE TIME -----
	CCR &= ~CCR_CLKEN;							//Disable clock to allow timer registers to be setup
	YEAR = 2009;								//Year value (0 to 4095)
	MONTH = 9;									//Month value (1 to 12)
	DOM = 15;									//Day of month value (1 to 28, 29, 30, or 31 depending on the month and whether it is a leap year)
	//DOY = 1;									//Day of year value in the range of 1 to 365 (366 for leap years).
	DOW = 2;									//Day of week value (0 to 6)
	HOUR = 14;									//Hours value (0 to 23)
	MIN = 22;									//Minutes value (0 to 59)
	SEC = 0;									//Seconds value (0 to 59)
	CCR |= CCR_CLKEN;							//Enable clock to start time

	//----- READ THE TIME -----
	BYTE rtc_year = 0;
	BYTE rtc_month = 0;
	BYTE rtc_date = 0;
	BYTE rtc_hours = 0;
	BYTE rtc_minutes = 0;			
	BYTE rtc_seconds = 0;

	DWORD time_value1 = 0xffffffff;
	DWORD time_value0;
	WORD year_temp;
	
	while (time_value1 != CTIME1)		//Protect against roll over of date while reading
	{
		time_value1 = CTIME1;
		time_value0 = CTIME0;
	}

    year_temp = (WORD)(time_value1 >> CTIME1_Year_BIT);
	while (year_temp >= 1000)			//Convert year to 0 - 99 for ffs
		year_temp -= 1000;
	while (year_temp >= 100)
		year_temp -= 100;
	rtc_year = (BYTE)year_temp;
	rtc_month = (BYTE)(time_value1 >> CTIME1_Month_BIT);
	rtc_date = (BYTE)(time_value1 >> CTIME1_Day_of_Month_BIT);
	rtc_hours = (BYTE)(time_value0 >> CTIME0_Hours_BIT);
	rtc_minutes = (BYTE)(time_value0 >> CTIME0_Minutes_BIT);
	rtc_seconds = (BYTE)(time_value0 >> CTIME0_Seconds_BIT);
	*/


	//----------------------------
	//----- SETUP INTERRUPTS -----
	//----------------------------
	//It is recommended that only one interrupt source should be classified as an FIQ.
	//It is always safe to program the Default Vector Address Register (VICDefVectAddr) with a dummy ISR address wherein the VIC would /be updated (by performing a
	//write operation on the VIC Vector Address register (VICVectAddr) to avoid any spurious interrupts.

	//----- TIMER 0 -----
    VICVectAddr4 = (unsigned int)&timer0_irq_handler;		//C function to call on interrupt
    VICVectPriority4 = 10;									//Priority [Highest]0 to 15[lowest]
	VICIntEnable |= VICIntEnable_TIMER0;

	//----- ENABLE INTERRUPTS -----
	ENABLE_INT;


}






//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************
//**********************************************************************************************************************************************


//***********************************
//***********************************
//********** MAIN FUNCTION **********
//***********************************
//***********************************
int main (void)
{


	//**********************
	//**********************
	//***** INITIALISE *****
	//**********************
	//**********************
	initialise();





	//*********************
	//*********************
	//***** MAIN LOOP *****
	//*********************
	//*********************
	while(1)						//(Do forever)
	{
		//----- RESET THE WATCHDOG TIMEOUT TIMER -----
		ClrWdt;


		//----- READ SWITCHES -----
		read_switches();


		//----- PROCESS MODE -----
		process_mode();


		//----- PROCESS FAT FILING SYSTEM -----
		ffs_process();





		
	}
}




//***********************************
//***********************************
//********** READ SWITCHES **********
//***********************************
//***********************************
void read_switches (void)
{
	BYTE switches_read;
	static BYTE switches_last = 0;
	static BYTE switches_debounced_last = 0;


	//RESET THE NEW SWITCH PRESS REGISTER
	switches_new = 0;

	//ONLY DO EVERY 10MS FOR SWITCH CONTACT DEBOUNCE
	if (read_switches_flag == 0)
		return;

	read_switches_flag = 0;

	//GET THE SWITCH INPUTS
	switches_read = 0;
	if (!(FIO1PIN & 0x04000000))
		switches_read |= 0x01;

	//DEBOUNCE
	switches_debounced = switches_last & switches_read;

	//FLAG NEW BUTTON PRESSES
	switches_new = switches_debounced ^ switches_debounced_last;
	switches_new &= switches_debounced;

	//STORE LAST REGISTERS FOR NEXT TIME
	switches_debounced_last = switches_debounced;
	switches_last = switches_read;

}





const char filename_all[] = {"*.*"};
const char filename_test_txt[] = {"test-c30.txt"};
const char filename_test_csv[] = {"test-c30.csv"};

const char read_access_mode[] = {"r"};
const char write_access_mode[] = {"w"};
const char append_access_mode[] = {"a"};
const char read_write_access_mode[] = {"r+"};
const char write_read_access_mode[] = {"w+"};
const char append_read_access_mode[] = {"a+"};

const char text_file_line1_string[] = {"THIS IS A SAMPLE FILE\r\n"};  //('\r' = carriage return, '\n' = line feed)
const char text_file_line2_string[] = {"Created by the embedded-code.com MMC / SD FAT driver\r\n"};
const char spreadsheet_file_no_text_file_string[] = {"The text.txt file could not be read!"};

//**********************************
//**********************************
//********** PROCESS MODE **********
//**********************************
//**********************************
void process_mode (void)
{
	static FFS_FILE *our_file_0;
	static FFS_FILE *our_file_1;
	BYTE b_temp;
	char c_string_buffer[60];
	int i_temp;



	//----- IF CARD IS REMOVED ENSURE WE RESET BACK WAITING FOR CARD TO BE INSERTED -----
	if ((test_application_state != TA_PROCESS_WAIT_FOR_CARD) && (!ffs_card_ok))
		test_application_state = TA_PROCESS_WAIT_FOR_CARD;

	//---------------------------------
	//----- PROCESS STATE MACHINE -----
	//---------------------------------
	switch (test_application_state)
	{
	case TA_PROCESS_WAIT_FOR_CARD:
		//-------------------------------------------
		//----- WAITING FOR CARD TO BE INSERTED -----
		//-------------------------------------------
		LED1(1);
		LED2(0);
		if (ffs_card_ok)
		{
			//A CARD HAS BEEN INSERTED AND IS READY TO ACCESS
			test_application_state = TA_PROCESS_CARD_INSERTED;
		}
		break;

	case TA_PROCESS_CARD_INSERTED:
		//----------------------------
		//----- CARD IS INSERTED -----
		//----------------------------
		LED1(0);
		LED2(1);
		if (SWITCH_1_NEW_PRESS)
		{
			//A CARD HAS BEEN INSERTED AND IS READY TO ACCESS
			test_application_state = TA_PROCESS_DELETE_AND_CREATE_FILES;
		}
		break;

	case TA_PROCESS_DELETE_AND_CREATE_FILES:
		//-------------------------------------------------
		//----- DELETE ALL FILES AND CREATE NEW FILES -----
		//-------------------------------------------------

		//ALL FILES IN THE ROOT DIRECTORY ARE DELETED
		//A NEW FILE CALLED TEST.TXT IS CREATED CONTAINING EXAMPLE TEST DATA.
		//A NEW SPREADSHEET FILE CALLED TEST.CSV IS CREATED CONTAINING TEST DATA FROM THE TEST.TXT FILE

		//----- DELETE ALL FILES IN THE ROOT DIRECTORY -----
		while (ffs_remove(filename_all) == 0)
			;

		//----- CREATE NEW FILE FOR WRITING -----
		our_file_0 = ffs_fopen(filename_test_txt, write_access_mode);
		if (our_file_0 != 0)
		{
			//----- FILE WAS SUCESSFULLY CREATED -----

			//----- WRITE STRING DATA -----
			if (ffs_fputs(text_file_line1_string, our_file_0) == FFS_EOF)
			{
				test_application_state = TA_PROCESS_ERROR;	//Write error
				break;
			}

			//----- WRITE A DATA BLOCK -----
			ffs_fwrite(text_file_line2_string, sizeof(char), (int)strlen(text_file_line2_string), our_file_0);

			//----- WRITE INDIVIDUAL BYTES OF DATA -----
			for (b_temp = '0'; b_temp <= '9'; b_temp++)
			{
				if (ffs_fputc((int)b_temp, our_file_0) == FFS_EOF)
				{
					test_application_state = TA_PROCESS_ERROR;	//Write error
					break;
				}
			}

			//----- CLOSE THE FILE -----
			if (ffs_fclose(our_file_0))
			{
				test_application_state = TA_PROCESS_ERROR;	//Error - could not close
				break;
			}

		}
		else
		{
			//----- ERROR - THE FILE COULD NOT BE CREATED -----
			test_application_state = TA_PROCESS_ERROR;
			break;
		}

		//----- CREATE NEW FILE FOR WRITING -----
		our_file_0 = ffs_fopen(filename_test_csv, write_access_mode);
		if (our_file_0 != 0)
		{
			//----- FILE WAS SUCESSFULLY CREATED -----

			//----- OPEN THE TEST.TXT FILE FOR READING IF IT EXISTS -----
			our_file_1 = ffs_fopen(filename_test_txt, read_access_mode);
			if (our_file_1 != 0)
			{
				//----- THE TEST.TXT FILE DOES EXIST -----
				//WRITE TO THE NEW SPREADSHEET FILE USING DATA FROM THE TEXT FILE

				//READ THE FIRST LINE FROM THE TEXT FILE
				if (ffs_fgets(c_string_buffer, 30, our_file_1) == 0)
				{
					test_application_state = TA_PROCESS_ERROR;		//Error - end of line not detected
					break;
				}

				//WRITE TO SPREADSHEET FILE
				if (ffs_fputs_char(c_string_buffer, our_file_0) == FFS_EOF)
				{
					test_application_state = TA_PROCESS_ERROR;		//Write error
					break;
				}

				//READ NEXT LINE AS A DATA BLOCK FROM THE TEXT FILE
				ffs_fread(c_string_buffer, sizeof(char), (int)strlen(text_file_line2_string), our_file_1);

				//WRITE TO SPREADSHEET FILE
				ffs_fwrite(c_string_buffer, sizeof(char), (int)strlen(text_file_line2_string), our_file_0);

				//WRITE SEVERAL COLUMNS  THE SPREADSHEET FILE
				ffs_fputc((int)'\r', our_file_0);
				ffs_fputc((int)'\n', our_file_0);

				for (b_temp = 'A'; b_temp <= 'Z'; b_temp++)
				{
					ffs_fputc((int)b_temp, our_file_0);
					ffs_fputc((int)',', our_file_0);
				}

				//CHECK TO SEE IF ANY ERROR HAS OCCURED
				if (ffs_ferror(our_file_0))
				{
					test_application_state = TA_PROCESS_ERROR;
					break;
				}


				//WRITE THE LAST CHARACTER OF THE TEXT FILE TO THE START OF THE NEXT ROW
				ffs_fputc((int)'\r', our_file_0);
				ffs_fputc((int)'\n', our_file_0);

				ffs_fseek(our_file_1, 0, FFS_SEEK_END);
				i_temp = ffs_fgetc(our_file_1);
				if (i_temp == FFS_EOF)
				{
					test_application_state = TA_PROCESS_ERROR;		//Read error
					break;
				}

				ffs_fputc(i_temp, our_file_0);

				ffs_fputc((int)'\r', our_file_0);
				ffs_fputc((int)'\n', our_file_0);

				//CLOSE THE TEST.TXT FILE
				if (ffs_fclose(our_file_1))
				{
					test_application_state = TA_PROCESS_ERROR;		//Error - could not close
					break;
				}
			}
			else
			{
				//----- THE TEST.TXT FILE DOES NOT EXIST -----
				//WRITE TO THE NEW SPREADSHEET FILE WITHOUT DATA FROM THE TEXT FILE

				if (ffs_fputs(spreadsheet_file_no_text_file_string, our_file_0) == FFS_EOF)
				{
					test_application_state = TA_PROCESS_ERROR;		//Write error
					break;
				}
			}



			//----- CLOSE THE SPREADSHEET FILE -----
			if (ffs_fclose(our_file_0))
			{
				test_application_state = TA_PROCESS_ERROR;		//Error - could not close
				break;
			}
		}
		else
		{
			//----- ERROR - THE FILE COULD NOT BE CREATED -----
			test_application_state = TA_PROCESS_ERROR;
			break;
		}

		//----- SUCCESS -----
		test_application_state = TA_PROCESS_CARD_OPERTATION_DONE;
		break;


	case TA_PROCESS_CARD_OPERTATION_DONE:
		//-----------------------------------------------------------------------------
		//----- OPERATION DONE - INDICATE SUCCESS AND WAIT FOR CARD TO BE REMOVED -----
		//-----------------------------------------------------------------------------
		LED1(0);
		LED2(0);
		break;


	case TA_PROCESS_ERROR:
		//--------------------------------------------------------------------------
		//----- ERROR OCCURED - INDICATE ERROR AND WAIT FOR CARD TO BE REMOVED -----
		//--------------------------------------------------------------------------
		LED1(1);
		LED2(1);

		//Try and close the files if they are open
		ffs_fclose(our_file_0);
		ffs_fclose(our_file_1);

		break;



	} //switch (test_application_state)



}















//*************************************************************************************************************************************
//*************************************************************************************************************************************
//*************************************************************************************************************************************
//*************************************************************************************************************************************
//*************************************************************************************************************************************
//*************************************************************************************************************************************
//*************************************************************************************************************************************

//************************************************
//************************************************
//********** INTERRUPT VECTOR LOCATIONS **********
//************************************************
//************************************************

//*******************************************
//*******************************************
//********** TIMER 0 HEARTBEAT IRQ **********
//*******************************************
//*******************************************
void timer0_irq_handler (void)
{
	static BYTE hb_10ms_timer = 0;
	static BYTE hb_100ms_timer = 0;
	static WORD hb_1sec_timer = 0;


	T0IR = 0x3f;							//Reset irq

	//-----------------------------
	//-----------------------------
	//----- HERE EVERY 1 mSec -----
	//-----------------------------
	//-----------------------------



	hb_10ms_timer++;
	if (hb_10ms_timer == 10)
	{
		//------------------------------
		//------------------------------
		//----- HERE EVERY 10 mSec -----
		//------------------------------
		//------------------------------
		hb_10ms_timer = 0;


		//----- GENERAL USE 10mS TIMER -----
		if (general_use_10ms_timer)
			general_use_10ms_timer--;


		//----- READ SWITCHES FLAG -----
		read_switches_flag = 1;

		//----- USER MODE 10mS TIMER -----
		if (user_mode_10ms_timer)
			user_mode_10ms_timer--;


		//----- FAT FILING SYSTEM DRIVER TIMER -----
		if (ffs_10ms_timer)
			ffs_10ms_timer--;

	} //if (hb_10ms_timer == 10)

	hb_100ms_timer++;
	if (hb_100ms_timer == 100)
	{
		//-------------------------------
		//-------------------------------
		//----- HERE EVERY 100 mSec -----
		//-------------------------------
		//-------------------------------
		hb_100ms_timer = 0;

		//----- GENERAL USE 100mS TIMER -----
		if (general_use_100ms_timer)
			general_use_100ms_timer--;


	} //if (hb_100ms_timer == 100)

	hb_1sec_timer++;
	if (hb_1sec_timer == 1000)
	{
		//----------------------------
		//----------------------------
		//----- HERE EVERY 1 Sec -----
		//----------------------------
		//----------------------------
		hb_1sec_timer = 0;





	} //if (hb_1sec_timer == 1000)


}	





