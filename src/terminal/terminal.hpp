#ifndef SRC_TERMINAL_TERMINAL_HPP_
#define SRC_TERMINAL_TERMINAL_HPP_

#include <map>
#include <string>
#include <vector>
using std::string;

namespace my_terminal {
struct OptionKeywords {
  static const char *COMMAND_NAME;
};
std::map<string, string> ParseOptions(int argc, char *argv[]);
void PrintToShell(string str);
const string InputMessage();
namespace decoration {
struct ShellColorCode {
  static const int BLACK;
  static const int RED;
  static const int GREEN;
  static const int YELLOW;
  static const int BLUE;
  static const int MAGENTA;
  static const int CYAN;
  static const int WHITE;
};
string AddColorToString(string str, int color, bool is_bg = false);
string CreateStrTable(std::vector<std::vector<string>> table_str);
size_t GetStrLen(string str);
}  // namespace decoration
}  // namespace my_terminal

#endif  // SRC_TERMINAL_TERMINAL_HPP_
