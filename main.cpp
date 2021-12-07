#include "airodump.h"
#include "utils.h"
#include "wireless.h"

map<Mac, dump_data> BeaconData;

int main(int argc, char const *argv[])
{
    if(argc != 2){
        fprintf(stderr,"syntax : airodump <interface>\n");
        fprintf(stderr,"sample : airodump mon0\n");
        return 1;
    }

    cout << "[1] Initializing Monitor Object\n";
    Mon mon;
    mon.dev = argv[1];
    mon.channels = channel_list(mon.dev);
    sleep(1);
    clear();

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_live(mon.dev.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (pcap == NULL){
		fprintf(stderr, "pcap_open_live(%s) return null - %s\n", mon.dev.c_str(), errbuf);
		return -1;
	}

    thread* t_print_data = new  thread(print_data);
    t_print_data->detach();
    
    while(true){
        struct pcap_pkthdr* header;
        const u_char* packet;
        int res = pcap_next_ex(pcap, &header, &packet);
        if (res == 0) continue;
        if (res == PCAP_ERROR || res == PCAP_ERROR_BREAK){
			printf("pcap_next_ex return %d(%s)\n", res, pcap_geterr(pcap));
			break;
        }

        airodump((u_char*)packet, header->caplen, mon);

        //memdump((uint8_t*)packet, 0xff);
		//printf("%u bytes captured\n", header->caplen);
    }

    pcap_close(pcap);

    return 0;
}
