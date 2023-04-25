# Reverse Engineering Project: Nostale

This project is the culmination of many years of studying computer architecture, compiler standards, and data structures. It is an effort to reverse engineer part of the original program, a binary game by the name of Nostale. Using professional tools like IDA Pro (used by malware analysts), assembly instructions and C++ pseudocode were reviewed and analyzed.

Here is an example of what a typical analysis of a binary program with IDA Pro looks like:
![IDA Pro](https://hex-rays.com/wp-content/themes/hx2021/dist/img/ida-pro.png)

## Project Process

The entire process can be broken down into several steps:

1. **Studying the binary**: By contrasting standard program behavior and content inside the binary, the compiler used was narrowed down to Borland's Delphi, probably version 2006, and the language was identified as Pascal.
2. **Understanding Pascal and Borland compiler**: Studied how Pascal behaves and how the Borland compiler creates memory structures, which led to the successful reverse engineering of the entire set of standard libraries inside the program binary.
3. **Building an injector**: Created an injector that launches the game, stops it, and replaces game functions with hooks to a custom-made library. The original functions were then reversed, rewritten in C++, and tested on runtime.

### Emphasis on Modern C++

The project uses modern C++ to write clean code that resembles how the original game source code should have looked like. A variety of tools were utilized, including IDA Pro, Microsoft Visual Studio, and an open-source Borland compiler compatible with Borland Delphi calling convention.

## Particularities and Problems

During the course of this project, a few particularities and problems were encountered:

- **Borland Fastcall calling convention**: Pascal Delphi uses Borland Fastcall calling convention for functions, which is not supported by any other implementation of C++. Switching to a Borland C++ compiler resolved this issue.
- **Assembly optimizations**: Sometimes the standard library made assembly optimizations that broke the language logic, causing crashes or stack pollution. To deal with these issues, the entire standard library was read and C++ keywords were used to alter the compiler behavior.

## How to Use

*This project is not meant to be used, but only acts as a public display of the results archived after my analysis.*
