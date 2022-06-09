/*
 * poller.h
 *
 *  Created on: Mar 31, 2022
 *      Author: moham
 */

#ifndef INC_TC72POLLER_H_
#define INC_TC72POLLER_H_

void TC72_Poll(void);
void TC72_StartPolling(void);
void TC72_StopPolling(void);
void TC72_SetPollingTime(int polling_time);

#endif /* INC_TC72POLLER_H_ */
