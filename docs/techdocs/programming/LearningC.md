# So you need to learn C fast

This guide assumes you are already profficent in another programming or scripting language and just need to familiarize yourself with the quirks of C. Most languages borrow a lot from C so it should be easy to pick up.

You may have heard a lot of scary things about C and assumed its a hardcore super complex language. Well its not... truth is its a very simple language... **a dangerously simple language**. The language's feature set is barebones and there is not much sitting between you and native machine code.

In assembly you are writing a long chain of machine code instructions and keeping mental notes about what memory address does what and where in the program you are (macro assemblers help a bit). C brings to the table a way to enforce a familiar structure to your code. It has loops, branches, variables, structures, enums, functions, and math expressions on integers/floats (string/bool support is optional and provided by the standard library or other ones)... Super simple language! Similarly to assembly this text gets translated to binary machine code (but unlike assembly, optimized automatically) by the compiler which gets executed directly by the hardware.

Higher level languages build large virtual machines, interpreters, recompilers, sandboxes and whatnot that sit between you and the hardware to make sure you aren't doing anything dangerous or dumb... or too clever. On the N64 your code runs at kernel level priveleges... You own the system! Security isn't a concern here so just have fun!

## C Syntax

This section is mainly aimed at people coming from languages like python that are a bit different from C

### Line Ends
* Lines finishing a [statement](https://en.cppreference.com/w/c/language/statements) must be finished with a semicolon `;`
* Line ends of a macro (ex. `#define`) that wish to continue to another line must be prepended with `\`

### Scopes
[Scopes](https://en.cppreference.com/w/c/language/scope) are best described these brackets `{}` anything inside these can be used to **define** the contents of a function, branch or loop body.

### Hello World
Your obligatory hello world program...
```C
#include <stdio.h> /* standard library io (provides printf) */

/* program entry function (don't worry about it for now) */
int main(int argc, char** argv)
{
    printf("Hello World!"); /* writes text to stdout file (console) */
    return 0; /* returning 0 indicates to the OS program was successful */
}
```

## Program Organization
Continuing the theme of C being super simple... this doesn't just apply to the learning curve but how it is compiled. Early computers didn't have the kind of power to compile languages with large dictionaries of symbols spread accross hundreds of files without help. Therefore C compilers more or less just scan through implementation files from start to finish and pick up bits of information as they go. Whatever variable/function/struct/enum you use must have been declared earlier in the file(s) and may only be declared or defined once.

### Definition vs Declaration

* Declaration means telling the compiler "this exists"
* Definition means telling the compiler "this is what it is"

Definition also functions as declaration but declaring something (and using it) without defining it somewhere in the program will raise a compiler error.

### Implementation Files (.C)

Implementation files are where your code lives that gets compiled into machine code. The compiler reads through it start to finish for declarations of types, instructions, etc. This is where you **Define** what your code does. Implementation files can talk to the rest of the codebase or other libraries (including the standard one) by ``#include``ing header files.

#### Example
``` C
/* global variable definition */
int MyGlobalVariable;

int MyFunction(MyType variable) {
    return variable.x + 32;
}
```

### Header Files (.H)

Header files are files which (ideally) only contain struct definitions and function declarations. Conceptualize these files as being copied and pasted into anywhere they are ``#include``d...

#### Example
``` C
#pragma once /* prevents infinite recursion */

/* structure definitions make most sense inside headers */
typedef struct {
    int x;
} MyType;

/* extern is used here to only declare a global variable exists */
extern int MyGlobalVariable;

int MyFunction(MyType variable);

/* inline functions are an exception to the only function declarations rule */
inline int MyInlineFunction(int a) {
    return a + 16;
}
```

#### Edge Cases
There are things called header only libraries that put their implementation in headers using macro tricks

### No Object Oriented Programming
The structure of a C program is a functional programming language rather than object oriented one.

* No classes (only structs)
* No namespaces
* No inheritance
* No member functions
* No virtual functions*
* No operator overrides
* No templates**
* No member protection
* No getters/setters

(*function pointers can mimic this, 
**macros and codegen can bridge the gap)

Structuring a C program comes down to defining data structures and functions which can operate on them. Soft skills around project organization and building abstractions are still super useful.

## C Features

### Preprocessor Macros
The macro system in C is a way to write text templates or prune out parts of your codebase

## Pointers

### Pointer Basics

### Null

### Pointers as Pass by Reference

### Pointers and Arrays

## Memory Management

## Error Management

## Debugging

## Additional Resources
* [Reference](https://en.cppreference.com/w/c/language)