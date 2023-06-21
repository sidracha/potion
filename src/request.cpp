#include <map>
#include <iostream>
#include <bitset>
#include <algorithm>


#include "../includes/tcpserver_unix.hpp"
#include "../includes/request.hpp"


/*
void Request::parse_headers() {
  
  std::string method = "";
  std::string request_str = "";
  std::string route = "";
  std::string line_str = "";

  size_t line = 0;
  bool found_method = false;
  bool on_route = false;

  for (size_t i = 0; i < receiveStruct.bytes_read; i++) {
    
    std::byte bt = (*receiveStruct.buffer)[i];
    char character = static_cast<char>(bt);
    request_str += character;
    line_str += character;
    if (on_route) {
      route += character;
    }

    if (character == '\n') {
      line++;
      
      if (line == 0) {
        continue;
      }
      
      std::string key;
      std::string value;
      bool key_found = false;
      std::string word = "";
      for (int j = 0; j < line_str.length(); j++) {
        
        word += line_str[j];
        if (!key_found && line_str[j] == ':') {
          key = word;
          key_found = true;
          continue;
        }
        if (line_str[j] == '\r' && key_found) {
          value = word.substr(1, word.length()-3);
        }

      }
      header_map[key] = value;
      

    }

    if (line == 0 && character == ' ') {
      if (!found_method && method == "") {
        continue;
      }

      
      if (!found_method) {
        header_map["method"] = request_str.substr(0, request_str.length()-1);
        found_method = true;
        on_route = true;
      }
      else {
        on_route = false;
        header_map["route"] = route.substr(0, route.length()-1);
      }
    }

      
      
  }
  bool print_req = true;
  if (print_req) {
    std::cout << request_str << std::endl;
  }

}
*/

void Request::parse_headers() {

  std::string line = "";
  std::vector<std::string> lines;
  std::string request_body = "";


  char character;
  for (size_t i = 0; i < receiveStruct.bytes_read; i++) {
    character = static_cast<char>((*receiveStruct.buffer)[i]);
    request_body += character;
    if (character == '\r') {
      lines.push_back(line);
      line = "";
    }

    if (character == '\n') {
      continue;
    }

    line += character;
    
  }

  char c;
  std::string w = "";
  std::string route = "";
  std::string method = "";
  bool found_method = false;
  bool on_route = false;
  for (int i = 0; i < lines[0].length(); i++) {
    c = lines[0][i];
    w += c;
    if (c == ' ' && !found_method) {
      method = w.substr(0, w.length()-1);
      w = "";
      on_route = true;
      found_method = true;
      continue;
    }

    if (c == ' ' && found_method) {
      route = w.substr(0, w.length()-1);
      header_map["method"] = method;
      header_map["route"] = route;
      //test_struct ts;
      //ts.key = "method";
      //ts.value = method;
      //test_vect.push_back(std::move(ts));
      //test_struct ts2;
      //ts2.key = "route";
      //ts2.value = route;
      //test_vect.push_back(std::move(ts2));
      break;
    }

  }
  
  std::string word = "";
  std::string key = "";
  std::string word2 = "";
  for (int i = 1; i < lines.size(); i++) {
    key = "";
    word = "";
    
    bool key_found = false;

    for (int j = 0; j < lines[i].length(); j++) {

      word += lines[i][j];
      if (lines[i][j] == ':' && !key_found) {
        key = word.substr(1, word.length()-2);
        word = "";
        key_found = true;
        continue;
      } 
      if (j == lines[i].length()-1) {
        if (word == "\r" || word == "\r\n" || word == "\n" || key == "\r" || key == "") {break;}
        word2 = word.substr(1, word.length()-1);
        header_map[key] = word2;
        //std::cout << key << header_map[key] << std::endl;
        //test_struct ts3;
        //ts3.key = key;
        //ts3.value = word2;
        //test_vect.push_back(std::move(ts3));
        
      }
    }

  
  }

  std::cout << request_body << std::endl;

}


std::string Request::get_header_value(std::string key) {
  return header_map[key];
}

std::string Request::get_method () { //returns first word of request
  return header_map["method"];
}

std::string Request::get_route () {
  return header_map["route"];
}

