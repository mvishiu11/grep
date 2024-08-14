#ifndef GREP_UTILS_HPP
#define GREP_UTILS_HPP

#include <string>
#include <vector>

/**
 * @brief Calculates the logical length of a pattern, ignoring quantifiers and other meta-characters.
 * 
 * @param pattern The regex pattern.
 * @return size_t The logical length of the pattern.
 */
size_t calculate_logical_pattern_length(const std::string& pattern);

/**
 * @brief Generates patterns with optional characters based on the '?' quantifier.
 * 
 * @param pattern The regex pattern with optional characters.
 * @return std::vector<std::string> The vector of all possible patterns.
 */
std::vector<std::string> generate_patterns_with_optional(const std::string& pattern);

/**
 * @brief Splits a pattern by the '|' character.
 * 
 * @param pattern The regex pattern to split.
 * @return std::vector<std::string> The vector of subpatterns.
 */
std::vector<std::string> split_pattern_by_pipe(const std::string& pattern);

/**
 * @brief Splits a pattern by the '.' character (wildcard).
 * 
 * @param pattern The regex pattern to split.
 * @return std::vector<std::string> The vector of subpatterns.
 */
std::vector<std::string> split_pattern_by_wildcard(const std::string& pattern);

/**
 * @brief Checks for a capture group pattern within the regex.
 * 
 * @param pattern The regex pattern containing a capture group.
 * @return std::pair<std::string, size_t> The capture group and its position.
 */
std::pair<std::string, size_t> check_for_capture_group_pattern(const std::string& pattern);

#endif // GREP_UTILS_HPP
