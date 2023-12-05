#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void part_one() {
  std::ifstream file("day1.txt");
  std::string line;
  int sum = 0;
  while (std::getline(file, line)) {
    char l = '.';
    char r = '.';
    for (auto c : line) {
      if (std::isdigit(c)) {
        if (l == '.') {
          l = c;
        }
        r = c;
      }
    }
    int lr = std::stoi(std::string(1, l) + std::string(1, r));
    sum += lr;
  }
  std::cout << sum << std::endl;
}

void part_two() {
  std::ifstream file("day1.txt");
  std::string line;
  int sum = 0;
  std::vector<std::string> digit_names = {"zero",  "one",  "two", "three",
                                          "four",  "five", "six", "seven",
                                          "eight", "nine"};
  while (std::getline(file, line)) {
    bool change = true;
    while (change) {
      change = false;
      for (int i = 0; i < digit_names.size(); i++) {
        std::string digit_name = digit_names[i];
        size_t pos = line.find(digit_name);
        if (pos != std::string::npos) {
          // avoid case one is part of another, i.e. zerone, hence do pos + 1
          line[pos + 1] = '0' + i;
          change = true;
        }
      }
    }
    char l = '.';
    char r = '.';
    for (auto c : line) {
      if (std::isdigit(c)) {
        if (l == '.') {
          l = c;
        }
        r = c;
      }
    }
    int lr = std::stoi(std::string(1, l) + std::string(1, r));
    sum += lr;
  }
  std::cout << sum << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}