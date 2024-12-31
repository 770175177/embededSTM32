#ifndef __CAR_H__
#define __CAR_H__
#include <pwm.h>

void car_go_ahead(int duty);
void car_go_back(int duty);

void car_stand_control(int duty);

#endif  /* __CAR_H__ */