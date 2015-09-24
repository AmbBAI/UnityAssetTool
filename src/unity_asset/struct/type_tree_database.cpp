#include "type_tree_database.h"
#include "utils/file_reader.h"

void TypeTreeDatabase::Read(DataReader& reader, int format)
{
	format = reader.ReadNumber<int32_t>();
	uint32_t stringTableLen = reader.ReadNumber<uint32_t>();
	uint32_t numberClasses = reader.ReadNumber<uint32_t>();

	typeMap.clear();
	for (uint32_t i = 0; i < numberClasses; ++i)
	{
		int32_t classID = reader.ReadNumber<int32_t>();
		BaseClass baseClass;
		baseClass.classID = classID;
		
		uint32_t numberFields = reader.ReadNumber<uint32_t>();
		baseClass.ReadTypeFormat(reader, format, numberFields);
		typeMap.insert({ classID, baseClass });
	}

	if (stringTable == nullptr)
		stringTable = std::make_shared<StringTable>();

	stringTable->Read(reader, stringTableLen);
}

std::map<int32_t, TypeTreeDatabase> TypeTreeDatabase::typeTreeDataBase;
void TypeTreeDatabase::LoadTypeTreeDatabase(int32_t format, std::string file)
{
	FileReader fileReader(file);
	typeTreeDataBase[format].Read(fileReader, 15);
}
