#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H
#include <stdint.h>

extern volatile uint8_t StopFlag;
extern uint8_t DirectionStp;
extern uint32_t StepsRotate;
extern uint32_t RevUp;
extern uint32_t RevDown;

void StartStepping(void);
void SetSteps(int32_t Steps);
void SetTestRevolutions(uint32_t Revolutions);
void StepMotorRoutine(long long * InsideCounter);

#define MOTOR_DISABLE           (*((volatile unsigned long *) 0x42218194))


#endif