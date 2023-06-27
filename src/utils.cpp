#include <iostream>

#include "../includes/utils.hpp"

void error(std::string msg) {
  throw std::runtime_error(msg);
}

int last_index_of(std::string str, char character) {
  for (int i = str.length()-1; i > -1; i--) {
    if (str[i] == character) {
      return i;
    }
  }
  return -1;
}



bool is_accessory_file_request(std::string route) {

  int extension_pos = last_index_of(route, '.');
  if (extension_pos < 0 || extension_pos == route.length()) {
    return false;
  }
  return true;
}


void string_to_char(std::string str, char* buffer) {
   
  str.copy(buffer, str.length());
}
