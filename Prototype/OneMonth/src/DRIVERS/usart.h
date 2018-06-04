/*
 * usart.h
 *
 * Created: 9/7/2017 9:31:55 PM
 *  Author: Mason
 */ 


#ifndef USART_H_
#define USART_H_

void usart_init(void);
void openlogger_tx(float data[16]);
void xbee_tx(float data[16]);

#endif /* USART_H_ */