#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

auto read_puzzle_input(std::string filepath) -> std::vector<int>
{
    auto result = std::vector<int>(); 
    std::ifstream file(filepath);
    for(std::string line; getline(file, line);) { result.emplace_back(std::stoi(line)); }
    return result;
}

auto find_desired_entries(const std::vector<int>& expense_report) -> std::pair<int, int>
{
    auto result = std::pair<int, int>();
    std::for_each(expense_report.begin(), expense_report.end(), 
        [&](auto const& first_entry) mutable
        { 
            std::for_each(expense_report.rbegin(), expense_report.rend(), 
            [&](auto const& second_entry) mutable
            {
                if(first_entry + second_entry == 2020) { result = std::pair<int, int>(first_entry, second_entry); }
            });
        });
    return result;    
}

int main(int argc, char** argv) 
{
    int answer = 0;
    auto expense_report = read_puzzle_input("../puzzle_input/day_01.txt");
    auto desired_entries = find_desired_entries(expense_report);
    answer = desired_entries.first * desired_entries.second;
    std::cout << "Answer: " << answer << "\n";
    return 0;
}