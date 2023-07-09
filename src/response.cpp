#include <filesystem>
#include <fstream>
#include <iostream>

#include <boost/json.hpp>
#include <boost/json/src.hpp>


#include "../include/response.hpp"
#include "../include/request.hpp"
#include "../include/utils.hpp"


namespace fs = std::filesystem;
namespace json = boost::json;

Response::Response(Request* r) : request(r) {

}

void Response::set_static_folder(std::string sf) {
  STATIC_FOLDER = sf;
}

void r_test(std::string route) {
  std::cout << last_index_of(route, '.') << std::endl;
  
}

route_struct_t Response::send_string(std::string str) {
  
  
  set_header("Content-Type", "text/plain");
  std::string headers = build_headers(200, true);


  route_struct_t routeStruct;
  char* buffer = new char[str.length() + headers.length()];
  for (size_t i = 0; i < headers.length(); i++) {
    buffer[i] = headers[i];
  }
  for (size_t i = 0; i < str.length(); i++) {
    buffer[i+headers.length()] = str[i];
  }
  
  routeStruct.buffer = buffer;
  routeStruct.buffer_size = str.length() + headers.length();
  return routeStruct;

}


route_struct_t Response::serve_static_file(std::string file_path) {
  
  route_struct_t routeStruct; 
  if (file_path[0] == '/') {
    file_path = file_path.substr(1, file_path.length()-1);
  }
  std::string fp = STATIC_FOLDER + "/" + file_path;
  fs::path path = fp;
  if (!file_exists(fp)) {
    return send_status_code_no_data(404);
  }
  size_t f_size = fs::file_size(path);
  
  set_header("Content-Type", extension_to_content_type(get_file_extension(file_path)));
  set_header("Content-Length", std::to_string(f_size));
  std::string headers = build_headers(200, true);
  
  size_t header_len = headers.length();
  size_t buffer_size = f_size + header_len;
  char* buffer = new char[buffer_size];

  for (size_t i = 0; i < header_len; i++) {
    buffer[i] = headers[i];
  }

  std::ifstream file(path);
  file.read(buffer + header_len, f_size);
  
  routeStruct.buffer = buffer;
  routeStruct.buffer_size = buffer_size;

  return routeStruct;

}

//only supports application/json for now

void Response::populate_headers(char* buffer, size_t buffer_size, std::string headers){
  
  if (buffer_size > headers.length()) {
    return;
  }

  for (size_t i = 0; i < headers.length(); i++) {
    buffer[i] = headers[i];
  }
  

}


route_struct_t Response::create_route_struct(char* buffer, size_t buffer_size) {
  route_struct_t rs;
  rs.buffer = buffer;
  rs.buffer_size = buffer_size;
  return rs;
}

route_struct_t Response::send_json(json::object obj) {
  

  std::string s = json::serialize(obj);
  set_header("Content-Type", "application/json");
  set_header("Content-Length", std::to_string(s.length()));
  std::string headers = build_headers(200, true);
  
  size_t buffer_size = s.length() + headers.length();
  char* buffer = new char[buffer_size];
  
  for (size_t i = 0; i < headers.length(); i++) {
    buffer[i] = headers[i];
  }
  
  for (size_t i = 0; i < s.length(); i++) {
    buffer[i+headers.length()] = s[i];
  }
  

  std::vector vect = value_to<std::vector<int>>(obj["list"]);
  return create_route_struct(buffer, buffer_size);

}

std::string Response::build_status_code_header(int status_code) {
  if (code_to_phrase(status_code) == "") {
    return "";
  }
  return "HTTP/1.1 " + std::to_string(status_code) + " " + code_to_phrase(status_code);
}

route_struct_t Response::send_status_code_no_data(int status_code) {
  if (code_to_phrase(status_code) == "") {
    return send_status_code_no_data(500);
  } 


  std::string resp = build_status_code_header(status_code);
  char* buffer = new char[resp.length()];
  string_to_char(resp, buffer);
  route_struct_t routeStruct;
  routeStruct.buffer = buffer;
  routeStruct.buffer_size = resp.length();
  return routeStruct;

}

route_struct_t Response::send_status_code(int status_code, json::object obj) {
  
  if (code_to_phrase(status_code) == "") {
    return send_status_code_no_data(500);
  }
  
  //fix this shit very bad
  std::string s = json::serialize(obj);
  route_struct_t routeStruct;
  
  if (s == "{}") {
    std::string to_send = "HTTP/1.1 " + std::to_string(status_code) + " " + code_to_phrase(status_code) + "\r\n";  
    char* buffer = new char[to_send.length()];
    string_to_char(to_send, buffer);
    routeStruct.buffer = buffer;
    routeStruct.buffer_size = to_send.length();
    return routeStruct;
  }

  set_header("Content-Type", "application/json");
  set_header("Content-Length", std::to_string(s.length()));
  std::string headers = build_headers(status_code, true);
  size_t header_len = headers.length();
  size_t buffer_size = header_len + s.length();
  char* buffer = new char[buffer_size];
  for(size_t i = 0; i < header_len; i++) {
    buffer[i] = headers[i];
  }
  for (size_t i = 0; i < s.length(); i++) {
    buffer[i+header_len] = s[i];
  }
  routeStruct.buffer = buffer;
  routeStruct.buffer_size = buffer_size;
  return routeStruct;

}



typedef struct {
  size_t start_byte;
  size_t end_byte;
} byte_range_struct_t;




static byte_range_struct_t get_byte_range(std::string content_range_str, size_t file_size) {
  size_t start_byte = 0;
  size_t end_byte = file_size - 1;
  byte_range_struct_t byr;
  byr.start_byte = start_byte;
  byr.end_byte = end_byte;

  if (content_range_str == "") {
    return byr;
  }
  std::string byte_str = "";
  int j = 0;
  int index = first_index_of(content_range_str, '=') + 1; 
  for (int i = index; i < content_range_str.length(); i++) {
    if (content_range_str[i] == '-') {
      j = i;
      break;
    }
    byte_str += content_range_str[i];
    j = i;
  }
  try {
    
    start_byte = std::stoi(byte_str);
    byr.start_byte = start_byte; 

  } catch (const std::exception& e) {
    return byr;
  }
  if (j >= content_range_str.length()) {
    return byr;
  }
  byte_str = "";
  for (int i = j; i < content_range_str.length(); i++) {
    byte_str += content_range_str[i];
  }
  try {
    end_byte = std::stoi(byte_str);
    if (end_byte >= file_size) {
      return byr;
    }
    byr.end_byte = end_byte;
  
  } catch (const std::exception& e) {
    return byr;
  }
  
  return byr;

}

route_struct_t Response::send_file(std::string file_path, std::string content_type) {
  

  //something fucky is going on here -> broken pipe when running on mac so I just took the error out of the sockets layer

  fs::path path = file_path;
  fs::path p = fs::current_path() / path;
  size_t f_size = fs::file_size(p);
 
  
  std::string range_val = request->get_header_value("Range");

  byte_range_struct_t byr = get_byte_range(range_val, f_size);
  
  std::ifstream file(p);
  file.seekg(byr.start_byte);

  size_t to_be_read_size = byr.end_byte - byr.start_byte + 1;

  set_header("Content-Type", content_type);
  set_header("Content-Length", std::to_string(to_be_read_size));
  set_header("Accept-Ranges", "bytes");
  
  std::string headers = "";

  if (range_val != "") {
    set_header("Content-Range", "bytes " + std::to_string(byr.start_byte) + "-" + std::to_string(byr.end_byte) + "/" + std::to_string(byr.end_byte+1));
    headers = build_headers(206, true);
  }
  else {
    headers = build_headers(200, true); 
  }
  
  
  
  size_t header_len = headers.length();
  size_t buffer_size = header_len + to_be_read_size;

  char* buffer = new char[buffer_size];
  
  for (int i = 0; i < header_len; i++) {
    buffer[i] = headers[i];
  }

  file.read(buffer + header_len, to_be_read_size);
  route_struct_t routeStruct;
  routeStruct.buffer = buffer;
  routeStruct.buffer_size = buffer_size;
  return routeStruct;
    
}

void Response::set_header(std::string key, std::string value) {
  header_vect_struct_t hv;
  hv.key = key;
  hv.value = value;
  headers_vect.push_back(hv);
}

std::string Response::build_headers(int status_code, bool content) {
  std::string phrase = code_to_phrase(status_code);
  if (phrase == "") {
    error("Invalid status code");
  }
  std::string headers_str = "HTTP/1.1 " + std::to_string(status_code) + " " + phrase + "\r\n";
  for (size_t i = 0; i < headers_vect.size(); i++) {
    
    headers_str = headers_str + headers_vect[i].key + ": " + headers_vect[i].value;
    headers_str += "\r\n";

  }
  if (content) {
    headers_str += "\r\n"; 
  }
  return headers_str;
}

std::string Response::code_to_phrase(int code) {
  
  switch (code) {
    
    //####### 1xx - Informational #######
	  case 100: return "Continue";
	  case 101: return "Switching Protocols";
	  case 102: return "Processing";
	  case 103: return "Early Hints";

	  //####### 2xx - Successful #######
	  case 200: return "OK";
	  case 201: return "Created";
	  case 202: return "Accepted";
	  case 203: return "Non-Authoritative Information";
    case 204: return "No Content";
    case 205: return "Reset Content";
    case 206: return "Partial Content";
    case 207: return "Multi-Status";
    case 208: return "Already Reported";
    case 226: return "IM Used";

    //####### 3xx - Redirection #######
    case 300: return "Multiple Choices";
    case 301: return "Moved Permanently";
    case 302: return "Found";
    case 303: return "See Other";
    case 304: return "Not Modified";
    case 305: return "Use Proxy";
    case 307: return "Temporary Redirect";
    case 308: return "Permanent Redirect";

    //####### 4xx - Client Error #######
    case 400: return "Bad Request";
    case 401: return "Unauthorized";
    case 402: return "Payment Required";
    case 403: return "Forbidden";
    case 404: return "Not Found";
    case 405: return "Method Not Allowed";
    case 406: return "Not Acceptable";
    case 407: return "Proxy Authentication Required";
    case 408: return "Request Timeout";
    case 409: return "Conflict";
    case 410: return "Gone";
    case 411: return "Length Required";
    case 412: return "Precondition Failed";
    case 413: return "Content Too Large";
    case 414: return "URI Too Long";
    case 415: return "Unsupported Media Type";
    case 416: return "Range Not Satisfiable";
    case 417: return "Expectation Failed";
    case 418: return "I'm a teapot";
    case 421: return "Misdirected Request";
    case 422: return "Unprocessable Content";
    case 423: return "Locked";
    case 424: return "Failed Dependency";
    case 425: return "Too Early";
    case 426: return "Upgrade Required";
    case 428: return "Precondition Required";
    case 429: return "Too Many Requests";
    case 431: return "Request Header Fields Too Large";
    case 451: return "Unavailable For Legal Reasons";

    //####### 5xx - Server Error #######
    case 500: return "Internal Server Error";
    case 501: return "Not Implemented";
    case 502: return "Bad Gateway";
    case 503: return "Service Unavailable";
    case 504: return "Gateway Timeout";
    case 505: return "HTTP Version Not Supported";
    case 506: return "Variant Also Negotiates";
    case 507: return "Insufficient Storage";
    case 508: return "Loop Detected";
    case 510: return "Not Extended";
    case 511: return "Network Authentication Required";

	  default: return ""; 

	}



}
