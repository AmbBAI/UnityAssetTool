#ifndef _TYPE_NODE_H_
#define _TYPE_NODE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "utils/data_reader.h"
#include "struct/type.h"

class TypeNode
{
public:
	int32_t numberFields = 0;
	int32_t stringTableLen = 0;
	std::vector<uint8_t> stringTable;
	std::vector<TypeNode> children;

public:
	TypeNode() = default;

	void Read(DataReader& reader, int format);
};

#endif //!_TYPE_NODE_H_