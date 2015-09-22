#include "utils/file_reader.h"
#include "utils/data_reader.h"


struct Field
{
	std::string type;
	std::string name;
	uint8_t treeLevel = 0;
	uint8_t isArray = 0;
	int32_t size = -1;
	int32_t index = 0;
	int32_t metaflag = 0;
};

struct Class
{
	int32_t id = 0;
	int32_t parent = -1;
	std::string name;
	std::vector<Field> fields;
};


int main()
{
	FileReader reader("classdata_0E.dat");
	FileWriter writer("types15.dat");

	writer.WriteNumber<uint16_t>(9);
	reader.Skip(4);
	uint8_t version = reader.ReadNumber<uint8_t>();
	uint8_t format = reader.ReadNumber<uint8_t>();
	if (version == 0) uint8_t format = reader.ReadNumber<uint8_t>();
	uint32_t stringTableLen = reader.ReadNumber<uint32_t>();
	writer.WriteNumber<uint32_t>(stringTableLen);
	uint32_t stringTableOffset = reader.ReadNumber<uint32_t>();
	writer.WriteNumber<uint32_t>(stringTableOffset);
	uint32_t numberClasses = reader.ReadNumber<uint32_t>();
	writer.WriteNumber<uint32_t>(numberClasses);

	size_t originOffset = reader.Tell();
	std::vector<uint8_t> stringTable;
	stringTable.assign(stringTableLen, 0);
	reader.Seek(stringTableOffset);
	reader.ReadBytes(&stringTable[0], stringTableLen);
	reader.Seek(originOffset);

	std::vector<Class> classList;
	for (uint32_t i = 0; i < numberClasses; ++i)
	{
		Class c;

		c.id = reader.ReadNumber<int32_t>();
		c.parent = reader.ReadNumber<int32_t>();
		int32_t classNameOffset = reader.ReadNumber<int32_t>();
		c.name = (const char*)&stringTable[classNameOffset];
		writer.WriteNumber<int32_t>(c.id);

		uint32_t fieldCount = reader.ReadNumber<uint32_t>();
		writer.WriteNumber<uint32_t>(fieldCount);
		c.fields.clear();
		for (uint32_t i = 0; i < fieldCount; ++i)
		{
			Field f;
			int32_t typeOffset = reader.ReadNumber<int32_t>();
			f.type = (const char*)&stringTable[typeOffset];
			int32_t nameOffset = reader.ReadNumber<int32_t>();
			f.name = (const char*)&stringTable[nameOffset];
			f.treeLevel = reader.ReadNumber<uint8_t>();
			f.isArray = reader.ReadNumber<uint8_t>();
			f.size = reader.ReadNumber<uint32_t>();
			f.index = reader.ReadNumber<uint32_t>();
			if (version == 0) f.metaflag = reader.ReadNumber<uint32_t>();

			writer.WriteNumber<uint16_t>(0); //version
			writer.WriteNumber<uint8_t>(f.treeLevel); //
			writer.WriteNumber<uint8_t>(f.isArray); //
			writer.WriteNumber<int32_t>(typeOffset); //
			writer.WriteNumber<int32_t>(nameOffset); //
			writer.WriteNumber<int32_t>(f.size); //
			writer.WriteNumber<int32_t>(f.index); //
			writer.WriteNumber<int32_t>(f.metaflag); //

			c.fields.emplace_back(f);
		}
		classList.emplace_back(c);
	}
	writer.WriteBytes((uint8_t*)&stringTable[0], stringTableLen);
	writer.Close();
}