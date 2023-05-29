#ifndef POTION_H_INCLUDED
#define POTION_H_INCLUDED

#include <map>
#include <iostream>
#include <cstdlib>

#include "tcpserver_unix.hpp"

//typedef int route_handler_func_t(int);
//typedef void route_func_t(std::string, route_handler_func_t*);
//typedef std::map<std::string, route_handler_func_t*> function_map_to;

using route_handler_func_t = int (int);
using route_set_func_t = void (std::string, route_handler_func_t*);
using function_map_t = std::map<std::string, route_handler_func_t*>;
using get_route_handler_func_struct_t = struct {
  route_handler_func_t* func;
  bool is_valid_method;
}

class PotionApp {
  public:
    function_map_t get_map;
    function_map_t head_map;
    function_map_t post_map;
    function_map_t put_map;
    function_map_t delete_map;
    function_map_t connect_map;
    function_map_t options_map;
    function_map_t trace_map;
    function_map_t patch_map;

    inline void set_get(std::string route, route_handler_func_t* func) {get_map[route] = func;}
    inline void set_head(std::string route, route_handler_func_t* func) {head_map[route] = func;}
    inline void set_post(std::string route, route_handler_func_t* func) {post_map[route] = func;}
    inline void set_put(std::string route, route_handler_func_t* func) {put_map[route] = func;}
    inline void set_delete(std::string route, route_handler_func_t* func) {delete_map[route] = func;}
    inline void set_connect(std::string route, route_handler_func_t* func) {connect_map[route] = func;}
    inline void set_options(std::string route, route_handler_func_t* func) {options_map[route] = func;}
    inline void set_trace(std::string route, route_handler_func_t* func) {trace_map[route] = func;}
    inline void set_patch(std::string route, route_handler_func_t* func) {patch_map[route] = func;}

    inline route_handler_func_t get_get_struct(std::string route); //need to fill in here figure out what to do
                                                                   //if handlder function does not exist

    //int executeHandler(Request* request);
    void run();

    auto get_handler_func(std::string method);

};

#endif
