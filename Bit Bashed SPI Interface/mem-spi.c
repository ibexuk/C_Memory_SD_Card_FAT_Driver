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
//BIT BASHED SPI INTERFACE C CODE FILE



#include "main.h"					//Global data type definitions (see https://github.com/ibexuk/C_Generic_Header_File )
#define MEM_SPI_C
#include "mem-spi.h"




//*****************************
//*****************************
//********** TX BYTE **********
//*****************************
//*****************************
void spi_tx_byte (BYTE data)
{
//Data is valid on the rising edge of the clock (Transmit occurs on transition from active to Idle clock state)
//Clock low in idle bus state

	spi_rx_data = 0;

	if (spi_speed_fast)
	{
		//------------------------
		//----- FAST SPI BUS -----
		//------------------------

		//----- DO BIT 7 -----
		//Setup data
		if (data & 0x80)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x80;

		SPI_CLK_PIN = 0;

		//----- DO BIT 6 -----
		//Setup data
		if (data & 0x40)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x40;

		SPI_CLK_PIN = 0;

		//----- DO BIT 5 -----
		//Setup data
		if (data & 0x20)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x20;

		SPI_CLK_PIN = 0;

		//----- DO BIT 4 -----
		//Setup data
		if (data & 0x10)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x10;

		SPI_CLK_PIN = 0;

		//----- DO BIT 3 -----
		//Setup data
		if (data & 0x08)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x08;

		SPI_CLK_PIN = 0;

		//----- DO BIT 2 -----
		//Setup data
		if (data & 0x04)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x04;

		SPI_CLK_PIN = 0;

		//----- DO BIT 1 -----
		//Setup data
		if (data & 0x02)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x02;

		SPI_CLK_PIN = 0;

		//----- DO BIT 0 -----
		//Setup data
		if (data & 0x01)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x01;

		SPI_CLK_PIN = 0;

		#ifdef SPI_20MHZ_CLOCK_DELAY
			SPI_20MHZ_CLOCK_DELAY;
		#endif

	}
	else
	{
		//------------------------
		//----- SLOW SPI BUS -----
		//------------------------

		//----- DO BIT 7 -----
		//Setup data
		if (data & 0x80)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x80;

		SPI_CLK_PIN = 0;

		//----- DO BIT 6 -----
		//Setup data
		if (data & 0x40)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x40;

		SPI_CLK_PIN = 0;

		//----- DO BIT 5 -----
		//Setup data
		if (data & 0x20)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x20;

		SPI_CLK_PIN = 0;

		//----- DO BIT 4 -----
		//Setup data
		if (data & 0x10)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x10;

		SPI_CLK_PIN = 0;

		//----- DO BIT 3 -----
		//Setup data
		if (data & 0x08)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x08;

		SPI_CLK_PIN = 0;

		//----- DO BIT 2 -----
		//Setup data
		if (data & 0x04)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x04;

		SPI_CLK_PIN = 0;

		//----- DO BIT 1 -----
		//Setup data
		if (data & 0x02)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x02;

		SPI_CLK_PIN = 0;

		//----- DO BIT 0 -----
		//Setup data
		if (data & 0x01)			//Send data bit
			SPI_DO_PIN = 1;
		else
			SPI_DO_PIN = 0;

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		SPI_CLK_PIN = 1;			//Clock the data in

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

		if (SPI_DI_PIN)				//Get data in
			spi_rx_data |= 0x01;

		SPI_CLK_PIN = 0;

		#ifdef SPI_400KHZ_CLOCK_DELAY
			SPI_400KHZ_CLOCK_DELAY;
		#endif

	}	//if (spi_speed_fast)






}















