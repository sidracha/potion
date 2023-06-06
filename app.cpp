#include "includes/potion.hpp"

void handle_get(PotionApp* app, int num) {
  app->print_num(num);
}

int main () {
  
  PotionApp app(8080);
  
  app.set_get("/", &handle_get);

  app.run();
  

  return 0;
}
