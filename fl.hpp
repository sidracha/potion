#include "includes/potion.hpp"

route_struct_t handle_file(PotionApp* app, Request* request, Response* response) {
  
  return response->render(app, "file.html");
}

void make_routes(PotionApp* app) {
  
  app->set_get("/file", &handle_file);
  
}
