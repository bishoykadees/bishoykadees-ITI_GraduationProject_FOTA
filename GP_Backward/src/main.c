/*
 * main.c
 *
 *  Created on: 22 Jun 2020
 *      Author: mirna
 */
#include "ESP8266_interface.h"
#include "DC_interface.h"

void main(void)
{


	ESP8266_AppInit();
	DC_init();
	DC_GoBackward();

	while(1)
	{

	}
}

