#include <map>
#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

auto read_puzzle_input(std::string filepath) -> std::vector<std::string>
{
    auto result = std::vector<std::string>(); 
    std::ifstream file(filepath);
    for(std::string line; std::getline(file, line);) { result.emplace_back(line); }
    return result;
}

auto tokenize_buffer(const std::vector<std::string>& buffer) -> std::map<std::string, std::string>
{
    auto result = std::map<std::string, std::string>();
    std::regex expression("(\\w+)|(\\#\\S+)");
    for(const auto& line : buffer)
    {
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), expression);
        auto words_end = std::sregex_iterator();
        for(std::sregex_iterator iter = words_begin; iter != words_end; std::advance(iter, 2))
        {
            auto field_match = *iter;
            std::string field_name = field_match.str();
            auto value_match = *std::next(iter);
            std::string field_value = value_match.str();
            result.emplace(field_name, field_value);
        }
    }
    return result;
}

auto is_valid_passport(const std::map<std::string, std::string>& passport) -> bool
{
    auto result = false;
    if(passport.size() == 8 || (passport.count("cid") == 0 && passport.size() == 7)) { result = true; }
    return result;
}

auto count_valid_passports(const std::vector<std::string>& passport_batch_file) -> int
{
    auto result = 0;
    std::vector<std::string> buffer;
    for(auto line : passport_batch_file)
    {
        if(line != "") { buffer.emplace_back(line); }
        else
        {
            auto tokenized_buffer = tokenize_buffer(buffer);
            if(is_valid_passport(tokenized_buffer)) { result++; }
            buffer.clear();     
        }
    }
    auto tokenized_buffer = tokenize_buffer(buffer);
    if(is_valid_passport(tokenized_buffer)) { result++; }
    return result;
}

auto main(int argc, char** argv) -> int
{
    auto answer = std::pair<int, int>();
    auto passport_batch_file = read_puzzle_input("../puzzle_input/day_04.txt");
    answer.first = count_valid_passports(passport_batch_file);
    std::cout << "Answer Part One: " << answer.first << "\nAnswer Part Two: " << answer.second << "\n";
    return 0;
}