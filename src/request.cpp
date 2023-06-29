#include <map>
#include <iostream>
#include <bitset>
#include <algorithm>


#include "../includes/tcpserver_unix.hpp"
#include "../includes/request.hpp"
#include "../includes/utils.hpp"
#include <curl/curl.h>


void Request::parse_headers() {

  std::string line = "";
  std::vector<std::string> lines;
  std::string request_body = "";


  char character;
  std::string first_word = "";
  
  //makes sure that the first word of the request is indeed a valid method

  int to;
  if (receiveStruct.bytes_read < 7) {
    to = receiveStruct.bytes_read;
  } 
  else {
    to = 8;
  }
  for (int i = 0; i < to; i++) {
    first_word += static_cast<char>((*receiveStruct.buffer)[i]);
  }
  int fi = first_index_of(first_word, ' ');
  if (fi < 0) {
    return;
  }
  first_word = first_word.substr(0, fi+1);
  if (!valid_method(first_word)) {
    return;
  }
  
  if (receiveStruct. bytes_read <= fi) { //if the request is just a word and a space it returns nothing
    return;
  }

  if (static_cast<char>((*receiveStruct.buffer)[fi+1]) != '/') { //returns if slash does not immedietely follow the space
    return;
  }

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
      break;
    }

  }
  
  std::string word = "";
  std::string key = "";
  std::string word2 = "";
  for (int i = 1; i < lines.size(); i++) {
    if (line == "\r\n") {
      return;
    }
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
        
      }
    }

  
  }
  //here we get the query params 
  //need to support url encoding at some point. added to todo
  parse_q_params();

}


void Request::parse_q_params () {
  std::string route = header_map["route"];
  int fi = first_index_of(route, '?');
  if (fi < 0 || fi == route.length()) {
    return;
  }
  std::string key = "";
  std::string word = "";
  for (int i = fi+1; i < route.length(); i++) {
    if (route[i] == '=' && word != "") {
      key = word;
      word = "";
      continue;
    }
    if (route[i] == '&' && word != "" && key != "") {
      q_params[key] = word;
      key = "";
      word = "";
      continue;
    }
    word += route[i];
  }

  if (key != "" && word != "") {
      q_params[key] = word;
  }
  header_map["route"] = route.substr(0, fi);

}

std::string Request::get_header_value(std::string key) {
  if (!header_map.count(key)) {
    return "";
  }
  return header_map[key];
}

std::string Request::get_method () { //returns first word of request
  return header_map["method"];
}

std::string Request::get_route () {
  return header_map["route"];
}




