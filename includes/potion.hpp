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
  
  private:
    
    std::map<std::string, std::map<std::string, route_handler_func_t*> > route_map;
    TCPServer server; 
    
    void close_request(receive_struct_t receiveStruct, route_struct_t routeStruct, int socket);
  public:
    
    PotionApp(int port);

    void run();
    void print_num(int num);
    void handle_request(int socket);

    void set_get(std::string route, route_handler_func_t* func) {route_map[route]["GET"] = func;} 

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
