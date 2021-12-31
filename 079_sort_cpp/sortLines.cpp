#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

//read from cin
template<typename T>
void readLines(std::vector<std::string> & v, T & s) {
  std::string line;
  while (getline(s, line)) {
    v.push_back(line);
  }
}

//printLines
void printLines(const std::vector<std::string> v) {
  std::vector<std::string>::const_iterator it;
  for (it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << "\n";
  }
}

int main(int argc, char const ** argv)
{
  //vector of strings
  std::vector<std::string> lines;
  if (argc == 1) {
    //read from cin
    readLines<std::istream>(lines, std::cin);
    std::sort (lines.begin(), lines.end());
    printLines(lines);
  }
  else{
    std::ifstream f;
    for (int i = 1; i < argc; i++) {
      f.open(argv[i]);
      if (f.good()) {
        readLines<std::ifstream>(lines, f);
        std::sort (lines.begin(), lines.end());
        printLines(lines);
	lines.clear();
        f.close();
      }
      else{
        std::cerr << "Cannot open file: " << argv[i];
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
