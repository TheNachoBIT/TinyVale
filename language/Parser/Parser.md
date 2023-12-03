# The Parser

The Parser is a crucial step in the compilation process, mostly because it takes care of tokenizing (by using The Lexer as a tool), and making an Abstract Syntax Tree (AST) with those tokens.

## By being an important step, you'll see that it is really BIG (code-wise)...

But don't worry, the base is pretty small. It all starts in [MainLoop()](#static-void-MainLoopbool-build--false).

### ```static void MainLoop(bool build = false)```

The entry point of the Parser. And from there it'll tokenize, and with those tokens it'll call other functions that'll do the same recursively until the Lexer hits the end of the file.

You can see that it comes with an argument. This tells the MainLoop() if after everything is generated (including the CodeGen), if its allowed to convert it into a binary. If false, it'll print/emit the generated LLVM CodeGen (LLVM IR).

The first thing MainLoop() does is to [Start the Main Target System](), and initialize a vector that'll contain all of the Programs we collect throughout our Vale code (a.k.a. Exported Functions):

```c++
StartMainTargetSystem();

std::vector<std::unique_ptr<AST::Program>> allPrograms;
```

*-- WIP --*