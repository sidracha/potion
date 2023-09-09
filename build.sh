g++ -c -fPIC -std=c++20 -I../lib/boostlib src/*.cpp

g++ *.o -shared -o $1

rm *.o
