#ifndef GREP_MATCHER_HPP
#define GREP_MATCHER_HPP

#include <string>
#include <vector>

/**
 * @brief Matches a pattern at a specific position within the input string.
 * 
 * @param input_line The line of text to search within.
 * @param pattern The regex pattern to match.
 * @param input_pos The position to start matching from.
 * @return std::pair<std::string, bool> The matched string and success status.
 */
std::pair<std::string, bool> match_pattern_at_position(const std::string& input_line, const std::string& pattern, size_t input_pos);

/**
 * @brief Matches a pattern against an input line. Adds support for line anchors.
 * 
 * @param input_line The line of text to search within.
 * @param pattern The regex pattern to match.
 * @return std::pair<std::string, bool> The matched string and success status.
 */
std::pair<std::string, bool> match_pattern(const std::string& input_line, const std::string& pattern);

/**
 * @brief Matches a pattern with wildcard support.
 * 
 * @param input_line The line of text to search within.
 * @param pattern The regex pattern to match.
 * @return std::pair<std::string, bool> The matched string and success status.
 */
std::pair<std::string, bool> match_pattern_with_wildcards(const std::string& input_line, const std::string& pattern);

/**
 * @brief Matches a pattern considering all cases (wildcards, options, etc.).
 * 
 * @param input_line The line of text to search within.
 * @param pattern The regex pattern to match.
 * @return std::pair<std::string, bool> The matched string and success status.
 */
std::pair<std::string, bool> match_pattern_all_cases(const std::string& input_line, const std::string& pattern);

/**
 * @brief Matches a pattern with alternation (pattern1|pattern2).
 * 
 * @param input_line The line of text to search within.
 * @param pattern The regex pattern to match.
 * @return std::pair<std::string, bool> The matched string and success status.
 */
std::pair<std::string, bool> match_pattern_with_alternatives(const std::string& input_line, const std::string& pattern);

/**
 * @brief Matches a pattern against an input line with backreference support.
 * 
 * @param input_line The line of text to search within.
 * @param pattern The regex pattern to match.
 * @return std::pair<std::string, bool> The matched string and success status.
 */
std::pair<std::string, bool> match_pattern_with_backref(const std::string& input_line, const std::string& pattern);

#endif // GREP_MATCHER_HPP