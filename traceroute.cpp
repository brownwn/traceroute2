#include "traceroute.h"
#include <iostream>

unsigned char* enICMPReqPack(){

    return (unsigned char*)"sss";
}

void sendICMPs(unsigned long destIP, ipmon::nic_device nd){
    unsigned short usSeqNo = 0;
    int TTL = 1;
    bool bReachDestHost = false;
    int iMaxHop = traceroute::DEF_MAX_HOP;

    pcap_t* handle;
    const char* devname = nd.name.c_str();
    unsigned long ipaddress = nd.ip_addr;
    char errbuf[PCAP_ERRBUF_SIZE];
    if(handle = pcap_open_live(devname, 65535, 1, 1000, errbuf)){
        std::cout << "open adapter success!" << std::endl;
    }else{
        std::cout << "open adpter failed!" << std::endl;
    }

    unsigned char* packet_icmp_req = enICMPReqPack();

    while( !bReachDestHost && iMaxHop--){
        pcap_sendpacket(handle, packet_icmp_req, 60);
    }
    std::cout<< "sendICMPs..." << std::endl;
}

//end

