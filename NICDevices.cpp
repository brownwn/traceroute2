//nic implenment
#include "NICDevices.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;
NICDevices::NICDevices(){}
NICDevices::~NICDevices(){}
void NICDevices::LoadAllEx(void)
{
    devices_.clear();
    pcap_if_t* alldevs;
    pcap_if_t* d;
    pcap_addr_t* pAdr;
    unsigned long chLocalIp;
    char errbuf[PCAP_ERRBUF_SIZE];

    if(pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        std::cout<<errbuf<<std::endl;
        return;
    }
    for(d = alldevs; d; d = d->next)
    {
        nic_device device;
        device.pcap_if = d;
        device.name = string(d->name);

        if(d->description)
        {
            //cout << d->description<<endl;
            device.description = string(d->description);
        }else{
            device.description = "";
        }
        pAdr = d->addresses;
        while(pAdr)
        {
            chLocalIp = ((struct sockaddr_in*)pAdr->addr)->sin_addr.s_addr;

            if(chLocalIp < 10)
            {
                pAdr = pAdr->next;
                continue;
            }
            device.ip_addr = chLocalIp;
            device.subnet_mask = ((struct sockaddr_in*)pAdr->netmask)->sin_addr.s_addr;
            break;
        }
        char mac[20];
        GetSelfMac(d->name, mac);
        memcpy(device.mac_addr, mac, 6);

        devices_.push_back(device);
    }
    pcap_freealldevs(alldevs);


}
unsigned char* NICDevices::GetSelfMac(char* pDev, char* mac)
{
    struct ifreq ifreq;
    int sock = 0;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        std::cout<<"error sock"<<std::endl;
        return (unsigned char*)("");
    }
    strcpy(ifreq.ifr_name, pDev);
    if(ioctl(sock, SIOCGIFHWADDR,&ifreq) < 0)
    {
        std::cout<<"error ioctl"<<std::endl;
        return (unsigned char*)("");
    }
    int i = 0;
    for(i = 0; i < 6; i++)
    {
        sprintf(mac+i, "%c", ifreq.ifr_hwaddr.sa_data[i]);
    }
    return (unsigned char*)mac;
}
int NICDevices::Size(void)
{
    return devices_.size();
}
nic_device NICDevices::GetDevice(int index) const
{
    if (index >= 0 && index < devices_.size())
    {
        return devices_[index];
    }
    nic_device device;
    memset(&device, 0, sizeof(nic_device));
    return device;
}
std::string NICDevices:: GetMacAddr(int index) const
{
    return string(mactos(GetDevice(index).mac_addr));
}
std::string NICDevices::GetIPAddr(int index) const
{
    return string(iptos(GetDevice(index).ip_addr));
}
std::string NICDevices::GetSubnetMask(int index) const
{
    return string(iptos(GetDevice(index).subnet_mask));
}
std::string NICDevices::GetName(int index) const
{
    return GetDevice(index).name;
}
//std::string NICDevices::GetDefaultGw(int index) const
//{return "";}
//std::string NICDevices::GetGwMacAddr(int index) const
//{return "";}
//nic_device NICDevices::GetDevice(int index) const
//{}
//void NICDevices::GetMacAddr(nic_device* device) const
//{}
