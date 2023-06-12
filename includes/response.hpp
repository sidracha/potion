#ifndef RESPONSE_H_INCLUDED
#define RESPONSE_H_INCLUDED

#include <string>

class Response {
  private:

  public:
    char* send_string(std::string str);
    char* render(std::string file_path);

};

#endif
