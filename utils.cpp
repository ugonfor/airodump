#include "utils.h"

vector<int> channel_list(string dev){
	int skfd;
	iwrange range;
	vector<int> res;

	skfd = iw_sockets_open();
	iw_get_range_info(skfd, dev.c_str(), &range);
	iw_sockets_close(skfd);

	cout << range.num_channels << " channels in " << dev << "\n";
	printf("channels : \n");
	for (int i = 0; i < range.num_channels; i++)
	{
		printf("%3d ", range.freq[i].i);
		res.push_back(range.freq[i].i);
		if (((i + 1) % 10) == 0) printf("\n");
	}
	printf("\n");
	return res;
}


bool memdump(uint8_t* mem, uint32_t len){
	if (0xff < len){
		printf("memdump : too long length(0x%u)\n",len);
		return false;
	}
	printf("Memory Dump\n");
	printf("      00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f  0123456789ABCDEF\n");

	int idx = 0;
	while (len != idx)
	{
		if(idx % 0x10 == 0) printf("0x%02x  ", idx);
		printf("%02x ", *(mem + idx));
		if(idx % 0x10 == 0xf) {
			printf(" ");
			for (int i = -15; i <= 0; i++) {
				if ( 31 < *(mem+idx+i) &&  *(mem+idx+i) < 127 ) printf("%c", *(mem+idx+i));
				else printf(".");
			}
			printf("\n");
		}

		idx++;
	}
	
	if(idx % 0x10 != 0){
		for (int i = -(0x10 - idx%0x10) + 1; i <= 0; i++) printf("   ");
		printf(" ");

		for (int i = -(idx%0x10) + 1; i <= 0; i++) {
			if ( 31 < *(mem+idx+i) &&  *(mem+idx+i) < 127 ) printf("%c", *(mem+idx+i));
			else printf(".");
		}
	}
	printf("\n");

	return true;
}

void clear(void){
	system("clear");
}