#ifndef COMMON_H
#define COMMON_H
//struct define
#pragma pack(push,1)
#include <pcap/pcap.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#define BROARDMAC       {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
#define EH_TYPE			0x0806							//ARP类型
#define ARP_HRD			0x0001							//硬件类型：以太网接口类型为1
#define ARP_PRO			0x0800							//协议类型：IP协议类型为0X0800
#define ARP_HLN			0x06							//硬件地址长度：MAC地址长度为6B
#define ARP_PLN			0x04							//协议地址长度：IP地址长度为4B
#define ARP_REQUEST		0x0001							//操作：ARP请求为1
#define ARP_REPLY		0x0002							//操作：ARP应答为2

#define ETH_HRD_DEFAULT {BROARDMAC, {0,0,0,0,0,0}, htons(EH_TYPE)}

#define IPTOSBUFFERS 12

using namespace std;
typedef struct ethernet_head
{
    unsigned char dest_mac[6];    //destination host mac address
    unsigned char source_mac[6];  //source host mac address
    unsigned short eth_type;      // Ethernet type
}ethernet_head_s;

typedef struct arp_head
{
    unsigned short hardware_type;  //hardware type: Ethernet interface type is 1
    unsigned short protocal_type;  //protocol type:ip is 0X0800
    unsigned char add_len;         //hardware address length:mac address length is 6B
    unsigned char pro_len;         //protocol address length:ip address length is 4B
    unsigned short option;         //operation: arp request is 1, arp reply is 2
    unsigned char sour_addr[6];    //source mac address
    unsigned int sour_ip;         //source ip address
    unsigned char dest_addr[6];    //destination mac address
    unsigned int dest_ip;         //destintion ip address
    unsigned char padding[18];
}arp_head_s;

typedef struct arp_packet
{
    struct ethernet_head eth;
    struct arp_head arp;
}arp_packet_s;

namespace ipmon{
  struct nic_device
    {
        pcap_if_t*  pcap_if;
        string name;
        string description;
        u_long ip_addr;
        u_long subnet_mask;
        //u_long default_gw;
        u_char mac_addr[6];
        //u_char gw_mac_addr[6];
    };

    struct record
    {
        std::string source;
        std::string destination;
        std::string protocol;
        int number;
    };

    typedef struct protocol
    {
        int type;
        char* name;
    }protocol_s;
}

namespace traceroute{
    typedef struct ipheader{
         unsigned char version :4;         //4 bits header
         unsigned char hdr_len :4;        //4 bits header's length
         unsigned char tos;                    //8 bits service type
         unsigned short total_len;         //16 bits total lenght
         unsigned short identifier;        //16 bits
         unsigned short frag_and_flags; // 3 bits flags and 13 bits offset
         unsigned char ttl;                     //8 bits time to live
         unsigned char protocal;          //8 bits protocal
         unsigned short checksum;     //16 bits checksum
         unsigned long sourceIP;         //32 bits source IP
         unsigned long destIP;             //32 bits dest IP
     }IP_HEADER;

    typedef struct icmpheader{
        unsigned char  type;                //8 bits type
        unsigned char code;                //8 bits code
        unsigned short cksum;            //16 bits checksum
        unsigned short id;                    //16 bits
        unsigned short seq;                 //16 bits serial num
    }ICMP_HEADER;

    const unsigned char ICMP_ECHO_REQUEST = 8;
    const unsigned char ICMP_ECHO_REPLY = 0;
    const unsigned char ICMP_ECHO_CODE = 0;
    const unsigned char ICMP_TIMEOUT = 11;

    const int DEF_ICMP_DATA_SIZE = 32;
    const int MAX_ICMP_PACKET_SIZE = 1024;
    const unsigned int DEF_ICMP_TIMEOUT = 3000;
    const int DEF_MAX_HOP = 30;

    //01000101
    #define IP_HRD_DEFAULT  {0x45,0x00,0x0000,0x0000,0x0000,0x00,0x02,0x0000,{0,0,0,0},{0,0,0,0}}
    #define ICMP_HRD_DEFAULT {ICMP_ECHO_REQUEST,ICMP_ECHO_CODE,0x00,0x00,0x00}
}

char* iptos(u_long in);
char* mactos(u_char* in);
string GetProtocol(unsigned char  Protocol);
#endif // COMMON_H
