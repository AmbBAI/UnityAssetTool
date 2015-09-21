#ifndef _BASE_CLASS_H_
#define _BASE_CLASS_H_

#include "utils/header.h"
#include "utils/data_reader.h"
#include "struct/type_field.h"

struct BaseClass
{
public:
	int32_t classID = 0;
	uint8_t scriptID[16] = { 0 };
	uint8_t oldTypeHash[16] = { 0 };

	typedef std::vector<uint8_t> StringTable;
	int32_t numberFields = 0;
	int32_t stringTableLen = 0;
	StringTable stringTable;
	std::vector<TypeField> typeFields;

public:
	void Read(DataReader& reader, int format, bool embedded);
	std::string CheckStringTable(const StringTable& stringTable, int32_t offset);

public:
	static StringTable defaultStringTable;
	static bool LoadDefaultStringTable(std::string file);
};

#endif //!_BASE_CLASS_H_