#include <iostream>


class Potion {
  using pass_func_t = void (int, Potion* app);
  private:
    void send();

  public:
    void run();
    void handle();
    void execute(pass_func_t* func);
    void print(std::string msg) {
      std::cout << msg << std::endl;
    };


};



using func_t = void (Potion::*) ();

class Threading : public Potion {
  
  public:
    void start_threads(func_t);
};

void Threading::start_threads(func_t func) {
  (this->*func)();
}

void Potion::execute(pass_func_t* func) {
  func(5, this);
}

void Potion::handle () {
  std::cout << "handle\n";

}

void Potion::run() {
  
  Threading thread_pool;

  thread_pool.start_threads(&Potion::handle);

}
