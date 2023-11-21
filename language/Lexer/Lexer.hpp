#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <iostream>
#include <vector>

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
	Then = -17,
	Else = -18,

	Return = -19,

	Procedure = -20,

	ComStore = -21,

	Mem = -22,
	LoadMem = -23,
	MemStore = -24,

	IntCast = -25,
	To = -26,

	While = -27,
	Do = -28,

	Block = -29,
	Goto = -30,
};

enum LexerIsInside {
	AProgram,
	AFunction
};

struct Lexer
{
	static std::string Content;

	static std::string IdentifierStr;
	static std::string NumValString;
	static std::string StringString;

	static int CurrentToken;
	static int Position;

	static int Line;
	static int Column;

	static std::string line_as_string;

	static std::vector<std::string> all_lines_vector;

	static LexerIsInside isInside;

	static int LastChar;

	static void AddContent(std::string c);

	static void Start();
	static int Advance();

	static int GetToken();
	static void GetNextToken();

	static bool IsIdentifier(std::string s);

	static bool IsStillIdentifier(char c);

	static int GetChar();
	static int GetString();

	static void StringSlash();

	static int GetIdentifier();
	static int GetNumber();
};

#endif