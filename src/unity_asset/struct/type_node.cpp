#include <cassert>
#include "type_node.h"
#include "utils/file_reader.h"

TypeNode::StringTable TypeNode::defaultStringTable;


void TypeNode::Read(DataReader& reader, int format)
{
	reader.SetByteOrder(ByteOrder_LittleEndian);

	numberFields = reader.ReadNumber<int32_t>();
	stringTableLen = reader.ReadNumber<int32_t>();

	typeFields.clear();
	for (int i = 0; i < numberFields; ++i)
	{
		TypeField typeField;
		typeField.Read(reader, format);
		typeFields.emplace_back(typeField);
	}

	stringTable.clear();
	stringTable.assign(stringTableLen, '\0');
	reader.ReadBytes(&stringTable[0], stringTableLen);

	for (int i = 0; i < numberFields; ++i)
	{
		if (format > 13)
		{
			typeFields[i].type = CheckStringTable(stringTable, typeFields[i].typeOffset);
			typeFields[i].name = CheckStringTable(stringTable, typeFields[i].nameOffset);
		}
	}
}


std::string TypeNode::CheckStringTable(const StringTable& stringTable, int32_t offset)
{
	if (defaultStringTable.size() <= 0)
	{
		FileReader fileReader("strings.dat");
		if (fileReader.isValid())
		{
			size_t size = fileReader.GetSize();
			defaultStringTable.assign(size, '\0');
			fileReader.ReadBytes(&defaultStringTable[0], size);
		}
		else printf("strings.dat not found!");

		fileReader.Close();
	}

	if (offset < 0)
	{
		offset = (offset & INT32_MAX);
		if (defaultStringTable.size() <= (size_t)offset) return "";
		return (const char*)&defaultStringTable[offset];
	}
	else
	{
		if (stringTable.size() <= (size_t)offset) return "";
		return (const char*)&stringTable[offset];
	}
}