#ifndef __ENC_H
#define __ENC_H
#include <stdint.h>

extern int EncVar;
extern uint32_t TotalSteps;
extern volatile int dirDet;
extern uint32_t StepsUp;
extern uint32_t StepsDown;
void EncIncrease(void);
void EncDecrease(void);




#endif