#include "type_tree.h"

void TypeTree::Read(DataReader& reader, int format)
{
	reader.SetByteOrder(ByteOrder_LittleEndian);
	version = reader.ReadString();
	attributes = reader.ReadNumber<uint32_t>();

	if (format > 13)
		embedded = (reader.ReadByte() != 0);
	else embedded = true;

	int32_t numberBaseClasses = reader.ReadNumber<int32_t>();
	for (int i = 0; i < numberBaseClasses; ++i)
	{
		int32_t classID = reader.ReadNumber<int32_t>();
		BaseClass baseClass;
		baseClass.classID = classID;
		baseClass.Read(reader, format, embedded);
		typeMap[classID] = baseClass;
	}

	if (format < 13)
	{
		int32_t unkonwn = reader.ReadNumber<int32_t>();
	}
}
