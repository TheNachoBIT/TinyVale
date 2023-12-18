#ifndef BORROW_CHECKER_HPP
#define BORROW_CHECKER_HPP

#include <vector>
#include <string>

struct BCVariable {

	std::string name;
	bool hasMoved;
};

struct BorrowChecker {

	static std::vector<BCVariable> allVariables;

	static BCVariable& CreateVariable(std::string name);

	static void MoveVariable(std::string name);

	static bool IsBorrowed(std::string name);
};

#endif