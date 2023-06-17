#include "includes/potion.hpp"

route_struct_t handle_file(PotionApp* app, int num) {
  
  return render(app, "file.html");
}

void make_routes(PotionApp* app) {
  
  app->set_get("/file", &handle_file);
  
}
