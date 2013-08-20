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
//PIC24 SAMPLE PROJECT C CODE FILE





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





//******************************************
//******************************************
//********** DEVICE CONFIGURATION **********
//******************************************
//******************************************
//These configuration defines do not need to be included, but having them means that the configuration bits will be automatically set and will be included in the .hex
//file created for the project, so that they do not need to be manually set when programming devices at manufacture.
//(The config names are given in the '.inc' file for the device being used)

#ifdef __DEBUG				//Debug mode selected in MPLAB
//----- WE'RE IN DEVELOPMENT MODE -----
	//--- FBS ---
	//Boot Segment Data Ram:-
	//RBS_LARGE_RAM = Large Sized Boot Ram, RBS_MEDIUM_RAM = Medium Sized Boot Ram, RBS_SMALL_RAM = Small Sized Boot Ram, RBS_NO_RAM = No Boot Ram
	//Boot Segment Program Memory:-
	//BSS_LARGE_FLASH_HIGH = High Security Large Boot Flash, BSS_MEDIUM_FLASH_HIGH = High Security Med Boot Flash, BSS_SMALL_FLASH_HIGH = High Security Small Boot Flash,
	//BSS_LARGE_FLASH_STD = Standard Security Lar Boot Flash, BSS_MEDIUM_FLASH_STD = Standard Security Med Boot Flash, BSS_SMALL_FLASH_STD = Standard Security Small Boot Flash,
	//BSS_NO_FLASH = No Boot Segment Program Memory
	//Write Protect :-
	//BWRP_WRPROTECT_ON = Enabled, BWRP_WRPROTECT_OFF = Disabled 
	_FBS(RBS_NO_RAM & BSS_NO_FLASH & BWRP_WRPROTECT_OFF)

	//--- FSS ---
	//Secure Segment Data Ram:-
	//RSS_LARGE_RAM = Large Sized Secure Ram, RSS_MEDIUM_RAM = Medium Sized Secure Ram, RSS_SMALL_RAM = Small Sized Secure Ram, RSS_NO_RAM = No Secure Ram
	//Secure Segment Program Memory:-
	//SSS_LARGE_FLASH_HIGH = High Security Lar Secure Flash, SSS_MEDIUM_FLASH_HIGH = High Security Med Secure Flash, SSS_SMALL_FLASH_HIGH = High Security Small Secure Flash,
	//SSS_LARGE_FLASH_STD = Standard Security Large Secure Flash, SSS_MEDIUM_FLASH_STD = Standard Security Med Secure Flash, SSS_SMALL_FLASH_STD = Standard Security Small Secure Flash,
	//SSS_NO_FLASH = No Secure Segment
	//Write Protect:-
	//SWRP_WRPROTECT_ON = Enabled, SWRP_WRPROTECT_OFF = Disabled 
	_FSS(RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF)

	//--- FGS ---
	//Code Protect:-
	//GSS_HIGH = high security protect on, GSS_STD = standard security code protect on, GSS_OFF = code protect off
	//Code Protect:-
	//GCP_ON = Enabled, GCP_OFF, Disabled
	//Write Protect:-
	//GWRP_ON = Enabled, GWRP_OFF = Disabled
	_FGS(GSS_OFF & GCP_OFF & GWRP_OFF)

	//--- FOSCSEL ---
	//Oscillator Source Selection:-
	//FNOSC_FRC = Fast RC oscillator, FNOSC_FRCPLL = Fast RC oscillator w/ divide and PLL, FNOSC_PRI = Primary oscillator (XT, HS, EC), FNOSC_PRIPLL = Primary oscillator (XT, HS, EC) w/ PLL,
	//FNOSC_SOSC = Secondary oscillator, FNOSC_LPRC = Low power RC oscillator, FNOSC_FRCDIV16 = Fast RC oscillator w/ divide by 16, FNOSC_LPRCDIVN = Low power Fast RC oscillator w/divide by N
	//Two-speed Oscillator Startup:-
	//IESO_OFF = Disabled, IESO_ON = Enabled
	_FOSCSEL(FNOSC_PRIPLL & IESO_OFF)

	//--- FOSC ---
	//Clock switching and clock monitor:-
	//FCKSM_CSECME = Both enabled, FCKSM_CSECMD = Only clock switching enabled, FCKSM_CSDCMD = Both disabled
	//OSC2 Pin function:-
	//OSCIOFNC_ON = Digital I/O, OSCIOFNC_OFF = OSC2 is clock O/P
	//Oscillator Selection:-
	//POSCMD_EC  = External clock, POSCMD_XT = XT oscillator, POSCMD_HS = HS oscillator, POSCMD_NONE = Primary disabled
	_FOSC(FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMD_XT)

	//--- FWDT ---
	//Watchdog Timer:-
	//FWDTEN_OFF = Disabled, FWDTEN_ON = Enabled
	//Windowed WDT:-
	//WINDIS_ON = Enabled, WINDIS_OFF = Disabled
	//Watchdog prescaler:-
	//WDTPRE_PR32 = 1:32 (1mS timeout), WDTPRE_PR128 = 1:128 (4mS timeout)
	//Watchdog postscaler:-
	//WDTPOST_PS1 = 1:1, WDTPOST_PS2 = 1:2, WDTPOST_PS4 = 1:4, WDTPOST_PS8 = 1:8, WDTPOST_PS16 = 1:16, WDTPOST_PS32 = 1:32, WDTPOST_PS64 = 1:64, WDTPOST_PS128 = 1:128, WDTPOST_PS256 = 1:256,
	//WDTPOST_PS512 = 1:512, WDTPOST_PS1024 = 1:1,024, WDTPOST_PS2048 = 1:2,048, WDTPOST_PS4096 = 1:4,096, WDTPOST_PS8192 = 1:8,192, WDTPOST_PS16384 = 1:16,384, WDTPOST_PS32768 = 1:32,768
	_FWDT(FWDTEN_ON & WINDIS_OFF & WDTPRE_PR32 & WDTPOST_PS2048)		//Wdt = 2.048 seconds

	//--- FPOR ---
	//Oower-on Reset Value:-
	//FPWRT_PWR1 = Disabled, FPWRT_PWR2 = 2ms, FPWRT_PWR4 = 4ms, FPWRT_PWR8 = 8ms, FPWRT_PWR16 = 16ms, FPWRT_PWR32 = 32ms, FPWRT_PWR64 = 64ms, FPWRT_PWR128 = 128ms
	_FPOR(FPWRT_PWR128);

#else
//----- WE'RE NOT IN DEVELOPMENT MODE -----
	//--- FBS ---
	//Boot Segment Data Ram:-
	//RBS_LARGE_RAM = Large Sized Boot Ram, RBS_MEDIUM_RAM = Medium Sized Boot Ram, RBS_SMALL_RAM = Small Sized Boot Ram, RBS_NO_RAM = No Boot Ram
	//Boot Segment Program Memory:-
	//BSS_LARGE_FLASH_HIGH = High Security Large Boot Flash, BSS_MEDIUM_FLASH_HIGH = High Security Med Boot Flash, BSS_SMALL_FLASH_HIGH = High Security Small Boot Flash,
	//BSS_LARGE_FLASH_STD = Standard Security Lar Boot Flash, BSS_MEDIUM_FLASH_STD = Standard Security Med Boot Flash, BSS_SMALL_FLASH_STD = Standard Security Small Boot Flash,
	//BSS_NO_FLASH = No Boot Segment Program Memory
	//Write Protect :-
	//BWRP_WRPROTECT_ON = Enabled, BWRP_WRPROTECT_OFF = Disabled 
	_FBS(RBS_NO_RAM & BSS_NO_FLASH & BWRP_WRPROTECT_OFF)

	//--- FSS ---
	//Secure Segment Data Ram:-
	//RSS_LARGE_RAM = Large Sized Secure Ram, RSS_MEDIUM_RAM = Medium Sized Secure Ram, RSS_SMALL_RAM = Small Sized Secure Ram, RSS_NO_RAM = No Secure Ram
	//Secure Segment Program Memory:-
	//SSS_LARGE_FLASH_HIGH = High Security Lar Secure Flash, SSS_MEDIUM_FLASH_HIGH = High Security Med Secure Flash, SSS_SMALL_FLASH_HIGH = High Security Small Secure Flash,
	//SSS_LARGE_FLASH_STD = Standard Security Large Secure Flash, SSS_MEDIUM_FLASH_STD = Standard Security Med Secure Flash, SSS_SMALL_FLASH_STD = Standard Security Small Secure Flash,
	//SSS_NO_FLASH = No Secure Segment
	//Write Protect:-
	//SWRP_WRPROTECT_ON = Enabled, SWRP_WRPROTECT_OFF = Disabled 
	_FSS(RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF)

	//--- FGS ---
	//Code Protect:-
	//GSS_HIGH = high security protect on, GSS_STD = standard security code protect on, GSS_OFF = code protect off
	//Code Protect:-
	//GCP_ON = Enabled, GCP_OFF, Disabled
	//Write Protect:-
	//GWRP_ON = Enabled, GWRP_OFF = Disabled
	_FGS(GSS_OFF & GCP_OFF & GWRP_OFF)

	//--- FOSCSEL ---
	//Oscillator Source Selection:-
	//FNOSC_FRC = Fast RC oscillator, FNOSC_FRCPLL = Fast RC oscillator w/ divide and PLL, FNOSC_PRI = Primary oscillator (XT, HS, EC), FNOSC_PRIPLL = Primary oscillator (XT, HS, EC) w/ PLL,
	//FNOSC_SOSC = Secondary oscillator, FNOSC_LPRC = Low power RC oscillator, FNOSC_FRCDIV16 = Fast RC oscillator w/ divide by 16, FNOSC_LPRCDIVN = Low power Fast RC oscillator w/divide by N
	//Two-speed Oscillator Startup:-
	//IESO_OFF = Disabled, IESO_ON = Enabled
	_FOSCSEL(FNOSC_PRIPLL & IESO_OFF)

	//--- FOSC ---
	//Clock switching and clock monitor:-
	//FCKSM_CSECME = Both enabled, FCKSM_CSECMD = Only clock switching enabled, FCKSM_CSDCMD = Both disabled
	//OSC2 Pin function:-
	//OSCIOFNC_ON = Digital I/O, OSCIOFNC_OFF = OSC2 is clock O/P
	//Oscillator Selection:-
	//POSCMD_EC  = External clock, POSCMD_XT = XT oscillator, POSCMD_HS = HS oscillator, POSCMD_NONE = Primary disabled
	_FOSC(FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMD_XT)

	//--- FWDT ---
	//Watchdog Timer:-
	//FWDTEN_OFF = Disabled, FWDTEN_ON = Enabled
	//Windowed WDT:-
	//WINDIS_ON = Enabled, WINDIS_OFF = Disabled
	//Watchdog prescaler:-
	//WDTPRE_PR32 = 1:32 (1mS timeout), WDTPRE_PR128 = 1:128 (4mS timeout)
	//Watchdog postscaler:-
	//WDTPOST_PS1 = 1:1, WDTPOST_PS2 = 1:2, WDTPOST_PS4 = 1:4, WDTPOST_PS8 = 1:8, WDTPOST_PS16 = 1:16, WDTPOST_PS32 = 1:32, WDTPOST_PS64 = 1:64, WDTPOST_PS128 = 1:128, WDTPOST_PS256 = 1:256,
	//WDTPOST_PS512 = 1:512, WDTPOST_PS1024 = 1:1,024, WDTPOST_PS2048 = 1:2,048, WDTPOST_PS4096 = 1:4,096, WDTPOST_PS8192 = 1:8,192, WDTPOST_PS16384 = 1:16,384, WDTPOST_PS32768 = 1:32,768
	_FWDT(FWDTEN_ON & WINDIS_OFF & WDTPRE_PR32 & WDTPOST_PS2048)		//Wdt = 2.048 seconds

	//--- FPOR ---
	//Oower-on Reset Value:-
	//FPWRT_PWR1 = Disabled, FPWRT_PWR2 = 2ms, FPWRT_PWR4 = 4ms, FPWRT_PWR8 = 8ms, FPWRT_PWR16 = 16ms, FPWRT_PWR32 = 32ms, FPWRT_PWR64 = 64ms, FPWRT_PWR128 = 128ms
	_FPOR(FPWRT_PWR128)
#endif




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
	WORD w_temp;

	//----- DISABLE INTERRUPTS DURING CONFIGURATION -----
	IFS0 = 0;
	IFS1 = 0;
	IFS2 = 0;
	IFS3 = 0;
	IFS4 = 0;
	IEC0 = 0;
	IEC1 = 0;
	IEC2 = 0;
	IEC3 = 0;
	IEC4 = 0;

	//----- RESET CONFIGURATION -----
	RCON = 0x0503;		//B15=TRAPR B14=IOPUWR B13=BGST B8=VREGS B7=EXTR B6=SWR B5=SWDTEN B4=WDTO B3=SLEEP B2=IDLE B1=BOR B0=POR

	//----- OSCILLATOR CONFIGURATION -----
	//Method to override OSCCON write protect
	//B13:12=COSC1:0 B9:8=NOSC1:0
	asm volatile("CLR.B W0");	
	asm volatile("MOV.B #0x78, W1");	
	asm volatile("MOV.B #0x9A, W2");	
	asm volatile("MOV.W #OSCCON, W3");	
	asm volatile("MOV.B W1, [W3+1]");	
	asm volatile("MOV.B W2, [W3+1]");	
	asm volatile("MOV.B W0, [W3+1]");	

	//B7=CLKLOCK B5=LOCK B3=CF B1=LPOSCEN B0=OSWEN
	asm volatile("CLR.B W0");	
	asm volatile("MOV.B #0x46, W1");	
	asm volatile("MOV.B #0x57, W2");	
	asm volatile("MOV.B W1, [W3+0]");	
	asm volatile("MOV.B W2, [W3+0]");	
	asm volatile("MOV.B W0, [W3+0]");	

	CLKDIV = 0;				//B15=ROI B14:12=DOZE2:0 B11=DOZEN B10:8=FRCDIV2:0 B7:6=PLLPOST1:0 B4:0=PLLPRE4:0
	PLLFBD = 0x001E;		//B8:0=PLLDIV8:0
	OSCTUN = 0;				//B5:0=TUN5:0

	//Wait for PLL to lock
	while(OSCCONbits.LOCK != 1)
		;

	//-------------------------
	//----- SETUP IO PINS -----
	//-------------------------
	//(Device will powerup with all IO pins as inputs)

	LATB =  0b0000000000000000;		//Setup the state of any pins that are outputs (inputs are don't care)
	TRISB = 0b0000000011000000;		//Setup the IO pin type (0 = output, 1 = input)

	LATC =  0b0000000000000000;
	TRISC = 0b0000000000000000;

	LATD =  0b0000000000000000;
	TRISD = 0b0000000000000011;
	ODCD =  0b0000000000000000;		//Setup the open drain option (0 = normal push pull, 1 = open drain)

	LATF =  0b0000000000000001;		//FFS_CE high on powerup
	TRISF = 0b0000000000000100;
	ODCF =  0b0000000000000000;

	LATG =  0b0000000000000000;
	TRISG = 0b0000000000000011;
	ODCG =  0b0000000000000000;

	//----- INPUT CHANGE NOTIFICATION CONFIGURATION -----
	CNEN1 = 0;		//Change notification interrupt enable (0 = off, 1 = enabled)
	CNEN2 = 0;
	CNPU1 = 0;		//Pin  pull ups (0 = no pull up, 1 = pull up enabled)
	CNPU2 = 0;

	//----- SETUP THE A TO D PINS -----
	AD1PCFGH = 0xFFFF;					//Select analog pins (1 = digital, 0 = analog)
	AD1PCFGL = 0xFFFF;
	AD1CON1 = 0;				//Analog module off
	//AD1CON2 = 0;
	//AD1CON3 = 0;
	//AD1CON4 = 0;
	//AD1CHS123 = 0;
	//AD1CHS0 = 0;
	//AD1CSSH = 0;
	//AD1CSSL = 0;

	//----- APPLICATION PIN DEFAULT STATES -----
	LED1_OFF = 1;
	LED2_OFF = 1;


	//------------------------
	//----- SETUP TIMERS -----
	//------------------------
	//(INCLUDE THE USAGE OF ALL TIMERS HERE EVEN IF NOT SETUP HERE SO THIS IS THE ONE POINT OF
	//REFERENCE TO KNOW WHICH TIMERS ARE IN USE AND FOR WHAT).


	//----- SETUP TIMER 1 -----
	//Used for: Available
	T1CON = 0;
	//TMR1 = 0;
	//PR1 = 0xffff;
	//(Timer is started later on in this function)


	//----- SETUP TIMER 2 -----
	//Used for: Available
	T2CON = 0;
	//TMR2 = 0;
	//PR2 = 0xffff;
	//(Timer is started later on in this function)


	//----- SETUP TIMER 3 -----
	//Used for: Available
	T3CON = 0;
	//TMR3 = 0;
	//TMR3HLD = 0;		//Timer holding register for 32bit
	//PR3 = 0xffff;
	//(Timer is started later on in this function)

	//----- SETUP TIMER 4 -----
	//Used for: Available
	T4CON = 0;
	//TMR4 = 0;
	//PR4 = 0xffff;
	//(Timer is started later on in this function)

	//----- SETUP TIMER 5 -----
	//Used for: Heartbeat
	T5CON = 0;
	TMR5 = 0;
	TMR5HLD = 0;
	PR5 = 0x1388;
	//(Timer is started later on in this function)

	//----- SETUP TIMER 6 -----
	//Used for: Available
	T6CON = 0;
	//TMR6 = 0;
	//PR6 = 0XFFFF;
	//(Timer is started later on in this function)

	//----- SETUP TIMER 7 -----
	//Used for: Available
	T7CON = 0;
	//TMR7 = 0;
	//TMR7HLD = 0;
	//PR7 = 0xffff;
	//(Timer is started later on in this function)

	//----- SETUP TIMER 8 -----
	//Used for: Available
	T8CON = 0;
	//TMR8 = 0;
	//PR8 = 0xffff;

	//----- SETUP TIMER 9 -----
	//Used for: Available
	T9CON = 0;
	//TMR9 = 0;
	//TMR9HLD = 0;
	//PR9 = 0xffff;
	//(Timer is started later on in this function)



	//-------------------------------
	//----- SETUP INPUT CAPTURE -----
	//-------------------------------
	IC1CON = 0;			//B13=ICSDL B7=ICTMR B6:5=ICI1:0 B4=ICOV B3=ICBNE B2:0=ICM2:0
	IC2CON = 0;			//B13=ICSDL B7=ICTMR B6:5=ICI1:0 B4=ICOV B3=ICBNE B2:0=ICM2:0
	IC3CON = 0;			//B13=ICSDL B7=ICTMR B6:5=ICI1:0 B4=ICOV B3=ICBNE B2:0=ICM2:0
	IC4CON = 0;			//B13=ICSDL B7=ICTMR B6:5=ICI1:0 B4=ICOV B3=ICBNE B2:0=ICM2:0
	IC5CON = 0;			//B13=ICSDL B7=ICTMR B6:5=ICI1:0 B4=ICOV B3=ICBNE B2:0=ICM2:0
	IC6CON = 0;			//B13=ICSDL B7=ICTMR B6:5=ICI1:0 B4=ICOV B3=ICBNE B2:0=ICM2:0
	IC7CON = 0;			//B13=ICSDL B7=ICTMR B6:5=ICI1:0 B4=ICOV B3=ICBNE B2:0=ICM2:0
	IC8CON = 0;			//B13=ICSDL B7=ICTMR B6:5=ICI1:0 B4=ICOV B3=ICBNE B2:0=ICM2:0


	//--------------------------------
	//----- SETUP OUTPUT COMPARE -----
	//--------------------------------
	OC1CON = 0;
	OC2CON = 0;
	OC3CON = 0;
	OC4CON = 0;
	OC5CON = 0;
	OC6CON = 0;
	OC7CON = 0;
	OC8CON = 0;
	OC1RS = 0;
	OC1R = 0;
	OC1CON = 0;
	OC2RS = 0;
	OC2R = 0;
	OC2CON = 0;
	OC3RS = 0;
	OC3R = 0;
	OC3CON = 0;
	OC4RS = 0;
	OC4R = 0;
	OC4CON = 0;
	OC5RS = 0;
	OC5R = 0;
	OC5CON = 0;
	OC6RS = 0;
	OC6R = 0;
	OC6CON = 0;
	OC7RS = 0;
	OC7R = 0;
	OC7CON = 0;
	OC8RS = 0;
	OC8R = 0;
	OC8CON = 0;


	//------------------------------------------
	//----- SETUP SYNCHRONOUS SERIAL PORTS -----
	//------------------------------------------

	//----- SETUP SPI 1 -----
	//Used for: MMC / SD card
	w_temp = SPI1BUF;
	SPI1STAT = 0;
	SPI1CON1 = 0b0000001100100001;	//SPI in master mode (Set the SPI clock frequencies in the mem-mmcsd.h file)(SPI1STATbits.SPIEN must be 0 to write to this register)
									//Data is valid on the rising edge of the clock (Transmit occurs on transition from active to Idle clock state)
									//Clock low in idle bus state
	SPI1CON2 = 0;
	SPI1STATbits.SPIEN = 1;			//Enable the port


	//----- SETUP SPI 2 -----
	//Used for: Disabled
	//w_temp = SPI2BUF;
	SPI2STAT = 0;
	SPI2CON1 = 0b0000001100100001;					//(SPI2STATbits.SPIEN must be 0 to write to this register)
	//SPI2CON2 = 0;
	SPI2STATbits.SPIEN = 1;			//Enable the port  (Enabled for silicon bug workaround with SPI1 and PIC24HJ64GP206)


	//----- SETUP I2C 1 -----
	//Used for: Disabled
	//w_temp = I2C1RCV;
	//I2C1ADD = 0;
	//I2C1BRG = 0;
	//I2C1STAT = 0;
	I2C1CON = 0;
	//I2C1CONbits.I2CEN = 1;		//Enable I2C



	//-----------------------
	//----- SETUP USART -----
	//-----------------------

	//----- SETUP UART 1 -----
	//Used for: Disabled
	//U1BRG = ;
	U1MODE = 0;
	//U1STA = 0;
	//SILICON BUG - DO NOT USE READ MODIFY WRITE INSTRUCTIONS ON UxSTA
	//SILICON BUG - UTXISEL0 bit (UxSTA<13>) is always read as zero regardless of the value written to it
	//U1MODEbits.UARTEN = 1;		//Enable UART
	//U1STAbits.UTXEN = 1;			//Enable tx (do after setting UARTEN)

	//----- SETUP UART 2 -----
	//Used for: Disabled
	//U2BRG = ;
	U2MODE = 0;
	//U2STA = 0;
	//SILICON BUG - DO NOT USE READ MODIFY WRITE INSTRUCTIONS ON UxSTA
	//SILICON BUG - UTXISEL0 bit (UxSTA<13>) is always read as zero regardless of the value written to it
	//U2MODEbits.UARTEN = 1;		//Enable UART
	//U2STAbits.UTXEN = 1;			//Enable tx (do after setting UARTEN)




	//---------------------
	//----- SETUP DMA -----
	//---------------------

	//----- SETUP DMA 0 -----
	//Used for: Available
	DMA0CON = 0;
	DMA0REQ = 0;
	DMA0STA = 0;
	DMA0STB = 0;
	DMA0PAD = 0;
	DMA0CNT = 0;

	//----- SETUP DMA 1 -----
	//Used for: Available
	DMA1CON = 0;
	DMA1REQ = 0;
	DMA1STA = 0;
	DMA1STB = 0;
	DMA1PAD = 0;
	DMA1CNT = 0;

	//----- SETUP DMA 2 -----
	//Used for: Available
	DMA2CON = 0;
	DMA2REQ = 0;
	DMA2STA = 0;
	DMA2STB = 0;
	DMA2PAD = 0;
	DMA2CNT = 0;

	//----- SETUP DMA 3 -----
	//Used for: Available
	DMA3CON = 0;
	DMA3REQ = 0;
	DMA3STA = 0;
	DMA3STB = 0;
	DMA3PAD = 0;
	DMA3CNT = 0;

	//----- SETUP DMA 4 -----
	//Used for: Available
	DMA4CON = 0;
	DMA4REQ = 0;
	DMA4STA = 0;
	DMA4STB = 0;
	DMA4PAD = 0;
	DMA4CNT = 0;

	//----- SETUP DMA 5 -----
	//Used for: Available
	DMA5CON = 0;
	DMA5REQ = 0;
	DMA5STA = 0;
	DMA5STB = 0;
	DMA5PAD = 0;
	DMA5CNT = 0;

	//----- SETUP DMA 6 -----
	//Used for: Available
	DMA6CON = 0;
	DMA6REQ = 0;
	DMA6STA = 0;
	DMA6STB = 0;
	DMA6PAD = 0;
	DMA6CNT = 0;

	//----- SETUP DMA 7 -----
	//Used for: Available
	DMA7CON = 0;
	DMA7REQ = 0;
	DMA7STA = 0;
	DMA7STB = 0;
	DMA7PAD = 0;
	DMA7CNT = 0;



	//------------------------
	//----- START TIMERS -----
	//------------------------
	T1CON = 0;
	T3CON = 0;
	T2CON = 0;
	T5CON = 0x8010;
	T4CON = 0;
	T7CON = 0;
	T6CON = 0;
	T9CON = 0;
	T8CON = 0;




	//-----------------------------
	//----- ENABLE INTERRUPTS -----
	//-----------------------------

	//----- INTERRUPT PRIORITIES -----
	IPC0 = 0x4444;
	IPC1 = 0x4444;
	IPC2 = 0x4444;
	IPC3 = 0x4444;
	IPC4 = 0x4444;
	IPC5 = 0x4444;
	IPC6 = 0x4444;
	IPC7 = 0x4444;
	IPC8 = 0x4444;
	IPC9 = 0x4444;
	IPC10 = 0x4444;
	IPC11 = 0x4444;
	IPC12 = 0x4444;
	IPC13 = 0x4444;
	IPC14 = 0x4444;
	IPC15 = 0x4444;
	IPC16 = 0x4444;
	IPC17 = 0x4444;

	INTCON1 = 0;
	INTCON2 = 0;

	IEC0 = 0;
	IEC1 = 0;
	IEC2 = 0;
	IEC3 = 0;
	IEC4 = 0;

	//ENABLE TIMER 5 (HEARTBEAT) IRQ
	IPC7bits.T5IP = 3;		//Set irq priority (0-7, 7=highest, 0=disabled)
	IEC1bits.T5IE = 1;		//Enable irq





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
		ClrWdt();


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
	if (!_RD0)
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
		LED1_OFF = 0;
		LED2_OFF = 1;
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
		LED1_OFF = 1;
		LED2_OFF = 0;
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
		LED1_OFF = 1;
		LED2_OFF = 1;
		break;


	case TA_PROCESS_ERROR:
		//--------------------------------------------------------------------------
		//----- ERROR OCCURED - INDICATE ERROR AND WAIT FOR CARD TO BE REMOVED -----
		//--------------------------------------------------------------------------
		LED1_OFF = 0;
		LED2_OFF = 0;

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


//*********************************************
//*********************************************
//********** HEARTBEAT IRQ (Timer 5) **********
//*********************************************
//*********************************************
void __attribute__((__interrupt__,__auto_psv__)) _T5Interrupt(void)
{
	static BYTE hb_10ms_timer = 0;
	static BYTE hb_100ms_timer = 0;
	static BYTE hb_1sec_timer = 0;
	
	_T5IF = 0;						//Reset the timer irq flag

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







			hb_1sec_timer++;
			if (hb_1sec_timer == 10)
			{
				//----------------------------
				//----------------------------
				//----- HERE EVERY 1 Sec -----
				//----------------------------
				//----------------------------
				hb_1sec_timer = 0;




			} //if (hb_1sec_timer == 10)
		} //if (hb_100ms_timer == 100)

}

















