#ifndef SRC_TERMINAL_TERMINAL_HPP_
#define SRC_TERMINAL_TERMINAL_HPP_

#include <map>
#include <string>
using std::string;

namespace my_terminal {
struct OptionKeywords {
  static const char *COMMAND_NAME;
};
std::map<string, string> ParseOptions(int argc, char *argv[]);
void PrintToShell(char *str);
const char *InputMessage();
}  // namespace my_terminal

#endif  // SRC_TERMINAL_TERMINAL_HPP_
