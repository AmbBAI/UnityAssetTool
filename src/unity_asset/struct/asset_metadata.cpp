#include "asset_metadata.h"

void AssetMetaData::Read(DataReader& reader, int format)
{
	reader.SetByteOrder(ByteOrder_LittleEndian);

	typeTree.Read(reader, format);

	int32_t objCount = reader.ReadNumber<int32_t>();
	if (format > 13) reader.Align(4);
	objectInfoMap.clear();
	for (int i = 0; i < objCount; ++i)
	{
		uint64_t pathID = 0LL;
		if (format > 13)
			pathID = (uint64_t)reader.ReadNumber<uint64_t>();
		else
			pathID = (uint64_t)reader.ReadNumber<uint32_t>();

		ObjectInfo objectInfo;
		objectInfo.pathID = pathID;
		objectInfo.Read(reader, format);
		objectInfoMap[pathID] = objectInfo;
	}

	// TODO
}
