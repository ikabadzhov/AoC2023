#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <numeric>
#include <string>
#include <vector>

void part_one_two(bool ispart2) {
  std::ifstream file("day11.txt");
  std::string line;
  std::vector<std::vector<bool>> grid;
  std::vector<bool> row_is_all_zeros;
  std::vector<bool> column_is_all_zeros;
  while (std::getline(file, line)) {
    if (column_is_all_zeros.empty()) {
      // first iteration, initialize the columns vector
      column_is_all_zeros = std::vector<bool>(line.size(), true);
    }
    std::vector<bool> row(line.size(), false);
    bool this_row_is_all_zeros = true;
    for (size_t i = 0; i < line.size(); ++i) {
      if (line[i] == '#') {
        row[i] = true;
        this_row_is_all_zeros = false;
        column_is_all_zeros[i] = false;
      }
    }
    grid.push_back(row);
    row_is_all_zeros.push_back(this_row_is_all_zeros);
  }
  long long sum_of_distances = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j]) {
        size_t row_dist = 0;
        // start looking from the current row, as there might be another galaxy
        for (int k = i; k < grid.size(); k++) {
          if (row_is_all_zeros[k]) {
            row_dist++;
            if (ispart2) {
              row_dist += 1000000 - 2;
            }
          }

          for (int l = 0; l < grid[k].size(); l++) {
            // galaxies on the same row, but to the left are already counted
            if (k == i && l <= j) {
              continue;
            }
            if (grid[k][l]) {
              size_t col_dist = 0;
              // the galaxy might be either on the left or on the right of the
              // current one
              for (int m = std::min(l, j); m < std::max(l, j); m++) {
                if (column_is_all_zeros[m]) {
                  col_dist++;
                  if (ispart2) {
                    col_dist += 1000000 - 2;
                  }
                }
                col_dist++;
              }
              sum_of_distances += row_dist + col_dist;
            }
          }
          row_dist++;
        }
      }
    }
  }
  std::cout << sum_of_distances << std::endl;
}

int main() {
  part_one_two(false);
  part_one_two(true);
  return 0;
}