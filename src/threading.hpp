#ifndef THREADING_H_INCLUDED
#define THREADING_H_INCLUDED

#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <thread>

#include "tcpserver_unix.hpp"

typedef void request_handler_function_t(int, TCPServer server);


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

    void startThreads(int num_threads, request_handler_function_t* requestHandler, TCPServer server);
    void worker(request_handler_function_t* requestHandler, TCPServer server);
    void addJob(int socket);
};


#endif
