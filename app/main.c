#include "uart.h"
#include "timers.h"
#include "ioconfig.h"
#include "LCD.h"
#include "nortos.h"
#include "enc.h"
#include "stepmotor.h"


int main(void)
{ 
   RCC->CR|=RCC_CR_HSEON; // �������� ��������� HSE.
  while (!(RCC->CR & RCC_CR_HSERDY)) {} // �������� ���������� HSE.
   RCC->CFGR &=~RCC_CFGR_SW; // �������� ���� SW0, SW1.
   RCC->CFGR |= RCC_CFGR_SW_HSE; // ������� HSE ��� ������������ SW0=1.
   RCC->CFGR &= ~RCC_CFGR_HPRE;           //������� ����� ������������ "AHB Prescaler"
   RCC->CFGR |=  RCC_CFGR_HPRE_DIV1;      //���������� "AHB Prescaler" ������ 8

  PortAConf();
  PortCConf();
  PortBConf();
  ButtonConf(); // button enable/disable signal
  MOTOR_DISABLE = 0;
  TIM2_init();
  TIM3_init();  //
  Init_UART1(); 
  F1_QueueIni();
  F2_QueueIni();
  ConfigureLCD();
  SetTestRevolutions(30000);
     while(1){
      F1_pull()();
      F2_pull()();
     }   

}