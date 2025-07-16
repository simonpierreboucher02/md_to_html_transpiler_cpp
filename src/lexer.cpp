#include "transpiler.hpp"
#include <iostream>
#include <algorithm>

Lexer::Lexer() : current_line(0), current_pos(0) {
    // Initialize regex patterns
    header_pattern = std::regex(R"(^(#{1,6})\s+(.+)$)");
    list_pattern = std::regex(R"(^[\s]*[-*+]\s+(.+)$)");
    bold_pattern = std::regex(R"(\*\*(.+?)\*\*)");
    italic_pattern = std::regex(R"(\*(.+?)\*|_(.+?)_)");
    code_inline_pattern = std::regex(R"(`([^`]+)`)");
    code_block_pattern = std::regex(R"(^```(\w*)$)");
    hr_pattern = std::regex(R"(^[\s]*[-*_]{3,}[\s]*$)");
    link_pattern = std::regex(R"(\[([^\]]+)\]\(([^)]+)\))");
    image_pattern = std::regex(R"(!\[([^\]]*)\]\(([^)]+)\))");
}

void Lexer::setInput(const std::vector<std::string>& input_lines) {
    lines = input_lines;
    current_line = 0;
    current_pos = 0;
}

Token Lexer::getNextToken() {
    if (current_line >= lines.size()) {
        return Token(TokenType::END_OF_FILE, "", current_line);
    }
    
    std::string line = lines[current_line];
    
    // Skip empty lines
    if (line.empty() || trim(line).empty()) {
        current_line++;
        return Token(TokenType::NEWLINE, "", current_line - 1);
    }
    
    // Classify the line type
    TokenType type = classifyLine(line);
    std::string value = line;
    std::smatch match; // Declare before switch to avoid jump errors
    // Extract specific content based on type
    switch (type) {
        case TokenType::HEADER:
            value = extractHeaderText(line);
            break;
        case TokenType::LIST_ITEM:
            // Extract the actual list item content
            if (std::regex_match(line, match, list_pattern)) {
                value = match[1].str();
            }
            break;
        case TokenType::HR:
            value = "";
            break;
        default:
            // For other types, use the line as is
            break;
    }
    
    current_line++;
    return Token(type, value, current_line - 1);
}

bool Lexer::hasMoreTokens() const {
    return current_line < lines.size();
}

void Lexer::reset() {
    current_line = 0;
    current_pos = 0;
}

TokenType Lexer::classifyLine(const std::string& line) {
    std::string trimmed = trim(line);
    
    // Check for horizontal rule
    if (std::regex_match(trimmed, hr_pattern)) {
        return TokenType::HR;
    }
    
    // Check for headers
    std::smatch header_match;
    if (std::regex_match(trimmed, header_match, header_pattern)) {
        return TokenType::HEADER;
    }
    
    // Check for list items
    std::smatch list_match;
    if (std::regex_match(trimmed, list_match, list_pattern)) {
        return TokenType::LIST_ITEM;
    }
    
    // Check for code blocks
    std::smatch code_block_match;
    if (std::regex_match(trimmed, code_block_match, code_block_pattern)) {
        return TokenType::CODE_BLOCK;
    }
    
    // Default to paragraph
    return TokenType::PARAGRAPH;
}

std::string Lexer::extractHeaderText(const std::string& line) {
    std::smatch match;
    if (std::regex_match(line, match, header_pattern)) {
        return trim(match[2].str());
    }
    return line;
}

int Lexer::getHeaderLevel(const std::string& line) {
    std::smatch match;
    if (std::regex_match(line, match, header_pattern)) {
        return match[1].str().length();
    }
    return 0;
} 