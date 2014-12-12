#ifndef TRACEROUTE_H
#define TRACEROUTE_H
#include "common.h"
#include <thread>
#include <mutex>
#include <functional>
void sendICMPs(unsigned long destIP, ipmon::nic_device nd);
unsigned char* enICMPReqPack(unsigned char *source_mac, unsigned long source_ip, unsigned long dest_ip);


#endif // TRACEROUTE_H
