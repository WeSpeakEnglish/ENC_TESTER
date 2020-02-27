#include "timers.h"
#include "LCD.h"
#include "uart.h"
#include "stm32f10x_it.h"
#include "enc.h"
#include "nortos.h"

#define PORTB_READ_2            (*((volatile unsigned long *) 0x42218108))
#define PORTB_READ_3            (*((volatile unsigned long *) 0x4221810c))


#define STEPS_MOTOR_REVOLUTION  12800

static u8 Polar1 = 0;
static u8 Polar2 = 0;
static uint8_t Direction = 0;

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
  static long long InsideCounter = 1;
  static uint8_t screen = 0;
  static int StopFlag = 0;
  static int DeadTime = 0;
  
  if (TIM2->SR & TIM_SR_UIF){
    TIM2->SR &= ~TIM_SR_UIF;        // очищаем флаг прерывания 
  }
  

  
  if (!StopFlag && !DeadTime){
    
     MOTOR_DISABLE = 0;
    
    if(InsideCounter%2){
      GPIOA->BSRR = GPIO_BSRR_BS8;
    }
    else {
      GPIOA->BSRR = GPIO_BSRR_BR8;
    }
    
    if(InsideCounter %(STEPS_MOTOR_REVOLUTION) == 0){
      Direction++;
      Direction %=2;
      DeadTime = 10000;
      
      if(Direction){
        GPIOA->BSRR = GPIO_BSRR_BR15;
        if (RevUp+RevDown > REVOLUTION_TEST_COUNT_STOP-1){
          StopFlag++;
        }
        else {
          F1_push(RevDecrease);
        }
      }
      else{ 
        GPIOA->BSRR = GPIO_BSRR_BS15;
        if (RevUp+RevDown > REVOLUTION_TEST_COUNT_STOP-1){
          StopFlag++;
        }
        else{
          F1_push(RevIncrease);
        }
      }

    }
  }
  else{
    MOTOR_DISABLE = 1;
    DeadTime--;
  }

    
  if(InsideCounter%STEPS_MOTOR_REVOLUTION == 1){
      screen++;
      screen %=6;
      if(screen < 3) F1_push(DisplaySteps);
      else F1_push(DisplayRevolutions);
  }
  InsideCounter++;
}

void TIM3_IRQHandler(void)
{
  static long long InsideCounter = 0;
  if (TIM3->SR & TIM_SR_UIF){
    TIM3->SR &= ~TIM_SR_UIF;        // очищаем флаг прерывания 
  }
  
  InsideCounter++;
}