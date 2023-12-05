#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

void part_one() {
  std::ifstream file("day3.txt");
  std::string line;
  int sum = 0;
  // create a moving window of 3 lines
  std::deque<std::string> window;
  // get the first line here as its size is needed
  std::getline(file, line);
  // create a dummy line to avoid front special case
  window.push_back(std::string(line.size(), '.'));
  window.push_back(line);
  bool last_line = false;
  while (true) {
    if (std::getline(file, line)) {
      window.push_back(line);
    } else {
      // add a dummy line to avoid back special case
      window.push_back(std::string(line.size(), '.'));
      last_line = true;
    }
    if (window.size() == 3) { // invariant
      // iterate through the middle line only
      std::vector<std::pair<std::string, size_t>> vals_pos;
      size_t dim = window[1].size(); // same for all
      for (int i = 0; i < dim; i++) {
        std::string temp_val = "";
        while (std::isdigit(window[1][i])) {
          temp_val += window[1][i];
          i++;
        }
        if (temp_val != "") {
          vals_pos.push_back(std::make_pair(temp_val, i - temp_val.size()));
        }
      }
      // check the neighbors of each value
      for (auto val_position : vals_pos) {
        bool is_part = false;
        // check the left neighbors
        if (val_position.second > 0) {
          // check all 3 lines in the window
          for (int i = 0; i < 3; i++) {
            if (window[i][val_position.second - 1] != '.') {
              is_part = true;
              break;
            }
          }
        }
        if (is_part) {
          sum += std::stoi(val_position.first);
          continue;
        }
        // check the right neighbors
        if (val_position.second + val_position.first.size() < dim - 1) {
          // check all 3 lines in the window
          for (int i = 0; i < 3; i++) {
            if (window[i][val_position.second + val_position.first.size()] !=
                '.') {
              is_part = true;
              break;
            }
          }
        }
        if (is_part) {
          sum += std::stoi(val_position.first);
          continue;
        }
        for (size_t i = val_position.second;
             i < val_position.second + val_position.first.size(); i++) {
          if (window[0][i] != '.' || window[2][i] != '.') {
            is_part = true;
            break;
          }
        }
        if (is_part) {
          sum += std::stoi(val_position.first);
        }
      }
      window.pop_front();
    } else {
      assert(0);
    }
    if (last_line) {
      break;
    }
  }
  std::cout << sum << std::endl;
}

void part_two() {
  std::ifstream file("day3.txt");
  std::string line;
  int sum = 0;
  // create a moving window of 3 lines
  std::deque<std::string> window;
  // get the first line here as its size is needed
  std::getline(file, line);
  // create a dummy line to avoid front special case
  window.push_back(std::string(line.size(), '.'));
  window.push_back(line);
  bool last_line = false;
  // keys are coordinates of the *
  // values is the list of adjacent parts
  std::map<std::pair<size_t, size_t>, std::vector<int>> spec_parts;
  size_t line_number = 0;
  while (true) {
    if (std::getline(file, line)) {
      window.push_back(line);
    } else {
      // add a dummy line to avoid back special case
      window.push_back(std::string(line.size(), '.'));
      last_line = true;
    }
    if (window.size() == 3) { // invariant
      line_number++;
      // iterate through the middle line only
      std::vector<std::pair<std::string, size_t>> vals_pos;
      size_t dim = window[1].size(); // same for all
      for (int i = 0; i < dim; i++) {
        std::string temp_val = "";
        while (std::isdigit(window[1][i])) {
          temp_val += window[1][i];
          i++;
        }
        if (temp_val != "") {
          vals_pos.push_back(std::make_pair(temp_val, i - temp_val.size()));
        }
      }
      // check the neighbors of each value
      for (auto val_position : vals_pos) {
        bool is_part = false;
        // check the left neighbors
        if (val_position.second > 0) {
          // check all 3 lines in the window
          for (int i = 0; i < 3; i++) {
            if (window[i][val_position.second - 1] == '*') {
              // add the part to the map
              spec_parts[std::make_pair(line_number - 1 + i,
                                        val_position.second - 1)]
                  .push_back(std::stoi(val_position.first));
              is_part = true;
              break;
            }
          }
        }
        if (is_part) {
          continue;
        }
        // check the right neighbors
        if (val_position.second + val_position.first.size() < dim - 1) {
          // check all 3 lines in the window
          for (int i = 0; i < 3; i++) {
            if (window[i][val_position.second + val_position.first.size()] ==
                '*') {
              spec_parts[std::make_pair(line_number - 1 + i,
                                        val_position.second +
                                            val_position.first.size())]
                  .push_back(std::stoi(val_position.first));
              is_part = true;
              break;
            }
          }
        }
        if (is_part) {
          continue;
        }
        for (size_t i = val_position.second;
             i < val_position.second + val_position.first.size(); i++) {
          if (window[0][i] == '*') {
            spec_parts[std::make_pair(line_number - 1, i)].push_back(
                std::stoi(val_position.first));
            break;
          } else if (window[2][i] == '*') {
            spec_parts[std::make_pair(line_number + 1, i)].push_back(
                std::stoi(val_position.first));
            break;
          }
        }
      }
      window.pop_front();
    } else {
      assert(0);
    }
    if (last_line) {
      break;
    }
  }
  for (auto val : spec_parts) {
    if (val.second.size() == 2) {
      sum += val.second[0] * val.second[1];
    }
    if (val.second.size() > 2) {
      assert(0);
    }
  }
  std::cout << sum << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}