#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <iostream>

#include "potion.hpp"
#include "tcpserver_unix.hpp"
#include "threading.hpp"


class Potion {
  
  private:
    std::vector<std::string> vect;
    RoutingContainer rContainer;

  public:
    
    void run();
    void add(std::string str) {vect.push_back(str);}
    void print_vect () {
      for (unsigned long i = 0; i < vect.size(); i++) {
        std::cout << vect[i] << std::endl;
      }
    }
    void set_get(std::string route, route_handler_func_t* func) {rContainer.set_route(route, func, "GET");}
    void set_head(std::string route, route_handler_func_t* func) {rContainer.set_route(route, func, "HEAD");}
    
    void set_post(std::string route, route_handler_func_t* func) {rContainer.set_route(route, func, "POST");}
    
    void set_put(std::string route, route_handler_func_t* func) {rContainer.set_route(route, func, "PUT");}
    void set_delete(std::string route, route_handler_func_t* func) {rContainer.set_route(route, func, "DELETE");}
    void set_connect(std::string route, route_handler_func_t* func) {rContainer.set_route(route, func, "CONNECT");}
    void set_options(std::string route, route_handler_func_t* func) {rContainer.set_route(route, func, "OPTIONS");}
    void set_trace(std::string route, route_handler_func_t* func) {rContainer.set_route(route, func, "TRACE");}
    void set_patch(std::string route, route_handler_func_t* func) {rContainer.set_route(route, func, "PATCH");}
};

#endif
