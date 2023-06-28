#include <iostream>
#include <map>
#include <filesystem>

#include "../includes/utils.hpp"

namespace fs = std::filesystem;

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

int first_index_of(std::string str, char character) {
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == character) {
      return i;
    }
  }
  return -1;
}

bool valid_method(std::string method) {
  
  return true;  

}

std::string get_file_extension(std::string name) {
  int lof = last_index_of(name, '.');
  std::string extension = name.substr(lof, name.length()-lof);
  return extension;
}

std::string extension_to_content_type(std::string extension) {
  
  std::map<std::string, std::string> m = {
    
    {"js", "text/javascript"},
    {"css", "text/css"},
    {"html", "text/html"}

  };
  return m[extension];

}

bool file_exists(fs::path path) { //from the current working directory *where compiled from*
  return fs::exists(path);
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

