#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <iostream>

#include "potion.hpp"
#include "tcpserver_unix.hpp"
#include "threading.hpp"


class Potion {
  
  private:
    PotionApp p_app;
    std::vector<std::string> vect;

  public:
    
    void run();
    void add(std::string str) {vect.push_back(str);}
    void print_vect () {
      for (unsigned long i = 0; i < vect.size(); i++) {
        std::cout << vect[i] << std::endl;
      }
    }
};

#endif
