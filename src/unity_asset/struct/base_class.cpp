#include "base_class.h"
#include "utils/file_reader.h"

void BaseClass::Read(DataReader& reader, int format, bool embedded)
{
	reader.SetByteOrder(ByteOrder_LittleEndian);

	if (format > 13)
	{
		if (classID < 0) reader.ReadBytes(scriptID, 16);
		reader.ReadBytes(oldTypeHash, 16);
	}

	if (!embedded) return;

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

		printf("%s - %s\n", typeFields[i].type.c_str(), typeFields[i].name.c_str());
	}
}

std::string BaseClass::CheckStringTable(const StringTable& stringTable, int32_t offset)
{
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

BaseClass::StringTable BaseClass::defaultStringTable;
bool BaseClass::LoadDefaultStringTable(std::string file)
{
	defaultStringTable.clear();

	FileReader fileReader(file);
	if (fileReader.isValid())
	{
		size_t size = fileReader.GetSize();
		defaultStringTable.assign(size, '\0');
		fileReader.ReadBytes(&defaultStringTable[0], size);
	}
	else
	{
		printf("%s not found!", file.c_str());
		return false;
	}

	fileReader.Close();
	return true;
}
