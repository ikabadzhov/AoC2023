#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

void part_one() {
  std::ifstream file("day5.txt");
  std::string line;
  std::getline(file, line);
  size_t pos = line.find(":");
  std::string seeds_str = line.substr(pos + 2);
  std::vector<std::pair<long long, bool>> seeds;
  pos = 0;
  while ((pos = seeds_str.find(" ")) != std::string::npos) {
    std::string token = seeds_str.substr(0, pos);
    if (token.size() > 0) {
      seeds.push_back(std::make_pair(std::stoll(token), false));
    }
    seeds_str.erase(0, pos + 1);
  }
  seeds.push_back(std::make_pair(std::stoll(seeds_str), false));
  while (std::getline(file, line)) {
    if (line.size() == 0) {
      continue;
    }
    if (line.find(":") != std::string::npos) {
      // update all flags
      for (size_t i = 0; i < seeds.size(); ++i) {
        seeds[i].second = false;
      }
      continue;
    }
    // tokenize by space
    pos = 0;
    std::vector<long long> rules;
    while ((pos = line.find(" ")) != std::string::npos) {
      std::string token = line.substr(0, pos);
      if (token.size() > 0) {
        rules.push_back(std::stoll(token));
      }
      line.erase(0, pos + 1);
    }
    rules.push_back(std::stoll(line));
    for (auto &seed : seeds) {
      if (seed.second) { // already updated
        continue;
      }

      if (seed.first >= rules[1] && seed.first <= rules[1] + rules[2]) {
        seed.first += rules[0] - rules[1];
        seed.second = true;
      }
    }
  }
  std::cout << std::min_element(seeds.begin(), seeds.end())->first << std::endl;
}

void part_two() {
  std::ifstream file("day5.txt");
  std::string line;
  std::getline(file, line);
  size_t pos = line.find(":");
  std::string seeds_str = line.substr(pos + 2);
  std::vector<long long> brute_force_seeds;
  // range start, range length, is updated
  std::vector<std::tuple<long long, long long, bool>> seeds;
  pos = 0;
  while ((pos = seeds_str.find(" ")) != std::string::npos) {
    std::string token = seeds_str.substr(0, pos);
    if (token.size() > 0) {
      brute_force_seeds.push_back(std::stoll(token));
    }
    seeds_str.erase(0, pos + 1);
  }
  brute_force_seeds.push_back(std::stoll(seeds_str));

  for (size_t i = 0; i < brute_force_seeds.size(); i += 2) {
    seeds.push_back(
        std::make_tuple(brute_force_seeds[i], brute_force_seeds[i + 1], false));
  }
  std::vector<std::tuple<long long, long long, long long>> rules;
  bool read_more = true;
  while (read_more) {
    read_more = (bool)std::getline(file, line); // unsafe...
    if (line.size() == 0) {
      continue;
    }
    if (line.find(":") != std::string::npos || !read_more) {
      if (rules.empty()) {
        continue;
      }
      // sort the rules by second element, i.e. the source
      // this is crucial!!! reason is that there might be a seed interval
      // that belongs to >2 rules, and we need to update the seed interval
      // we need to guarantee that the newly generated seed intervals are
      // going to be updated by all current rules
      std::sort(rules.begin(), rules.end(),
                [](const std::tuple<long long, long long, long long> &a,
                   const std::tuple<long long, long long, long long> &b) {
                  return std::get<1>(a) < std::get<1>(b);
                });
      for (const auto &rule : rules) {
        std::vector<std::tuple<long long, long long, bool>> new_seeds;
        for (auto &seed : seeds) {
          if (std::get<2>(seed)) { // already updated
            continue;
          }
          // we need to check for the matching of 2 intervals (seed and rule)
          // differentiate 2 general cases
          // start of rule is 1. inside the seed || 2. left to the seed
          if (!((std::get<0>(seed) <= std::get<1>(rule) &&
                 std::get<1>(rule) <= std::get<0>(seed) + std::get<1>(seed)) ||
                (std::get<1>(rule) <= std::get<0>(seed) &&
                 std::get<0>(seed) <= std::get<1>(rule) + std::get<2>(rule)))) {
            // no overlap
            continue;
          }
          if (std::get<0>(seed) < std::get<1>(rule)) {
            // partial overlap from the left, only possible in first case
            new_seeds.push_back(
                std::make_tuple(std::get<0>(seed),
                                std::get<1>(rule) - std::get<0>(seed), false));
          }
          if (std::get<0>(seed) + std::get<1>(seed) >
              std::get<1>(rule) + std::get<2>(rule)) {
            // partial overlap from the right
            new_seeds.push_back(
                std::make_tuple(std::get<1>(rule) + std::get<2>(rule),
                                std::get<0>(seed) + std::get<1>(seed) -
                                    std::get<1>(rule) - std::get<2>(rule),
                                false));
          }
          // map the seed to the rule, this is the hardest part imo
          // idea: determine if the seed is inside the rule,
          // eventually trim the seed to fit the rule
          // and then notice that we are taking the offset of the seed
          std::get<1>(seed) = std::min(std::get<0>(seed) + std::get<1>(seed),
                                       std::get<1>(rule) + std::get<2>(rule)) -
                              std::get<0>(seed);
          std::get<0>(seed) += std::get<0>(rule) - std::get<1>(rule);
          std::get<2>(seed) = true;
        }
        seeds.insert(seeds.end(), new_seeds.begin(), new_seeds.end());
      }
      // reset the rules
      rules.clear();
      // update all flags
      for (size_t i = 0; i < seeds.size(); ++i) {
        std::get<2>(seeds[i]) = false;
      }
      continue;
    }
    pos = 0;
    std::vector<long long> rule;
    // tokenize by space
    while ((pos = line.find(" ")) != std::string::npos) {
      std::string token = line.substr(0, pos);
      if (token.size() > 0) {
        rule.push_back(std::stoll(token));
      }
      line.erase(0, pos + 1);
    }
    rule.push_back(std::stoll(line));
    rules.push_back(std::make_tuple(rule[0], rule[1], rule[2]));
  }
  // by default tuple comparison is by the first element
  auto min_seed = std::min_element(seeds.begin(), seeds.end());
  std::cout << std::get<0>(*min_seed) << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}