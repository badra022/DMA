/*
 * poller.h
 *
 *  Created on: Mar 31, 2022
 *      Author: moham
 */

#ifndef INC_TC72_H_
#define INC_TC72_H_

#define MAX_NUM_OF_SUBSCRIBERS		10

typedef void(*CLIENT_ACCEPT_FUNCTION_PTR)(u8);

void TC72_init(void);
u8 TC72_getData(void);
void notifyClients(u8 data);
void TC72_manageData(void);
u8 TC72_subscribe(CLIENT_ACCEPT_FUNCTION_PTR function_ptr);
u8 TC72_unsubscribe(CLIENT_ACCEPT_FUNCTION_PTR function_ptr);


#endif /* INC_TC72_H_ */
