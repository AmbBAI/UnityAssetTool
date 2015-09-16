#include <cassert>
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

		if (format > 13)
		{
			if (classID < 0) reader.ReadBytes(baseClass.scriptID, 16);
			reader.ReadBytes(baseClass.oldTypeHash, 16);
		}

		if (embedded)
		{
			baseClass.typeTree.Read(reader, format);
		}

		typeMap[classID] = baseClass;
	}
}
