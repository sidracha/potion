#ifndef THREADING_H_INCLUDED
#define THREADING_H_INCLUDED

#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <thread>

#include "tcpserver_unix.hpp"
#include "routes.hpp"

//typedef void request_handler_function_t(int, TCPServer);

//using request_handler_func_t = void (RoutingContainer::*)(int, TCPServer*);

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

    void start_threads(int num_threads, RoutingContainer* container, TCPServer* server);
    void worker(RoutingContainer* container, TCPServer* server);
    void add_job(int socket);
};


#endif
