#pragma once
#include <Arduino.h>
#include <stdint.h>
#include <sys_def.h>

void wait_for_serial(uint32_t time_ms);
void timestamp(void);
void Handle_user(void);