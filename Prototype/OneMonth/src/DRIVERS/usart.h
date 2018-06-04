/*
 * usart.h
 *
 * Created: 9/7/2017 9:31:55 PM
 *  Author: Mason
 */ 


#ifndef USART_H_
#define USART_H_

void usart_init(void);

void usart_tx(USART_t* usart_channel, const char* text, ...);
char * usart_rx(USART_t* usart_channel,char* read_buffer);

#endif /* USART_H_ */