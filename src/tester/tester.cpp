#include "tester/tester.hpp"

#include <iostream>

#include "lib/json.hpp"
#include "terminal/terminal.hpp"
using my_terminal::OptionKeywords;

const char *my_tester::DefaultConfig::TESTDATA_FILE_NAME =
    "./.github/classroom/autograding.json";

bool my_tester::IsMatchTest(string result, string expected, string *std_out) {
  bool ret_flag = true;
  bool while_flag = true;
  size_t r_r_index = result.find_first_of('\r');
  while (r_r_index != string::npos) {
    result = result.erase(r_r_index, 1);
    r_r_index = result.find_first_of('\r');
  }
  size_t e_r_index = expected.find_first_of('\r');
  while (e_r_index != string::npos) {
    expected = expected.erase(e_r_index, 1);
    e_r_index = expected.find_first_of('\r');
  }
  while (result != "" || expected != "") {
    size_t r_el_index = result.find_first_of('\n');
    size_t e_el_index = expected.find_first_of('\n');
    string line_result = result;
    string line_expected = expected;
    if (r_el_index != string::npos) {
      line_result = result.substr(0, r_el_index);
      result = result.substr(r_el_index + 1);
    } else {
      result = "";
    }
    if (e_el_index != string::npos) {
      line_expected = expected.substr(0, e_el_index);
      expected = expected.substr(e_el_index + 1);
    } else {
      expected = "";
    }
    if (line_result != line_expected) {
      ret_flag = false;
      int red_color = my_terminal::decoration::ShellColorCode::RED;
      int green_color = my_terminal::decoration::ShellColorCode::GREEN;
      *std_out += my_terminal::decoration::AddColorToString(
          "-- " + line_result + '\n', red_color);
      *std_out += my_terminal::decoration::AddColorToString(
          "++ " + line_expected + '\n', green_color);
    } else {
      *std_out += "   " + line_result + '\n';
    }
  }
  *std_out += '\n';

  return ret_flag;
}

std::vector<my_tester::TestData> my_tester::GetTestDataByJSON(
    string json_content) {
  std::vector<my_tester::TestData> ret_datas;
  nlohmann::json json = nlohmann::json::parse(json_content)["tests"];
  for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
    TestData test_data = {};
    test_data.test_name = (*it)["name"];
    string it_input = (*it)["input"].get<string>();
    string it_run = (*it)["run"].get<string>();
    size_t it_run_sp_index = it_run.find_first_of(" ");
    test_data.type = Run;
    if (it_run_sp_index != string::npos) {
      test_data.file_name = it_run.substr(it_run_sp_index + 1);
      size_t it_run_next_sp_index = test_data.file_name.find_first_of(" ");
      if (it_run_next_sp_index != string::npos) {
        test_data.file_name =
            test_data.file_name.substr(0, it_run_next_sp_index);
        if (test_data.file_name == "-o") {
          size_t last_it = it_run.find_last_of(" ");
          if (last_it != string::npos) {
            test_data.file_name = it_run.substr(last_it + 1);
          }
        }
      }
      if (it_input == "") {
        string it_run_command = it_run.substr(0, it_run_sp_index);
        size_t it_run_command_exe_index = it_run_command.find_first_of(".exe");
        if (it_run_command_exe_index != string::npos) {
          it_run_command = it_run_command.erase(it_run_command_exe_index);
        }
        for (int i = 0; i < io::DefaultConfig::COMPILERS_SIZE; i++) {
          if (it_run_command == io::DefaultConfig::COMPILERS[i]) {
            test_data.type = Compile;
            break;
          }
        }
      }
    } else {
      test_data.file_name = it_run;
    }
    test_data.input = it_input;
    test_data.output = (*it)["output"].get<string>();

    ret_datas.push_back(test_data);
  }

  return ret_datas;
}

bool my_tester::RunTests(std::map<string, string> options) {
  if (options.find(OptionKeywords::TESTDATA_FILE_NAME) == options.end()) {
    options[OptionKeywords::TESTDATA_FILE_NAME] =
        DefaultConfig::TESTDATA_FILE_NAME;
  }
  string test_data_file;
  if (!io::FileOpen(options[OptionKeywords::TESTDATA_FILE_NAME],
                    &test_data_file)) {
    return false;
  }
  std::vector<TestData> test_datas = GetTestDataByJSON(test_data_file);
  std::vector<std::vector<string>> std_table;
  std_table.push_back(std::vector<string>{"Status", "Name", "File"});
  string last_file;
  int red_code = my_terminal::decoration::ShellColorCode::RED;
  int green_code = my_terminal::decoration::ShellColorCode::GREEN;
  size_t last_name_length = 0;
  for (int i = 0; i < test_datas.size(); i++) {
    size_t spase_length =
        last_name_length > test_datas[i].test_name.length()
            ? last_name_length - test_datas[i].test_name.length()
            : 0;
    my_terminal::PrintToShell('\r' + test_datas[i].test_name +
                              string(spase_length, ' '));
    last_name_length = test_datas[i].test_name.length();
    bool is_pass = false;
    if (test_datas[i].type == Compile) {
      last_file = io::CompileCppFile(test_datas[i].file_name);
      is_pass = last_file != "";
      if (!is_pass) {
        my_terminal::PrintToShell("\r");
        my_terminal::PrintToShell(
            my_terminal::decoration::AddColorToString(
                test_datas[i].test_name + " : " + test_datas[i].file_name,
                red_code, true) +
            "\n\n");
      }
    } else if (test_datas[i].type == Run) {
      if (last_file != "") {
        string std_out = io::RunFile(last_file, test_datas[i].input);
        string test_out = "";
        is_pass = IsMatchTest(std_out, test_datas[i].output, &test_out);
        if (!is_pass) {
          my_terminal::PrintToShell("\r");
          my_terminal::PrintToShell(
              my_terminal::decoration::AddColorToString(
                  test_datas[i].test_name + " : " + test_datas[i].file_name,
                  red_code, true) +
              '\n');
          my_terminal::PrintToShell(test_out);
        }
      } else {
        is_pass = false;
      }
    }
    string status_str =
        is_pass ? my_terminal::decoration::AddColorToString("PASS", green_code)
                : my_terminal::decoration::AddColorToString("FAIL", red_code);
    std_table.push_back(std::vector<string>{status_str, test_datas[i].test_name,
                                            test_datas[i].file_name});
  }
  my_terminal::PrintToShell("\r");
  my_terminal::PrintToShell(my_terminal::decoration::CreateStrTable(std_table));
  return 0;
}
