# Markdown to HTML Transpiler Demo

This is a **demonstration** of the C++ Markdown to HTML transpiler. It showcases various Markdown features and how they are converted to HTML.

## Features Supported

### Headers
The transpiler supports headers from `#` to `######`:

# Header 1
## Header 2
### Header 3
#### Header 4
##### Header 5
###### Header 6

### Text Formatting

You can use **bold text** and *italic text* or _also italic_. You can even combine them: **_bold and italic_**.

### Lists

#### Unordered Lists
- First item
- Second item
- Third item with **bold text**
- Fourth item with *italic text*

#### Nested Lists
- Main item
  - Sub item 1
  - Sub item 2
    - Sub-sub item
- Another main item

### Code

#### Inline Code
You can use `inline code` within paragraphs.

#### Code Blocks
```
This is a code block
It can contain multiple lines
And preserve formatting
```

### Links and Images

#### Links
Here's a [link to GitHub](https://github.com) and another [link with text](https://example.com).

#### Images
![Example Image](https://via.placeholder.com/300x200)

### Horizontal Rules

You can create horizontal rules with three or more dashes:

---

Or with asterisks:

***

### Mixed Content

This paragraph contains **bold text**, *italic text*, `inline code`, and a [link](https://example.com).

## Technical Details

The transpiler follows a classic compiler pipeline:

1. **Lexer**: Scans the input and identifies tokens
2. **Parser**: Builds a structured representation
3. **Generator**: Converts the structure to HTML

### Example Output

When you run the transpiler on this file, it will generate clean, semantic HTML that you can view in any web browser.

---

*This demo file was created to test all the features of the C++ Markdown to HTML transpiler.* 