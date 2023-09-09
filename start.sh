rm ./a.out
g++ -std=c++20 app.cpp -I../lib/boostlib -L./bin -lpotion_x86_64
LD_LIBRARY_PATH=./bin ./a.out
