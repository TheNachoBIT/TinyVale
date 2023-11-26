#include "Lexer.hpp"

std::string Lexer::Content;

std::string Lexer::IdentifierStr;
std::string Lexer::NumValString;
std::string Lexer::StringString;

int Lexer::CurrentToken;
int Lexer::Position;
int Lexer::Line;
int Lexer::Column;
std::string Lexer::line_as_string;
std::vector<std::string> Lexer::all_lines_vector;
LexerIsInside Lexer::isInside;

int Lexer::LastChar;

void Lexer::AddContent(std::string c) {

	Content += c;
}

void Lexer::Start() {

	Position = -1;
	Line = 1;
	Column = 1;
	LastChar = ' ';
}

int Lexer::Advance() {

	Position += 1;

	Column += 1;

	line_as_string += Content[Position];

	if (Content[Position] == '\n') {

		Line += 1;
		Column = 1;

		all_lines_vector.push_back(line_as_string);

		line_as_string.clear();
	}

	return Content[Position];
}

void Lexer::GetNextToken() {

	CurrentToken = GetToken();
}

int Lexer::GetToken() {

	while (isspace(LastChar)) { LastChar = Advance(); }

	if (isalpha(LastChar)) { return GetIdentifier(); }

	if (isdigit(LastChar)) { return GetNumber(); }

	if(LastChar == '\'') { return GetChar(); }

	if(LastChar == '\"') { return GetString(); }

	if (LastChar == '#')
	{
		// Comment until end of line.
		do
		{
			LastChar = Advance();
		}
		while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

		if (LastChar != EOF) return GetToken();
	}

	if (LastChar == EOF) return Token::EndOfFile;

	int ThisChar = LastChar;
	LastChar = Advance();

	// This is a fail-safe in case memory corruption appears.
	// Since at this point, we're looking for normal characters,
	// it makes no sense to find characters that are below space in
	// the ASCII table. Meaning that if we find one like that at this point,
	// its undefined behavior.
	if (ThisChar < 32) { ThisChar = Token::EndOfFile; }

	return ThisChar;
}

bool Lexer::IsIdentifier(std::string s) {

	return IdentifierStr == s;
}

bool Lexer::IsStillIdentifier(char c) {

	return isalnum(c) || c == '_';
}

int Lexer::GetChar() {

	LastChar = Advance();

	NumValString = "";

	if(LastChar == '\\')
		StringSlash();

	NumValString += std::to_string(LastChar);

	LastChar = Advance();

	if(LastChar == '\'') { LastChar = Advance(); }

	return Token::Number;
}

int Lexer::GetString() {

	StringString = "";
	LastChar = Advance();

	do
	{
		if(LastChar == '\\')
			StringSlash();

		StringString += LastChar;
		LastChar = Advance();
	} while(LastChar != '\"' && LastChar != Token::EndOfFile && LastChar >= 32);

	if(LastChar == '\"') { LastChar = Advance(); }

	return Token::String;
}

void Lexer::StringSlash() {

	LastChar = Advance();

	if(LastChar == 'n') LastChar = '\n';
	else if(LastChar == 'r') LastChar = '\r';
	else if(LastChar == 't') LastChar = '\t';
	else if(LastChar == '0') LastChar = '\0';
	else if(LastChar == '\"') LastChar = '\"';
	else if(LastChar == '\\') LastChar = '\\';
}

int Lexer::GetIdentifier() {

	IdentifierStr = LastChar;

	while (IsStillIdentifier((LastChar = Advance())))
	{
		IdentifierStr += LastChar;
	}

	if (IsIdentifier("program")) return Token::Program;

	else if(IsIdentifier("com")) return Token::Com;

	else if(IsIdentifier("llreturn")) return Token::LLReturn;

	else if(IsIdentifier("add")) return Token::Add;
	else if(IsIdentifier("sub")) return Token::Sub;

	else if(IsIdentifier("and")) return Token::And;
	else if(IsIdentifier("or")) return Token::Or;
	else if(IsIdentifier("xor")) return Token::Xor;

	else if(IsIdentifier("COMPARE")) return Token::Compare;

	else if(IsIdentifier("if")) return Token::If;
	else if(IsIdentifier("else")) return Token::Else;

	else if(IsIdentifier("return")) return Token::Return;

	else if(IsIdentifier("func") || IsIdentifier("funky")) return Token::Procedure;

	else if(IsIdentifier("comstore")) return Token::ComStore;

	else if(IsIdentifier("mem")) return Token::Mem;
	else if(IsIdentifier("loadmem")) return Token::LoadMem;
	else if(IsIdentifier("memstore")) return Token::MemStore;

	else if(IsIdentifier("intcast")) return Token::IntCast;
	else if(IsIdentifier("to")) return Token::To;

	else if(IsIdentifier("block")) return Token::Block;
	else if(IsIdentifier("goto")) return Token::Goto;

	else if(IsIdentifier("exported")) return Token::Exported;

	return Token::Identifier;
}

int Lexer::GetNumber() {
	
	std::string NumStr;

	do
	{
		if(LastChar != '_') NumStr += LastChar;
		LastChar = Advance();
	} while (isdigit(LastChar) || LastChar == '.' || LastChar == 'f' || LastChar == '_');

	NumValString = NumStr;
	return Token::Number;
}