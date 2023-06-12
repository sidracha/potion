#include <vector>
#include <iostream>
#include <cstddef>
#include <bitset>

int main () {
  
  char str[6] = "hello";

  char *ptr = str + 4;
    
  std::cout << &str << std::endl;
  std::cout << ptr << std::endl;

  return 0;

} 
