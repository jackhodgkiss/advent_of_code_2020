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

auto decode_seat = [](const auto& seat)
{
    auto result = 0;
    auto lower_upper_rows = std::pair<int, int>(0, 127);
    auto lower_upper_columns = std::pair<int, int>(0, 7);
    auto decoded_row_column = std::pair<int, int>(0, 0);
    for(auto counter = 0; counter < seat.size(); counter++)
    {
        auto character = seat[counter];
        if(counter < 7)
        {
            float row_range = lower_upper_rows.second - lower_upper_rows.first;
            if(character == 'F') { lower_upper_rows.second -= std::ceil(row_range / 2); }
            else { lower_upper_rows.first += std::ceil(row_range / 2); }
        }
        else
        {
            float column_range = lower_upper_columns.second - lower_upper_columns.first;
            if(character == 'L') { lower_upper_columns.second -= std::ceil(column_range / 2); }
            else { lower_upper_columns.first += std::ceil(column_range / 2); }
        }
    }
    decoded_row_column = std::pair<int, int>(lower_upper_rows.first, lower_upper_columns.first);
    result = decoded_row_column.first * 8 + decoded_row_column.second;
    return result;
};

auto find_missing_seat = [](auto decoded_seat_ids)
{
    auto result = 0;
    std::sort(decoded_seat_ids.begin(), decoded_seat_ids.end());
    for(auto counter = decoded_seat_ids[0]; counter < decoded_seat_ids[decoded_seat_ids.size() - 1]; counter++)
    {
        auto index = counter - decoded_seat_ids[0];
        if(counter != decoded_seat_ids[index]) { result = counter; break; }
    }
    return result;
};

auto main(int argc, char** argv) -> int
{
    auto answer = std::pair<int, int>();
    auto airline_seats = read_puzzle_input("../puzzle_input/day_05.txt");
    auto decoded_seat_ids = std::vector<int>();
    std::transform(airline_seats.begin(), airline_seats.end(), std::back_inserter(decoded_seat_ids), decode_seat);
    answer.first = *std::max_element(decoded_seat_ids.begin(), decoded_seat_ids.end());
    answer.second = find_missing_seat(decoded_seat_ids);
    std::cout << "Answer Part One: " << answer.first << "\nAnswer Part Two: " << answer.second << "\n";
    return 0;
}