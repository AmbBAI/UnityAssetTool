#ifndef _TYPE_TREE_H_
#define _TYPE_TREE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "utils/data_reader.h"
#include "struct/base_class.h"

class TypeTree
{
public:
	std::string version;
	uint32_t attributes = 0;
	bool embedded = false;
	std::map<int32_t, BaseClass> typeMap;

public:
	TypeTree() = default;

	void Read(DataReader& reader, int format);
};

#endif //!_TYPE_TREE_H_