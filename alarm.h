#ifndef ALARM_H
#define ALARM_H

#include <stdint.h>

#define DAY_IN_SECONDS 24*60*60

void alarm_clock_init(void);
void alarm_clock_reschedule(uint8_t alarm_options, int8_t alarm_hour, int8_t alarm_minute);

void load_alarm_clock(uint8_t * alarm_options, int8_t * alarm_hour, int8_t * alarm_minute);
void store_alarm_clock(uint8_t alarm_options, int8_t alarm_hour, int8_t alarm_minute);

#endif /* ALARM_H */