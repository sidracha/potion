
#include <map>
#include <iostream>
#include <cstdlib>

#include "tcpserver.h"

typedef int route_handler_func_t(int x);  

class PotionApp {
  private:
    std::map<std::string, route_handler_func_t*> function_map; 
  public:
    void set_route (std::string route, route_handler_func_t* func) {
      function_map[route] = func;
    }
    
    int execute_function(std::string route) {
      auto func = function_map[route];
      int result = func(5);
      return result;
    }

    void run() {

    }

};

