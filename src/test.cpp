#include <iostream>

#include "potion.h"

int add (int a) {
  return a * 2;
}

int main () {
  PotionApp app;

  app.set_route("/", &add);
  int result = app.execute_function("/");

  std::cout << result << std::endl;
  return 0;
}
