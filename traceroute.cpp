#include "traceroute.h"
#include <iostream>

unsigned char* enICMPReqPack(unsigned char* source_mac, unsigned long source_ip, unsigned long dest_ip){
    ICMPPACK icmpp_default = {ETH_HRD_DEFAULT, IP_HRD_DEFAULT, ICMP_HRD_DEFAULT};
    static ICMPPACK icmpp;
    memcpy(&icmpp, &icmpp_default, sizeof(icmpp_default));
    memcpy(icmpp.eth.source_mac, source_mac, 6);
    icmpp.ih.sourceIP = source_ip;
    icmpp.ih.destIP = dest_ip;
    return (unsigned char*)&icmpp;
}

void sendICMPs(unsigned long destIP, ipmon::nic_device nd){
    unsigned short usSeqNo = 0;
    int TTL = 1;
    bool bReachDestHost = false;
    int iMaxHop = DEF_MAX_HOP;

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
    std::cout << packet_icmp_req << std::endl;
    while( !bReachDestHost && iMaxHop--){
        pcap_sendpacket(handle, packet_icmp_req, 60);
    }
    std::cout<< "sendICMPs..." << std::endl;
}

//end

