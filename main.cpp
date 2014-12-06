//This is the main file
#include <iostream>
#include "NICDevices.h"
#include "traceroute.h"
#include <thread>
#include <mutex>
//#include "common.h"
using namespace std;
using namespace ipmon;
int main()
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
    //while(1);
    traceroute::Traceroute tr = traceroute::Traceroute();
}
