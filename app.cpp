#include <filesystem>


#include "includes/potion.hpp"
#include "fl.hpp"

namespace fs = std::filesystem;

route_struct_t handle_get_home(PotionApp* app, Request* request, Response* response) {
  
  //return response->render("home.html");
  return response->serve_static_file("home.html");
}

route_struct_t handle_get_string(PotionApp* app, Request* request, Response* response) {
  return response->send_string("<h1>Hello, World!<h1>");
}

route_struct_t handle_get_img(PotionApp* app, Request* request, Response* response) {
  
  return response->send_file("catimg.jpeg", "image/jpeg");

} 

route_struct_t handle_get_video(PotionApp*app, Request* request, Response* response) {
  return response->send_file("crashothy.mp4", "video/mp4");
}


int main () {
  
  PotionApp app(8080);

  app.config["READ_TIMEOUT"] = 60;
  app.config["STATIC_FOLDER"] = "tests/static";

  app.set_get("/", &handle_get_home);
  app.set_get("/string", &handle_get_string);
  app.set_get("/image", &handle_get_img);
  app.set_get("/video", &handle_get_video);

  make_routes(&app);

  app.run();
  

  return 0;
}
