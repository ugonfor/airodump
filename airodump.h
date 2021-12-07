#pragma once

// c
#include <stdio.h>
#include <stdint.h>
#include <time.h>

// cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>

// packet
#include <pcap.h>
#include "Gheader/mac.h"

using namespace std;


struct Mon{
    string dev;
    vector<int> channels;
};

struct dump_data{
    uint32_t BeaconCnt;
    char ESSID[0x100];
    uint8_t PWR;
};

extern map<Mac, dump_data> BeaconData;

void print_data(void);
void airodump(u_char* packet, uint32_t caplen, Mon mon);