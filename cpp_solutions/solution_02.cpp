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

auto is_valid_password(const std::string& database_row, const bool& use_toboggan_policy) -> bool
{
    auto result = false;
    auto find_hyphen_iterator = std::find(database_row.begin(), database_row.end(), '-');
    auto find_space_iterator = std::find(database_row.begin(), database_row.end(), ' ');
    auto find_colon_iterator = std::find(database_row.begin(), database_row.end(), ':');
    auto lower_range = std::stoi(database_row.substr(0, find_hyphen_iterator - database_row.begin()));
    auto upper_range = std::stoi(database_row.substr(1 + find_hyphen_iterator - database_row.begin(), 
        find_space_iterator - database_row.begin() - 2));
    auto desired_character = *(find_space_iterator + 1);
    auto potential_password = database_row.substr(find_colon_iterator - database_row.begin() + 2);
    auto character_frequency = std::count(potential_password.begin(), potential_password.end(), desired_character);
    if(!use_toboggan_policy)
    {
        if(character_frequency >= lower_range && character_frequency <= upper_range) { result = true; }
    }
    else
    {
        auto character_at_lower = potential_password.at(lower_range - 1);
        auto character_at_upper = potential_password.at(upper_range - 1);
        if(character_at_lower != character_at_upper)
        {
            result = (desired_character == character_at_lower) 
                ? true : (desired_character == character_at_upper) ? true : false;
        }
    }
    return result;
}

auto main(int argc, char** argv) -> int
{
    auto answer = std::pair<int, int>();
    auto corrupted_database = read_puzzle_input("../puzzle_input/day_02.txt");
    auto valid_sled_database_rows = std::vector<std::string>();
    auto valid_toboggan_database_rows = std::vector<std::string>();
    std::for_each(corrupted_database.begin(), corrupted_database.end(), 
        [&](const auto& database_row) 
        { 
            if(is_valid_password(database_row, false)) 
            { 
                valid_sled_database_rows.emplace_back(database_row); 
            }
        }
    );
    std::for_each(corrupted_database.begin(), corrupted_database.end(), 
        [&](const auto& database_row) 
        { 
            if(is_valid_password(database_row, true)) 
            { 
                valid_toboggan_database_rows.emplace_back(database_row); 
            }
        }
    );
    answer.first = valid_sled_database_rows.size();
    answer.second = valid_toboggan_database_rows.size();
    std::cout << "Answer Part One: " << answer.first << "\nAnswer Part Two: " << answer.second << "\n";
    return 0;
}