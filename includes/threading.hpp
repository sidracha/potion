#ifndef THREADING_H_INCLUDED
#define THREADING_H_INCLUDED

#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <thread>

#include "tcpserver_unix.hpp"
#include "potion.hpp"

//typedef void request_handler_function_t(int, TCPServer);


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

    void start_threads(int num_threads, PotionApp* app, TCPServer* server);
    void worker(PotionApp* app, TCPServer* server);
    void add_job(int socket);
};


#endif
