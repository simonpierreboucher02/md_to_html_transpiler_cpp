#include "transpiler.hpp"
#include <iostream>
#include <algorithm>

Parser::Parser() : current_token(0) {}

void Parser::setTokens(const std::vector<Token>& token_list) {
    tokens = token_list;
    current_token = 0;
}

std::shared_ptr<Element> Parser::parse() {
    auto root = std::make_shared<Element>("div", "");
    
    while (!isAtEnd()) {
        auto block = parseBlock();
        if (block) {
            root->addChild(block);
        }
    }
    
    return root;
}

void Parser::reset() {
    current_token = 0;
}

std::shared_ptr<Element> Parser::parseBlock() {
    if (isAtEnd()) {
        return nullptr;
    }
    
    Token current = peek();
    
    switch (current.type) {
        case TokenType::HEADER:
            return parseHeader();
        case TokenType::LIST_ITEM:
            return parseList();
        case TokenType::CODE_BLOCK:
            return parseCodeBlock();
        case TokenType::HR:
            consume(); // Consume the HR token
            return std::make_shared<Element>("hr", "");
        case TokenType::PARAGRAPH:
            return parseParagraph();
        case TokenType::NEWLINE:
            consume(); // Skip newlines
            return nullptr;
        default:
            // Treat as paragraph
            return parseParagraph();
    }
}

std::shared_ptr<Element> Parser::parseHeader() {
    Token token = consume();
    
    // Determine header level from the original line
    std::string header_text = token.value;
    int level = 1; // Default to h1
    
    // Count the number of # symbols at the beginning
    size_t hash_count = 0;
    for (char c : header_text) {
        if (c == '#') {
            hash_count++;
        } else {
            break;
        }
    }
    
    // Remove the # symbols and trim
    if (hash_count > 0) {
        header_text = header_text.substr(hash_count);
        header_text = trim(header_text);
        level = std::min(6, static_cast<int>(hash_count)); // Cap at h6
    }
    
    std::string tag = "h" + std::to_string(level);
    auto element = std::make_shared<Element>(tag, "");
    
    // Parse inline elements within the header
    auto inline_element = parseInlineElements(header_text);
    if (inline_element) {
        element->addChild(inline_element);
    } else {
        element->content = header_text;
    }
    
    return element;
}

std::shared_ptr<Element> Parser::parseList() {
    auto list_element = std::make_shared<Element>("ul", "");
    
    while (!isAtEnd() && match(TokenType::LIST_ITEM)) {
        Token token = consume();
        
        auto list_item = std::make_shared<Element>("li", "");
        
        // Parse inline elements within the list item
        auto inline_element = parseInlineElements(token.value);
        if (inline_element) {
            list_item->addChild(inline_element);
        } else {
            list_item->content = token.value;
        }
        
        list_element->addChild(list_item);
    }
    
    return list_element;
}

std::shared_ptr<Element> Parser::parseParagraph() {
    std::string paragraph_text = "";
    
    // Collect all text until we hit a block-level element
    while (!isAtEnd()) {
        Token current = peek();
        
        if (current.type == TokenType::HEADER || 
            current.type == TokenType::LIST_ITEM || 
            current.type == TokenType::CODE_BLOCK ||
            current.type == TokenType::HR) {
            break;
        }
        
        if (current.type == TokenType::PARAGRAPH) {
            if (!paragraph_text.empty()) {
                paragraph_text += " ";
            }
            paragraph_text += current.value;
        }
        
        consume();
    }
    
    if (paragraph_text.empty()) {
        return nullptr;
    }
    
    auto paragraph = std::make_shared<Element>("p", "");
    
    // Parse inline elements within the paragraph
    auto inline_element = parseInlineElements(paragraph_text);
    if (inline_element) {
        paragraph->addChild(inline_element);
    } else {
        paragraph->content = paragraph_text;
    }
    
    return paragraph;
}

std::shared_ptr<Element> Parser::parseCodeBlock() {
    consume(); // Consume the opening ```
    
    std::string code_content = "";
    
    // Collect all lines until we hit another ```
    while (!isAtEnd()) {
        Token current = peek();
        
        if (current.type == TokenType::CODE_BLOCK) {
            consume(); // Consume the closing ```
            break;
        }
        
        if (!code_content.empty()) {
            code_content += "\n";
        }
        code_content += current.value;
        consume();
    }
    
    auto code_block = std::make_shared<Element>("pre", "");
    auto code_element = std::make_shared<Element>("code", code_content);
    code_block->addChild(code_element);
    
    return code_block;
}

std::shared_ptr<Element> Parser::parseInlineElements(const std::string& text) {
    // For now, we'll implement a simple version that handles basic inline formatting
    // In a more complete implementation, you'd want to parse this more carefully
    
    std::string processed_text = text;
    
    // Handle bold text
    std::regex bold_regex(R"(\*\*(.+?)\*\*)");
    std::string bold_replacement = "<strong>$1</strong>";
    processed_text = std::regex_replace(processed_text, bold_regex, bold_replacement);
    
    // Handle italic text
    std::regex italic_regex(R"(\*(.+?)\*|_(.+?)_)");
    std::string italic_replacement = "<em>$1$2</em>";
    processed_text = std::regex_replace(processed_text, italic_regex, italic_replacement);
    
    // Handle inline code
    std::regex code_regex(R"(`([^`]+)`)");
    std::string code_replacement = "<code>$1</code>";
    processed_text = std::regex_replace(processed_text, code_regex, code_replacement);
    
    // Handle links
    std::regex link_regex(R"(\[([^\]]+)\]\(([^)]+)\))");
    std::string link_replacement = "<a href=\"$2\">$1</a>";
    processed_text = std::regex_replace(processed_text, link_regex, link_replacement);
    
    // Handle images
    std::regex image_regex(R"(!\[([^\]]*)\]\(([^)]+)\))");
    std::string image_replacement = "<img src=\"$2\" alt=\"$1\">";
    processed_text = std::regex_replace(processed_text, image_regex, image_replacement);
    
    // If the text was modified, return a text element
    if (processed_text != text) {
        auto text_element = std::make_shared<Element>("span", "");
        text_element->content = processed_text;
        return text_element;
    }
    
    return nullptr;
}

Token Parser::peek() const {
    if (current_token >= tokens.size()) {
        return Token(TokenType::END_OF_FILE, "", 0);
    }
    return tokens[current_token];
}

Token Parser::consume() {
    if (current_token >= tokens.size()) {
        return Token(TokenType::END_OF_FILE, "", 0);
    }
    return tokens[current_token++];
}

bool Parser::match(TokenType type) const {
    if (current_token >= tokens.size()) {
        return false;
    }
    return tokens[current_token].type == type;
}

bool Parser::isAtEnd() const {
    return current_token >= tokens.size() || 
           tokens[current_token].type == TokenType::END_OF_FILE;
} 