#ifndef POTION_H_INCLUDED
#define POTION_H_INCLUDED

#include <map>
#include <iostream>
#include <cstdlib>

#include "tcpserver_unix.hpp"

typedef int route_handler_func_t(int);  

class PotionApp {
  private:
    std::map<std::string, route_handler_func_t*> function_map; 
  public:
    void set_route (std::string route, route_handler_func_t* func);
    int execute_function(std::string route);
    void run();

};

#endif
