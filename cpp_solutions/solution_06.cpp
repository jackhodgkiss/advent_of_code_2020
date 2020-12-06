#include <map>
#include <string>
#include <vector>
#include <numeric>
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

auto identify_questions_answered = [](const auto group_buffer)
{
    auto result = std::vector<char>();
    for(auto buffer_entry : group_buffer)
    {
        for(auto question_id : buffer_entry)
        {
            auto find_iter = std::find(result.begin(), result.end(), question_id);
            if(find_iter == result.end()) { result.emplace_back(question_id); }
        }
    }
    return result;
};

auto get_answer_count = [](const auto& collected_answers)
{
    auto question_to_frequency = std::map<char, int>();
    for(auto character_int = (int) 'a'; character_int <= (int) 'z'; character_int++) 
    { question_to_frequency.insert(std::make_pair<char, int>((char)character_int, 0)); }
    auto group_buffer = std::vector<std::string>();
    for(auto line : collected_answers)
    {
        if(line != "") { group_buffer.emplace_back(line); }
        else
        {
            auto group_response = identify_questions_answered(group_buffer);
            for(auto question_id : group_response)
            {
                question_to_frequency[question_id] += 1;
            }
            group_buffer.clear();
        }
    }
    auto group_response = identify_questions_answered(group_buffer);
    for(auto question_id : group_response)
    {
        question_to_frequency[question_id] += 1;
    }
    return question_to_frequency;
};

auto identify_questions_answered_by_group = [](const auto group_buffer)
{
    auto result = std::vector<char>();
    auto question_to_frequency = std::map<char, int>();
    for(auto character_int = (int) 'a'; character_int <= (int) 'z'; character_int++);
    for(auto buffer_entry : group_buffer)
    {
        for(auto question_id : buffer_entry)
        {
            question_to_frequency[question_id] += 1;
        }
    }
    auto group_size = group_buffer.size();
    for(auto iter : question_to_frequency) { if(iter.second == group_size) { result.emplace_back(iter.first); } }
    return result;
};

auto get_real_answer_count = [](const auto& collected_answers)
{
    auto result = 0;
    auto group_buffer = std::vector<std::string>();
    for(auto line : collected_answers)
    {
        if(line != "") { group_buffer.emplace_back(line); }
        else
        {
            auto group_response = identify_questions_answered_by_group(group_buffer);
            result += group_response.size();
            group_buffer.clear();
        }
    }
    auto group_response = identify_questions_answered_by_group(group_buffer);
    result += group_response.size();
    return result;
};


auto main(int argc, char** argv) -> int
{
    auto answer = std::pair<int, int>();
    auto collected_answers = read_puzzle_input("../puzzle_input/day_06.txt");
    // std::for_each(collected_answers.begin(), collected_answers.end(), [](const auto& line) { std::cout << line << "\n"; });
    auto question_to_frequency = get_answer_count(collected_answers);
    answer.first = std::accumulate(question_to_frequency.begin(), question_to_frequency.end(), 0, 
        [](int sum, const std::map<char, int>::value_type& pair) { return sum + pair.second; });
    answer.second = get_real_answer_count(collected_answers);
    std::cout << "Answer Part One: " << answer.first << "\nAnswer Part Two: " << answer.second << "\n";
    return 0;
}