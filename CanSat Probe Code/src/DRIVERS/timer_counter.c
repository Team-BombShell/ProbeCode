/*
 * timer_counter.c
 *
 * Created: 9/7/2017 8:58:25 PM
 *  Author: Mason
 */ 

#include "Drivers/timer_counter.h"
#include <asf.h>

   void timer_bounter_init(uint16_t period, uint16_t duty_cycle){
	   PORTA.DIRSET = 0b00000010;
	   TCA0.CTRLA = 0b00000111;
	   TCA0.CTRLB = 0b10000011;
	   TCA0.PER = (uint16_t)(period);
	   //TCA0.CCA = TCA0.PER-(TCA0.PER/10);
	   //TCA0.CCB = TCA0.PER-(TCA0.PER/10);
	   //TCA0.CCC = TCA0.PER-(TCA0.PER/10);
	   TCA0.CCD = TCA0.PER*((float)duty_cycle/100);
   }
   
  void timer_counter_init(uint16_t period, uint16_t duty_cycle){
	  PORTA.DIRSET = 0b00000100;
	  TCA0.CTRLA = 0b00000111;
	  TCA0.CTRLB = 0b10000011;
	  TCA0.PER = (uint16_t)(period);
	  //TCA0.CCA = TCA0.PER-(TCA0.PER/10);
	  //TCA0.CCB = TCA0.PER-(TCA0.PER/10);
	  //TCA0.CCC = TCA0.PER-(TCA0.PER/10);
	  TCA0.CCD = TCA0.PER*((float)duty_cycle/100);
  }
  
 void timer_dounter_init(uint16_t period, uint16_t duty_cycle){
	 PORTA.DIRSET = 0b00001000;
	 TCA0.CTRLA = 0b00000111;
	 TCA0.CTRLB = 0b10000011;
	 TCA0.PER = (uint16_t)(period);
	 //TCA0.CCA = TCA0.PER-(TCA0.PER/10);
	 //TCA0.CCB = TCA0.PER-(TCA0.PER/10);
	 //TCA0.CCC = TCA0.PER-(TCA0.PER/10);
	 TCA0.CCD = TCA0.PER*((float)duty_cycle/100);
 }
 
void timer_founter_init(uint16_t period, uint16_t duty_cycle){
	PORTA.DIRSET = 0b00010000;
	TCA0.CTRLA = 0b00000111;
	TCA0.CTRLB = 0b00010011;
	TCA0.PER = (uint16_t)(period);
	TCA0.CCA = TCA0.PER*((float)duty_cycle/100);
	//TCA0.CCB = TCA0.PER-(TCA0.PER/10);
	//TCA0.CCC = TCA0.PER-(TCA0.PER/10);
	//TCA0.CCD = TCA0.PER-(TCA0.PER/10);
}

void timer_counter_buzzer(){
	PORTF.DIR = 0b11111111;
	TCF1.CTRLA = 0b00000111;
	TCF1.CTRLB = 0b11110011;
	TCF1.PER = 12;
	TCF1.CCA = .9 * TCF1.PER;
	TCF1.CCB = TCF1.PER/1;

/* Timer Counter init for LEDs
static void my_cfa_callback(void)
{
	PORTF.OUT |= 0b00000001;
}
static void my_cfb_callback(void)
{
	PORTF.OUT &= 0b11111110;
}
void timer_counter_init(void){
	pmic_init();
	cpu_irq_enable();
	tc_enable(&TCF0);
	tc_set_cca_interrupt_callback(&TCF0, my_cfa_callback);
	tc_set_ccb_interrupt_callback(&TCF0, my_cfb_callback);
	tc_set_wgm(&TCF0, TC_WG_NORMAL);
	tc_write_period(&TCF0, 10000);
	tc_write_cc(&TCF0, TC_CCA, 100);
	tc_write_cc(&TCF0, TC_CCB, 1000);
	tc_enable_cc_channels(&TCF0,(TC_CCAEN | TC_CCBEN));
	tc_set_cca_interrupt_level(&TCF0, TC_INT_LVL_LO);
	tc_set_ccb_interrupt_level(&TCF0, TC_INT_LVL_MED);
	tc_write_clock_source(&TCF0, TC_CLKSEL_DIV1024_gc);
}

// Timer counter setup for LEDs
void timer_counter_setup(uint16_t period, uint16_t on, uint16_t off){
	tc_write_period(&TCF0, period);
	tc_write_cc(&TCF0, TC_CCA, on);
	tc_write_cc(&TCF0, TC_CCB, off);
}

// Timer counter init for buzzer
static void my_cda_callback(void)
{
	PORTD.OUT |= 0b00001000;
}
static void my_cdb_callback(void)
{
	PORTD.OUT &= 0b111110111;
}
void timer_dounter_init(void){
	pmic_init();
	cpu_irq_enable();
	tc_enable(&TCD0);
	tc_set_cca_interrupt_callback(&TCD0, my_cda_callback);
	tc_set_ccb_interrupt_callback(&TCD0, my_cdb_callback);
	tc_set_wgm(&TCD0, TC_WG_NORMAL);
	tc_write_period(&TCD0, 10000);
	tc_write_cc(&TCD0, TC_CCA, 100);
	tc_write_cc(&TCD0, TC_CCB, 1000);
	tc_enable_cc_channels(&TCD0,(TC_CCAEN | TC_CCBEN));
	tc_set_cca_interrupt_level(&TCD0, TC_INT_LVL_LO);
	tc_set_ccb_interrupt_level(&TCD0, TC_INT_LVL_MED);
	tc_write_clock_source(&TCD0, TC_CLKSEL_DIV1024_gc);
}

// Timer counter setup for Buzzer
void timer_dounter_setup(uint16_t period, uint16_t on, uint16_t off){
	tc_write_period(&TCD0, period);
	tc_write_cc(&TCD0, TC_CCA, on);
	tc_write_cc(&TCD0, TC_CCB, off);
}

static void my_cea_callback(void)
{
	PORTE.OUT = 0b10101010;
}
static void my_ceb_callback(void)
{
	PORTE.OUT = 0b01010101;
}
void timer_eounter_init(void){
	pmic_init();
	cpu_irq_enable();
	tc_enable(&TCE0);
	tc_set_cca_interrupt_callback(&TCE0, my_cea_callback);
	tc_set_ccb_interrupt_callback(&TCE0, my_ceb_callback);
	tc_set_wgm(&TCE0, TC_WG_NORMAL);
	tc_write_period(&TCE0, 10000);
	tc_write_cc(&TCE0, TC_CCA, 100);
	tc_write_cc(&TCE0, TC_CCB, 1000);
	tc_enable_cc_channels(&TCE0,(TC_CCAEN | TC_CCBEN));
	tc_set_cca_interrupt_level(&TCE0, TC_INT_LVL_LO);
	tc_set_ccb_interrupt_level(&TCE0, TC_INT_LVL_MED);
	tc_write_clock_source(&TCE0, TC_CLKSEL_DIV1024_gc);
}

// Timer counter setup for Test LEDs
void timer_eounter_setup(uint16_t period, uint16_t on, uint16_t off){
	tc_write_period(&TCE0, period);
	tc_write_cc(&TCE0, TC_CCA, on);
	tc_write_cc(&TCE0, TC_CCB, off);
}*/