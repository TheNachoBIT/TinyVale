#ifndef OWNERSHIP_MANAGER_HPP
#define OWNERSHIP_MANAGER_HPP

#include <vector>
#include <string>

struct OMVariable {

	std::string name;
	bool hasMoved;
};

struct OwnershipManager {

	static std::vector<OMVariable> allVariables;

	static OMVariable& CreateVariable(std::string name);

	static void MoveVariable(std::string name);

	static bool IsBorrowed(std::string name);
};

#endif