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
#include <stdlib.h>
#include <plib.h>







//******************************************
//******************************************
//********** DEVICE CONFIGURATION **********
//******************************************
//******************************************
//These configuration defines do not need to be included, but having them means that the configuration bits will be automatically set and will
//be included in the .hex file created for the project, so that they do not need to be manually set when programming devices at manufacture.
//(The config names are given for each device in MPLAB help, under 'Topics... -> PIC32MX Configuration Settings')

#ifdef __DEBUG				//Debug mode selected in MPLAB
//----- WE'RE IN DEVELOPMENT MODE -----
	#pragma config FPLLMUL = MUL_20			//PLL Multiplier
	#pragma config FPLLIDIV = DIV_2			//PLL Input Divider
	#pragma config FPLLODIV = DIV_4			//PLL Output Divider
	#pragma config FPBDIV = DIV_1			//Peripheral Clock divisor
	#pragma config FWDTEN = OFF				//Watchdog Timer
	#pragma config WDTPS = PS1				//Watchdog Timer Postscale
	#pragma config FCKSM = CSDCMD			//Clock Switching & Fail Safe Clock Monitor
	#pragma config OSCIOFNC = OFF			//CLKO Enable
	#pragma config POSCMOD = HS				//Primary Oscillator
	#pragma config IESO = OFF				//Internal/External Switch-over
	#pragma config FSOSCEN = OFF			//Secondary Oscillator Enable (KLO was off)
	#pragma config FNOSC = PRIPLL			//Oscillator Selection
	#pragma config CP = OFF					//Code Protect
	#pragma config BWP = OFF				//Boot Flash Write Protect
	#pragma config PWP = OFF				//Program Flash Write Protect
	#pragma config ICESEL = ICS_PGx1		//ICE/ICD Comm Channel Select
	#pragma config DEBUG = ON				//Background Debugger Enable
#else
//----- WE'RE NOT IN DEVELOPMENT MODE -----
	#pragma config FPLLMUL = MUL_20			//PLL Multiplier
	#pragma config FPLLIDIV = DIV_2			//PLL Input Divider
	#pragma config FPLLODIV = DIV_4			//PLL Output Divider
	#pragma config FPBDIV = DIV_1			//Peripheral Clock divisor
	#pragma config FWDTEN = ON				//Watchdog Timer
	#pragma config WDTPS = PS2048			//Watchdog Timer Postscale (no postscale = 1mS timeout)
	#pragma config FCKSM = CSDCMD			//Clock Switching & Fail Safe Clock Monitor
	#pragma config OSCIOFNC = OFF			//CLKO Enable
	#pragma config POSCMOD = HS				//Primary Oscillator
	#pragma config IESO = OFF				//Internal/External Switch-over
	#pragma config FSOSCEN = OFF			//Secondary Oscillator Enable (KLO was off)
	#pragma config FNOSC = PRIPLL			//Oscillator Selection
	#pragma config CP = OFF					//Code Protect
	#pragma config BWP = OFF				//Boot Flash Write Protect
	#pragma config PWP = OFF				//Program Flash Write Protect
	#pragma config ICESEL = ICS_PGx1		//ICE/ICD Comm Channel Select
	#pragma config DEBUG = ON				//Background Debugger Enable
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
	BYTE b_temp;

	//##### GENERAL NOTE ABOUT PIC32'S #####
	//Try and use the peripheral libraries instead of special function registers for everything (literally everything!) to avoid
	//bugs that can be caused by the pipeline and interrupts.
	

	//---------------------------------
	//----- CONFIGURE PERFORMANCE -----
	//---------------------------------
	
	//----- SETUP EVERYTHING FOR OPTIMUM PERFORMANCE -----
	Nop();
	SYSTEMConfigPerformance(20000000L);		//Note this sets peripheral bus to '1' max speed (regardless of configuration bit setting)
											//Use PBCLK divider of 1:1 to calculate UART baud, timer tick etc

	//----- SET PERIPHERAL BUS DIVISOR -----
	//To minimize dynamic power the PB divisor should be chosen to run the peripherals at the lowest frequency that provides acceptable system performance
	//mOSCSetPBDIV(OSC_PB_DIV_1);			//OSC_PB_DIV_1, OSC_PB_DIV_2, OSC_PB_DIV_4, OSC_PB_DIV_8, 

	ClearWDT();

	//-------------------------
	//----- SETUP IO PINS -----
	//-------------------------
	//(Device will powerup with all IO pins as inputs)

	//----- TURN OFF THE JTAG PORT -----
	//(JTAG is on by default)
	mJTAGPortEnable(0);

	#define	PORTB_IO	0x0000				//Setup the IO pin type (0 = output, 1 = input)
	mPORTBWrite(0x0000);					//Set initial ouput pin states
	mPORTBSetPinsDigitalIn(PORTB_IO);		//(Sets high bits as input)
	mPORTBSetPinsDigitalOut(~PORTB_IO);		//(Sets high bits as output)

	#define	PORTC_IO	0x0000				//Setup the IO pin type (0 = output, 1 = input)
	mPORTCWrite(0x0000);					//Set initial ouput pin states
	mPORTCSetPinsDigitalIn(PORTC_IO);		//(Sets high bits as input)
	mPORTCSetPinsDigitalOut(~PORTC_IO);		//(Sets high bits as output)

	#define	PORTD_IO	0x0003				//Setup the IO pin type (0 = output, 1 = input)
	mPORTDWrite(0x00c0);					//Set initial ouput pin states
	mPORTDSetPinsDigitalIn(PORTD_IO);		//(Sets high bits as input)
	mPORTDSetPinsDigitalOut(~PORTD_IO);		//(Sets high bits as output)

	#define	PORTE_IO	0x0000				//Setup the IO pin type (0 = output, 1 = input)
	mPORTEWrite(0x0000);					//Set initial ouput pin states
	mPORTESetPinsDigitalIn(PORTE_IO);		//(Sets high bits as input)
	mPORTESetPinsDigitalOut(~PORTE_IO);		//(Sets high bits as output)

	#define	PORTF_IO	0x0006				//Setup the IO pin type (0 = output, 1 = input)
	mPORTFWrite(0x0001);					//Set initial ouput pin states
	mPORTFSetPinsDigitalIn(PORTF_IO);		//(Sets high bits as input)
	mPORTFSetPinsDigitalOut(~PORTF_IO);		//(Sets high bits as output)

	#define	PORTG_IO	0x0004				//Setup the IO pin type (0 = output, 1 = input)
	mPORTGWrite(0x0000);					//Set initial ouput pin states
	mPORTGSetPinsDigitalIn(PORTG_IO);		//(Sets high bits as input)
	mPORTGSetPinsDigitalOut(~PORTG_IO);		//(Sets high bits as output)

	//Read pins using:
	// mPORTAReadBits(BIT_0);
	//Write pins using:
	// mPORTAClearBits(BIT_0);
	// mPORTASetBits(BIT_0);
	// mPORTAToggleBits(BIT_0);

	//----- INPUT CHANGE NOTIFICATION CONFIGURATION -----
	//EnableCN0();
	//ConfigCNPullups(CN10_PULLUP_ENABLE | CN11_PULLUP_ENABLE);


	//----- SETUP THE A TO D PINS -----
	AD1PCFG = 0xFFFFE;				//All digital
	//mPORTBSetPinsAnalogIn(BIT_0 | BIT_1);

	CloseADC10();// ensure the ADC is off before setting the configuration
	//OpenADC10(
	//		(ADC_MODULE_ON | ADC_IDLE_STOP | ADC_FORMAT_INTG16 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON | ADC_SAMP_ON), //AD1CON1 register
	//		(ADC_VREF_AVDD_AVSS | ADC_SCAN_OFF | ADC_ALT_INPUT_OFF | ADC_SAMPLES_PER_INT_10),						//AD1CON2 register
	//		(ADC_SAMPLE_TIME_4 | ADC_CONV_CLK_PB | ADC_CONV_CLK_Tcy),												//AD1CON3 register
	//		(ENABLE_AN0_ANA),																						//AD1PCFG register
	//		(0)																										//AD1CSSL register
	//		);
	//EnableADC10();
	//Read the voltage from ADC1BUF0


	

	//------------------------
	//----- SETUP TIMERS -----
	//------------------------
	//(INCLUDE THE USAGE OF ALL TIMERS HERE EVEN IF NOT SETUP HERE SO THIS IS THE ONE POINT OF
	//REFERENCE TO KNOW WHICH TIMERS ARE IN USE AND FOR WHAT).

	//----- SETUP TIMER 1 -----
	//Used for: Available
	//OpenTimer1((T1_ON | T1_IDLE_CON | T1_GATE_OFF | T1_PS_1_4 | T1_SOURCE_INT), 20000);

	//----- SETUP TIMER 2 -----
	//Used for: Available
	//OpenTimer2((T2_ON | T2_IDLE_CON | T2_GATE_OFF | T2_PS_1_1 | T2_SOURCE_INT), 0xffff);		//0xffff = 305Hz

	//----- SETUP TIMER 3 -----
	//Used for: Available
	//OpenTimer3((T3_ON | T3_IDLE_CON | T3_GATE_OFF | T3_PS_1_1 | T3_SOURCE_INT), PIEZO_TIMER_PERIOD);

	//----- SETUP TIMER 4 -----
	//Used for: Available
	//OpenTimer4((T4_ON | T4_IDLE_CON | T4_GATE_OFF | T4_PS_1_1 | T4_SOURCE_INT), 20000);

	//----- SETUP TIMER 5 -----
	//Used for: Heartbeat
	OpenTimer5((T5_ON | T5_IDLE_CON | T5_GATE_OFF | T5_PS_1_1 | T5_SOURCE_INT), 20000);
	ConfigIntTimer5(T5_INT_ON | T5_INT_PRIOR_7);


	//---------------------
	//----- SETUP PWM -----
	//---------------------

	//OC2CON
	//Used for: Available
	//OpenOC2(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);		// Config, OCxRS (PWM setting), OCxR

	//OC3CON
	//Used for: Available
	//OpenOC3(OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);		// Config, OCxRS (PWM setting), OCxR


	

	//------------------------------------------
	//----- SETUP SYNCHRONOUS SERIAL PORTS -----
	//------------------------------------------

	//----- SETUP SPI 1 -----
	//Used for: SD card
	//Idle low, active high
	//Transmit on active to idle (falling edge)
	SpiChnOpen(1, (SPI_CON_MSTEN | SPI_CON_MODE8 | SPI_OPEN_CKE_REV), 2);    //20MHz fpb / 2 = 10MHz

	//----- SETUP SPI 2 -----
	//Used for: Disabled


	//----- SETUP I2C 1 -----
	//Used for: Disabled
	//OpenI2C1(I2C_EN, 23);

	//----- SETUP I2C 2 -----
	//Used for: Disabled



	//-----------------------
	//----- SETUP USART -----
	//-----------------------

	//----- SETUP UART 1 -----
	//Used for: Disabled


	//----- SETUP UART 2 -----
	//Used for: Disabled





	//-----------------------------
	//----- ENABLE INTERRUPTS -----
	//-----------------------------
	//INTEnableSystemSingleVectoredInt();
	INTEnableSystemMultiVectoredInt();



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
		ClearWDT();


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
	if (!mPORTDReadBits(BIT_0))
		switches_read |= 0x01;
	if (!mPORTDReadBits(BIT_1))
		switches_read |= 0x02;

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
const char filename_test_txt[] = {"test-c32.txt"};
const char filename_test_csv[] = {"test-c32.csv"};

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


//*********************************************
//*********************************************
//********** HEARTBEAT IRQ (Timer 5) **********
//*********************************************
//*********************************************
void __ISR(_TIMER_5_VECTOR, ipl7) Timer5IntHandler(void) 	//(ipl# must match the priority level assigned to the irq where its enabed)
{
	static BYTE hb_10ms_timer = 0;
	static BYTE hb_100ms_timer = 0;
	static BYTE hb_1sec_timer = 0;

	
	
	INTClearFlag(INT_T5);						//Reset the timer irq flag

	//-----------------------------
	//-----------------------------
	//----- HERE EVERY 1 mSec -----
	//-----------------------------
	//-----------------------------


	//>>>>>>>>>
	/*
	if (mPORTGReadBits(BIT_6))
		mPORTGClearBits(BIT_6);
	else
		mPORTGSetBits(BIT_6);
	*/
	//<<<<<<<<<<<


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



//***************************************************
//***************************************************
//********** UNHANDLED EXCEPTION INTERRUPT **********
//***************************************************
//***************************************************
//Useful interrupt to include as it will be called if any exception occurs that is not handled
//There are CPU registers that will tell you where the exception occurred etc.
//View them in the watch window for a more useful description to be shown.
void __attribute__((nomips16)) _general_exception_handler(void)
{
	Nop();

	SoftReset();

}









