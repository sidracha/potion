#include "includes/potion.hpp"

route_struct_t handle_get_home(PotionApp* app, int num) {
  
  return render("index.html");

}

route_struct_t handle_get_string(PotionApp* app, int num) {
  return send_string("<h1>Hello, World!<h1>");
}


int main () {
  
  PotionApp app(8080);
  
  app.set_get("/", &handle_get_home);
  app.set_get("/string", &handle_get_string);

  app.run();
  

  return 0;
}
