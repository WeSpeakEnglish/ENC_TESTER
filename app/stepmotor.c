#include <stdint.h>
#include "stepmotor.h"
#include "nortos.h" 
#include "stm32f10x_it.h"


#define ANGLEPERSTEP 1.8
#define REVOLUTION_TEST_COUNT_STOP 10000
#define EDGESPERSTEP 64 





#define STEPS_MOTOR_REVOLUTION  12800

uint8_t volatile StopFlag = 0;
uint8_t DirectionStp = 0;
uint32_t StepsRotate = 0;
uint8_t Direction = 0;
uint32_t RevUp = 0;
uint32_t RevDown = 0;


void StartStepping(void){
 StopFlag = 0;
}

void SetParams(float angle){   
  
  if(angle < 0){
    angle = - angle;
    DirectionStp = 0;

 }
 else{
     DirectionStp = 1;
 }
 
 StepsRotate = (uint32_t)((float)angle/(float)ANGLEPERSTEP)  * (float)EDGESPERSTEP;
 MOTOR_DISABLE = 0;
}

void RevIncrease(void){
RevUp++;
}
void RevDecrease(void){
RevDown++;
}

void StepMotorRoutine(long long * InsideCounter){
 if (!StopFlag){
   if(MOTOR_DISABLE){
     *InsideCounter = 0;
   }
   else{
    
    if(*InsideCounter%2){
      GPIOA->BSRR = GPIO_BSRR_BS8;
    }
    else {
      GPIOA->BSRR = GPIO_BSRR_BR8;
    }
    
    if(*InsideCounter == StepsRotate){
      MOTOR_DISABLE = 1; 
      
      if(DirectionStp){
        GPIOA->BSRR = GPIO_BSRR_BR15;
          F1_push(RevDecrease);
      }
      else{ 
        GPIOA->BSRR = GPIO_BSRR_BS15;
          F1_push(RevIncrease);
      }

    }
   }
  }

    
 // if(*InsideCounter%STEPS_MOTOR_REVOLUTION == 1){
 //     screen++;
 //     screen %=6;
 //     if(screen < 3) F1_push(DisplaySteps);
//      else F1_push(DisplayRevolutions);
 // }
}

