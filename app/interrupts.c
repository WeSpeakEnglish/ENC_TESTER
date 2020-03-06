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
  if (Polar1 == Polar2) 
    F1_push(EncDecrease);
  else 
    F1_push(EncIncrease);
/*
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
*/
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
#define DispShowDelay 32

void TIM3_IRQHandler(void)
{
  static uint32_t State         = 0;
  static uint32_t StateDisp     = 0;
  
  if (TIM3->SR & TIM_SR_UIF){
    TIM3->SR &= ~TIM_SR_UIF;        // очищаем флаг прерывания 
  }
  
  if(milliseconds% 100 == 0){ 
   switch (State%36){
    case 0: 
      if(!FinishFlag){
          SetSteps(200);
          F1_push(StartStepping);
      }
      break;
    case 18:\
      if(!FinishFlag){
          SetSteps(-200);
          F1_push(StartStepping);
      }
      break; 
     }
   switch (State%8){
    case 0:
      StateDisp++;
      if(StateDisp%DispShowDelay < (DispShowDelay>>1))
          F2_push(DisplaySteps);
      if(StateDisp%DispShowDelay > (DispShowDelay>>1))
          F2_push(DisplayRevolutions);
      break;
   }
   State++;
  }
  
  milliseconds++;
}