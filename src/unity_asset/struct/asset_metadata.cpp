#include <cassert>
#include "asset_metadata.h"

void AssetMetaData::Read(DataReader& reader, int format)
{
	reader.SetByteOrder(ByteOrder_LittleEndian);

	typeTree.Read(reader, format);

	int32_t objCount = reader.ReadNumber<int32_t>();
	objectInfoMap.clear();
	for (int i = 0; i < objCount; ++i)
	{
		uint64_t pathID = 0LL;
		if (format > 13)
			pathID = reader.ReadNumber<uint64_t>();
		else
			pathID = (uint64_t)reader.ReadNumber<uint32_t>();

		ObjectInfo objectInfo;
		objectInfo.Read(reader);
		objectInfoMap[pathID] = objectInfo;
	}
}
