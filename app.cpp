#include <filesystem>

#include <boost/json/src.hpp>
#include <boost/json.hpp>

#include "includes/potion.hpp"
#include "fl.hpp"

namespace fs = std::filesystem;
namespace json = boost::json;

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

route_struct_t handle_get_hello(PotionApp* app, Request* request, Response* response) {
  std::map<std::string, std::string> args = request->get_args();
  std::cout << args["key1"] << std::endl;
  return response->send_string("Hi!");
}


int main () {


  json::object obj;
  
  std::vector<int> vect = {1, 2, 3};
  json::value value = json::value_from(vect);

  obj["list"] = value;
  json::value v2 = obj["list"];
  
  std::vector<int> arr = value_to<std::vector<int>>(v2);
  std::cout << arr[1] << std::endl;

  //std::cout << v2[2] << std::endl;
  

  return 0;
  
  PotionApp app(8080);

  app.config["READ_TIMEOUT"] = 60;
  app.config["STATIC_FOLDER"] = "tests/static";

  app.set_get("/", &handle_get_home);
  app.set_get("/string", &handle_get_string);
  app.set_get("/image", &handle_get_img);
  app.set_get("/video", &handle_get_video);


  app.set_get("/hello", &handle_get_hello);

  make_routes(&app);

  app.run();
  

  return 0;
}
