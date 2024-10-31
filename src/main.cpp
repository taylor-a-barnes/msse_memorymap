#include<iostream>
#include <stdint.h>

int reference_var;

int main(int argc, char *argv[]) {

  std::intptr_t reference_var_address = reinterpret_cast<std::intptr_t>(&reference_var);
  std::intptr_t main_address = reinterpret_cast<std::intptr_t>(main);
  std::cout << "Relative location of main: " << main_address - reference_var_address << std::endl;

}