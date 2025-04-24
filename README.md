# LangCompilerStandard
 The source code that doesn't require any other building system

## Coding style
 For header file:
 place `#ifndef header`, `#define header`, and `#pragma once` first, `#include<>` and `#include""` second. And then code.
 If there are descriptions place it at the top.
 ```cpp
/*
* description of the header
*/
 #ifndef header
 #define header
 #pragma once

 #include<file>

 #include"file"

 //code

 #endif
 ```
