g++ -c -fPIC -std=c++20 -I../lib/boostlib src/utils.cpp src/threading.cpp src/tcpserver_unix.cpp src/request.cpp src/response.cpp src/potion.cpp

g++ utils.o threading.o tcpserver_unix.o response.o request.o potion.o -shared -o bin/libpotion_arm64.so

rm potion.o
rm tcpserver_unix.o
rm utils.o
rm request.o
rm response.o
rm threading.o
