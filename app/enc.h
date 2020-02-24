#ifndef __ENC_H
#define __ENC_H
#include <stdint.h>

extern int EncVar;
extern uint32_t TotalSteps;
extern volatile int dirDet;
void EncIncrease(void);
void EncDecrease(void);
#endif