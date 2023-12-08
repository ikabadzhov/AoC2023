#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <numeric>
#include <string>
#include <vector>

void part_one() {
  std::ifstream file("day8.txt");
  std::string line;
  std::map<std::string, std::vector<std::pair<std::string, std::string>>>
      navigation;
  std::getline(file, line);
  std::string directions = line;
  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }
    std::string current = line.substr(0, 3);
    std::string left = line.substr(7, 3);
    std::string right = line.substr(12, 3);
    navigation[current].push_back(std::make_pair(left, right));
  }
  int seen = 0;
  std::string current = "AAA";
  while (current != "ZZZ") {

    if (directions[seen % directions.size()] == 'L') {
      current = navigation[current][0].first;
    } else {
      current = navigation[current][0].second;
    }
    seen++;
  }
  std::cout << seen << std::endl;
}

void part_two() {
  std::ifstream file("day8.txt");
  std::string line;
  std::map<std::string, std::vector<std::pair<std::string, std::string>>>
      navigation;
  std::getline(file, line);
  std::string directions = line;
  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }
    std::string current = line.substr(0, 3);
    std::string left = line.substr(7, 3);
    std::string right = line.substr(12, 3);
    navigation[current].push_back(std::make_pair(left, right));
  }
  std::vector<std::string> starts;
  // get all strings that end with an A
  for (auto node : navigation) {
    if (node.first[2] == 'A') {
      starts.push_back(node.first);
    }
  }
  long long running_lcm = 1; // basically counting cycles
  for (auto &start : starts) {
    long long seen = 0;
    while (start[2] != 'Z') {
      if (directions[seen % directions.size()] == 'L') {
        start = navigation[start][0].first;
      } else {
        start = navigation[start][0].second;
      }
      seen++;
    }
    running_lcm = std::lcm(running_lcm, seen);
  }
  std::cout << running_lcm << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}