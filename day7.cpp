#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <numeric>
#include <string>
#include <vector>

int evaluate_card(char card, bool is_part_one) {
  if (card >= '2' && card <= '9') {
    return card - '0';
  } else if (card == 'T') {
    return 10;
  } else if (card == 'J') {
    return (is_part_one ? 11 : 1);
  } else if (card == 'Q') {
    return 12;
  } else if (card == 'K') {
    return 13;
  } else if (card == 'A') {
    return 14;
  }
  assert(0);
  return -1;
}

void part_one() {
  std::ifstream file("day7.txt");
  std::string line;
  std::vector<std::tuple<std::vector<int>, std::string, int>> collection;
  while (std::getline(file, line)) {
    size_t pos = line.find(" ");
    std::string cards = line.substr(0, pos);
    std::string bids = line.substr(pos + 1);
    std::vector<std::pair<int, int>> hand;
    for (auto card : cards) {
      bool found = false;
      for (auto &pair : hand) {
        if (pair.second == evaluate_card(card, true)) {
          pair.first++;
          found = true;
          break;
        }
      }
      if (!found) {
        hand.push_back(std::make_pair(1, evaluate_card(card, true)));
      }
    }
    // reverse order by count
    std::sort(hand.begin(), hand.end(), std::greater<>());
    std::vector<int> counters;
    for (auto pair : hand) {
      counters.push_back(pair.first);
    }
    collection.push_back(std::make_tuple(counters, cards, std::stoi(bids)));
  }
  std::sort(collection.begin(), collection.end(),
            [](const auto &lhs, const auto &rhs) {
              // few different cards <=> better rank
              if (std::get<0>(lhs).size() != std::get<0>(rhs).size()) {
                return std::get<0>(lhs).size() > std::get<0>(rhs).size();
              }
              // could return here, if {4k, fh} or {3k, 2p}
              for (size_t i = 0; i < std::get<0>(lhs).size(); ++i) {
                if (std::get<0>(lhs)[i] != std::get<0>(rhs)[i]) {
                  return std::get<0>(lhs)[i] < std::get<0>(rhs)[i];
                }
              }
              // I should read the rules better!
              // in case of a rank tie, take the input order string...
              for (size_t i = 0; i < std::get<1>(lhs).size(); ++i) {
                if (std::get<1>(lhs)[i] != std::get<1>(rhs)[i]) {
                  return evaluate_card(std::get<1>(lhs)[i], true) <
                         evaluate_card(std::get<1>(rhs)[i], true);
                }
              }
              return false;
            });
  long long total_win = 0;
  for (size_t i = 0; i < collection.size(); i++) {
    total_win += std::get<2>(collection[i]) * (i + 1);
  }
  std::cout << total_win << std::endl;
}

void part_two() {
  std::ifstream file("day7.txt");
  std::string line;
  std::vector<std::tuple<std::vector<int>, std::string, int>> collection;
  while (std::getline(file, line)) {
    size_t pos = line.find(" ");
    std::string cards = line.substr(0, pos);
    std::string bids = line.substr(pos + 1);
    std::vector<std::pair<int, int>> hand;
    for (auto card : cards) {
      bool found = false;
      for (auto &pair : hand) {
        if (pair.second == evaluate_card(card, false)) {
          pair.first++;
          found = true;
          break;
        }
      }
      if (!found) {
        hand.push_back(std::make_pair(1, evaluate_card(card, false)));
      }
    }
    int jacks = 0;
    for (auto &pair : hand) {
      if (pair.second == 1) {
        jacks = pair.first;
        // pop the jack
        hand.erase(std::remove(hand.begin(), hand.end(), pair), hand.end());
        break;
      }
    }
    // reverse order by count
    std::sort(hand.begin(), hand.end(), std::greater<>());
    // hand was jacks only
    if (hand.empty()) {
      assert(jacks == 5);
      hand.push_back(std::make_pair(jacks, 1));
    } else {
      hand[0].first += jacks;
    }
    std::vector<int> counters;
    for (auto pair : hand) {
      counters.push_back(pair.first);
    }
    collection.push_back(std::make_tuple(counters, cards, std::stoi(bids)));
  }
  std::sort(collection.begin(), collection.end(),
            [](const auto &lhs, const auto &rhs) {
              // few different cards <=> better rank
              if (std::get<0>(lhs).size() != std::get<0>(rhs).size()) {
                return std::get<0>(lhs).size() > std::get<0>(rhs).size();
              }
              // could return here, if {4k, fh} or {3k, 2p}
              for (size_t i = 0; i < std::get<0>(lhs).size(); ++i) {
                if (std::get<0>(lhs)[i] != std::get<0>(rhs)[i]) {
                  return std::get<0>(lhs)[i] < std::get<0>(rhs)[i];
                }
              }
              // I should read the rules better!
              // in case of a rank tie, take the input order string...
              for (size_t i = 0; i < std::get<1>(lhs).size(); ++i) {
                if (std::get<1>(lhs)[i] != std::get<1>(rhs)[i]) {
                  return evaluate_card(std::get<1>(lhs)[i], false) <
                         evaluate_card(std::get<1>(rhs)[i], false);
                }
              }
              return false;
            });
  long long total_win = 0;
  for (size_t i = 0; i < collection.size(); i++) {
    total_win += std::get<2>(collection[i]) * (i + 1);
  }
  std::cout << total_win << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}