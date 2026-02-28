#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <algorithm>

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

// Function to calculate Mean (mu)
double calculateMean(const std::vector<double>& data, const std::vector<bool>& mask) {
    double sum = 0;
    int count = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        if (mask[i]) { // If mask[i] is true, it's included
            sum += data[i];
            count++;
        }
    }
    if (count == 0) return 0.0;
    return sum / count;
}

// Function to calculate Sample Standard Deviation (sigma)
double calculateStdDev(const std::vector<double>& data, const std::vector<bool>& mask, double mu) {
    double sum_sq_diff = 0;
    int count = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        if (mask[i]) {
            sum_sq_diff += std::pow(data[i] - mu, 2);
            count++;
        }
    }
    if (count <= 1) return 0.0; //needs N-1 > 0
    return std::sqrt(sum_sq_diff / (count - 1));
}

double calculateStdError(double sigma, size_t N) {
    if (N == 0) return 0.0; // Avoid division by zero
    return sigma / std::sqrt(N);
}

std::vector<bool> yearMask(const std::vector<std::string>& codes, int targetYear) {
    std::vector<bool> mask(codes.size(), false);
    char targetChar = targetYear + '0'; // Convert year to corresponding character

    for (size_t i = 0; i < codes.size(); ++i) {
        // Check if the code is not empty and if the first character matches the target year
        if (!codes[i].empty() && codes[i][0] == targetChar) {
            mask[i] = true;
        }
    }
    return mask;
}

int main() {
    // Vectors to store the columns
    std::vector<double> marks;
    std::vector<std::string> unit_codes;
    std::vector<std::string> unit_names;
    std::vector<bool> mask; //Make mask vector to store which entries are included in the statistics calculations

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

    mask.assign(marks.size(), true); // Initially, all entries are included in the statistics calculations

    // Verification output
    std::cout << "Successfully loaded " << marks.size() << " entries." << std::endl;

    //check();

    std::cout << "Do you want to calculate statistics for a specific year? (y/n): " <<std::endl;
    char choice;
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        std::cout << "Enter the year (1, 2, 3 or 4): " << std::endl;
        int year;
        std::cin >> year;

        mask = yearMask(unit_codes, year); // Update the mask based on the selected year

        std::vector<double> yearMarks;
    }

    int N = std::count(mask.begin(), mask.end(), true); // Count how many entries are true in the mask

    if (N > 0) {
        //pass same mask to every function
        double mu = calculateMean(marks, mask);
        double sigma = calculateStdDev(marks, mask, mu);
        double sigma_mu = calculateStdError(sigma, N);

        std::cout << "\nEntries:    " << N << std::endl;
        std::cout << "Mean:       " << std::fixed << std::setprecision(2) << mu << std::endl;
        std::cout << "Std Dev:    " << sigma << std::endl;
        std::cout << "Std Error:  " << sigma_mu << std::endl;
    }

    return 0;
}