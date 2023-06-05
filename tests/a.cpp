
#include "p.h"

void handler(int num, Potion* app) {
  
  app->print("hello");
  std::cout << num << std::endl;

}

int main () {
  
  Potion app;
  app.run();
  app.execute(&handler);
  return 0;

}
