#include "includes/potion.hpp"
#include "fl.hpp"

int handle_get(int num) {
  std::cout << "GET\n";
  //std::cout << num << std::endl;
  return 0;
}

int handle_post(int num) {
  std::cout << "POST\n";
  //std::cout << num << std::endl;
  return 0;
} 


int main () {
  
  Potion* app;
  app = new Potion;
  
  

  app->set_get("/", &handle_get);
  app->set_post("/", &handle_post);
  

  app->run();
  
  delete app;

  return 0;
}
