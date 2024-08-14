#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <thread>

std::pair<std::string, bool> match_pattern_at_position(const std::string& input_line, const std::string& pattern, size_t input_pos) {
    size_t pattern_pos = 0;
    std::string matched_string = "";

    std::cout << "Starting match:\n";
    std::cout << "Pattern: \"" << pattern << "\"\n";
    std::cout << "Input Line: \"" << input_line << "\"\n";
    std::cout << "Initial Input Position: " << input_pos << "\n";

    while (pattern_pos < pattern.length() && input_pos < input_line.length()) {
        std::cout << "\nPattern Position: " << pattern_pos << ", Input Position: " << input_pos << "\n";

        if (pattern[pattern_pos] == '\\' && pattern_pos + 1 < pattern.length()) {
            char next_pattern_char = pattern[pattern_pos + 1];
            std::cout << "Escape sequence found: \\" << next_pattern_char << "\n";

            if (next_pattern_char == 'd') {
                std::cout << "Checking for a digit at Input[" << input_pos << "] = '" << input_line[input_pos] << "'\n";
                if (isdigit(input_line[input_pos])) {
                    //std::cout << "Matched digit: '" << input_line[input_pos] << "'\n";
                } else {
                    //std::cout << "Failed to match digit\n";
                    return std::pair<std::string, bool>("", false);
                }
            } else if (next_pattern_char == 'w') {
                //std::cout << "Checking for a word character at Input[" << input_pos << "] = '" << input_line[input_pos] << "'\n";
                if (isalnum(input_line[input_pos]) || input_line[input_pos] == '_') {
                    //std::cout << "Matched word character: '" << input_line[input_pos] << "'\n";
                } else {
                    //std::cout << "Failed to match word character\n";
                    return std::pair<std::string, bool>("", false);
                }
            }

            pattern_pos += 2;
            matched_string += input_line[input_pos];
            input_pos++;
        } else if (pattern[pattern_pos] == '[' && pattern_pos + 1 < pattern.length()) {
            bool is_negative = (pattern[pattern_pos + 1] == '^');
            size_t end_bracket_pos = pattern.find(']', pattern_pos);

            if (end_bracket_pos == std::string::npos) {
                throw std::runtime_error("Invalid pattern: unmatched '['");
            }

            std::string char_group = pattern.substr(pattern_pos + (is_negative ? 2 : 1), end_bracket_pos - pattern_pos - (is_negative ? 2 : 1));
            //std::cout << "Checking for character group [" << (is_negative ? "^" : "") << char_group << "] at Input[" << input_pos << "] = '" << input_line[input_pos] << "'\n";
            
            bool match = is_negative ? (char_group.find(input_line[input_pos]) == std::string::npos) : (char_group.find(input_line[input_pos]) != std::string::npos);

            if (match) {
                //std::cout << "Matched character group\n";
                pattern_pos = end_bracket_pos + 1;
                matched_string += input_line[input_pos];
                input_pos++;
            } else {
                //std::cout << "Failed to match character group\n";
                return std::pair<std::string, bool>("", false);
            }
        } else if (pattern_pos + 1 < pattern.length() && pattern[pattern_pos + 1] == '+') {
            char repeat_char = pattern[pattern_pos];
            //std::cout << "Checking for one or more '" << repeat_char << "' at Input[" << input_pos << "]\n";
            size_t match_count = 0;

            while (input_pos < input_line.length() && input_line[input_pos] == repeat_char) {
                std::cout << "Matched '" << repeat_char << "' at Input[" << input_pos << "]\n";
                matched_string += input_line[input_pos];
                input_pos++;
                match_count++;
            }

            if (match_count == 0) {
                std::cout << "Failed to match one or more '" << repeat_char << "'\n";
                return std::pair<std::string, bool>("", false);
            }

            pattern_pos += 2; // Skip past the character and the '+'
        } else {
            std::cout << "Checking for character literal: '" << pattern[pattern_pos] << "' at Input[" << input_pos << "] = '" << input_line[input_pos] << "'\n";
            if (input_line[input_pos] != pattern[pattern_pos]) {
                std::cout << "Failed to match character literal\n";
                return std::pair<std::string, bool>("", false);
            }

            pattern_pos++;
            matched_string += input_line[input_pos];
            input_pos++;
        }
    }

    std::cout << "[END MATCHING] Matched String: " << matched_string << std::endl;

    // Wait for a second to simulate a long running process
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return std::pair<std::string, bool>(matched_string, pattern_pos == pattern.length());
}

size_t calculate_logical_pattern_length(const std::string& pattern) {
    size_t logical_length = 0;
    size_t i = 0;

    while (i < pattern.length()) {
        if (pattern[i] == '\\' && i + 1 < pattern.length()) {
            // Handle escape sequences like \d or \w
            if(pattern[i + 1] == '1')
            {
                i += 2;
                continue;
            }
            logical_length++;
            i += 2;
        } else if (pattern[i] == '[') {
            // Handle character classes like [abc] or [^abc]
            size_t end_bracket_pos = pattern.find(']', i);
            if (end_bracket_pos == std::string::npos) {
                throw std::runtime_error("Invalid pattern: unmatched '['");
            }
            logical_length++;
            i = end_bracket_pos + 1;
        } else if (pattern[i] == '+' || pattern[i] == '?' || pattern[i] == '.' || pattern[i] == '|' || pattern[i] == '(' || pattern[i] == ')') {
            // The '+','?', '.'  and '|' quantifiers do not increase logical length
            if (logical_length == 0) {
                throw std::runtime_error("Invalid pattern: quantifier '" + std::string(1, pattern[i]) + "' cannot be at the start or after another quantifier.");
            }
            i++;
        } else {
            // Handle literal characters
            logical_length++;
            i++;
        }
    }

    return logical_length;
}

std::pair<std::string, bool> match_pattern(const std::string& input_line, const std::string& pattern) {
    std::cout << "Checking for pattern: " << pattern << std::endl;

    if (pattern.empty()) {
        return std::pair<std::string, bool>("", true);
    }

    if (pattern[0] == '^') {
        // Only try to match from the start of the input line
        return match_pattern_at_position(input_line, pattern.substr(1), 0);
    }

    if (pattern.back() == '$') {
        // Calculate logical pattern length without the trailing '$'
        size_t logical_pattern_length = calculate_logical_pattern_length(pattern.substr(0, pattern.length() - 1));

        // Only try to match the pattern at the end of the input line
        if (input_line.length() >= logical_pattern_length) {
            return match_pattern_at_position(input_line, pattern.substr(0, pattern.length() - 1), input_line.length() - logical_pattern_length);
        } else {
            return std::pair<std::string, bool>("", false);
        }
    }

    size_t logical_pattern_length = calculate_logical_pattern_length(pattern);

    // Try to match the pattern starting from every position in the input string
    for (size_t i = 0; i <= input_line.length() - logical_pattern_length; ++i) {
        std::cout << "Input line length: " << input_line.length() << ", Logical Pattern Length: " << logical_pattern_length << "\n";
        std::cout << "Starting match attempt from Input Position: " << i << std::endl;
        auto match_result = match_pattern_at_position(input_line, pattern, i);
        if (match_result.second) {
            std::cout << "Found: true" << std::endl;
            return match_result;
        }
    }

    std::cout << "Found: false" << std::endl;
    return std::pair<std::string, bool>("", false);
}

std::vector<std::string> generate_patterns_with_optional(const std::string& pattern) {
    std::vector<std::string> patterns;
    patterns.push_back("");  // Start with an empty base pattern

    for (size_t i = 0; i < pattern.length(); ++i) {
        if (i + 1 < pattern.length() && pattern[i + 1] == '?') {
            std::vector<std::string> new_patterns;
            for (const auto& base : patterns) {
                // Generate both versions: with and without the optional character
                new_patterns.push_back(base + pattern[i]);     // Include the optional character
                new_patterns.push_back(base);                  // Exclude the optional character
            }
            patterns = new_patterns;
            i++; // Skip the '?' character
        } else {
            for (auto& base : patterns) {
                base += pattern[i];
            }
        }
    }

    return patterns;
}

std::vector<std::string> split_pattern_by_wildcard(const std::string& pattern) {
    std::vector<std::string> subpatterns;
    std::string current_subpattern;

    for (char c : pattern) {
        if (c == '.') {
            if (!current_subpattern.empty()) {
                subpatterns.push_back(current_subpattern);
                current_subpattern.clear();
            }
            subpatterns.push_back(".");  // Add the wildcard itself as a subpattern
        } else {
            current_subpattern += c;
        }
    }

    if (!current_subpattern.empty()) {
        subpatterns.push_back(current_subpattern);
    }

    return subpatterns;
}

std::vector<std::string> split_pattern_by_pipe(const std::string& pattern) {
    std::vector<std::string> subpatterns;
    std::string current_subpattern;

    for (char c : pattern) {
        if (c == '|') {
            if (!current_subpattern.empty()) {
                subpatterns.push_back(current_subpattern);
                current_subpattern.clear();
            }
        }
        else if (c == '(' or c == ')') {
            continue;
        } else {
            current_subpattern += c;
        }
    }

    // Add the last subpattern if any
    if (!current_subpattern.empty()) {
        subpatterns.push_back(current_subpattern);
    }

    return subpatterns;
}

std::pair<std::string, bool> match_pattern_with_wildcards(const std::string& input_line, const std::string& pattern) {
    std::vector<std::string> subpatterns = split_pattern_by_wildcard(pattern);
    size_t current_pos = 0;
    std::string matched_string = "";

    for (const auto& subpattern : subpatterns) {
        if (subpattern == ".") {
            // Wildcard: match any single character
            if (current_pos >= input_line.length()) {
                return std::pair<std::string, bool>("", false);  // No character to match
            }
            current_pos++;  // Move past the wildcard match
            matched_string += '.';
        } else {
            // Try to find subpattern in the input line starting from current_pos
            auto match_result = match_pattern(input_line.substr(current_pos), subpattern);
            if (match_result.second == false) {
                return std::pair<std::string, bool>("", false);  // Subpattern not found or not in sequence
            }
            matched_string += match_result.first;
            current_pos += subpattern.length();
        }
    }

    return std::pair<std::string, bool>(matched_string, true);
}

std::pair<std::string, bool> match_pattern_all_cases(const std::string& input_line, const std::string& pattern) {
    bool result = false;
    std::string matched_string = "";

    if (pattern.find('?') != std::string::npos) {
        std::vector<std::string> patterns = generate_patterns_with_optional(pattern);
        for (const auto& p : patterns) {
            auto match_result = match_pattern_with_wildcards(input_line, p);
            if (match_result.second) {
                matched_string = match_result.first;
                result = true;
                break;
            }
        }
    } else if (pattern.find('.') != std::string::npos) {
        auto match_result = match_pattern_with_wildcards(input_line, pattern);
        result = match_result.second;
        matched_string = match_result.first;
    } else {
        auto match_result = match_pattern(input_line, pattern);
        result = match_result.second;
        matched_string = match_result.first;
    }

    return std::pair<std::string, bool>(matched_string, result);
}

std::pair<std::string, bool> match_pattern_with_alternatives(const std::string& input_line, const std::string& pattern) {
    std::vector<std::string> subpatterns = split_pattern_by_pipe(pattern);

    for (const auto& subpattern : subpatterns) {
        auto match_result = match_pattern_all_cases(input_line, subpattern);
        if (match_result.second) {
            return match_result;
        }
    }

    return std::pair<std::string, bool>("", false);
}

std::pair<std::string, size_t> check_for_capture_group_pattern(const std::string& pattern) {
    int initial_pos = 0;
    if (pattern.find('|') == std::string::npos) {
        initial_pos = pattern.find('(');
    }
    else {
        initial_pos = pattern.substr(1).find('(') + 1;
        if (initial_pos == std::string::npos) {
              throw std::runtime_error("Invalid pattern: backref unmatched by a capture group");
        }
    }
    if (initial_pos + 1 < pattern.length()) {
        size_t end_pos = pattern.find(')', initial_pos + 1);
        if (end_pos == std::string::npos) {
            throw std::runtime_error("Invalid pattern: unmatched '('");
        }

        std::string capture_group = pattern.substr(initial_pos + 1, end_pos - initial_pos - 1);
        std::cout << "Capture Group: " << capture_group << std::endl;
        std::pair<std::string, int> capture_group_pattern = std::pair<std::string, int>(capture_group, initial_pos);
        return capture_group_pattern;
    }

    return std::pair<std::string, int>("", -1);
}

std::pair<std::string, bool> match_pattern_with_backref(const std::string& input_line, const std::string& pattern) {
    if(pattern.find("\\1") == std::string::npos) {
        std::cout << "No backref found\n";
        return match_pattern_with_alternatives(input_line, pattern);
    }
    std::cout << "Backref found, checking for capture group\n";
    std::pair<std::string, size_t> capture_group_pattern = check_for_capture_group_pattern(pattern);
    if(capture_group_pattern.second == -1) {
        throw std::runtime_error("Invalid pattern: backref unmatched by a capture group");
    }
    std::string capture_group = capture_group_pattern.first;
    size_t capture_group_pos = capture_group_pattern.second;
    size_t backref_pos = pattern.find("\\1");

    std::string first_pattern = pattern.substr(capture_group_pos + capture_group.length() + 2, backref_pos);
    std::cout << "First Pattern: \"" << first_pattern << "\"" << std::endl;

    auto match_result = match_pattern_with_alternatives(input_line, first_pattern);
    if(!match_result.second) {
        return std::pair<std::string, bool>(match_result.first, false);
    }
    size_t matched_string_pos = input_line.find(match_result.first);
    auto capture_group_match = match_pattern_with_alternatives(input_line.substr(0, matched_string_pos), capture_group);
    if(!capture_group_match.second) {
        return std::pair<std::string, bool>(match_result.first, false);
    }
    std::string capture_group_match_string = capture_group_match.first;
    auto backref_match = match_pattern_with_alternatives(input_line.substr(matched_string_pos + match_result.first.length()), capture_group_match_string);
    if(!backref_match.second) {
        return std::pair<std::string, bool>(match_result.first, false);
    }
    return std::pair<std::string, bool>(capture_group_match_string + match_result.first + backref_match.first, true);
}

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

        return result ? 0 : 1;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
