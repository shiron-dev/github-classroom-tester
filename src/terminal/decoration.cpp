#include "terminal/terminal.hpp"

const int my_terminal::decoration::ShellColorCode::BLACK = 30;
const int my_terminal::decoration::ShellColorCode::RED = 31;
const int my_terminal::decoration::ShellColorCode::GREEN = 32;
const int my_terminal::decoration::ShellColorCode::YELLOW = 33;
const int my_terminal::decoration::ShellColorCode::BLUE = 34;
const int my_terminal::decoration::ShellColorCode::MAGENTA = 35;
const int my_terminal::decoration::ShellColorCode::CYAN = 36;
const int my_terminal::decoration::ShellColorCode::WHITE = 37;

string my_terminal::decoration::AddColorToString(string str, int color,
                                                 bool is_bg) {
  int color_code = color;
  if (is_bg) {
    color_code += 10;
  }
  string color_str = "\u001b[" + std::to_string(color_code) + "m";
  return color_str + str + "\u001b[m";
}

string my_terminal::decoration::CreateStrTable(
    std::vector<std::vector<string>> table_str) {
  int vertical = static_cast<int>(table_str.size());
  int horizontal = static_cast<int>(table_str[0].size());
  int *max_length = new int[horizontal];
  for (int i = 0; i < vertical; i++) {
    for (int j = 0; j < horizontal; j++) {
      if (i == 0) {
        max_length[j] = static_cast<int>(GetStrLen(table_str[i][j]));
      } else {
        if (max_length[j] < static_cast<int>(GetStrLen(table_str[i][j]))) {
          max_length[j] = static_cast<int>(GetStrLen(table_str[i][j]));
        }
      }
    }
  }
  const string v_str = "|";
  const string h_str = "-";
  string str = "";
  for (int i = -2; i < vertical + 1; i++) {
    str += v_str;
    for (int j = 0; j < horizontal; j++) {
      int it = i;
      if (i <= 0 || i == vertical) {
        if (i == -1) {
          it = 0;
        } else {
          it = -1;
          for (int k = 0; k < max_length[j] + 2; k++) {
            str += h_str;
          }
        }
      }
      if (it != -1) {
        string blank_str = "";
        for (int k = 0;
             k < max_length[j] - static_cast<int>(GetStrLen(table_str[it][j]));
             k++) {
          blank_str += " ";
        }
        str += " " + table_str[it][j] + blank_str + " ";
      }
      str += v_str;
    }
    str += "\n";
  }
  delete[] max_length;
  return str;
}

size_t my_terminal::decoration::GetStrLen(string str) {
  if (str.length() != 0) {
    while (true) {
      size_t u_index = str.find_first_of('\u001b');
      if (u_index == string::npos) {
        return str.length();
      }
      size_t m_index = str.find_first_of('m');
      if (m_index != string::npos) {
        str = str.substr(0, u_index) + str.substr(m_index + 1);
      } else {
        return str.length() - 1;
      }
    }
  }
  return 0;
}
