#ifndef RESPONSE_H_INCLUDED
#define RESPONSE_H_INCLUDED

#include <string>

class PotionApp;

typedef struct route_struct_t {
  char* buffer;
  size_t buffer_size;
} route_struct_t;

route_struct_t send_string(PotionApp* app, std::string str);
route_struct_t render(PotionApp* app, std::string file_path);
route_struct_t send_status_code(PotionApp* app, uint16_t status_code);

route_struct_t send_js_file(PotionApp* app, std::string file_path);

#endif
