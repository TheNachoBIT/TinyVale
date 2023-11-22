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