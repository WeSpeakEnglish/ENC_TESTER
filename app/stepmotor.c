#include <stdint.h>
#include "stepmotor.h"
#include "nortos.h" 
#include "stm32f10x_it.h"


#define ANGLEPERSTEP 1.8
//#define REVOLUTION_TEST_COUNT_STOP 10
#define EDGESPERSTEP 64 





#define STEPS_MOTOR_REVOLUTION  12800

uint8_t volatile StopFlag = 1;
uint8_t FinishFlag = 0 ;
uint8_t DirectionStp = 0;
uint32_t StepsRotate = 0;
uint8_t Direction = 0;
uint32_t RevUp = 0;
uint32_t RevDown = 0;
uint32_t TestRevTotal = 0;

void StartStepping(void){
 StopFlag = 0;
}

void SetTestRevolutions(uint32_t Revolutions){
 TestRevTotal =  Revolutions;
 StopFlag = 0;
}

void SetSteps(int32_t Steps){   
  
  if(Steps < 0){
    Steps = - Steps;
    DirectionStp = 0;

 }
 else{
     DirectionStp = 1;
 }
 
 StepsRotate = (uint32_t)Steps * EDGESPERSTEP;
 MOTOR_DISABLE = 0;
 GPIOB->BSRR = GPIO_BSRR_BR5;
}

void RevIncrease(void){
RevUp++;

}
void RevDecrease(void){
RevDown++;
}

void StepMotorRoutine(long long * InsideCounter){

 if (!StopFlag){
   if(TestRevTotal == (RevUp + RevDown)){
   StopFlag = 1;
   FinishFlag = 1;
   } 
            
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
      GPIOB->BSRR = GPIO_BSRR_BS5;
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
 else {
 GPIOB->BSRR = GPIO_BSRR_BS5;
 }
}

