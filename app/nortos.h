// NORTOS: The simplisity matter! By Aleksei Tertychnyi, 2015, WTFPL licenced
#ifndef _NORTOS_H
#define _NORTOS_H
#define Q_SIZE_FAST 32

void F1_QueueIni(void); // initialization of Queue
int F1_push(void (*pointerQ)(void) ); // push element from the queue
void (*F1_pull(void))(void); // pull element from the queue

// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----
void F2_QueueIni(void); // initialization of Queue
int F2_push(void (*pointerQ)(void) ); // push element from the queue
void (*F2_pull(void))(void); // pull element from the queue

// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----
void F3_QueueIni(void); // initialization of Queue
int F3_push(void (*pointerQ)(void) ); // push element from the queue
void (*F3_pull(void))(void); // pull element from the queue

// ------ 8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----

#endif
