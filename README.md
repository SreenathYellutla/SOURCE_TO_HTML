# Source to HTML Converter

## 📌 Project Overview

**Source to HTML Converter** is a C programming project that converts C source code files into HTML files.

The application reads a C source file, processes its contents, applies syntax highlighting, adds line numbers, and generates an HTML file that displays the source code in a well-formatted and readable way.

The main objective of this project is to understand file handling, character processing, parsing, and HTML generation using C.

## ✨ Features

- **Source File Handling** – Reads C source code from an input file.
- **HTML Generation** – Converts the source code into an HTML document.
- **Syntax Highlighting** – Highlights different elements of C source code.
- **Line Numbering** – Displays line numbers alongside the source code.
- **Comment Detection** – Identifies single-line and multi-line comments.
- **HTML Character Escaping** – Converts special characters into HTML entities to display source code correctly.
- **File Handling** – Reads input files and writes generated HTML output.
- **Error Handling** – Handles file-opening errors and invalid input conditions.

## 🛠️ Technologies Used

- C Programming
- File Handling
- Pointers
- Structures
- String Handling
- HTML
- CSS

## 📂 Project Structure

```text
Source-to-HTML/
│
├── main.c
├── header.h
├── open_files.c
├── scan_source.c
├── comment_scan.c
├── html_generation.c
├── test.c
└── README.md
```

*Note: Update the filenames according to your actual project structure.*

## ⚙️ Compilation

Make sure GCC is installed on your system.

Compile the project using:

```bash
gcc -Wall -Wextra -std=c11 *.c -o source_to_html
```

If your project contains additional test files with their own `main()` functions, exclude those files from the compilation command.

## ▶️ How to Run

Pass the input C file and output HTML file as command-line arguments.

```bash
./source_to_html input.c output.html
```

For example:

```bash
./source_to_html test.c result.html
```

## 📄 Output

After successful execution, the application generates an HTML file.

Open `result.html` in any web browser to view the converted source code with:

- Syntax highlighting
- Line numbers
- Formatted source code
- Styled comments

## 📚 Concepts Learned

Through this project, I gained practical experience in:

- File handling using `fopen()`, `fgetc()`, and `fclose()`
- Character-by-character file processing
- Pointer and structure usage
- String manipulation
- Identifying C language elements
- HTML tag generation
- Handling special HTML characters
- Modular programming and debugging

## 🚀 Future Enhancements

- Support additional programming languages.
- Improve syntax highlighting for more C language constructs.
- Add customizable themes.
- Improve HTML page styling.
- Support larger source files efficiently.

## 👨‍💻 Author

**Sreenath Yellutla**

C Programming | Embedded Systems | Software Development

## ⭐ Acknowledgment

This project was developed as part of my C programming learning journey to gain hands-on experience with file handling, parsing, and source code processing.

If you find this project useful, consider giving the repository a ⭐.
