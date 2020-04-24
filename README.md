# Lexical-Analyzer
_A Lexical Analyzer written in C++ for the programming language Cell._


Cell is a minimalist programming language that was made with the intention of being easy to read and easy to understand. Not meant for commercial use, The goals of Cell are purely educational and to teahc others how a programming language's compiler works.

Cell's compiler was originally written in Python, but I decided to see if I could rewrite it for C++. While I'm still working on the Parser(_parser.cpp_) and the Interpreter(_interpreter.cpp_), the Lexical Analyzer(_lexer.cpp_) is finished and can return the correct output for a properly formatted text file.

Since Cell is a minimal programming Language, the syntax of the language is made up of the following categories (called "tokens"):

* Operators: '+' , '-' , '/' , '*'
* Special Characters: '(' , ')' , '{' , '}' , ',' , ';' , '=' , ':'
* Strings: any group of characters that begins with a " " " or a " ' "
* Numbers: any combination of digits from 0 to 9
* Symbols: any group of characters that begins with either a letter or an underscore, and is followed by either letters or numbers

the full documentation of Cell can be found at:
https://gitlab.com/cell_lang/cell
