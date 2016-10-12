#include <fstream>
#include <iostream>

int main()
{
  std::ifstream file;
  char current;
  file.open("map.dat");
  while (!file.eof())
    {
      file.get(current);
      std::cout << current;
    }
  return 0;
}
