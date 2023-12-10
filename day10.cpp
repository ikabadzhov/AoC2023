#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <numeric>
#include <string>
#include <vector>

void part_one() {
  std::ifstream file("day10.txt");
  std::string line;
  std::vector<std::vector<char>> grid;
  std::pair<int, int> prev_coord = {0, 0};
  while (std::getline(file, line)) {
    std::vector<char> row;
    for (char c : line) {
      if (c == 'S') {
        prev_coord = {grid.size(), row.size()};
      }
      row.push_back(c);
    }
    grid.push_back(row);
  }
  // look at the neighbors of the start coord
  // later need the previous coord to know which direction to go
  std::pair<int, int> current_coord = prev_coord;
  /*
  | is a vertical pipe connecting north and south.
  - is a horizontal pipe connecting east and west.
  L is a 90-degree bend connecting north and east.
  J is a 90-degree bend connecting north and west.
  7 is a 90-degree bend connecting south and west.
  F is a 90-degree bend connecting south and east.
  */
  // suffices to check 3 directions as a possible start since loop
  bool found = false;
  if (current_coord.first > 0) {
    if (grid[current_coord.first - 1][current_coord.second] == '|' ||
        grid[current_coord.first - 1][current_coord.second] == '7' ||
        grid[current_coord.first - 1][current_coord.second] == 'F') {
      current_coord.first--;
      found = true;
    }
  }
  if (current_coord.first < grid.size() - 1 && !found) {
    if (grid[current_coord.first + 1][current_coord.second] == '|' ||
        grid[current_coord.first + 1][current_coord.second] == 'L' ||
        grid[current_coord.first + 1][current_coord.second] == 'J') {
      current_coord.first++;
      found = true;
    }
  }
  if (current_coord.second > 0 && !found) {
    if (grid[current_coord.first][current_coord.second - 1] == '-' ||
        grid[current_coord.first][current_coord.second - 1] == 'L' ||
        grid[current_coord.first][current_coord.second - 1] == 'F') {
      current_coord.second--;
      found = true;
    }
  }
  if (!found) {
    assert(0);
  }
  int path_length = 0;
  while (grid[current_coord.first][current_coord.second] != 'S') {
    auto current_copy = current_coord;
    if (grid[current_coord.first][current_coord.second] == '|') {
      current_coord.first += (current_coord.first > prev_coord.first) ? 1 : -1;
    } else if (grid[current_coord.first][current_coord.second] == '-') {
      current_coord.second +=
          (current_coord.second > prev_coord.second) ? 1 : -1;
    } else if (grid[current_coord.first][current_coord.second] == 'L') {
      if (current_coord.first > prev_coord.first) {
        current_coord.second++;
      } else {
        current_coord.first--;
      }
    } else if (grid[current_coord.first][current_coord.second] == 'J') {
      if (current_coord.first > prev_coord.first) {
        current_coord.second--;
      } else {
        current_coord.first--;
      }
    } else if (grid[current_coord.first][current_coord.second] == '7') {
      if (current_coord.first < prev_coord.first) {
        current_coord.second--;
      } else {
        current_coord.first++;
      }
    } else if (grid[current_coord.first][current_coord.second] == 'F') {
      if (current_coord.first < prev_coord.first) {
        current_coord.second++;
      } else {
        current_coord.first++;
      }
    } else {
      assert(0);
    }
    path_length++;
    prev_coord = current_copy;
  }
  std::cout << (path_length + 1) / 2 << std::endl;
}

void part_two() {
  std::ifstream file("day10.txt");
  std::string line;
  // the grid now contains a flag which is either
  // 0 if the entry is not part of the path
  // 1 if the entry is part of the path but below no south end
  // 2 if the entry is part of the path and below a south end
  std::vector<std::vector<std::pair<char, bool>>> grid;
  std::pair<int, int> prev_coord = {0, 0};
  while (std::getline(file, line)) {
    std::vector<std::pair<char, bool>> row;
    for (char c : line) {
      if (c == 'S') {
        prev_coord = {grid.size(), row.size()};
      }
      row.push_back({c, false});
    }
    grid.push_back(row);
  }
  // look at the neighbors of the start coord
  // later need the previous coord to know which direction to go
  std::pair<int, int> current_coord = prev_coord;
  /*
  | is a vertical pipe connecting north and south.
  - is a horizontal pipe connecting east and west.
  L is a 90-degree bend connecting north and east.
  J is a 90-degree bend connecting north and west.
  7 is a 90-degree bend connecting south and west.
  F is a 90-degree bend connecting south and east.
  */
  int found = 0; // to replace the S afterwards
  // suffices to check 3 directions as a possible start since loop
  if (current_coord.first > 0) { // check north
    if (grid[current_coord.first - 1][current_coord.second].first == '|' ||
        grid[current_coord.first - 1][current_coord.second].first == '7' ||
        grid[current_coord.first - 1][current_coord.second].first == 'F') {
      current_coord.first--;
      found = 1;
    }
  }
  if (current_coord.first < grid.size() - 1 && !found) { // check south
    if (grid[current_coord.first + 1][current_coord.second].first == '|' ||
        grid[current_coord.first + 1][current_coord.second].first == 'L' ||
        grid[current_coord.first + 1][current_coord.second].first == 'J') {
      current_coord.first++;
      found = 2;
    }
  }
  if (current_coord.second > 0 && !found) { // check west
    if (grid[current_coord.first][current_coord.second - 1].first == '-' ||
        grid[current_coord.first][current_coord.second - 1].first == 'L' ||
        grid[current_coord.first][current_coord.second - 1].first == 'F') {
      current_coord.second--;
      found = 3;
    }
  }
  // since the path is a loop, no need to check east
  if (!found) {
    assert(0);
  }
  grid[current_coord.first][current_coord.second].second = true;
  // same as before, but in the end flag the path
  while (grid[current_coord.first][current_coord.second].first != 'S') {
    auto current_copy = current_coord;
    if (grid[current_coord.first][current_coord.second].first == '|') {
      current_coord.first += (current_coord.first > prev_coord.first) ? 1 : -1;
    } else if (grid[current_coord.first][current_coord.second].first == '-') {
      current_coord.second +=
          (current_coord.second > prev_coord.second) ? 1 : -1;
    } else if (grid[current_coord.first][current_coord.second].first == 'L') {
      if (current_coord.first > prev_coord.first) {
        current_coord.second++;
      } else {
        current_coord.first--;
      }
    } else if (grid[current_coord.first][current_coord.second].first == 'J') {
      if (current_coord.first > prev_coord.first) {
        current_coord.second--;
      } else {
        current_coord.first--;
      }
    } else if (grid[current_coord.first][current_coord.second].first == '7') {
      if (current_coord.first < prev_coord.first) {
        current_coord.second--;
      } else {
        current_coord.first++;
      }
    } else if (grid[current_coord.first][current_coord.second].first == 'F') {
      if (current_coord.first < prev_coord.first) {
        current_coord.second++;
      } else {
        current_coord.first++;
      }
    } else {
      assert(0);
    }
    grid[current_coord.first][current_coord.second].second = true;
    prev_coord = current_copy;
  }
  // determine what must be S
  if (found == 1) {
    // path started with north, can finish with either s,e,w
    if (prev_coord.first > current_coord.first) {
      grid[current_coord.first][current_coord.second].first = '|';
    } else if (prev_coord.second > current_coord.second) {
      grid[current_coord.first][current_coord.second].first = 'L';
    } else {
      grid[current_coord.first][current_coord.second].first = 'J';
    }
  }
  if (found == 2) {
    // path started with south, can finish with either n,e,w
    if (prev_coord.first < current_coord.first) {
      grid[current_coord.first][current_coord.second].first = '|';
    } else if (prev_coord.second > current_coord.second) {
      grid[current_coord.first][current_coord.second].first = 'F';
    } else {
      grid[current_coord.first][current_coord.second].first = '7';
    }
  }
  if (found == 3) {
    // path started with west, can finish with either n,s,e
    if (prev_coord.first < current_coord.first) {
      grid[current_coord.first][current_coord.second].first = 'J';
    } else if (prev_coord.first > current_coord.first) {
      grid[current_coord.first][current_coord.second].first = '7';
    } else {
      grid[current_coord.first][current_coord.second].first = '-';
    }
  }
  // applying the nonzero-rule: https://en.wikipedia.org/wiki/Nonzero-rule
  // https://www.reddit.com/r/adventofcode/comments/18eza5g/2023_day_10_animated_visualization/
  int inner_gaps = 0;
  for (int i = 0; i < grid.size() - 1; i++) {
    // each line (of the path) will start with an arrow up with a south neighbor
    bool arrow_up_with_south_neighbor = false;
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j].second &&
          (grid[i][j].first == '|' || grid[i][j].first == '7' ||
           grid[i][j].first == 'F')) {
        // the negation is equivalent to reversing the arrow, i.e. going down
        arrow_up_with_south_neighbor = !arrow_up_with_south_neighbor;
      }
      // not in arrow, last arrow was pointing up, and not insde the path
      else if (arrow_up_with_south_neighbor && !grid[i][j].second) {
        inner_gaps++;
      }
    }
    // last arrow (if any) must be pointing down
    assert(!arrow_up_with_south_neighbor);
  }
  std::cout << inner_gaps << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}