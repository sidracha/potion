rm a.out

g++ -std=c++20 -I../lib/boost/boost_1_79_0 app.cpp src/utils.cpp src/threading.cpp src/tcpserver_unix.cpp src/potion.cpp src/request.cpp src/response.cpp
./a.out
