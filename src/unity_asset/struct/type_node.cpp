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
		Type type;
		type.Read(reader, format);
		types.emplace_back(type);
	}


}
