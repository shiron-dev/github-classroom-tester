#ifndef SRC_TESTER_TESTER_HPP_
#define SRC_TESTER_TESTER_HPP_

#include <map>
#include <string>
using std::string;

namespace my_tester {
namespace io {
string RunByShell(string command);
void CompileCppFile(string file, string compiler = "", string option = "");
string RunFile(string file, string input = "");
}  // namespace io
}  // namespace my_tester

#endif  // SRC_TESTER_TESTER_HPP_
