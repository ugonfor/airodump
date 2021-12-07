#include "airodump.h"
#include "wirelesspkt.h"
#include "utils.h"

void print_data(void){
    while (true)
    {
        cout << "BSSID              PWR  Beacons    ESSID\n";
        
        for (auto it = BeaconData.begin(); it != BeaconData.end(); it++)
        {   
            cout << string(it->first).c_str() << "  -"<< (0x100 - it->second.PWR) << "  " 
                << it->second.BeaconCnt << "\t   " << it->second.ESSID << "\n";        
        }
        
        this_thread::sleep_for(chrono::milliseconds(100));

        clear();
    }
    
}

void airodump(u_char* packet, uint32_t caplen, Mon mon){
    radiotap_header* radio_pkt = (radiotap_header*) packet;
    BeaconFrame* beacon_pkt = (BeaconFrame*)(packet + radio_pkt->it_len);
    
    //memdump((uint8_t*)beacon_pkt, 0xff);
    //printf("%p %p %d\n", packet, beacon_pkt, ntohs(beacon_pkt->type));

    if(beacon_pkt->type != 0x80) return ;

    // BSSID
    uint8_t* BSSID = beacon_pkt->BSSID;
    
    // ESSID    
    char* ESSID;
    if (beacon_pkt->tag_data.tag_num != 0){
        fprintf(stderr,"No ESSID Data!");
        exit(1);
    }
    else
        ESSID = (char*)beacon_pkt->tag_data.data; // commonly tag number

    // PWR
    uint8_t PWR = *(packet + 0x16);

    // beacons
    auto it = BeaconData.find(BSSID);
    if (it == BeaconData.end()){
        BeaconData[BSSID].BeaconCnt = 1;
        BeaconData[BSSID].PWR = PWR;
        memcpy(BeaconData[BSSID].ESSID, ESSID, beacon_pkt->tag_data.tag_len);
    }
    else{
        BeaconData[BSSID].BeaconCnt++;
        BeaconData[BSSID].PWR = PWR;
    }

    return ;
}