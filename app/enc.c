#include "enc.h"
#include "nortos.h"

int32_t EncVar = 0;
uint32_t TotalSteps = 0;
volatile int dirDet = 0;

void EncIncrease(void){
 TotalSteps++; 
 EncVar++;
}
void EncDecrease(void){
 TotalSteps++;
 EncVar--;
}
