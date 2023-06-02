#include "includes/test.hpp"
#include "fl.hpp"

int main () {
  
  Potion* app;
  app = new Potion;
  
  app->add("first");
  make_routes(app);
  app->print_vect(); 

  app->run();
  
  delete app;

  return 0;
}
