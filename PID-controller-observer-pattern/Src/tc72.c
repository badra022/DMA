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
#include <tc72.h>

static CLIENT_ACCEPT_FUNCTION_PTR subscribers[MAX_NUM_OF_SUBSCRIBERS];
static u8 getEmptySubscribtionIndex(u8* result_ptr);

void TC72_init(void){
	for(u8 idx=0; idx < MAX_NUM_OF_SUBSCRIBERS; idx++){
		subscribers[idx] = NULL;
	}
	SPI_VidInit();
}

u8 TC72_getData(void){
	return SPI1_VidSendDataU8(0);
}

void notifyClients(u8 data){
	for(u8 idx=0; idx < MAX_NUM_OF_SUBSCRIBERS; idx++){
		if(subscribers[idx] != NULL){
			subscribers[idx](data);
		}
		else{
			/* No subscriber in this index of the array */
		}
	}
}

void TC72_manageData(void)
{
	static u32 average_data = 0;
	static u8 num_data = 0;
	average_data += (u32)TC72_getData();
	num_data++;
	if(num_data == 5){		/* if we collected 5 data, then we get the average and notify the clients with the result */
		average_data /= (u32)num_data;
		notifyClients(average_data);
		num_data = 0;
	}
	else{
		/* We didn't collect 5 data chunks yet */
	}
}

u8 TC72_subscribe(CLIENT_ACCEPT_FUNCTION_PTR function_ptr){
	u8 idx;
	u8 status = getEmptySubscribtionIndex(&idx);
	if(status == OK){
		subscribers[idx] = function_ptr;
	}
	else{
		/* Couldn't subscribe the client, Max number of clients reached */
	}
	return status;
}

u8 TC72_unsubscribe(CLIENT_ACCEPT_FUNCTION_PTR function_ptr){
	u8 status;
	for(u8 idx=0; idx < MAX_NUM_OF_SUBSCRIBERS; idx++){
		if(subscribers[idx] == function_ptr){
			subscribers[idx] = NULL;
			idx = MAX_NUM_OF_SUBSCRIBERS;		// ends the loop
			status = OK;
		}
		else{
			/* check the next location */
			status = ERROR;
		}
	}
	return status;
}

static u8 getEmptySubscribtionIndex(u8* result_ptr){
	u8 status;
	for(u8 idx=0; idx < MAX_NUM_OF_SUBSCRIBERS; idx++){
		if(subscribers[idx] == NULL){
			*result_ptr = idx;
			idx = MAX_NUM_OF_SUBSCRIBERS;		// ends the loop
			status = OK;
		}
		else{
			/* check the next location */
			status = ERROR;
		}
	}
	return status;
}
