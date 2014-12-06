main:NICDevices.o traceroute.o main.o common.o 
	g++ -std=c++11 -o main common.o NICDevices.o traceroute.o main.o -lpcap
main.o: main.cpp
	g++ -std=c++11 -c main.cpp -lpcap
common.o:common.cpp common.h
	g++ -c common.cpp
NICDevices.o:NICDevices.cpp NICDevices.h common.h
	g++ -c NICDevices.cpp -lpcap
traceroute.o:traceroute.cpp traceroute.h common.h
	g++ -std=c++11 -c traceroute.cpp
clean:
	rm -f NICDevices.o traceroute.o main.o common.o
