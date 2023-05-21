#ifndef THREADING_H_INCLUDED
#define THREADING_H_INCLUDED

typedef void request_handler_function_t(int);


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

    void startThreads(int num_threads, request_handler_function_t* requestHandler);
    void worker(request_handler_function_t* requestHandler);

};


#endif
