#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <numeric>
#include <string>
#include <vector>

void part_one_two(bool is_part_two) {
  std::ifstream file("day13.txt");
  std::string line;
  std::vector<size_t> rows;
  std::vector<size_t> cols;
  size_t mirrors = 0;
  bool is_last_grid = false;
  while (!is_last_grid) {
    if (!std::getline(file, line))
      is_last_grid = true;
    if (line == "" || is_last_grid) {
      for (size_t mid = 1; mid < cols.size(); mid++) {
        size_t diffs = 0;
        for (size_t offset = 0; offset < std::min(mid, cols.size() - mid);
             offset++) {
          diffs +=
              __builtin_popcount(cols[mid - offset - 1] ^ cols[mid + offset]);
          if (diffs > is_part_two) // 0 in part 1, and 1 in part 2 :D
            break;
        }
        if (diffs == is_part_two)
          mirrors += mid;
      }
      for (size_t mid = 1; mid < rows.size(); mid++) {
        size_t diffs = 0;
        for (size_t offset = 0; offset < std::min(mid, rows.size() - mid);
             offset++) {
          diffs +=
              __builtin_popcount(rows[mid - offset - 1] ^ rows[mid + offset]);
          if (diffs > is_part_two)
            break;
        }
        if (diffs == is_part_two)
          mirrors += mid * 100;
      }
      // reset
      rows.clear();
      cols.clear();
    } else {
      if (cols.empty()) {
        cols.resize(line.size());
      }
      size_t row = 0;
      for (size_t i = 0; i < line.size(); i++) {
        row |= (line[i] == '#') << i;
        cols[i] |= (line[i] == '#') << rows.size();
      }
      rows.push_back(row);
    }
  }
  std::cout << mirrors << std::endl;
}

int main() {
  part_one_two(false);
  part_one_two(true);
  return 0;
}