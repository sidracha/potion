#include "includes/potion.hpp"

void handle_get_home(PotionApp* app, int num) {
  std::cout << "welcome home!\n";
}

void handle_get_notebooks(PotionApp* app, int num) {
  std::cout << "welcome to notebooks!\n";
}


int main () {
  
  PotionApp app(8080);
  
  app.set_get("/", &handle_get_home);
    app.set_get("/", &handle_get_notebooks);

  app.run();
  

  return 0;
}
