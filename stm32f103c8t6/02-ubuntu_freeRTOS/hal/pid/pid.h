#ifndef __PID_CALC_H__
#define __PID_CALC_H__
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
} pid_calc_t, *ppid_calc_t;

typedef enum _PID_PARAM{
    PID_PARAM_KP = 0,
    PID_PARAM_KI = 1,
    PID_PARAM_KD = 2,
    PID_PARAM_MAX
} PID_PARAM;

#define PID_PARAM_INDEX(_x)     ()

void pid_init(pid_calc_t *ppid, int target, int iValid, int iOutLimit, int pidMax);
void pid_set_param(pid_calc_t *ppid, float Kp, float Ki, float Kd);
void pid_limit(int *key, int max);
int pid_calc(pid_calc_t *ppid, int NextPoint);

#endif  /* end __PID_CALC_H__ */