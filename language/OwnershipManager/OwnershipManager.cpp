#include "OwnershipManager.hpp"
#include <iostream>

std::vector<OMVariable> OwnershipManager::allVariables;

OMVariable& OwnershipManager::CreateVariable(std::string name) {

	OMVariable bcv;
	bcv.name = name;

	OwnershipManager::allVariables.push_back(bcv);
	return OwnershipManager::allVariables[OwnershipManager::allVariables.size() - 1];
}

void OwnershipManager::MoveVariable(std::string name) {

	std::cout << "Borrow Checker: Moving '" << name << "'...\n";

	if(name == "") {
		return;
	}

	for(auto i : OwnershipManager::allVariables) {
		if(i.name == name) {
			i.hasMoved = true;
			return;
		}
	}
}

bool OwnershipManager::IsBorrowed(std::string name) {

	std::cout << "Borrow Checker: Checking for '" << name << "'...\n";

	if(name == "") {
		return false;
	}

	for(auto i : OwnershipManager::allVariables) {
		if(i.name == name) {
			if(i.hasMoved) {
				return true;
			}
		}
	}

	return false;
}