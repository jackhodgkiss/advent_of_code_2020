#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <iostream>
#include <algorithm>

auto read_puzzle_input(std::string filepath) -> std::vector<int>
{
    auto result = std::vector<int>(); 
    std::ifstream file(filepath);
    for(std::string line; getline(file, line);) { result.emplace_back(std::stoi(line)); }
    return result;
}

auto find_desired_entries(int target, int entry_count, const std::vector<int>& expense_report) -> std::vector<int>
{
    auto result = std::vector<int>();
    auto potential_entries = std::vector<int>();
    std::copy_if(expense_report.begin(), expense_report.end(), std::back_inserter(potential_entries), [target](auto entry) { return entry <= target; });
    for(auto first_iterator = potential_entries.begin(); first_iterator != potential_entries.end(); first_iterator++)
    {
        for(auto second_iterator = potential_entries.rbegin(); second_iterator != potential_entries.rend(); second_iterator++)
        {
            if(entry_count == 2)
            {
                auto sum = *first_iterator + *second_iterator;
                if(sum == target) { result.emplace_back(*first_iterator); result.emplace_back(*second_iterator); }
            }
            else
            {
                for(auto third_iterator = potential_entries.begin(); third_iterator != potential_entries.end(); third_iterator++)
                {
                    auto sum = *first_iterator + *second_iterator + *third_iterator;
                    if(sum == target) { result.emplace_back(*first_iterator); result.emplace_back(*second_iterator); result.emplace_back(*third_iterator); }
                }
                if(!result.empty()) { break; }
            }            
        }
        if(!result.empty()) { break; }
    }
    return result;    
}

auto main(int argc, char** argv) -> int
{
    auto answer = std::pair<int, int>();
    auto expense_report = read_puzzle_input("../puzzle_input/day_01.txt");
    auto desired_entries_double = find_desired_entries(2020, 2, expense_report);
    answer.first = std::accumulate(desired_entries_double.begin(), desired_entries_double.end(), 1, std::multiplies<int>());
    auto desired_entries_triple = find_desired_entries(2020, 3, expense_report);
    answer.second = std::accumulate(desired_entries_triple.begin(), desired_entries_triple.end(), 1, std::multiplies<int>());
    std::cout << "Answer Part One: " << answer.first << "\nAnswer Part Two: " << answer.second << "\n";
    return 0;
}