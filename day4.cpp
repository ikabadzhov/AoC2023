#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <numeric>
#include <string>
#include <vector>

void part_one() {
  std::ifstream file("day4.txt");
  std::string line;
  int sum = 0;
  while (std::getline(file, line)) {
    size_t pos = line.find(":");
    std::string numbers_str = line.substr(pos + 2);
    pos = numbers_str.find("|");
    std::string left = numbers_str.substr(0, pos);
    std::string right = numbers_str.substr(pos + 2);
    std::vector<int> lottery;
    std::vector<int> mytrial;
    pos = 0;
    while ((pos = left.find(" ")) != std::string::npos) {
      std::string token = left.substr(0, pos);
      if (token.size() > 0) {
        lottery.push_back(std::stoi(token));
      }
      left.erase(0, pos + 1);
    }
    pos = 0;
    while ((pos = right.find(" ")) != std::string::npos) {
      std::string token = right.substr(0, pos);
      if (token.size() > 0) {
        mytrial.push_back(std::stoi(token));
      }
      right.erase(0, pos + 1);
    }
    mytrial.push_back(std::stoi(right));
    // compare the two vectors
    int count = 0;
    for (auto i : lottery) {
      for (auto j : mytrial) {
        if (i == j) {
          count++;
        }
      }
    }
    if (count >= 1) {
      sum += pow(2, count - 1);
    }
  }
  std::cout << sum << std::endl;
}

void part_two() {
  std::ifstream file("day4.txt");
  std::string line;
  // TODO: ok, size 207 is cheating, I handle one input anyway...
  // begin with one instance of each card
  std::vector<int> prizes(207, 1);
  while (std::getline(file, line)) {
    size_t pos = line.find(":");
    int card_id = std::stoi(line.substr(5, pos - 5));
    std::string numbers_str = line.substr(pos + 2);
    pos = numbers_str.find("|");
    std::string left = numbers_str.substr(0, pos);
    std::string right = numbers_str.substr(pos + 2);
    std::vector<int> lottery;
    std::vector<int> mytrial;
    pos = 0;
    while ((pos = left.find(" ")) != std::string::npos) {
      std::string token = left.substr(0, pos);
      if (token.size() > 0) {
        lottery.push_back(std::stoi(token));
      }
      left.erase(0, pos + 1);
    }
    pos = 0;
    while ((pos = right.find(" ")) != std::string::npos) {
      std::string token = right.substr(0, pos);
      if (token.size() > 0) {
        mytrial.push_back(std::stoi(token));
      }
      right.erase(0, pos + 1);
    }
    mytrial.push_back(std::stoi(right));
    // compare the two vectors
    int count = 0;
    for (auto i : lottery) {
      for (auto j : mytrial) {
        if (i == j) {
          count++;
        }
      }
    }
    // current card is card_id - 1 in the vector
    for (int i = 0; i < count; i++) {
      prizes[card_id + i] += prizes[card_id - 1];
    }
  }
  std::cout << std::accumulate(prizes.begin(), prizes.end(), 0) << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}