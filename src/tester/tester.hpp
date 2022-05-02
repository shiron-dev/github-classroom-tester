#ifndef SRC_TESTER_TESTER_HPP_
#define SRC_TESTER_TESTER_HPP_

#include <map>
#include <string>
#include <vector>
using std::string;

namespace my_tester {
enum TestRunType { Compile, Run };
struct TestData {
  string test_name;
  string file_name;
  TestRunType type;
  string input = "";
  string output = "";
};
struct DefaultConfig {
  static const char *TESTDATA_FILE_NAME;
};
bool IsMatchTest(string result, string expected);
std::vector<TestData> GetTestDataByJSON(string json_content);
bool RunTests(std::map<string, string> options);
namespace io {
struct DefaultConfig {
  static const char *COMPILERS[];
  static const int COMPILERS_SIZE;
  static const char *CHECK_COMMAND;
  static const char *COMPILE_OUT_FILE;
  static const char *PRINT_COMMAND;
  static const char *DELETE_COMMAND;
  static const char *INPUT_TEXT_FILE_NAME;
};
bool RunByShell(string cmd, string *std_out, int *status_code);
bool CheckHasCommand(string cmd);
string CompileCppFile(string file, string compiler = "", string option = "");
string RunFile(string file, string input = "");
bool FileOpen(string file, string *file_out);
bool FileWrite(string file, string content);
}  // namespace io
}  // namespace my_tester

#endif  // SRC_TESTER_TESTER_HPP_
