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

auto is_valid_passport(const std::map<std::string, std::string>& passport, bool use_full_validation) -> bool
{
    auto result = false;
    auto birth_year_validation = [](const auto& birth_year) 
    { 
        auto birth_year_as_number = std::stoi(birth_year); 
        if(birth_year_as_number >= 1920 && birth_year_as_number <= 2002) { return true; }
        return false;
    };
    auto issue_year_validation = [](const auto& issue_year)
    {
        auto issue_year_as_number = std::stoi(issue_year); 
        if(issue_year_as_number >= 2010 && issue_year_as_number <= 2020) { return true; }
        return false;
    };
    auto expiration_year_validation = [](const auto& expiration_year)
    {
        auto expiration_year_as_number = std::stoi(expiration_year); 
        if(expiration_year_as_number >= 2020 && expiration_year_as_number <= 2030) { return true; }
        return false;
    };
    auto height_validation = [](const auto& height)
    {
        std::regex expression("([0-9]+)|(\\w+)");
        auto regex_begin_iter = std::sregex_iterator(height.begin(), height.end(), expression);
        if(std::distance(regex_begin_iter, std::sregex_iterator()) == 2) 
        {
            auto value = std::stoi(regex_begin_iter->str());
            if(std::next(regex_begin_iter)->str() == "cm") { if(value >= 150 && value <= 193) { return true; } }
            else { if(value >= 59 && value <= 76) { return true; } }
            return false;
        }
        return false;
    };
    auto hair_color_validation = [](const auto& hair_color)
    {
        std::regex expression("#([a-f|0-9]){6}");
        auto regex_begin_iter = std::sregex_iterator(hair_color.begin(), hair_color.end(), expression);
        if(regex_begin_iter->length() == 7) { return true; }
        return false;
    };
    auto passport_id_validation = [](const auto& passport_id)
    {
        std::regex expression("^[0-9]{9}$");
        auto regex_begin_iter = std::sregex_iterator(passport_id.begin(), passport_id.end(), expression);
        if(regex_begin_iter->length() == 9) { return true; }
        return false;
    };
    auto eye_color_validation = [](const auto& eye_color)
    {
        if(eye_color == "amb" || eye_color == "blu" || eye_color == "brn" || eye_color == "gry" 
        || eye_color == "grn" || eye_color == "hzl" || eye_color == "oth") { return true; }
        return false;
    };
    if(passport.size() == 8 || (passport.count("cid") == 0 && passport.size() == 7)) 
    { 
        result = true;
        if(use_full_validation)
        {
            if(!birth_year_validation(passport.at("byr"))) { result = false; }
            if(!issue_year_validation(passport.at("iyr"))) { result = false; }
            if(!expiration_year_validation(passport.at("eyr"))) { result = false; }
            if(!eye_color_validation(passport.at("ecl"))) { result = false; }
            if(!height_validation(passport.at("hgt"))) { result = false; }
            if(!hair_color_validation(passport.at("hcl"))) { result = false; };
            if(!passport_id_validation(passport.at("pid"))) { result = false; };
        }        
    }
    return result;
}

auto count_valid_passports(const std::vector<std::string>& passport_batch_file, bool use_full_validation) -> int
{
    auto result = 0;
    std::vector<std::string> buffer;
    for(auto line : passport_batch_file)
    {
        if(line != "") { buffer.emplace_back(line); }
        else
        {
            auto tokenized_buffer = tokenize_buffer(buffer);
            if(is_valid_passport(tokenized_buffer, use_full_validation)) { result++; }
            buffer.clear();     
        }
    }
    auto tokenized_buffer = tokenize_buffer(buffer);
    if(is_valid_passport(tokenized_buffer, use_full_validation)) { result++; }
    return result;
}

auto main(int argc, char** argv) -> int
{
    auto answer = std::pair<int, int>();
    auto passport_batch_file = read_puzzle_input("../puzzle_input/day_04.txt");
    answer.first = count_valid_passports(passport_batch_file, false);
    answer.second = count_valid_passports(passport_batch_file, true);
    std::cout << "Answer Part One: " << answer.first << "\nAnswer Part Two: " << answer.second << "\n";
    return 0;
}