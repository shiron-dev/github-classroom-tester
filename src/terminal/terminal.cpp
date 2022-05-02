#include "terminal/terminal.hpp"

#include <iostream>

const char *my_terminal::OptionKeywords::COMMAND_NAME = "command";
const char *my_terminal::OptionKeywords::TESTDATA_FILE_NAME = "testdata";
const char *my_terminal::OptionKeywords::TARGET_TEST_NAME = "test";

std::map<string, string> my_terminal::ParseOptions(int argc, char *argv[]) {
  std::map<string, string> options;

  if (argc == 0) {
    return options;
  }

  options[OptionKeywords::COMMAND_NAME] = argv[0];

  for (int i = 1; i < argc; i++) {
    string str = string(argv[i]);
    if (str.substr(0, 2) == "--") {
      size_t eq_index = str.find_first_of('=');
      if (eq_index != string::npos) {
        options[str.substr(2, eq_index - 2)] = str.substr(eq_index + 1);
      } else {
        options[str.substr(2)] = "true";
      }
    } else {
      options[OptionKeywords::TESTDATA_FILE_NAME] = str;
    }
  }

  return options;
}

void my_terminal::PrintToShell(string str) { std::cout << str; }

const string my_terminal::InputMessage() {
  string str;
  std::getline(std::cin, str);
  return str;
}
