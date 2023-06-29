#include <filesystem>

namespace fs = std::filesystem;

int last_index_of(std::string str, char character);
int first_index_of(std::string str, char character);
bool is_accessory_file_request(std::string route);
void string_to_char(std::string str, char* buffer);
bool valid_method(std::string method);
bool file_exists(fs::path path);
std::string get_file_extension(std::string name);
std::string extension_to_content_type(std::string extension);

std::string urldecode(std::string str);

void error(std::string msg);

