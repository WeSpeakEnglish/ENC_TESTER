#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H

extern volatile uint8_t StopFlag;
extern uint8_t DirectionStp;
extern uint32_t StepsRotate;
extern uint32_t RevUp;
extern uint32_t RevDown;

void StartStepping(void);
void SetParams(float angle);
void StepMotorRoutine(long long * InsideCounter);

#define MOTOR_DISABLE           (*((volatile unsigned long *) 0x42218194))


#endif