#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

int check() {
    std::ifstream input_file("course_marks.dat");

    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open 'course_marks.dat'. Check if the file exists!" << std::endl;
        return 1;
    }

    double temp_mark;
    std::string temp_code;
    std::string temp_name;

    while (input_file >> temp_mark >> temp_code) {
        std::getline(input_file >> std::ws, temp_name); 
        std::cout << "Mark: " << temp_mark << ", Code: " << temp_code << ", Name: " << temp_name << std::endl;
    }

    input_file.close();
    return 0;
}

int main() {
    // Vectors to store the columns
    std::vector<double> marks;
    std::vector<std::string> unit_codes;
    std::vector<std::string> unit_names;

    std::ifstream input_file("course_marks.dat");

    // Check if the file actually opened
    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open 'course_marks.dat'. Check if the file exists!" << std::endl;
        return 1;
    }

    double temp_mark;
    std::string temp_code;
    std::string temp_name;

    // Reading logic: 
    // 1. Read the mark (double)
    // 2. Read the unit code (string, no spaces)
    // 3. Use std::ws to discard leading whitespace, then getline for the rest of the line
    while (input_file >> temp_mark >> temp_code) {
        std::getline(input_file >> std::ws, temp_name); 
        
        marks.push_back(temp_mark);
        unit_codes.push_back(temp_code);
        unit_names.push_back(temp_name);
    }

    input_file.close();

    // Verification output
    std::cout << "Successfully loaded " << marks.size() << " entries." << std::endl;

    check();

    return 0;
}