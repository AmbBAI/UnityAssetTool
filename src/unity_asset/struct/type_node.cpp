#include <cassert>
#include "type_node.h"

void TypeNode::Read(DataReader& reader, int format)
{
	reader.SetByteOrder(ByteOrder_LittleEndian);

	numberFields = reader.ReadNumber<int32_t>();
	stringTableLen = reader.ReadNumber<int32_t>();

	std::vector<Type> types;
	for (int i = 0; i < numberFields; ++i)
	{
		uint8_t bytes[24];
		reader.ReadBytes(bytes, 24);
//		Type type;
//		type.Read(reader, format);
//		types.emplace_back(type);
	}

	std::vector<uint8_t> stringTable(stringTableLen, '\0');
	reader.ReadBytes(&stringTable[0], stringTableLen);

}
