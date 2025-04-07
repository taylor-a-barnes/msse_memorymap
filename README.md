# Mapping Virtual Memory

## Introduction

In this problem, you will explore the way in which the data associated with your code is mapped into virtual memory.
You should come away with a much clearer picture of exactly what causes certain types of information to be stored in stack, heap, *etc*.

You're going to create numerous variables and functions, and print out the location where they are stored in virtual memory.
To make things simpler and more human-readable, we'll be representing all pointers (including function pointers) as integers; you can do this by casting them to the `intptr_t` type.
Note that the C++ standard does **not** guarantee that it is possible to cast a function pointer to an `intptr_t` (or to a `void*`, for that matter).
This is because (among other reasons) on certain platforms function pointers and object pointers might not necessarily be the same size.
Nonetheless, the POSIX standard (which largely governs implementations of Linux, among others) **does** guarantee that it is possible to cast a function pointer to a `void*` (and thus to a `intptr_t`):

>All function pointer types shall have the same representation as the type pointer to void. Conversion of a function pointer to `void *` shall not alter the representation. A `void *` value resulting from such a conversion can be converted back to the original function pointer type, using an explicit cast, without loss of information.
>
>Note: The ISO C standard does not require this, but it is required for POSIX conformance.

The bottom line is that as long as you are working within a Linux Docker container, or using one of the Linux runners on GitHub Actions, you can safely cast function pointers to `intptr_t`.
For example, you could create a pointer to the virtual memory location of function `main` by doing:

```
  std::intptr_t main_address = reinterpret_cast<std::intptr_t>(main);
```

One interesting opportunity this opens up is that we can easily compute the **relative** location of variables in memory using normal integer arithmetic.
For example, suppose we have a global variable named `reference_var`.
We can print the virtual memory location of the function `main`, relative to `reference_var`, with the following code:

```
#include<iostream>
#include <stdint.h>

int reference_var;

int main(int argc, char *argv[]) {

  std::intptr_t reference_var_address = reinterpret_cast<std::intptr_t>(&reference_var);
  std::intptr_t main_address = reinterpret_cast<std::intptr_t>(main);
  std::cout << "Relative location of main: " << main_address - reference_var_address << std::endl;

}
```

Note that we don't need to use an ampersand (`&`) when casting a function (such as `main`) to an `intptr_t`, because when using a function name in this way, it is treated as a function pointer to that function.
We **do** need the ampersand when casting `reference_var`, because we need a pointer to `reference_var` (`&reference_var`).
A more verbose (but perhaps clearer) way you could optionally write the above code would be:

```
#include<iostream>
#include <stdint.h>

int reference_var;

int main(int argc, char *argv[]) {

  int *reference_var_ptr = &reference_var;
  int (*main_ptr)(int, char**) = main;
  std::intptr_t reference_var_address = reinterpret_cast<std::intptr_t>(reference_var_ptr);
  std::intptr_t main_address = reinterpret_cast<std::intptr_t>(main_ptr);
  std::cout << "Relative location of main: " << main_address - reference_var_address << std::endl;

}
```


## Part 1

Write a program that declares a global variable of type `int` (we'll assume this variable is named `reference_var`) for the rest of these instructions.
Whenever you see the phrase **relative virtual memory address** throughout the rest of this problem, that means the virtual memory address relative to the virtual memory address of `reference_var`.
Also define a class (we'll assume it is called `MemoryTest`) that includes at least the following members:

1. A variable of type `int`, which is **not** declared using the `static` keyword.  For the rest of these instructions, we'll assume you named this variable `nonstatic_int`.
2. A variable of type `int`, which **is** declared using the `static` keyword.  For the rest of these instructions, we'll assume you named this variable `static_int`.
3. A variable of type `double*`, which is **not** declared using the `static` keyword.  For the rest of these instructions, we'll assume you named this variable `double_ptr`.  In the class constructor, assign `double_ptr = new double[10]`.


## Part 2

Have your code print each of the following:

1. The relative virtual memory address of `argc`.
2. The relative virtual memory address of `argv`.
3. The relative virtual memory address of a variable of type `double` that is declared in the `main` function and has automatic lifespan.
4. The relative virtual memory address of a variable of type `double*` that has automatic lifespan.
5. The relative virtual memory address of a variable of type `double` that has global scope.
6.
   1. The relative virtual memory address of an array of length `10` in which the elements are of type `double`, and the elements are of automatic lifespan.
   2. The relative virtual memory address of the first element of this array.
   3. The relative virtual memory address of the last element of this array.
7.
   1. The relative virtual memory address of a `double*` that points to an array of length `10` in which the elements are of type `double`, and the elements are of dynamic lifespan.
   2. The relative virtual memory address of the first element of this array.
   3. The relative virtual memory address of the last element of this array.
8.
   1. The relative virtual memory address of an `std::vector` of length `10` in which the elements are of type `double`, and the vector has automatic lifespan.
   2. The relative virtual memory address of the first element of this vector.
   3. The relative virtual memory address of the last element of this vector.
9.
   1. The relative virtual memory address of an instance of the `MemoryTest` class that has automatic lifespan.
   2. The relative virtual memory address of this instance's `nonstatic_int` member.
   3. The relative virtual memory address of this instance's `static_int` member.
   4. The relative virtual memory address of this instance's `double_ptr` member.
   5. The relative virtual memory address of the first `double` in the array that this instance's `double_ptr` points to.
   6. The relative virtual memory address of the last `double` in the array that this instance's `double_ptr` points to.
10.
    1. The relative virtual memory address of an instance of the `MemoryTest` class that has dynamic lifespan.
    2. The relative virtual memory address of this instance's `nonstatic_int` member.
    3. The relative virtual memory address of this instance's `static_int` member.
    4. The relative virtual memory address of this instance's `double_ptr` member.
    5. The relative virtual memory address of the first `double` in the array that this instance's `double_ptr` points to.
    6. The relative virtual memory address of the last `double` in the array that this instance's `double_ptr` points to.
11.
    1. The relative virtual memory address of an instance of the `MemoryTest` class that has global scope.
    2. The relative virtual memory address of this instance's `nonstatic_int` member.
    3. The relative virtual memory address of this instance's `static_int` member.
    4. The relative virtual memory address of this instance's `double_ptr` member.
    5. The relative virtual memory address of the first `double` in the array that this instance's `double_ptr` points to.
    6. The relative virtual memory address of the last `double` in the array that this instance's `double_ptr` points to.
12. The relative virtual memory address of the `main` function.
13.
    1. The relative virtual memory address of a function (aside from `main`) having global scope.
    2. The relative virtual memory address of a variable of automatic lifespan that is declared within this function.
    3. The relative virtual memory address of a variable of static lifespan that is declared within this function.

Hint: Remember to keep in mind the difference between an instance of a class and a pointer to an instance of a class.  Also note that the specific values you get will be different each time you run; for the purpose of the rest of this problem, just analyze the results from any single execution of your code.

## Part 3

At the end of this `README.md` file, list each required value from Part 1 alongside its relative virtual memory location, clearly indicating which requirement of Part 2 it satisfies.
In addition, indicate for each value which of the following regions of memory it is expected to be stored in: (1) Startup / Stack, (2) Heap, (3) Global / Static, and (4) Text.
Order the results from highest relative virtual memory location to lowest relative virtual memory location.
You **aren't** required to write code to do the ordering; you may do it by hand if you prefer.

For example, your answer might partially be:

| Brief Description               | Requirement   | Relative Virtual Memory Address |  Region         |
| ------------------------------- | ------------- | ------------------------------- | --------------- |
| argc                            | 1             | 46031242593288                  | Startup / Stack |
| dynamic MemoryTest instance     | 10.i          | 10064608                        | Heap            |
| static variable in a function   | 13.iii        | -336                            | Global / Static |

## Answer

Place your answer here.
