#ifndef TRANSPILER_HPP
#define TRANSPILER_HPP

#include <string>
#include <vector>
#include <memory>
#include <regex>

// Token types for the lexer
enum class TokenType {
    HEADER,         // # ## ### etc.
    LIST_ITEM,      // - * + 
    PARAGRAPH,      // Regular text
    BOLD,           // **text**
    ITALIC,         // *text* or _text_
    CODE_INLINE,    // `code`
    CODE_BLOCK,     // ```code```
    HR,             // --- or ***
    LINK,           // [text](url)
    IMAGE,          // ![alt](url)
    TEXT,           // Plain text
    NEWLINE,        // Line break
    END_OF_FILE     // End of input
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
    int line_number;
    
    Token(TokenType t, const std::string& v, int line = 0) 
        : type(t), value(v), line_number(line) {}
};

// Element structure for the parser
struct Element {
    std::string tag;                    // HTML tag name
    std::string content;                // Text content
    std::vector<std::string> attributes; // HTML attributes
    std::vector<std::shared_ptr<Element>> children; // Nested elements
    
    Element(const std::string& t = "", const std::string& c = "") 
        : tag(t), content(c) {}
    
    void addChild(std::shared_ptr<Element> child) {
        children.push_back(child);
    }
    
    void addAttribute(const std::string& attr) {
        attributes.push_back(attr);
    }
};

// Lexer class
class Lexer {
private:
    std::vector<std::string> lines;
    size_t current_line;
    size_t current_pos;
    
    // Regex patterns
    std::regex header_pattern;
    std::regex list_pattern;
    std::regex bold_pattern;
    std::regex italic_pattern;
    std::regex code_inline_pattern;
    std::regex code_block_pattern;
    std::regex hr_pattern;
    std::regex link_pattern;
    std::regex image_pattern;
    
public:
    Lexer();
    void setInput(const std::vector<std::string>& input_lines);
    Token getNextToken();
    bool hasMoreTokens() const;
    void reset();
    
private:
    TokenType classifyLine(const std::string& line);
    std::string extractHeaderText(const std::string& line);
    int getHeaderLevel(const std::string& line);
};

// Parser class
class Parser {
private:
    std::vector<Token> tokens;
    size_t current_token;
    
public:
    Parser();
    void setTokens(const std::vector<Token>& token_list);
    std::shared_ptr<Element> parse();
    void reset();
    
private:
    std::shared_ptr<Element> parseBlock();
    std::shared_ptr<Element> parseHeader();
    std::shared_ptr<Element> parseList();
    std::shared_ptr<Element> parseParagraph();
    std::shared_ptr<Element> parseCodeBlock();
    std::shared_ptr<Element> parseInlineElements(const std::string& text);
    Token peek() const;
    Token consume();
    bool match(TokenType type) const;
    bool isAtEnd() const;
};

// Generator class
class Generator {
public:
    Generator();
    std::string generateHTML(const std::shared_ptr<Element>& root);
    std::string generateHTML(const Element& element);
    
private:
    std::string escapeHTML(const std::string& text);
    std::string generateAttributes(const std::vector<std::string>& attributes);
};

// Utility functions
std::vector<std::string> readLinesFromFile(const std::string& filename);
void writeToFile(const std::string& filename, const std::string& content);
std::string trim(const std::string& str);
bool startsWith(const std::string& str, const std::string& prefix);

#endif // TRANSPILER_HPP 