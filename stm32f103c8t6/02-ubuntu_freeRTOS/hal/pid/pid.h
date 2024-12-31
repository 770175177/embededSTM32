#ifndef __PID_H__
#define __PID_H__
#include "stm32f10x.h"

typedef struct
{
    float Kp;
    float Ki;
    float Kd;

    int target;
    int current;

    int e;
    int lastE;

    int pOut;
    int iOut;
    int dOut;
    int pidOut;

    int integralValid;
    int integralLimit;
    int pidOutMax;
} pid_t, *ppid_t;

void pid_init(pid_t *ppid, int target, int iValid, int iOutLimit, int pidMax);
void pid_set_param(pid_t *ppid, float Kp, float Ki, float Kd);
void pid_limit(int *key, int max);
int pid_calc(pid_t *ppid, int NextPoint);

#endif