#ifndef NICDEVICES_H
#define NICDEVICES_H
//nic class
#include <vector>
#include "common.h"
using namespace ipmon;
typedef std::vector<nic_device> nic_devices;
class NICDevices
{
public:
    NICDevices();
    ~NICDevices();
    void LoadAllEx(void);
    int Size(void);
    nic_device GetDevice(int index) const;
    std::string GetMacAddr(int index) const;
    std::string GetIPAddr(int index) const;
    std::string GetSubnetMask(int index) const;
    std::string GetName(int index) const;
    //std::string GetDefaultGw(int index) const;
    //std::string GetGwMacAddr(int index) const;
    //nic_device GetDevice(int index) const;
    unsigned char* GetSelfMac(char* pdev, char* mac) ;
private:
    void GetMacAddr(nic_device* device) const;
private:
    nic_devices devices_;
};
#endif // NICDEVICES_H
