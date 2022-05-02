#include <iostream>
using std::string;

#include "terminal/terminal.hpp"
#include "tester/tester.hpp"

int main(int argc, char *argv[]) {
  // Main method
  std::map<string, string> options = my_terminal::ParseOptions(argc, argv);
  my_tester::RunTests(options);
  /*
  for (auto itr = options.begin(); itr != options.end(); ++itr) {
    std::cout << "key = " << itr->first              // キーを表示
              << ", val = " << itr->second << "\n";  // 値を表示
  }*/
}
