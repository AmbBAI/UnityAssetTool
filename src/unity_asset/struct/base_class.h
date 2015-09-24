#ifndef _BASE_CLASS_H_
#define _BASE_CLASS_H_

#include "utils/header.h"
#include "utils/data_reader.h"
#include "struct/type_field.h"
#include "struct/string_table.h"

struct BaseClass
{
public:
	int32_t classID = 0;
	std::string typeHash;
	std::string oldTypeHash;

	std::shared_ptr<StringTable> stringTable;
	std::vector<TypeField> typeFields;

public:
	void Read(DataReader& reader, int format, bool embedded);
	void ReadTypeFormat(DataReader& reader, int format, int32_t numberFields);
	void SetStringTable(std::shared_ptr<StringTable>& stringTable) { this->stringTable = stringTable; }
	std::shared_ptr<StringTable> GetStringTable() { return this->stringTable; }

public:
	static std::string HashToString(uint8_t hash[16]);
};

#endif //!_BASE_CLASS_H_