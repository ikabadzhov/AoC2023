#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

bool check_if_possible(int r, int g, int b) {
  return r <= 12 && g <= 13 && b <= 14;
}

void part_one() {
  std::ifstream file("day2.txt");
  std::string line;
  int sum = 0;
  while (std::getline(file, line)) {
    size_t pos = line.find(":");
    int game_id = std::stoi(line.substr(5, pos - 5));
    std::string balls_str = line.substr(pos + 2);
    std::vector<std::string> balls_strs;
    size_t pos2 = 0;
    // split by space
    while ((pos2 = balls_str.find(" ")) != std::string::npos) {
      balls_strs.push_back(balls_str.substr(0, pos2));
      balls_str.erase(0, pos2 + 1);
    }
    balls_strs.push_back(balls_str);

    int r = 0;
    int g = 0;
    int b = 0;
    bool possible = true;
    for (size_t i = 0; i < balls_strs.size(); i += 2) {
      // it is easy to see that numbers are at even positions
      if (balls_strs[i + 1][0] == 'b') {
        b = std::stoi(balls_strs[i]);
      } else if (balls_strs[i + 1][0] == 'r') {
        r = std::stoi(balls_strs[i]);
      } else if (balls_strs[i + 1][0] == 'g') {
        g = std::stoi(balls_strs[i]);
      }
      if (balls_strs[i + 1][balls_strs[i + 1].size() - 1] == ';') {
        if (!check_if_possible(r, g, b)) {
          possible = false;
          break;
        }
      }
    }
    if (possible) {
      // check the last one
      if (check_if_possible(r, g, b)) {
        sum += game_id;
      }
    }
  }
  std::cout << sum << std::endl;
}

void part_two() {
  std::ifstream file("day2.txt");
  std::string line;
  int sum = 0;
  while (std::getline(file, line)) {
    size_t pos = line.find(":");
    std::string balls_str = line.substr(pos + 2);
    std::vector<std::string> balls_strs;
    size_t pos2 = 0;
    // split by space
    while ((pos2 = balls_str.find(" ")) != std::string::npos) {
      balls_strs.push_back(balls_str.substr(0, pos2));
      balls_str.erase(0, pos2 + 1);
    }
    balls_strs.push_back(balls_str);

    int r = 0;
    int g = 0;
    int b = 0;
    for (size_t i = 0; i < balls_strs.size(); i += 2) {
      // it is easy to see that numbers are at even positions
      if (balls_strs[i + 1][0] == 'b') {
        b = std::max(std::stoi(balls_strs[i]), b);
      } else if (balls_strs[i + 1][0] == 'r') {
        r = std::max(std::stoi(balls_strs[i]), r);
      } else if (balls_strs[i + 1][0] == 'g') {
        g = std::max(std::stoi(balls_strs[i]), g);
      }
    }
    sum += r * g * b;
  }
  std::cout << sum << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}