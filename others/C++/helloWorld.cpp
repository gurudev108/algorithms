#include <string>
#include <iostream>

int main()
{
  std::cout<<"Hello world"<<std::endl;

  std::string input;

  std::getline(std::cin, input);

  std::cout<<input<<std::endl;

  return 0;
}
