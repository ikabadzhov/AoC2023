#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <numeric>
#include <string>
#include <vector>

void part_one() {
  std::ifstream file("day6.txt");
  std::string line;
  std::vector<std::vector<int>> vals;
  while (std::getline(file, line)) {
    size_t pos = line.find(":");
    std::string numbers_str = line.substr(pos + 1);
    pos = 0;
    vals.push_back(std::vector<int>());
    while ((pos = numbers_str.find(" ")) != std::string::npos) {
      std::string token = numbers_str.substr(0, pos);
      if (token.size() > 0) {
        vals[vals.size() - 1].push_back(std::stoi(token));
      }
      numbers_str.erase(0, pos + 1);
    }
    vals[vals.size() - 1].push_back(std::stoi(numbers_str));
  }
  long long prod = 1;
  for (size_t i = 0; i < vals[0].size(); i++) {
    int possibilities = 0;
    for (int j = 0; j < vals[0][i]; j++) {
      if ((vals[0][i] - j) * j > vals[1][i]) {
        possibilities++;
      }
    }
    prod *= possibilities;
  }
  std::cout << prod << std::endl;
}

void part_two() {
  // TODO: ok, no bother parsing :D
  // time is low, this is easy to brute force
  long long time = 71530;
  long long dist = 940200;
  long long possibilities = 0;
  for (long long i = 0; i < time; i++) {
    if ((time - i) * i > dist) {
      possibilities++;
    }
  }
  std::cout << possibilities << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}