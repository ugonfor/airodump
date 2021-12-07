#pragma once

#include "airodump.h"

// for channel list
#include <iwlib.h>

vector<int> channel_list(string dev);

bool memdump(uint8_t* mem, uint32_t len);

void clear(void);