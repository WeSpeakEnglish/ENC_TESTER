#include "timers.h"
#include "LCD.h"
#include "hd44780_driver.h"
#include "uart.h"
#include "enc.h"
#include "nortos.h"

void TIM2_init(void)
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   //разрешить подачу тактовых импульсов на TIM2
  TIM2->CNT = 0;
  TIM2->SR = 0;
  TIM2->CR2=0x0;          //обнуляем регистр
  TIM2->CR1=0x0;          //обнуляем регистр
  
  TIM2->PSC = 124;          // предделитель таймера 2
  TIM2->ARR = 4;      //
  
  TIM2->CR1 &= ~TIM_CR1_DIR;      //прямой счёт - 0 (обратный - 1) отсчёт
  TIM2->CR1 &= ~TIM_CR1_UDIS;      //запр.-1; разрешаем событие по перепол.таймера -0
  TIM2->CR1 &= ~TIM_CR1_CKD;      //clock division
  TIM2->CR1 &= ~TIM_CR1_ARPE;      //запрещаем 0 - когда прграмно не надо менять значение ARR;разрешаем=1 перзагрузку
  TIM2->CR1 &= ~TIM_CR1_OPM;      //Запрещаем работу в режиме одиночного импульса
  TIM2->DIER |= TIM_DIER_UIE;      //&UPDATE INTERRPUT - прерывание по переполнению &&&
  
  TIM2->CR1 |= TIM_CR1_URS;
  TIM2->EGR &= ~TIM_EGR_UG;      // сбрасываем 0 ;update enable  ARR и прескалер грузятся из предварительного в теневой регистр
  TIM2->CR1 |= TIM_CR1_CEN;       //запускаем таймер2
  NVIC_EnableIRQ (TIM2_IRQn);    //разрешаем прерывание
}

void TIM3_init(void)
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;   //разрешить подачу тактовых импульсов на TIM2
  TIM3->CNT = 0;
  TIM3->SR = 0;
  TIM3->CR2=0x0;          //обнуляем регистр
  TIM3->CR1=0x0;          //обнуляем регистр
  
  TIM3->PSC = 79;          // предделитель таймера 3
  TIM3->ARR = 99;      //
  
  TIM3->CR1 &= ~TIM_CR1_DIR;      //прямой счёт - 0 (обратный - 1) отсчёт
  TIM3->CR1 &= ~TIM_CR1_UDIS;      //запр.-1; разрешаем событие по перепол.таймера -0
  TIM3->CR1 &= ~TIM_CR1_CKD;      //clock division
  TIM3->CR1 &= ~TIM_CR1_ARPE;      //запрещаем 0 - когда прграмно не надо менять значение ARR;разрешаем=1 перзагрузку
  TIM3->CR1 &= ~TIM_CR1_OPM;      //Запрещаем работу в режиме одиночного импульса
  TIM3->DIER |= TIM_DIER_UIE;      //&UPDATE INTERRPUT - прерывание по переполнению &&&
  
  TIM3->CR1 |= TIM_CR1_URS;
  TIM3->EGR &= ~TIM_EGR_UG;      // сбрасываем 0 ;update enable  ARR и прескалер грузятся из предварительного в теневой регистр
  TIM3->CR1 |= TIM_CR1_CEN;       //запускаем таймер 3
  NVIC_EnableIRQ (TIM3_IRQn);    //разрешаем прерывание
}

