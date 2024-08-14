#include "Grep/Matcher.hpp"
#include <iostream>
#include <string>
#include <chrono>

int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // Start timing
    auto start_time = std::chrono::high_resolution_clock::now();

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    std::string input_line;
    std::getline(std::cin, input_line);
    
    try {
        auto res = match_pattern_with_backref(input_line, pattern);
        bool result = res.second;
        std::string matched_string = res.first;
        
        // Stop timing
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        
        std::cout << "Result: " << (result ? "true" : "false") << std::endl;
        std::cout << "Matched String: " << matched_string << std::endl;
        std::cout << "Execution time: " << duration << " microseconds" << std::endl;

        int return_val = result ? 0 : 1;
        std::cout << "Return value: " << return_val << std::endl;
        return return_val;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
