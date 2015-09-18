#ifndef _TYPE_NODE_H_
#define _TYPE_NODE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "utils/data_reader.h"
#include "struct/type_field.h"

class TypeNode
{
public:
	typedef std::vector<uint8_t> StringTable;
	int32_t numberFields = 0;
	int32_t stringTableLen = 0;
	StringTable stringTable;
	static StringTable defaultStringTable;
	std::vector<TypeField> typeFields;

public:
	TypeNode() = default;

	void Read(DataReader& reader, int format);
	std::string CheckStringTable(const StringTable& stringTable, int32_t offset);

};

#endif //!_TYPE_NODE_H_