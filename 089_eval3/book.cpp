#include "book.hpp"

//test if a file exist
bool exist(const char * filename) {
  std::ifstream f (filename);
  if (f.is_open()) {
    return f.good();
  }
  return false;
}

//this function read all pages in dir
void Book::getPage(const char * dir, const unsigned pageNum) {
  std::stringstream ss;
  ss << dir << "/page" << pageNum << ".txt"; //build up the file name
  std::string filename = ss.str();
  if (!exist(filename.c_str())) { //base case
    if (pageNum == 1) { err("Missing page1.txt!\n"); }
    return;  //we finished reading pages
  }
  Page * newPage = new Page(filename.c_str());
  if (newPage == NULL) { err("Unable to allocate!\n"); }
  pages.push_back(newPage);
  getPage(dir, pageNum + 1); //tail recursion to next page
}

//constructor of Book using getPage
Book::Book(const char * dir) {
  try {
    getPage(dir, 1);
  }
  catch(const std::exception & e) {
    std::cerr << e.what() << '\n';
    exit(EXIT_FAILURE);
  }
}

//will return the state of this page
int Book::showPage(unsigned pageNum) {
  if (pageNum < 0 || pageNum >= pages.size()) {
    err("Invalid page number!\n");
  }
  pages[pageNum]->printAll();
  return pages[pageNum]->getState(); 
}

//run check on the whole book
void Book::checkBook() {
  std::set<unsigned> verified;
  unsigned winCount = 0;
  unsigned loseCount = 0;
  std::vector<unsigned> nextPages;
  std::vector<Page *>::iterator it_p;
  std::vector<unsigned>::iterator it_n;
  for (it_p = pages.begin(); it_p != pages.end(); ++it_p) {
    nextPages = (*it_p)->next(); //first check the reference
    for (it_n = nextPages.begin(); it_n != nextPages.end(); ++it_n) {
      if (verified.count(*it_n) != 0) { continue; } //if already verified
      if (*it_n > pages.size() || *it_n < 1) {  //if a invalid reference
        err("Invalid page reference!\n"); 
      }
      verified.insert(*it_n);
    }
    if ((*it_p)->getState() == 1) { winCount++; }
    else if ((*it_p)->getState() == -1) { loseCount++; }
  }
  verified.insert(1); //add page 1 if it is not referenced
  if (verified.size() != pages.size()) { err("At least one page is not referenced!\n"); }
  if (winCount == 0 || loseCount == 0) { err("Missing WIN or LOSE page!\n"); }
}

std::vector<unsigned> Book::getNext(unsigned pageNum) { 
  return pages[pageNum]->next(); 
}

//check if there's non digit in a string
bool validString(const std::string str) {
  if (str.empty()) { return false; }
  std::string::const_iterator it;
  for (it = str.begin(); it != str.end(); ++it) {
    if (!isdigit(*it)) { return false; }
  }
  return true;
}

//step 2 running function
void run_story(Book & b, unsigned pageNum) {
  int state = b.showPage(pageNum);
  if (state != 0) { return; } //base case
  if (!std::cin.good()) { err("You haven't finished the story!\n"); }
  std::vector<unsigned> nextPages = b.getNext(pageNum);
  std::string curr;
  unsigned chosen = 0;
  while (std::getline(std::cin, curr)) {
    if (!validString(curr)) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
      continue;
    }
    chosen = getNumHelper(curr);
    if (chosen < 1 || chosen > nextPages.size() || !isdigit(curr[0])) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
      continue;
    }
    break;
  }
  run_story(b, nextPages[chosen - 1] - 1); 
}
