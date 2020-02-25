#ifndef __ENC_H
#define __ENC_H
#include <stdint.h>

extern int EncVar;
extern uint32_t TotalSteps;
extern volatile int dirDet;
extern uint32_t StepsUp;
extern uint32_t StepsDown;
extern uint32_t RevUp;
extern uint32_t RevDown;
void EncIncrease(void);
void EncDecrease(void);
void RevIncrease(void);
void RevDecrease(void);
#endif