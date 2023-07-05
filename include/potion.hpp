#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <map>


#include "tcpserver_unix.hpp"
#include "response.hpp"
#include "request.hpp"



class PotionApp {
  
  using route_handler_func_t = route_struct_t (PotionApp* app, Request* request, Response* response);
  using config_t = std::variant<std::string, int>;
  
  private:

    
    std::map<std::string, std::map<std::string, route_handler_func_t*> > route_map;
    TCPServer server; 
    
    void close_request(receive_struct_t receiveStruct, route_struct_t routeStruct, int socket);
  public:

    std::map<std::string, config_t> config = {

      {"STATIC_FOLDER", "/static"},
      {"READ_TIMEOUT", 60},
      {"READ_SIZE", 1}, //In kilobytes
      {"READ_SIZE_MAX", 1} //In kilobytes



    };
    
    PotionApp(int port);

    void run();
    void print_num(int num);
    void handle_connection(int socket);

    inline void set_get(std::string route, route_handler_func_t* func) {route_map[route]["GET"] = func;}
    inline void set_head(std::string route, route_handler_func_t* func) {route_map[route]["HEAD"] = func;}
    inline void set_post(std::string route, route_handler_func_t* func) {route_map[route]["POST"] = func;}
    inline void set_put(std::string route, route_handler_func_t* func) {route_map[route]["PUT"] = func;}
    inline void set_delete(std::string route, route_handler_func_t* func) {route_map[route]["DELETE"] = func;}
    inline void set_connect(std::string route, route_handler_func_t* func) {route_map[route]["CONNECT"] = func;}
    inline void set_options(std::string route, route_handler_func_t* func) {route_map[route]["OPTIONS"] = func;}
    inline void set_trace(std::string route, route_handler_func_t* func) {route_map[route]["TRACE"] = func;}
    inline void set_patch(std::string route, route_handler_func_t* func) {route_map[route]["PATCH"] = func;}


  
};




using request_handler_func_t =  void (PotionApp::*) ();


template <class T>
class BlockingQueue {
  private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;

  public:
    
  void push (T value);
  T pop();

};



class ThreadPool {
  
  private:
    std::vector<std::thread> threads;
    BlockingQueue<int> b_queue;


  public:

    void start_threads(int num_threads, PotionApp* app);
    void worker(PotionApp* app);
    void add_job(int socket);



};

#endif
