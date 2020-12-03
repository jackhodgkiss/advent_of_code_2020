#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <iostream>
#include <algorithm>

auto read_puzzle_input(std::string filepath) -> std::vector<std::string>
{
    auto result = std::vector<std::string>(); 
    std::ifstream file(filepath);
    for(std::string line; std::getline(file, line);) { result.emplace_back(line); }
    return result;
}

auto find_tree_hit_count(const std::vector<std::string>& grid_map, 
    const std::vector<std::pair<int, int>>& routes) -> std::vector<int>
{
    auto result = std::vector<int>();
    for(const auto& route : routes)
    {
        auto hits = 0;
        auto row = 0;
        auto column = 0;
        while(row < grid_map.size())
        {
            if(grid_map[row][column] == '#') { hits++; }
            column += route.first; row += route.second;
            column = column % 31;
        }
        result.emplace_back(hits);
    }
    
    return result;
}

auto main(int argc, char** argv) -> int
{
    auto answer = std::pair<int, int>();
    auto grid_map = read_puzzle_input("../puzzle_input/day_03.txt");
    auto routes = std::vector<std::pair<int, int>> { 
        std::make_pair(1, 1), std::make_pair(3, 1), 
        std::make_pair(5, 1), std::make_pair(7, 1), 
        std::make_pair(1, 2) 
    };
    auto trees_hit_per_route = find_tree_hit_count(grid_map, routes);
    answer.first = trees_hit_per_route[1];
    answer.second = std::accumulate(trees_hit_per_route.begin(), trees_hit_per_route.end(), 1, std::multiplies<int>());
    std::cout << "Answer Part One: " << answer.first << "\nAnswer Part Two: " << answer.second << "\n";
    return 0;
}