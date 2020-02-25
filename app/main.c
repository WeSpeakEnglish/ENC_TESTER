#include "uart.h"
#include "timers.h"
#include "ioconfig.h"
#include "LCD.h"
#include "nortos.h"


int main(void)
{ 
   RCC->CR|=RCC_CR_HSEON; // Включить генератор HSE.
  while (!(RCC->CR & RCC_CR_HSERDY)) {} // Ожидание готовности HSE.
   RCC->CFGR &=~RCC_CFGR_SW; // Очистить биты SW0, SW1.
   RCC->CFGR |= RCC_CFGR_SW_HSE; // Выбрать HSE для тактирования SW0=1.
   RCC->CFGR &= ~RCC_CFGR_HPRE;           //Очистка битов предделителя "AHB Prescaler"
   RCC->CFGR |=  RCC_CFGR_HPRE_DIV1;      //Установить "AHB Prescaler" равным 8

  PortAConf();
  PortCConf();
  PortBConf();
  ButtonConf(); // button enable/disable signal
  TIM2_init();  //
  TIM3_init();
  Init_UART1(); 
  F1_QueueIni();
  ConfigureLCD();

     while(1){
      F1_pull()();
     }   

}