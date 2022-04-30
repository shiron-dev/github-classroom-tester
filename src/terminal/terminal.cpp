#include "terminal/terminal.hpp"

const char *my_terminal::OptionKeywords::COMMAND_NAME = "command";

std::map<string, string> my_terminal::ParseOptions(int argc, char *argv[]) {
  return std::map<string, string>();
}

void my_terminal::PrintToShell(char *str) {
  //
}

const char *my_terminal::InputMessage() {
  //
  return (string("")).c_str();
}
