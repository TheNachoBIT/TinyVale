# The Lexer

The Lexer is the process that takes care of converting letters, numbers, words, etc. into tokens for the Parser. This makes it easier for the Parser to figure out what is what in your code, and can be analyzed more quickly, efficient and organized.

## How does it work?

Well, compared to other compilers, instead of gathering all of the tokens and once done, start the next step, the Lexer is designed to work alongside the Parser. The Parser fires up the Lexer by calling ```Lexer::Start()``` *(this can also be used to reset the Lexer, if needed)*, and it'll start at the beginning of your code. 

Once that's done, the Parser will start getting the next token with ```Lexer::GetNextToken()```. Once that's added, it'll check what kind it is, do what it has to do (which it'll be explained in the Parser section), and the process repeats until you hit the end of the line.

So to recap, the Lexer is designed to be used as a toolkit by other processes (in this case, the only one using it is the Parser, so far), rather than being its own thing.

## Code

*wip lol*