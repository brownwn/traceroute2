#ifndef TRACEROUTE_H
#define TRACEROUTE_H
#include "common.h"
#include <thread>
#include <mutex>
#include <functional>
void sendICMPs(unsigned long destIP, ipmon::nic_device nd);


#endif // TRACEROUTE_H
