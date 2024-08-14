# 🛠️ Custom GREP Implementation

![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)
![License](https://img.shields.io/badge/license-MIT-red.svg)
![C++](https://img.shields.io/badge/language-C%2B%2B-blue.svg)

Welcome to the **Custom GREP Implementation** project! This project is a custom implementation of the classic `grep` utility, focusing on regular expression pattern matching. It supports various regex features, and the goal is to mirror many of the functionalities found in traditional `grep` tools.

---

## 📚 Table of Contents

- [Introduction](#introduction)
- [Supported Patterns](#supported-patterns)
  - [Literal Characters](#literal-characters)
  - [\d Pattern - Digits](#d-pattern---digits)
  - [\w Pattern - Alphanumerical Characters](#w-pattern---alphanumerical-characters)
  - [\[--\] Pattern - Positive Character Groups](#--pattern---positive-character-groups)
  - [\[^--\] Pattern - Negative Character Groups](#--pattern---negative-character-groups)
  - [^ Pattern - Start of String / Line Anchor](#-pattern---start-of-string--line-anchor)
  - [$ Pattern - End of String / Line Anchor](#-pattern---end-of-string--line-anchor)
  - [+ Pattern - "One or More" Quantifier](#-pattern---one-or-more-quantifier)
  - [? Pattern - "Zero or One" Quantifier](#-pattern---zero-or-one-quantifier--optional-quantifier)
  - [. Pattern - Wildcard](#-pattern---wildcard)
  - [(-|-) Pattern - Alternation Pattern](#--pattern---alternation-pattern)
- [Future Additions](#future-additions)
- [Setup and Usage](#setup-and-usage)
- [Implementation Details](#implementation-details)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

---

## Introduction

[Regular expressions](https://en.wikipedia.org/wiki/Regular_expression) (Regexes, for short) are patterns used to match character combinations in strings. [`grep`](https://en.wikipedia.org/wiki/Grep) is a CLI tool for searching using Regexes.

This project is a custom implementation that mirrors many features of `grep` when it comes to matching patterns defined by regexes within any text corpus. It's built in C++ and aims to be both educational and practical.

---

## Supported Patterns

### Literal Characters
Matches the exact sequence of characters in the input string.

**Example:**
```bash
$ echo "hello" | ./grep.sh -E "hello"
```

### \d Pattern - Digits
Matches any digit character `[0-9]`.

**Example:**
```bash
$ echo "2023" | ./grep.sh -E "\d\d\d\d"
```

### \w Pattern - Alphanumerical Characters
Matches any alphanumeric character `[a-zA-Z0-9_]`.

**Example:**
```bash
$ echo "hello123" | ./grep.sh -E "\w\w\w\w\w\d\d\d"
```

### \[--\] Pattern - Positive Character Groups
Matches any character within the specified group.

**Example:**
```bash
$ echo "hello" | ./grep.sh -E "[aeiou]"
```

### \[^--\] Pattern - Negative Character Groups
Matches any character NOT within the specified group.

**Example:**
```bash
$ echo "hello" | ./grep.sh -E "[^aeiou]"
```

### ^ Pattern - Start of String / Line Anchor
Matches the start of a string or line.

**Example:**
```bash
$ echo "hello" | ./grep.sh -E "^h"
```

### $ Pattern - End of String / Line Anchor
Matches the end of a string or line.

**Example:**
```bash
$ echo "hello" | ./grep.sh -E "o$"
```

### + Pattern - "One or More" Quantifier
Matches one or more occurrences of the preceding element.

**Example:**
```bash
$ echo "hellooo" | ./grep.sh -E "o+"
```

### ? Pattern - "Zero or One" Quantifier / Optional Quantifier
Matches zero or one occurrence of the preceding element.

**Example:**
```bash
$ echo "color" | ./grep.sh -E "colou?r"
```

### . Pattern - Wildcard
Matches any single character.

**Example:**
```bash
$ echo "dog" | ./grep.sh -E "d.g"
```

### (-|-) Pattern - Alternation Pattern
Matches either of the patterns separated by `|`.

**Example:**
```bash
$ echo "cat" | ./grep.sh -E "cat|dog"
```

---

## Future Additions

Planned future enhancements include:

- Support for single backreferences
- Handling multiple backreferences
- Nested backreferences

---

## Setup and Usage

1. **Ensure you have `cmake` installed locally.**
2. **Run `./grep.sh` to execute the program.** The main implementation is in `src/Server.cpp`.
3. **Example usage:**
    ```bash
    $ echo "cats and dogs" | ./grep.sh -E "cat."
    ```

   **Note:** The `.` character acts as a wildcard, matching any single character.

   **Example Result:**
   ```bash
   No backref found
   Checking for pattern: cat
   Input line length: 13, Logical Pattern Length: 3
   Starting match attempt from Input Position: 0
   Starting match:
   Pattern: "cat"
   Input Line: "cats and dogs"
   Initial Input Position: 0

   Pattern Position: 0, Input Position: 0
   Checking for character literal: 'c' at Input[0] = 'c'

   Pattern Position: 1, Input Position: 1
   Checking for character literal: 'a' at Input[1] = 'a'

   Pattern Position: 2, Input Position: 2
   Checking for character literal: 't' at Input[2] = 't'
   [END MATCHING] Matched String: cat
   Found: true
   Result: true
   Matched String: cat.
   Execution time: 1000334 microseconds
   ```

   **Notev2:** The program intelligently reduces patterns by eliminating unnecessary wildcards, making pattern matching more efficient.

---

## Implementation Details

### Literal Matching
This feature matches exact characters in the input string. It's the most basic form of pattern matching.

### Pattern Quantifiers
Quantifiers like `+` and `?` modify the behavior of the preceding element, allowing flexible pattern matching.

### Character Groups
Character groups and their negations (`[--]`, `[^--]`) provide powerful ways to match specific sets of characters.

### Anchors
Anchors like `^` and `$` allow you to match patterns at specific positions within the string.

### Wildcards
Wildcards match any character, making your patterns versatile.

### Alternation
The `(-|-)` pattern allows you to match one pattern or another, increasing the power of your regex.

---

## Contributing

Contributions are welcome! Please feel free to submit issues, feature requests, and pull requests.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- Inspired by the classic `grep` utility and [CodeCrafters project](https://app.codecrafters.io/courses/grep/introduction).
- Thanks to all contributors and supporters!