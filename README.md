CyLang
======

Compiler for an Object Oriented language.

#Description:
Compiler based on LLVM.

Uses flex and bison to create an AST, LLVM to optimize and generate binary.

#Build:
run `./build` in this directory

use `./build -a` to ignore pre compiled modules

(no makefile for the moment)

#Test:
run `./do_test.sh` to run the compiler with some source files.

#Usage:
`cyexec -evatoO file.cy`

-e Execute file.

-v Verify functions.

-a Show llvm assembly on stderr.

-t Show AST.

-o Output llvm assembly in out.ss

-O Do some llvm optimisation.

#Differencies with other languages:
##C/C++

No pointers.

import statement, only one include per file.

##Java:

Less boilerplate code (no main class, main static methode)

Operator overloading.

var keyword for less verbeous code.

No packages, no file hierarchy for classes.

##Python:

Static typing

More C-Like syntax

No duck typing.

##PHP:

Static typing.

More consise syntax.

Less duck typing.

#Future:
* switch statement
* multidimensionnal aray
* try/catch/finally
* Void returning methods can be appended with another method for chaining without value returning.