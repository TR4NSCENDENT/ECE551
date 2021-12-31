#include "cyoa.hpp"

//error handling function
void err(const char * msg) {
  std::cerr << msg;
  exit(EXIT_FAILURE);
}

void checkName(const char * filename) {
  std::string s(filename); //"page(number).txt"
  size_t found = s.rfind('/');
  if (found != std::string::npos) {
    s = s.substr(found + 1);
  }
  found = s.find("page");
  if (found == 0) {
    if (s.find(".txt") == s.size() - 4) {
      return;
    }
  }
  err("Incorrect file name!\n");
}

//read from the file
Page::Page(const char * filename) : pageState(0) { 
  try {
    checkName(filename); //check the format of filename
    read(filename);
  }
  catch(const std::bad_alloc & a) {
    err("Not enough memory!\n");
  }
  catch(const std::exception & e) {
    std::cerr << e.what() << '\n';
    exit(EXIT_FAILURE);
  }
}

//This function prints the whole page
void Page::printAll() {
  std::vector<std::string>::iterator it;
  if (story.empty()) { std::cout << std::endl; }
  for (it = story.begin(); it != story.end(); ++it) {
    std::cout << *it << std::endl;
  }
  if (pageState != 0) { //if this page has an ending (WIN or LOSE)
    if (navigation.size() != 1) {
      err("Invalid choices!\n"); //error if more than 1 choice
    }
    std::cout << navigation[0].second << std::endl;
  }
  else { 
    std::cout << "What would you like to do?" << std::endl;
    std::cout << std::endl;
    for (size_t i = 0; i < navigation.size(); i++) {
      std::cout << " " << i+1 << ". ";
      std::cout << navigation[i].second << std::endl;
    }
  }
}

//this function extract the first valid integer from str without overflow for uint32
unsigned long getNumHelper(const std::string & str) {
  std::stringstream ss(str);
  unsigned long test = 0;
  ss >> test;
  if (str.size() > 10 || test > __UINT32_MAX__) { //if overflow (10 digits for 4294967295)
    err("Page number is too large!\n"); 
  }
  return test;
}

//convert string to number
unsigned getNum(const std::string & str) {
  if (str.empty()) { err("Missing page number!\n"); }
  std::string::const_iterator it;
  for (it = str.begin(); it != str.end(); ++it) {
    if (!std::isdigit(*it)) { //check invalid char
      err("Invalid Page NUmber!\n");
    }
  }
  unsigned ans = getNumHelper(str); //extract as unsigned 
  return ans;
}

//read all choices
void Page::getChoice(const std::string & line) {
  choice ch;
  ch.first = 0;
  if (line == "WIN") {
    ch.second = "Congratulations! You have won. Hooray!";
    pageState = 1;
  }
  else if (line == "LOSE") {
    ch.second = "Sorry, you have lost. Better luck next time!";
    pageState = -1;
  }
  else { //begin parsing
    size_t found = line.find(":");
    if(found == std::string::npos) { //if there's no ":"
      err("This line does not have a semicolon!\n");
    }
    ch.first = getNum(line.substr(0, found));
    ch.second = line.substr(found + 1);
  }
  navigation.push_back(ch);
}

void Page::read(const char * filename) {
  std::ifstream f;
  f.open(filename);
  if (!f.is_open()) {
    err("Unable to open the file!\n");
  }
  std::string line;
  bool isStory = false; //switch between parse and simply read
  while (f.good()) {
    std::getline(f, line);
    if (line[0] == '#') { 
      isStory = true; 
      continue; //ignore this line
    }
    if (isStory) { 
      story.push_back(line);
      continue;
    }
    getChoice(line);
  }
  f.clear();
  f.close();
  if (f.fail()) {
    err("Unable to close the file!\n");
  }
}

std::vector<unsigned> Page::next() { //possible next steps
  std::vector<unsigned> ans;
  if (pageState != 0) { return ans; }
  std::vector<choice>::iterator it;
  for (it = navigation.begin(); it != navigation.end(); ++it) {
    ans.push_back(it->first);
  }
  return ans;
} 

int Page::getState() { 
  return pageState;
} 

