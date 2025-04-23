#ifndef __CAR_H__
#define __CAR_H__
#include <pwm.h>

typedef enum _CAR_STAT {
    CAR_STAT_STOP = 0,
    CAR_STAT_RUN = 1,
} CAR_STAT;

void car_go_ahead(int duty);
void car_go_back(int duty);
void car_stop();

void car_stand_control(int duty);

#endif  /* __CAR_H__ */