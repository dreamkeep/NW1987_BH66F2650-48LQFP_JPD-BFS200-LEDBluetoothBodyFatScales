#ifndef INTERRUPT_H__
#define INTERRUPT_H__

#if 0
DEFINE_ISR(isr_int0,INT0_VECTOR);
DEFINE_ISR(isr_int1,INT1_VECTOR);
DEFINE_ISR(isr_adc,ADC_VECTOR);
/* Multi function0 STM0 & PTM0 */
DEFINE_ISR(isr_mf0,MuFunction0_VECTOR);
/*  Multi function1 PTM1 & PTM2 */
DEFINE_ISR(isr_mf1,MuFunction1_VECTOR);
/*  Multi function2 LVD & EEPROM W */
DEFINE_ISR(isr_mf2,MuFunction2_VECTOR);
DEFINE_ISR(isr_timebase0,Timebase0_VECTOR);
DEFINE_ISR(isr_timebase1,Timebase1_VECTOR);
DEFINE_ISR(isr_uart,UART_VECTOR);
DEFINE_ISR(isr_sim,SIM_VECTOR);
DEFINE_ISR(isr_spi,SPI_VECTOR);
#endif

#endif //INTERRUPT_H__
