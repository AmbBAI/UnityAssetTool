#include "string_table.h"
#include "utils/file_reader.h"

void StringTable::Read(DataReader& reader, uint32_t stringTableLen)
{
	data.clear();
	data.assign(stringTableLen, '\0');
	reader.ReadBytes(&(data[0]), stringTableLen);
}

std::string StringTable::LoadString(int32_t offset)
{
	if (offset < 0)
	{
		return defaultStringTable.LoadString(offset & INT32_MAX);
	}
	else
	{
		if (data.size() <= (size_t)offset) return "";
		return (const char*)&data[offset];
	}
}

StringTable StringTable::defaultStringTable;
bool StringTable::LoadDefaultStringTable(std::string file)
{
	FileReader fileReader(file);
	if (fileReader.isValid())
	{
		size_t size = fileReader.GetSize();
		defaultStringTable.Read(fileReader, size);
	}
	else
	{
		printf("%s not found!", file.c_str());
		return false;
	}

	fileReader.Close();
	return true;
}
