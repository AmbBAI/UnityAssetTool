#ifndef _STRING_TABLE_H_
#define _STRING_TABLE_H_

#include "utils/header.h"
#include "utils/data_reader.h"

class StringTable
{
private:
	std::vector<uint8_t> data;

public:
	StringTable() = default;

	void Read(DataReader& reader, uint32_t stringTableLen);
	std::string LoadString(int32_t offset);

private:
	static StringTable defaultStringTable;

public:
	static bool LoadDefaultStringTable(std::string file);
};

#endif //!_STRING_TABLE_H_