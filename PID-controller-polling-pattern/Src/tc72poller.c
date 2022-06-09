/*
 * poller.c
 *
 *  Created on: Mar 31, 2022
 *      Author: badra
 */

#include "stdtypes.h"
#include "macros.h"
#include "port.h"

#include "spi.h"
#include <tc72poller.h>
#include <tc72pollingDataClient.h>

int polling_enabled= 1;
int polling_counter= 1;
int counter = 0 ;

void TC72_Poll(void)
{
	if(polling_enabled && (!counter))
	{
		u8 data = SPI1_VidSendDataU8(0);
		pid_controller(data);
	}
	counter++;
	counter = counter%polling_counter;
}

void TC72_StartPolling(void)
{
	polling_enabled=1;
}

void TC72_StopPolling(void)
{
	polling_enabled=0;
}

void TC72_SetPollingTime(int polling_time)
{
	polling_counter = polling_time;
}
