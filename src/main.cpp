#include "transpiler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// Utility function implementations
std::vector<std::string> readLinesFromFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return lines;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();
    return lines;
}

void writeToFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not create output file '" << filename << "'" << std::endl;
        return;
    }
    
    file << content;
    file.close();
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

bool startsWith(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) {
        return false;
    }
    return str.substr(0, prefix.length()) == prefix;
}

void printUsage(const std::string& program_name) {
    std::cout << "Usage: " << program_name << " <input_file> [output_file]" << std::endl;
    std::cout << std::endl;
    std::cout << "Arguments:" << std::endl;
    std::cout << "  input_file   Path to the input Markdown file" << std::endl;
    std::cout << "  output_file  Path to the output HTML file (optional, defaults to 'output.html')" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  " << program_name << " document.md" << std::endl;
    std::cout << "  " << program_name << " document.md output.html" << std::endl;
}

int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc < 2) {
        std::cerr << "Error: No input file specified" << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    std::string input_file = argv[1];
    std::string output_file = (argc > 2) ? argv[2] : "output.html";
    
    std::cout << "Markdown to HTML Transpiler" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Input:  " << input_file << std::endl;
    std::cout << "Output: " << output_file << std::endl;
    std::cout << std::endl;
    
    // Read input file
    std::cout << "Reading input file..." << std::endl;
    auto lines = readLinesFromFile(input_file);
    if (lines.empty()) {
        std::cerr << "Error: Input file is empty or could not be read" << std::endl;
        return 1;
    }
    
    // Lexical analysis
    std::cout << "Performing lexical analysis..." << std::endl;
    Lexer lexer;
    lexer.setInput(lines);
    
    std::vector<Token> tokens;
    while (lexer.hasMoreTokens()) {
        tokens.push_back(lexer.getNextToken());
    }
    
    std::cout << "Generated " << tokens.size() << " tokens" << std::endl;
    
    // Parsing
    std::cout << "Parsing tokens..." << std::endl;
    Parser parser;
    parser.setTokens(tokens);
    auto root_element = parser.parse();
    
    if (!root_element) {
        std::cerr << "Error: Failed to parse input" << std::endl;
        return 1;
    }
    
    // HTML generation
    std::cout << "Generating HTML..." << std::endl;
    Generator generator;
    std::string html = generator.generateHTML(root_element);
    
    // Add HTML document structure
    std::ostringstream full_html;
    full_html << "<!DOCTYPE html>" << std::endl;
    full_html << "<html lang=\"en\">" << std::endl;
    full_html << "<head>" << std::endl;
    full_html << "    <meta charset=\"UTF-8\">" << std::endl;
    full_html << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << std::endl;
    full_html << "    <title>Generated from Markdown</title>" << std::endl;
    full_html << "    <style>" << std::endl;
    full_html << "        body { font-family: Arial, sans-serif; line-height: 1.6; margin: 40px; }" << std::endl;
    full_html << "        h1, h2, h3, h4, h5, h6 { color: #333; }" << std::endl;
    full_html << "        code { background-color: #f4f4f4; padding: 2px 4px; border-radius: 3px; }" << std::endl;
    full_html << "        pre { background-color: #f4f4f4; padding: 10px; border-radius: 5px; overflow-x: auto; }" << std::endl;
    full_html << "        ul, ol { padding-left: 20px; }" << std::endl;
    full_html << "        hr { border: none; border-top: 1px solid #ccc; margin: 20px 0; }" << std::endl;
    full_html << "    </style>" << std::endl;
    full_html << "</head>" << std::endl;
    full_html << "<body>" << std::endl;
    full_html << html << std::endl;
    full_html << "</body>" << std::endl;
    full_html << "</html>" << std::endl;
    
    // Write output file
    std::cout << "Writing output file..." << std::endl;
    writeToFile(output_file, full_html.str());
    
    std::cout << "Success! HTML file generated: " << output_file << std::endl;
    std::cout << "You can open it in your web browser to view the result." << std::endl;
    
    return 0;
} 