#include "timers.h"
#include "LCD.h"
#include "uart.h"
#include "stm32f10x_it.h"
#include "enc.h"
#include "nortos.h"
#include "stepmotor.h"

#define PORTB_READ_2            (*((volatile unsigned long *) 0x42218108))
#define PORTB_READ_3            (*((volatile unsigned long *) 0x4221810c))

static u8 Polar1 = 0;
static u8 Polar2 = 0;

void EXTI0_IRQHandler(void)
{
  static u8 InsideCounter = 0;
  
  EXTI->PR|=0x01; // clear interrupt
  InsideCounter++;
}

void EXTI1_IRQHandler(void)
{
  static u8 InsideCounter = 0;
  
  EXTI->PR|=0x02; // clear interrupt
  InsideCounter++;
}

void EXTI2_IRQHandler(void)
{
  static u8 InsideCounter = 0;
  
  EXTI->PR|=0x04; // clear interrupt
  
  Polar1 = PORTB_READ_2;
  Polar2 = PORTB_READ_3;
  if (Polar1 == 0){
    if( Polar2 == 0){
      if(dirDet == -1)  F1_push(EncDecrease);
      else              F1_push(EncIncrease);
    }
    dirDet = 1;
  }
  else{
    if(dirDet == -1)      F1_push(EncDecrease);
    else                  F1_push(EncIncrease);
  }
  InsideCounter++;
}

void EXTI3_IRQHandler(void)
{
  static u8 InsideCounter = 0;
  
  EXTI->PR|=0x08; // clear interrupt
  
  Polar1 = PORTB_READ_2;
  Polar2 = PORTB_READ_3;
  
  if(Polar2 == 0){
    if(Polar1 == 1)  dirDet = -1;
    else             dirDet = 1;
  }
  else{
    if(Polar1 == 1) dirDet = 1;
    else            dirDet = -1;
  }
  InsideCounter++;
}

void EXTI4_IRQHandler(void)
{
  static u8 InsideCounter = 0;
  
  EXTI->PR|=0x10; // clear interrupt
  InsideCounter++;
}

void TIM2_IRQHandler(void)
{
  static long long InsideCounter = 0;
  
  if (TIM2->SR & TIM_SR_UIF){
    TIM2->SR &= ~TIM_SR_UIF;        // очищаем флаг прерывания 
  }
  
  StepMotorRoutine(&InsideCounter);
   
  
  InsideCounter++;
}

void TIM3_IRQHandler(void)
{
  static uint32_t State = 0;
  
  if (TIM3->SR & TIM_SR_UIF){
    TIM3->SR &= ~TIM_SR_UIF;        // очищаем флаг прерывания 
  }
  
  if(milliseconds% 100 == 0){ 
   switch (State%24){
    case 0: 
      SetParams(360);
      F1_push(StartStepping);
      break;
    case 1:
      break;
    case 2: 
      break;
    case 3:
      break;      
    case 4: 
      break;
    case 5:
      break; 
    case 6: 
      break;
    case 7:
      break; 
    case 8: 
      break;
    case 9:
      break; 
    case 10: 
      break;
    case 11:
      break; 
    case 12:
      SetParams(-360);
      F1_push(StartStepping);
      break; 
    case 13:
      break;
    case 14: 
      break;
    case 15:
      break;      
    case 16: 
      break;
    case 17:
      break; 
    case 18: 
      break;
    case 19:
      break; 
    case 20: 
      break;
    case 21:
      break; 
    case 22: 
      break;
    case 23:
      break; 
    }
   State++;
  }
 
  
  milliseconds++;
}