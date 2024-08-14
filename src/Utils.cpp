#include "Grep/Utils.hpp"
#include <stdexcept>

/**
 * @brief Calculates the logical length of a pattern, ignoring quantifiers and other meta-characters.
 */
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

/**
 * @brief Generates patterns with optional characters based on the '?' quantifier.
 */
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

/**
 * @brief Splits a pattern by the '|' character.
 */
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

/**
 * @brief Splits a pattern by the '.' character (wildcard).
 */
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
        std::pair<std::string, int> capture_group_pattern = std::pair<std::string, int>(capture_group, initial_pos);
        return capture_group_pattern;
    }

    return std::pair<std::string, int>("", -1);
}