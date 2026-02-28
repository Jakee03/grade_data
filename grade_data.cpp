#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <cmath>

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
double calculateMean(const std::vector<double>& data) {
    if (data.empty()) return 0.0;
    
    //sums up the vector from start to end
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

// Function to calculate Sample Standard Deviation (sigma)
double calculateStdDev(const std::vector<double>& data, double mu) {
    if (data.size() <= 1) return 0.0; // Avoid division by zero

    double sum_sq_diff = 0.0;
    for (double x : data) {
        sum_sq_diff += std::pow(x - mu, 2);
    }

    // Formula from slide
    return std::sqrt(sum_sq_diff / (data.size() - 1));
}

double calculateStdError(double sigma, size_t N) {
    if (N == 0) return 0.0; // Avoid division by zero
    return sigma / std::sqrt(N);
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

    //check();

    if (!marks.empty()) {
        double mu = calculateMean(marks);
        double sigma = calculateStdDev(marks, mu);
        double sigma_mu = calculateStdError(sigma, marks.size());

        std::cout << "Mean (mu): " << std::fixed << std::setprecision(2) << mu << std::endl;
        std::cout << "Std Deviation (sigma): " << sigma << std::endl;
        std::cout << "Standard Error (sigma_mu): " << sigma_mu << std::endl;
    }

    return 0;
}