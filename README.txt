This code is written by Jacob Fairham

This program takes in a dataset in the structure: grade(double)  unit_code(string) unit_name(string) and stores the data in three vectors
The relevant marks, codes, names and statistics are printed (number of entries, mean, standard deviation, standard error)
The user is prompted if they want to filter for a specific year
The user is prompted if they want to arrange the modules in alphabetical order
The user inputs are verified to ensure they are only the single digit/character required with no extra information
A mask is created to filter the data by the desired year
The statistical calculations ensure no division by zero errors occur

To compile: 'g++ grade_data.cpp -o grade_data.exe'
To run: '.\grade_data.exe'