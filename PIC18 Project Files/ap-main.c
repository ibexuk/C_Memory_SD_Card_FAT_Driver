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
//PIC18 SAMPLE PROJECT C CODE FILE




//----- INCLUDE FILES FOR THIS SOURCE CODE FILE -----
#include "main.h"					//Global data type definitions (see https://github.com/ibexuk/C_Generic_Header_File )
#define	MAIN_C						//(Define used for following header file to flag that it is the header file for this source file)
#include "ap-main.h"				//(Include header file for this source file)

//----- OTHER PROJECT FILES REQUIRED BY THIS SOURCE CODE FILE -----
#include "mem-ffs.h"

//----- COMPILER LIBRARY FILES REQUIRED BY THIS SOURCE CODE FILE -----
#include <stdio.h>					//(Needed for printf)
//#include <stdlib.h>
//#include <usart.h>
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
	#pragma config OSC = HSPLL			//Ocsillator type
	#pragma config FCMEN = OFF			//Fail safe clock monitor (On = if osc fails the internal osc will be used)
	#pragma config IESO = OFF			//Internal / external ocsillator switchover mode
	#pragma config BOREN = SBORDIS		//Brown out reset (OFF = Disabled, ON = SBOREN bit enabled in software, NOSLP = enabled except SLEEP, SBOREN Disabled, SBORDIS enabled, SBOREN Disabled)
	#pragma config PWRT = OFF			//Powerup timer (not available when debugging)
#ifdef USING_3V3_POWER
	#pragma config BORV = 3				//Brown out reset voltage (0 = maximum, 3 = minimum - see device datasheet)
#else
	#pragma config BORV = 1				//Brown out reset voltage (0 = maximum, 3 = minimum - see device datasheet)
#endif
	#pragma config WDT = OFF			//Watchdog timer (not available when debugging)
	#pragma config WDTPS = 128			//Watchdog postscaller
	#pragma config MCLRE = ON			//MCLR pin enable
	#pragma config LPT1OSC = OFF		//Low power timer 1 oscillator
	#pragma config PBADEN = OFF			//PortB AtoD enable
	#pragma config CCP2MX = PORTC		//CCP2 pin
	#pragma config DEBUG = ON			//Background Debugger
	#pragma config LVP = OFF			//Low voltage in circuit programming
	#pragma config STVREN = ON			//Stack overflow reset
	#pragma config XINST = OFF			//Extended instruction set enable
	#pragma config CP0 = OFF			//Code protect block
	#pragma config CP1 = OFF			//Code protect block
	#pragma config CP2 = OFF			//Code protect block
	#pragma config CP3 = OFF			//Code protect block
	#pragma config CPB = OFF			//Code protect boot block
	#pragma config CPD = OFF			//Protect data eeprom
	#pragma config WRT0 = OFF			//Table write protect block
	#pragma config WRT1 = OFF			//Table write protect block
	#pragma config WRT2 = OFF			//Table write protect block
	#pragma config WRT3 = OFF			//Table write protect block
	#pragma config WRTB = OFF			//Boot block write protect
	#pragma config WRTC = OFF			//Config registers write protect
	#pragma config WRTD = OFF			//Data eeprom write protect
	#pragma config EBTR0 = OFF			//Table read protect block
	#pragma config EBTR1 = OFF			//Table read protect block
	#pragma config EBTR2 = OFF			//Table read protect block
	#pragma config EBTR3 = OFF			//Table read protect block
	#pragma config EBTRB = OFF			//Table read protect boot block

#else
//----- WE'RE NOT IN DEVELOPMENT MODE -----
	#pragma config OSC = HSPLL			//Ocsillator type
	#pragma config FCMEN = OFF			//Fail safe clock monitor (On = if osc fails the internal osc will be used)
	#pragma config IESO = OFF			//Internal / external ocsillator switchover mode
	#pragma config BOREN = SBORDIS		//Brown out reset (OFF = Disabled, ON = SBOREN bit enabled in software, NOSLP = enabled except SLEEP, SBOREN Disabled, SBORDIS = enabled, SBOREN Disabled)
	#pragma config PWRT = ON			//Powerup timer
#ifdef USING_3V3_POWER
	#pragma config BORV = 3				//Brown out reset voltage (0 = maximum, 3 = minimum - see device datasheet)
#else
	#pragma config BORV = 1				//Brown out reset voltage (0 = maximum, 3 = minimum - see device datasheet)
#endif
	#pragma config WDT = ON				//Watchdog timer
	#pragma config WDTPS = 128			//Watchdog postscaller
	#pragma config MCLRE = ON			//MCLR pin enable
	#pragma config LPT1OSC = OFF		//Low power timer 1 oscillator
	#pragma config PBADEN = OFF			//PortB AtoD enable
	#pragma config CCP2MX = PORTC		//CCP2 pin
	#pragma config DEBUG = OFF			//Background Debugger
	#pragma config LVP = OFF			//Low voltage in circuit programming
	#pragma config STVREN = ON			//Stack overflow reset
	#pragma config XINST = OFF			//Extended instruction set enable
	#pragma config CP0 = OFF			//Code protect block		(Note that setting code protection bits for devices powered at < 4.5V will mean that the
	#pragma config CP1 = OFF			//Code protect block		device will need to be powered at >4.5V if it ever needs to be programmed in circuit
	#pragma config CP2 = OFF			//Code protect block		again - i.e. for 3V3 circuits 5V power will have to be applied to reset the protection)
	#pragma config CP3 = OFF			//Code protect block
	#pragma config CPB = OFF			//Code protect boot block
	#pragma config CPD = OFF			//Protect data eeprom
	#pragma config WRT0 = OFF			//Table write protect block
	#pragma config WRT1 = OFF			//Table write protect block
	#pragma config WRT2 = OFF			//Table write protect block
	#pragma config WRT3 = OFF			//Table write protect block
	#pragma config WRTB = OFF			//Boot block write protect
	#pragma config WRTC = OFF			//Config registers write protect
	#pragma config WRTD = OFF			//Data eeprom write protect
	#pragma config EBTR0 = OFF			//Table read protect block
	#pragma config EBTR1 = OFF			//Table read protect block
	#pragma config EBTR2 = OFF			//Table read protect block
	#pragma config EBTR3 = OFF			//Table read protect block
	#pragma config EBTRB = OFF			//Table read protect boot block
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

	ClrWdt();

	//-------------------------
	//----- SETUP IO PINS -----
	//-------------------------
	//(Device will powerup with all IO pins as inputs)

	//Setup the state of any pins that are outputs (inputs are don't care)
	LATA = 0b00000000;
	LATB = 0b00000000;
	LATC = 0b00000010;		//FFS_CE high on powerup
	LATD = 0b00000000;
	LATE = 0b00000000;

	LED1_OFF = 1;
	LED2_OFF = 1;

	//Setup the IO pin type (0 = output, 1 = input)
	TRISA = 0b00000000;
	TRISB = 0b00000011;
	TRISC = 0b00010101;
	TRISD = 0b00000000;
	TRISE = 0b00000000;

	//Setup internal pull ups
	INTCON2bits.RBPU = 0;				//Port B pull ups (0 = on)


	//----- SETUP THE A TO D PINS -----
	ADCON0 = 0b00000000;
	ADCON1 = 0b00001111;				//All pins are digital
	//ADCON2 = 0b10111110;


	//------------------------
	//----- SETUP TIMERS -----
	//------------------------
	//(INCLUDE THE USAGE OF ALL TIMERS HERE EVEN IF NOT SETUP HERE SO THIS IS THE ONE POINT OF
	//REFERENCE TO KNOW WHICH TIMERS ARE IN USE AND FOR WHAT).

	//----- SETUP TIMER 0 -----
	//Used for: Heartbeat
	T0CONbits.T08BIT = 0;				//Configured as a 16bit timer
	T0CONbits.T0CS = 0;					//Use internal instruction clock
	T0CONbits.T0SE = 0;
	T0CONbits.PSA = 0;					//Prescaller is in use (0 = in use)
	T0CONbits.T0PS2 = 0;				//Prescaler 1:2
	T0CONbits.T0PS1 = 0;
	T0CONbits.T0PS0 = 0;
	T0CONbits.TMR0ON = 1;				//Timer 0 on

	INTCONbits.TMR0IE = 1;				//Enable the Timer 0 irq

	//----- SETUP TIMER 1 -----
	//Used for: Available
	/*
	T1CONbits.RD16 = 1;					//R/W 16bits in 1 operation
	T1CONbits.T1RUN = 0;				//Don't use timer 1 dedicated oscillator
	T1CONbits.T1OSCEN = 0;				//Timer 1 dedicated oscillator disabled
	T1CONbits.T1CKPS1 = 0;				//1:1 prescale
	T1CONbits.T1CKPS0 = 0;
	T1CONbits.T1SYNC = 0;
	T1CONbits.TMR1CS = 0;				//Use internal instruction  clock
	T1CONbits.TMR1ON = 1;				//Enable timer 1
	*/

	//----- SETUP TIMER 2 -----
	//Used for: Available
	/*
	T2CONbits.T2OUTPS3 = 0;				//1:1 postscale
	T2CONbits.T2OUTPS2 = 0;
	T2CONbits.T2OUTPS1 = 0;
	T2CONbits.T2OUTPS0 = 0;
	T2CONbits.T2CKPS1 = 0;				//1:1 prescale
	T2CONbits.T2CKPS0 = 0;
	PR2 = ;
	T2CONbits.TMR2ON = 1;				//Enable timer 2
	*/


	//----- SETUP TIMER 3 -----
	//Used for: Available
	/*
	T3CONbits.RD16 = 1;					// R/W 16bits in 1 operation
	T3CONbits.T3CCP2 = 0;				// R/W 16bits in 1 operation
	T3CONbits.T3CCP1 = 0;
	T3CONbits.T3CKPS1 = 0;				//1:1 prescale
	T3CONbits.T3CKPS0 = 0;
	T3CONbits.T3SYNC = 0;
	T3CONbits.TMR3CS = 0;				//Use internal instruction  clock
	T3CONbits.TMR3ON = 1;				//Enable timer 3
	*/



	//-----------------------------------------------
	//----- SETUP SYNCHRONOUS SERIAL PORT (SSP) -----
	//-----------------------------------------------
	//SETUP SPI BUS
	SSPSTATbits.SMP = 1;
	SSPSTATbits.CKE = 1;		//Data is valid on the rising edge of the clock (Transmit occurs on transition from active to Idle clock state)
	SSPCON1bits.CKP = 0;		//Clock low in idle bus state
	SSPCON1bits.SSPM3 = 0;		//SPI in master mode (Set the SPI clock frequencies in the mem-mmcsd.h file)
	SSPCON1bits.SSPM2 = 0;
	SSPCON1bits.SSPM1 = 0;
	SSPCON1bits.SSPM0 = 0;
	SSPCON1bits.SSPEN = 1;		//Enable SSP Port



	//-----------------------
	//----- SETUP USART -----
	//-----------------------
	/*
	//SETUP BAUD RATE
	TXSTAbits.BRGH = 0;					//Low speed mode
	BAUDCONbits.BRG16 = 1;				//16 bit baud rate value
	SPBRGH = (BYTE)(((((DWORD)INSTRUCTION_CLOCK_FREQUENCY << 2) / 9600) / 16) - 1) >> 8;			//(((OSCILLATOR_FREQUENCY / DESIRED_BAUD) / DIVIDE_VALUE) - 1)
	SPBRG = (BYTE)(((((DWORD)INSTRUCTION_CLOCK_FREQUENCY << 2) / 9600) / 16) - 1) & 0x00ff;		//Note that different BRGH & BRG16 settings use different divide values - see device datasheet

	//SETUP TX
	TXSTAbits.TX9 = 0;					//8 bit tx
	TXSTAbits.TXEN = 1;					//Transmit enabled
	TXSTAbits.SYNC = 0;					//Asynchronous mode
	
	//SETUP RX
	RCSTAbits.RX9 = 0;					//8 bit rx
	RCSTAbits.ADDEN = 0;				//Address detect disabled
	RCSTAbits.CREN = 1;					//Enable receiver
	RCSTAbits.SPEN = 1;					//Serial port enabled
	*/


	//------------------------
	//----- USING PRINTF -----
	//------------------------
	//If using C18 and the compiler small memory model (devices <= 64K of program memory) you can use '(rom far char*)' to stop a build warning
	//being generated, otherwise omit the (rom far char*)

	//Example displaying just text:-
	//printf ((rom far char*)"\n----- POWER-UP ----- \n\r");

	//Example displaying a value:-
	//temp_value = 199;
	//itoa((int) temp_value, temp_string);
	//printf ((rom far char*)"%s\n\r", temp_string);

	//Example of getting terminal input:-
	//printf ((rom far char*)"\nEnter 5 digit value\n\r");
	//getsUSART((char*)temp_string,5);
	//temp_string[5] = 0x00;
	//printf ((rom far char*)"You typed: %s\n\r", temp_string);


	//-----------------------------
	//----- ENABLE INTERRUPTS -----
	//-----------------------------
	//INTCONbits.PEIE = 1;			//Enable peripheral irq's
	RCONbits.IPEN = 0;				//Disable priority feature on interrupts
	INTCONbits.GIE = 1;    	    	//Enable interrupts 





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
void main ( void )
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
	if (PORTBbits.RB0)
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
const char filename_test_txt[] = {"test-c18.txt"};
const char filename_test_csv[] = {"test-c18.csv"};

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
				ffs_fwrite(text_file_line2_string, sizeof(char), (int)strlen(text_file_line2_string), our_file_0);

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

//***********************************
//***** HIGH PRIORITY INTERRUPT *****
//***********************************
#pragma code highVector=0x08			//This is the vector address for a PIC18 high priority interrupt 
void athighvector (void)
{
	_asm 	GOTO	interruptisrh	_endasm
}
#pragma code 		//(Return to normal)

//**********************************
//***** LOW PRIORITY INTERRUPT *****
//**********************************
#pragma code lowVector=0x18			//This is the vector address for a PIC18 low priority interrupt 
void atlowvector (void)
{
	_asm	goto	interruptisrl	_endasm
}
#pragma code 		//(Return to normal)



//*************************************************************
//*************************************************************
//********** HIGH PRIORITY INTERRUPT SERVICE ROUTINE **********
//*************************************************************
//*************************************************************
//#pragma interrupt interruptisrh			//<<< This is the normal C18 compiler definition to indicate the interrupt high priority function.
#pragma interruptlow interruptisrh			//<<<For PIC18 devices with the silicon bug that means the RETFIE FAST instruction cannot be used use this C18
											//compiler definition so that the low priority context saving aproach is used (if not sure just use this)
void interruptisrh (void)
{
	static BYTE hb_100ms_timer = 0;
	static BYTE hb_1sec_timer = 0;

	//************************
	//***** USART TX IRQ *****
	//************************
	//if(PIE1bits.TXIE && PIR1bits.TXIF)
	//	usart_transmit_irq();

	//************************
	//***** USART RX IRQ *****
	//************************
	//if(PIE1bits.RCIE && PIR1bits.RCIF)
	//	usart_receive_irq();


	//***************************************
	//********** TIMER 0 HEARTBEAT **********
	//***************************************
	if(INTCONbits.TMR0IF && INTCONbits.TMR0IE)
	{
		INTCONbits.TMR0IF = 0;					//Reset the timer 0 irq flag

		_asm
		//Reset timer for the next rollover (in assembler for accuracy)
		movff	TMR0L,asm_irq_temp				//read the current timer value (read low byte loads the high byte)
		movff	TMR0H,asm_irq_temp1
		movlw	((0x10000 - (((INSTRUCTION_CLOCK_FREQUENCY / 100) / 2) - 14)) & 0x00ff)		//<<< /100 for 10mS irq, /1000 for 1mS irq
		addwf	asm_irq_temp,1,0				//(1 = file register, 0 = access ram)
		movlw	((0x10000 - (((INSTRUCTION_CLOCK_FREQUENCY / 100) / 2) - 14)) >> 8)			//<<< /100 for 10mS irq, /1000 for 1mS irq
		addwfc	asm_irq_temp1,1,0				//(1 = file register, 0 = access ram)
		movff	asm_irq_temp1,TMR0H				//Store new value (high byte first)
		movff	asm_irq_temp,TMR0L
		_endasm

		//The above code takes 12 instruction cycles
		//The timer is inhibited for 2 instruction cycles after the low byte is written
		//Therefore subtract 14 from the value to be written


		//------------------------------
		//------------------------------
		//----- HERE EVERY 10 mSec -----
		//------------------------------
		//------------------------------

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



		hb_100ms_timer++;
		if (hb_100ms_timer == 10)
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


			}
		}
	}



	//<<<<< ADD OTHER HIGH PRIORITY INTERRUPTS HERE <<<<<
	
	
}	
	

//************************************************************
//************************************************************
//********** LOW PRIORITY INTERRUPT SERVICE ROUTINE **********
//************************************************************
//************************************************************
#pragma interruptlow interruptisrl			//<<< C18 compiler definition to indicate the interrupt low priority function.
void interruptisrl (void)
{


	//<<<<< ADD OTHER LOW PRIORITY INTERRUPTS HERE <<<<<
	
	
}
#pragma code 		//(Return to normal)












