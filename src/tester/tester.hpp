#ifndef SRC_TESTER_TESTER_HPP_
#define SRC_TESTER_TESTER_HPP_

#include <map>
#include <string>
using std::string;

namespace my_tester {
namespace io {
struct DefaultConfig {
  static const char *COMPILERS[];
  static const int COMPILERS_SIZE;
  static const char *CHECK_COMMAND;
  static const char *COMPILE_OUT_FILE;
  static const char *PRINT_COMMAND;
};
int RunByShell(string cmd, string *std_out, int *status_code);
bool CheckHasCommand(string cmd);
string CompileCppFile(string file, string compiler = "", string option = "");
string RunFile(string file, string input = "");
int FileOpen(string file, string *file_out);
}  // namespace io
}  // namespace my_tester

#endif  // SRC_TESTER_TESTER_HPP_
