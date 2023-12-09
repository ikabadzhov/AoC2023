#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <numeric>
#include <string>
#include <vector>

void part_one() {
  std::ifstream file("day9.txt");
  std::string line;
  long long sum = 0;
  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }
    std::vector<int> report;
    // tokenize by space and convert to int
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
      token = line.substr(0, pos);
      report.push_back(std::stoi(token));
      line.erase(0, pos + delimiter.length());
    }
    report.push_back(std::stoi(line));
    long long sum_of_diffs = report[report.size() - 1];
    for (size_t i = 0; i < report.size(); ++i) {
      // O(1) space by overwriting the first part of the report
      bool all_zeros = true;
      for (size_t j = 1; j < report.size() - i; ++j) {
        report[j - 1] = report[j] - report[j - 1];
        if (report[j - 1] != 0) {
          all_zeros = false;
        }
      }
      if (all_zeros) {
        break;
      }
      sum_of_diffs += report[report.size() - 2 - i];
    }
    sum += sum_of_diffs;
  }
  std::cout << sum << std::endl;
}

void part_two() {
  std::ifstream file("day9.txt");
  std::string line;
  long long sum = 0;
  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }
    std::vector<int> report;
    // tokenize by space and convert to int
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
      token = line.substr(0, pos);
      report.push_back(std::stoi(token));
      line.erase(0, pos + delimiter.length());
    }
    report.push_back(std::stoi(line));
    long long sum_of_diffs = report[0];
    for (size_t i = 0; i < report.size(); ++i) {
      // O(1) space by overwriting the first part of the report
      bool all_zeros = true;
      for (size_t j = 1; j < report.size() - i; ++j) {
        report[j - 1] = report[j] - report[j - 1];
        if (report[j - 1] != 0) {
          all_zeros = false;
        }
      }
      if (all_zeros) {
        break;
      }
      // doing s = c_4, then s = c_3 - s, then s = c_2 - s and so on
      // which is the same as s = c_0 - c_1 + c_2 - c_3
      sum_of_diffs += report[0] * std::pow((-1), (1 - i % 2));
    }
    sum += sum_of_diffs;
  }
  std::cout << sum << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}