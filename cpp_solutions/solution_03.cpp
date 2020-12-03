#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

auto read_puzzle_input(std::string filepath) -> std::vector<std::string>
{
    auto result = std::vector<std::string>(); 
    std::ifstream file(filepath);
    for(std::string line; std::getline(file, line);) { result.emplace_back(line); }
    return result;
}

auto find_tree_hit_count(const std::vector<std::string>& grid_map) -> int
{
    auto result = 0;
    auto row = 0;
    auto column = 0;
    while(row < grid_map.size())
    {
        auto current_location = grid_map[row][column];
        if(current_location == '#') { result++; }
        column += 3; row++;
        column = column % 31;
    }
    return result;
}

auto main(int argc, char** argv) -> int
{
    auto answer = std::pair<int, int>();
    auto grid_map = read_puzzle_input("../puzzle_input/day_03.txt");
    answer.first = find_tree_hit_count(grid_map);
    std::cout << "Answer Part One: " << answer.first << "\nAnswer Part Two: " << answer.second << "\n";
    return 0;
}