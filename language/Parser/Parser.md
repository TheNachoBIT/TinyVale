# The Parser

The Parser is a crucial step in the compilation process, mostly because it takes care of tokenizing (by using The Lexer as a tool), and making an Abstract Syntax Tree (AST) with those tokens.

## By being an important step, you'll see that it is really BIG (code-wise)...

But don't worry, the base is pretty small. It all starts in [MainLoop()](#static-void-MainLoopbool-build--false), and from the inside it'll recursively call other functions that have almost the same mechanism but with different goals. This process will keep going until we hit the end of our Vale code.

## Variables

### ```static std::string main_target;```

This is where the name of the first variable that's used at the beginning of the line is stored, in case that info about that is needed.

It gets grabbed anytime you create, set or move a "com" or "mem" variable by using SetMainTarget().

Although this is efficient when needed, this system will probably be replaced in the future with a much more flexible one.

### ```static bool can_main_target_be_modified;```

This is a check to prevent main_target from being modified by accident via SetMainTarget(). If you don't need the current main_target anymore, you can use ResetMainTarget(), which it'll flip this boolean back to true (among other things).

### ```static std::string current_procedure_name;```

Contains the current name of the Function the Parser is currently in. Internally this is called a Procedure due to Mascal Programming Language's Architechture being ported to this.

### ```static std::vector<std::unique_ptr<AST::Procedure>> all_procedures;```

Contains all of the Functions (Procedures). Everytime you finish parsing a function, it'll be moved to this vector.

### ```static std::unordered_map<std::string, AST::Type*> all_parser_coms;```

Contains all of the "com" variables (Parser Version). Once a variable of this type is parsed successfully, it gets pushed to this vector.

### ```static std::unordered_map<std::string, std::unique_ptr<Parser_Mem>> all_parser_mems;```

Contains all of the "mem" variables (Parser Version). Once a variable of this type is parsed successfully, it gets pushed to this vector

### ```static AST::Attributes currentAttributes;```

Contains all of the current Attributes of the function in the shape of a single variable, which down the pipeline it'll get copied for deeper analysis in the CodeGen.

### ```static std::vector<std::string> allBlockNames;```

Contains all of the names of a block. Once a block gets completely parsed via ParseBlock(), its name will get cloned and pushed to this vector.

## Functions

### ```static void MainLoop(bool build = false)```

The entry point of the Parser. And from there it'll tokenize, and with those tokens it'll call other functions that'll do the same recursively until the Lexer hits the end of the file.

You can see that it comes with an argument. This tells the MainLoop() if after everything is generated (including the CodeGen), if its allowed to convert it into a binary. If false, it'll print/emit the generated LLVM CodeGen (LLVM IR).

The first thing MainLoop() does is to [Start the Main Target System](), and initialize a vector that'll contain all of the Programs we collect throughout our Vale code (a.k.a. Exported Functions):

```c++
StartMainTargetSystem();

std::vector<std::unique_ptr<AST::Program>> allPrograms;
```

Once all of this is set up, we start with the Parsing loop that'll 

*-- WIP --*