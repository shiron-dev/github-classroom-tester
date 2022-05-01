#include <cstdio>
#include <fstream>
#include <memory>

#include "terminal/terminal.hpp"
#include "tester/tester.hpp"

const char *my_tester::io::DefaultConfig::COMPILERS[] = {"g++", "c++", "cl"};
const int my_tester::io::DefaultConfig::COMPILERS_SIZE = 3;
const char *my_tester::io::DefaultConfig::CHECK_COMMAND = "where";
const char *my_tester::io::DefaultConfig::COMPILE_OUT_FILE = "test.o";
const char *my_tester::io::DefaultConfig::PRINT_COMMAND = "echo";

// 現在Windowsのみの対応
int my_tester::io::RunByShell(string cmd, string *std_out, int *status_code) {
  std::shared_ptr<FILE> pipe(_popen(cmd.c_str(), "r"), [&](FILE *p) {
    status_code = new int(_pclose(p));
  });
  if (!pipe) {
    return -1;
  }
  char buf[256];
  while (!feof(pipe.get())) {
    if (fgets(buf, sizeof(buf), pipe.get()) != nullptr) {
      *std_out += string(buf);
    }
  }
  *status_code = *(new int(_pclose(pipe.get())));

  return 0;
}

bool my_tester::io::CheckHasCommand(string cmd) {
  string get_cmd = string(DefaultConfig::CHECK_COMMAND) + " " + cmd;
  string std_out = "";
  int status_code = -1;
  if (RunByShell(get_cmd, &std_out, &status_code)) {
    if (status_code == 0) {
      return true;
    }
  }
  return false;
}

string my_tester::io::CompileCppFile(string file, string compiler,
                                     string option) {
  string use_compiler = "";
  if (compiler != "") {
    if (CheckHasCommand(compiler)) {
      use_compiler = compiler;
    } else {
      my_terminal::PrintToShell("There is not " + compiler + ".");
      return "";
    }
  }
  if (compiler == "") {
    for (int i = 0; i < DefaultConfig::COMPILERS_SIZE; i++) {
      if (CheckHasCommand(DefaultConfig::COMPILERS[i])) {
        use_compiler = DefaultConfig::COMPILERS[i];
        break;
      }
    }
  }
  if (use_compiler != "") {
    string cmd = use_compiler + " " + file + " " + option + " -o " +
                 DefaultConfig::COMPILE_OUT_FILE;
    string std_out = "";
    int status_code = -1;
    if (RunByShell(cmd, &std_out, &status_code)) {
      const int max_path = 128;
      char szDrive[8], szPath[max_path], szFName[max_path], szExt[max_path];
      _splitpath_s(file.c_str(), szDrive, sizeof(szDrive), szPath,
                   sizeof(szPath), szFName, sizeof(szFName), szExt,
                   sizeof(szExt));
      return string(szPath) + DefaultConfig::COMPILE_OUT_FILE;
    }
  }
  return "";
}

string my_tester::io::RunFile(string file, string input) {
  string cmd = "";
  if (input == "") {
    cmd = file;
  } else {
    cmd = string(DefaultConfig::PRINT_COMMAND) + " \"" + input + "\" | " + file;
  }
  string std_out = "";
  int status_code = -1;
  if (my_tester::io::RunByShell(cmd, &std_out, &status_code)) {
    return std_out;
  }
  return "";
}

int my_tester::io::FileOpen(string file, string *file_out) {
  std::ifstream ifs(file);
  string str;
  if (ifs.fail()) {
    my_terminal::PrintToShell("Failed to open " + file + ".");
    return -1;
  }
  while (getline(ifs, str)) {
    *file_out += str + '\n';
  }
  return 0;
}
