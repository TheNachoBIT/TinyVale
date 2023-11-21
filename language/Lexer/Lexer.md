# The Lexer

The Lexer is the process that takes care of converting letters, numbers, words, etc. into tokens for the Parser.

This makes it easier to detect all of the elements of your code for other processes that depend of the Lexer, since you can just check if there's an identifier by ID rather 