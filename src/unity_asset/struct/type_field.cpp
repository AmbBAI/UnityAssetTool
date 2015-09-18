#include <cassert>
#include "type_field.h"

void TypeField::Read(DataReader& reader, int format)
{
	reader.SetByteOrder(ByteOrder_LittleEndian);

	if (format > 13)
	{
		version = reader.ReadNumber<uint16_t>();
		treeLevel = reader.ReadByte();
		isArray = (reader.ReadByte() != 0);
		typeOffset = reader.ReadNumber<int32_t>();
		nameOffset = reader.ReadNumber<int32_t>();
		size = reader.ReadNumber<uint32_t>();
		index = reader.ReadNumber<uint32_t>();
		metaFlag = reader.ReadNumber<uint32_t>();
	}
	else
	{
		type = reader.ReadString();
		name = reader.ReadString();
		size = reader.ReadNumber<uint32_t>();
		index = reader.ReadNumber<uint32_t>();
		isArray = (reader.ReadNumber<int32_t>() != 0);
		version = (uint16_t)reader.ReadNumber<uint32_t>();
		metaFlag = reader.ReadNumber<uint32_t>();
	}
}
