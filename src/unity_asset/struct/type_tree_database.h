#ifndef _TYPE_TREE_DATABASE_H_
#define _TYPE_TREE_DATABASE_H_

#include "utils/header.h"
#include "utils/data_reader.h"
#include "struct/base_class.h"

class TypeTreeDatabase
{
public:
	std::map<int32_t, BaseClass> typeMap;
	std::shared_ptr<StringTable> stringTable;

public:
	TypeTreeDatabase() = default;
	void Read(DataReader& reader, int format);

private:
	static std::map<int32_t, TypeTreeDatabase> typeTreeDataBase;
public:
	static void LoadTypeTreeDatabase(int32_t format, std::string file);
};

#endif //!_TYPE_TREE_DATABASE_H_