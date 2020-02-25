#include "enc.h"
#include "nortos.h"

int32_t EncVar = 0;
//uint32_t TotalSteps = 0;
uint32_t StepsUp = 0;
uint32_t StepsDown = 0;
volatile int dirDet = 0;
uint32_t RevUp = 0;
uint32_t RevDown = 0;

void EncIncrease(void){
 StepsUp++; 
 EncVar++;
}
void EncDecrease(void){
 StepsDown++;
 EncVar--;
}
void RevIncrease(void){
RevUp++;
}
void RevDecrease(void){
RevDown++;
}