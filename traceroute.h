#ifndef TRACEROUTE_H
#define TRACEROUTE_H
#include "common.h"
#include <thread>
#include <mutex>
#include <functional>
namespace traceroute {
    class Traceroute
    {
    public:
        Traceroute();
        ~Traceroute();
        void sendICMPs();
    };
}


#endif // TRACEROUTE_H
