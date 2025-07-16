# Markdown to HTML Transpiler

[![License: MIT](https://img.shields.io/github/license/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](LICENSE)
[![Language: C++](https://img.shields.io/github/languages/top/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/search?l=cpp)
[![Last Commit](https://img.shields.io/github/last-commit/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/commits/main)
[![Open Issues](https://img.shields.io/github/issues/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/issues)
[![Open PRs](https://img.shields.io/github/issues-pr/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/pulls)
[![Stars](https://img.shields.io/github/stars/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/stargazers)
[![Forks](https://img.shields.io/github/forks/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/network/members)
[![Repo Size](https://img.shields.io/github/repo-size/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp)
[![Platform: CMake](https://img.shields.io/badge/platform-cmake-blue?style=flat-square)](https://cmake.org/)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/actions)
[![C++ Version](https://img.shields.io/badge/C%2B%2B-17-blue?style=flat-square&logo=c%2B%2B)](https://isocpp.org/)
[![Code Lines](https://img.shields.io/tokei/lines/github/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp)
[![GitHub Contributors](https://img.shields.io/github/contributors/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/graphs/contributors)
[![GitHub Commits](https://img.shields.io/github/commit-activity/t/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/commits)
[![GitHub Release](https://img.shields.io/github/v/release/simonpierreboucher02/md_to_html_transpiler_cpp?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/releases)
[![GitHub Downloads](https://img.shields.io/github/downloads/simonpierreboucher02/md_to_html_transpiler_cpp/total?style=flat-square)](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp/releases)

---

> **GitHub Repo:** [simonpierreboucher02/md_to_html_transpiler_cpp](https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp)
> 
> **👨‍💻 Author:** [Simon Pierre Boucher](https://github.com/simonpierreboucher02)

A C++ implementation of a Markdown to HTML transpiler that demonstrates compiler design principles including lexical analysis, parsing, and code generation.

## 🚀 Features

- **Headers**: Support for `#` to `######` (H1-H6)
- **Text Formatting**: **Bold**, *Italic*, `Inline Code`
- **Lists**: Unordered lists with `-`, `*`, `+`
- **Code Blocks**: Triple backtick code blocks
- **Links**: `[text](url)` syntax
- **Images**: `![alt](url)` syntax
- **Horizontal Rules**: `---` or `***`
- **Clean HTML Output**: Semantic HTML with CSS styling

## 📁 Project Structure

```
markdown-transpiler/
├── include/
│   └── transpiler.hpp          # Main header with all classes and structures
├── src/
│   ├── main.cpp               # Command-line interface and main program
│   ├── lexer.cpp              # Lexical analysis implementation
│   ├── parser.cpp             # Parsing implementation
│   ├── generator.cpp          # HTML generation implementation
├── examples/
│   └── demo.md               # Example markdown file for testing
├── build/                    # Build directory (created during build)
├── CMakeLists.txt           # CMake configuration
└── README.md               # This file
```

## 🧠 Compiler Pipeline

The transpiler follows a classic three-stage compiler pipeline:

1. **Lexer (Tokenizer)**: Scans the Markdown text and splits it into tokens
2. **Parser**: Builds a logical structure (tree) from the tokens
3. **Generator**: Converts the structure into HTML tags

### Example Pipeline

**Input Markdown:**
```markdown
# Hello World
This is **bold** text.
- Item 1
- Item 2
```

**Lexer Output:**
```
Token(HEADER, "Hello World")
Token(PARAGRAPH, "This is **bold** text.")
Token(LIST_ITEM, "Item 1")
Token(LIST_ITEM, "Item 2")
```

**Parser Output:**
```
Element("h1", "Hello World")
Element("p", "This is <strong>bold</strong> text.")
Element("ul", [
  Element("li", "Item 1"),
  Element("li", "Item 2")
])
```

**Generator Output:**
```html
<h1>Hello World</h1>
<p>This is <strong>bold</strong> text.</p>
<ul>
  <li>Item 1</li>
  <li>Item 2</li>
</ul>
```

## 🛠️ Building the Project

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or higher

### Build Instructions

1. **Clone or download the project**
   ```bash
   git clone https://github.com/simonpierreboucher02/md_to_html_transpiler_cpp.git
   cd md_to_html_transpiler_cpp
   ```

2. **Create build directory**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake**
   ```bash
   cmake ..
   ```

4. **Build the project**
   ```bash
   cmake --build .
   ```

5. **Install (optional)**
   ```bash
   cmake --install .
   ```

## 📖 Usage

### Command Line Interface

```bash
./markdown-transpiler <input_file> [output_file]
```

### Examples

```bash
# Convert demo.md to output.html
./markdown-transpiler examples/demo.md

# Convert with custom output filename
./markdown-transpiler examples/demo.md my_output.html

# Convert any markdown file
./markdown-transpiler my_document.md
```

### Example Input/Output

**Input (`demo.md`):**
```markdown
# My Title

This is **bold** and *italic* text.

- Item 1
- Item 2

---

Visit [GitHub](https://github.com) for more info.
```

**Output (`output.html`):**
```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Generated from Markdown</title>
    <style>
        body { font-family: Arial, sans-serif; line-height: 1.6; margin: 40px; }
        h1, h2, h3, h4, h5, h6 { color: #333; }
        code { background-color: #f4f4f4; padding: 2px 4px; border-radius: 3px; }
        pre { background-color: #f4f4f4; padding: 10px; border-radius: 5px; overflow-x: auto; }
        ul, ol { padding-left: 20px; }
        hr { border: none; border-top: 1px solid #ccc; margin: 20px 0; }
    </style>
</head>
<body>
    <h1>My Title</h1>
    <p>This is <strong>bold</strong> and <em>italic</em> text.</p>
    <ul>
        <li>Item 1</li>
        <li>Item 2</li>
    </ul>
    <hr>
    <p>Visit <a href="https://github.com">GitHub</a> for more info.</p>
</body>
</html>
```

## 🔧 Technical Details

### Token Types

The lexer recognizes these token types:
- `HEADER`: `# ## ###` etc.
- `LIST_ITEM`: `- * +` 
- `PARAGRAPH`: Regular text
- `BOLD`: `**text**`
- `ITALIC`: `*text*` or `_text_`
- `CODE_INLINE`: `` `code` ``
- `CODE_BLOCK`: ``` ```code``` ```
- `HR`: `---` or `***`
- `LINK`: `[text](url)`
- `IMAGE`: `![alt](url)`
- `TEXT`: Plain text
- `NEWLINE`: Line break

### Element Structure

```cpp
struct Element {
    std::string tag;                    // HTML tag name
    std::string content;                // Text content
    std::vector<std::string> attributes; // HTML attributes
    std::vector<std::shared_ptr<Element>> children; // Nested elements
};
```

## 🎯 What This Project Demonstrates

- **C++ Modern Features**: Smart pointers, regex, string manipulation
- **Compiler Design**: Lexical analysis, parsing, code generation
- **Clean Architecture**: Separation of concerns, modular design
- **Error Handling**: Robust file I/O and error reporting
- **Documentation**: Comprehensive comments and examples

## 🚀 Future Enhancements

- [ ] Ordered lists (`1. 2. 3.`)
- [ ] Nested lists support
- [ ] Tables support
- [ ] Blockquotes (`> text`)
- [ ] Syntax highlighting for code blocks
- [ ] Custom CSS themes
- [ ] Table of contents generation
- [ ] Math formula support (LaTeX)

## 📝 License

This project is open source and available under the MIT License.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📚 References

- [Markdown Specification](https://spec.commonmark.org/)
- [C++ Standard Library](https://en.cppreference.com/)
- [CMake Documentation](https://cmake.org/documentation/)

---

*Built with ❤️ in C++* 