//This is the main file
#include <iostream>
#include "NICDevices.h"
#include "traceroute.h"
#include <thread>
#include <mutex>
#include <arpa/inet.h>
#include <netdb.h>
//#include "common.h"
using namespace std;
using namespace ipmon;
unsigned long IPoHosttol(char* str){
    unsigned long destIP = inet_addr(str);
    if(destIP == INADDR_NONE){
        hostent* pHost = gethostbyname(str);
        if(pHost){
            destIP = (*(in_addr* )pHost->h_addr_list[0]).s_addr;
            //cout << iptos(destIP) << endl;
        }else{
            cout << "invalide dest address." << endl;
            exit(0);
        }
    }
    return destIP;
}
int main(int argc, char* argv[])
{
    NICDevices* nics = new NICDevices();
    nics->LoadAllEx();
    int size = nics->Size();
    std::cout << size << std::endl;
    std::cout << nics->GetIPAddr(0) << endl;
    std::cout << nics->GetSubnetMask(0) << endl;
    std::cout << nics->GetMacAddr(0) << endl;
    std::cout << nics->GetName(0) << endl;
    nic_device nd = nics->GetDevice(0);
    unsigned long destIP;
    destIP = IPoHosttol(argv[1]);

    //cout << destIP << endl;
    sendICMPs(destIP, nd);
}
