#include "base_class.h"
#include "utils/file_reader.h"

void BaseClass::Read(DataReader& reader, int format, bool embedded)
{
	reader.SetByteOrder(ByteOrder_LittleEndian);

	if (format > 13)
	{
		uint8_t hash[16];
		if (classID < 0)
		{
			reader.ReadBytes(hash, 16);
			typeHash = HashToString(hash);
		}
		reader.ReadBytes(hash, 16);
		oldTypeHash = HashToString(hash);
	}

	if (!embedded) return;

	int32_t numberFields = reader.ReadNumber<int32_t>();
	int32_t stringTableLen = reader.ReadNumber<int32_t>();

	ReadTypeFormat(reader, format, numberFields);
	
	if (stringTable == nullptr)
		stringTable = std::make_shared<StringTable>();
	stringTable->Read(reader, stringTableLen);
}

void BaseClass::ReadTypeFormat(DataReader& reader, int format, int32_t numberFields)
{
	typeFields.clear();
	for (int i = 0; i < numberFields; ++i)
	{
		TypeField typeField;
		typeField.Read(reader, format);
		typeFields.emplace_back(typeField);
	}
}

std::string BaseClass::HashToString(uint8_t hash[16])
{
	std::string hex(32, '\0');
	sprintf((char*)hex.c_str(),
		"%08x%08x%08x%08x",
		*(((uint32_t*)hash) + 3),
		*(((uint32_t*)hash) + 2),
		*(((uint32_t*)hash) + 1),
		*(((uint32_t*)hash) + 0));
	std::reverse(hex.begin(), hex.end());
	return hex;
}

