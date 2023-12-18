#include "BorrowChecker.hpp"
#include <iostream>

std::vector<BCVariable> BorrowChecker::allVariables;

BCVariable& BorrowChecker::CreateVariable(std::string name) {

	BCVariable bcv;
	bcv.name = name;

	BorrowChecker::allVariables.push_back(bcv);
	return BorrowChecker::allVariables[BorrowChecker::allVariables.size() - 1];
}

void BorrowChecker::MoveVariable(std::string name) {

	std::cout << "Borrow Checker: Moving '" << name << "'...\n";

	if(name == "") {
		return;
	}

	for(auto i : BorrowChecker::allVariables) {
		if(i.name == name) {
			i.hasMoved = true;
			return;
		}
	}
}

bool BorrowChecker::IsBorrowed(std::string name) {

	std::cout << "Borrow Checker: Checking for '" << name << "'...\n";

	if(name == "") {
		return false;
	}

	for(auto i : BorrowChecker::allVariables) {
		if(i.name == name) {
			if(i.hasMoved) {
				return true;
			}
		}
	}

	return false;
}