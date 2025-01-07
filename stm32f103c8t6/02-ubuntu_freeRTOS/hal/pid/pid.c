#include "pid.h"
#include <math.h>

void pid_init(pid_calc_t *ppid, int target, int iValid, int iOutLimit, int pidMax)
{
    ppid->Kp     = 0.1f;                // 比例
    ppid->Ki     = 0.0f;                // 积分
    ppid->Kd     = 0.0f;                // 微分

    ppid->target = target;
    ppid->lastE = 0;

    ppid->pOut  = 0;     
    ppid->iOut  = 0;     
    ppid->dOut  = 0;     

    ppid->integralValid  = iValid;      // 误差小于该值时积分生效
    ppid->integralLimit  = iOutLimit;   // 积分限幅
    ppid->pidOutMax      = pidMax;      // PID整体输出限幅
}

void pid_set_param(pid_calc_t *ppid, float Kp, float Ki, float Kd)
{
    ppid->Kp = Kp;
    ppid->Ki = Ki;
    ppid->Kd = Kd;
}

void pid_limit(int *key, int max)
{
    int maxAbs = fabs(max);

    if (*key > maxAbs)
        *key = maxAbs;
    else if (*key < -maxAbs)
        *key = -maxAbs;
}

int pid_calc(pid_calc_t *ppid, int current)
{
    ppid->current = current;

    // 当前误差
    ppid->e = ppid->target - ppid->current;

    // 比例
    ppid->pOut = (int32_t)(ppid->Kp * ppid->e);

    // 积分分离，当误差e项小于某个值时，才让它发挥作用
    if (fabs(ppid->e) < ppid->integralValid) {
        // 积分
        ppid->iOut += (int32_t)(ppid->Ki * ppid->e);
        // 积分限幅
        pid_limit(&(ppid->iOut), ppid->integralLimit);
    } else {
        ppid->iOut = 0;
    }

    // 微分
    ppid->dOut = (int32_t)(ppid->Kd * (ppid->e - ppid->lastE));

    // 输出总的PID
    ppid->pidOut = ppid->pOut + ppid->iOut + ppid->dOut;

    // PID输出限幅
    pid_limit(&(ppid->pidOut), ppid->pidOutMax);

    ppid->lastE = ppid->e;

    return ppid->pidOut;
}