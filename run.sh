rm a.out
g++ -std=c++20 -I../lib/boostlib app.cpp src/potion.cpp src/request.cpp src/response.cpp src/tcpserver_unix.cpp src/threading.cpp src/utils.cpp
./a.out
