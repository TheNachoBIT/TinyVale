# The Lexer

The Lexer is the process that takes care of converting letters, numbers, words, etc. into tokens for the Parser. This makes it easier for the Parser to figure out what is what in your code, and can be analyzed more quickly, efficient and organized.

## How does it work?

Well, compared to other compilers, instead of gathering all of the tokens and once done, start the next step, the Lexer is designed to work alongside the Parser. The Parser fires up the Lexer by calling ```Lexer::Start()``` *(this can also be used to reset the Lexer, if needed)*, and it'll start at the beginning of your code. 

Once that's done, the Parser will start getting the next token with ```Lexer::GetNextToken()```. Once that's added, it'll check what kind it is, do what it has to do (which it'll be explained in the Parser section), and the process repeats until you hit the end of the line.

So to recap, the Lexer is designed to be used as a toolkit by other processes (in this case, the only one using it is the Parser, so far), rather than being its own thing.

# Code

### All Token Types (so far)

This section is self explanatory. These are all the token types that are available so far.

```
enum Token
{
	EndOfFile = -1,
	Program = -2,

	String = -5,
	Number = -6,

	Identifier = -7,

	Com = -8,

	LLReturn = -9,

	Add = -10,
	Sub = -11,

	And = -12,
	Or = -13,
	Xor = -14,

	Compare = -15,

	If = -16,
	Else = -17,

	Return = -18,

	Procedure = -19,

	ComStore = -20,

	Mem = -21,
	LoadMem = -22,
	MemStore = -23,

	IntCast = -24,
	To = -25,

	While = -26,
	Do = -27,

	Block = -28,
	Goto = -29,

	Exported = -30
};
```

These are in the negatives because tokens act as "negative" characters, so you can check for both characters and tokens in the same process without having to code two different scenarios.

For example, in the Parser, to check if the token is an identifier, you can do:

```
// Check if the Token is an Identifier.
if(Lexer::CurrentToken == Token::Identifier) {
	// ...
}
```

...and to check if there's a semicolon, you can do:

```
// Check if there's a semicolon.
if(Lexer::CurrentToken == ';') {
	// ...
}
```

...all in the same process!

### The "LexerIsInside" enum

This enum is mostly a way to tell the Lexer where it is in the Parser, if it is inside of a program or inside of a function. The use of this can be found inside of the Lexer struct.

```
enum LexerIsInside {
	AProgram,
	AFunction
};
```

## The "Lexer" struct

This is the heart of the entire Lexer, where all of the functions and variables dedicated to it are.

### ```static std::string Content```

Where the entire code loaded from one or more .vale files is stored.

### ```static std::string IdentifierStr```

This contains the current or last identifier's name is stored. So to get the name of a variable or function, in the Parser you can simply do:

```
// Just in case, let's check if there's an identifier in the first place.
if(Lexer::CurrentToken != Token::Identifier) {
	// If there is no identifier, throw a parsing/lexing error.
	ExprError("Expected identifier.");
}

// Got the name of the variable/function!
std::string getName = Lexer::IdentifierStr;
```

### ```static std::string NumValString```

This acts like IdentifierStr, but for numbers instead.

Why this is a string instead of an integer or a float? Because it's easier to work with, specially when you get into hexadecimal territory. The Lexer can just grab any number type in form of a string, and later on in the Parser we can just convert it into whatever type we want or need. This is also more compact in terms of code size, because otherwise you could have to split all of the possible functionality for each and individual number types, one for ints, other one for floats, other for hex, etc.

```
if(Lexer::NumValString.find(".") != std::string::npos) {
	// Found float/decimal!
}
else if(Lexer::NumValString.find("x") != std::string::npos) {
	// Found hex!
}
else {
	// Found int!
}

// ...
```

If an int is found for example, we can simply use ```std::stoi``` to convert it to int.

```
int finalNumber = std::stoi(Lexer::NumValString);
```

### ```static std::string StringString```

I have to admit, this is a funny name lol

But there's a reason of why is it named like this: This is a string that gets the current/last string from your code.

```
myString str = "Hello!";
#                 ^
#                 |
#              This one
```

Its functionality is the same as NumValString and IdentifierStr, with the same way of getting the info.

### ```static int CurrentToken```

Contains the Current Token.

This value is heavily used for the Parser to check what type of token or character did you found. So if you're going to add anything new, this is one of the most important variables you should know about.

```
if(Lexer::CurrentToken == Token::INSERT-TOKEN-HERE)
```

### ```static int Position```

Has the current position of where the Lexer is in your Vale code. Its measure unit is in characters, and shows how far it is from the starting point.

Let's show an example of how it works:

```
exported func main()
#       ^
#       |
```

Let's suppose that the Lexer is here. We're in the first line of our Vale Code. You just used "Lexer::GetNextToken()" in the Parser and the result from "Lexer::CurrentToken" is 'exported'. Because 'exported' has 8 characters, the Lexer is currently in position '8'.

```
exported func main()
#            ^
#            |
```

Now let's do "Lexer::GetNextToken()" again. We found out that it's a 'func' keyword, all that jazz... Because it skips spaces, new lines, and characters that aren't really important, it goes forward 1 character and does nothing with it.

So, our last position we measured (8) + the space we skipped (1) + 'func' (4) = 13. So we're now in position '13'.

If we add an X amount of spaces in between our keywords, let's say, 5 spaces, for demonstration purposes.

```
exported     func     main()
#                ^
#                |
```

Because we added more characters, the position in this case will increase if we pass the Lexer again. New Lines and Tabs are also characters ('\n', '\t', '\r'), so each line of code will guarantee the count to be increased by 1 once we hit the end of it.

```
# And comments will also increase the Position count.
#    ^
#    |
#    Position: 5
```

### ```static int Line```

Shows in what line of code the Lexer is currently in.

This count increases by one each time the Lexer sees a new line chatacter ('\n').

```
exported func main() { 		# This is the first line, so starts as "1"
							# If the lexer is right here where this comment is. Line will be equals to "2".
	com aVariable int = 10;	# Line = 3
							# Line = 4
	aVariable += 2;			# Line = 5
							# And so on...
}
```

### ```static int Column```

Shows in what column the Lexer is located.

This acts the same as Position, with the difference being that once the Lexer hits a new line, its count will be reseted back to "1".

### ```static std::string line_as_string```

Contains the current line in form of a string. Characters will keep being added to this the further the Lexer goes. Once it reaches to the end of the line, it gets copied and pushed back to all_lines_vector and it clears itself out.

```
exported func main() {			# line_as_string = "exported func main() {\n"
								# line_as_string = "\n"
	com aVariable int = 10; 	# line_as_string = "com aVariable int = 10;\n"
								# line_as_string = "\n"
	aVariable += 2;				# line_as_string = "aVariable += 2;\n"
								# line_as_string = "\n"
}								# line_as_string = "}\n"
```

```
exported func main() {			# line_as_string = "exported func main() {\n"
								# line_as_string = "\n"
	com aVariable int = 10; 	# line_as_string = "com "
#      ^
#      |
#   Lexer is here.
```

### ```static std::vector<std::string> all_lines_vector```

Contains all of the lines collected from line_as_string.