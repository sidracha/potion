#include <filesystem>


#include "includes/potion.hpp"
#include "fl.hpp"

namespace fs = std::filesystem;

route_struct_t handle_get_home(PotionApp* app, int num) {
  
  return render(app, "index.html");

}

route_struct_t handle_get_string(PotionApp* app, int num) {
  return send_string(app, "<h1>Hello, World!<h1>");
}

route_struct_t handle_get_img(PotionApp* app, int num) {
  
  return send_file(app, "catimg.jpeg");

} 

route_struct_t handle_get_video(PotionApp*app, int num) {
  std::cout << fs::file_size("testvid.mp4") << std::endl; 
  return send_file(app, "crashothy.mp4");
}


int main () {
  
  PotionApp app(8080);


  app.config("static_folder") = "/hello";
  
  app.set_get("/", &handle_get_home);
  app.set_get("/string", &handle_get_string);
  app.set_get("/img", &handle_get_img);
  app.set_get("/video", &handle_get_video);

  make_routes(&app);

  app.run();
  

  return 0;
}
