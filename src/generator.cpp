#include "transpiler.hpp"
#include <sstream>
#include <algorithm>

Generator::Generator() {}

std::string Generator::generateHTML(const std::shared_ptr<Element>& root) {
    return generateHTML(*root);
}

std::string Generator::generateHTML(const Element& element) {
    std::ostringstream out;
    
    // Handle self-closing tags
    if (element.tag == "hr" || element.tag == "img") {
        out << "<" << element.tag;
        if (!element.attributes.empty()) {
            out << " " << generateAttributes(element.attributes);
        }
        out << ">";
        return out.str();
    }
    
    // Opening tag
    out << "<" << element.tag;
    if (!element.attributes.empty()) {
        out << " " << generateAttributes(element.attributes);
    }
    out << ">";
    
    // Content and children
    if (!element.children.empty()) {
        for (const auto& child : element.children) {
            out << generateHTML(child);
        }
    } else if (!element.content.empty()) {
        out << escapeHTML(element.content);
    }
    
    // Closing tag
    out << "</" << element.tag << ">";
    
    return out.str();
}

std::string Generator::escapeHTML(const std::string& text) {
    std::string result;
    for (char c : text) {
        switch (c) {
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            case '\'': result += "&#39;"; break;
            default: result += c; break;
        }
    }
    return result;
}

std::string Generator::generateAttributes(const std::vector<std::string>& attributes) {
    std::ostringstream out;
    
    for (size_t i = 0; i < attributes.size(); ++i) {
        if (i > 0) {
            out << " ";
        }
        out << attributes[i];
    }
    
    return out.str();
} 