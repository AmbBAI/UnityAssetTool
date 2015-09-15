#include <cassert>
#include "asset_header.h"

void AssetHeader::Read(DataReader& reader)
{
	int startOffset = reader.Tell();

	reader.SetByteOrder(ByteOrder_BigEndian);
	metadataSize = reader.ReadNumber<int32_t>();
	fileSize = reader.ReadNumber<uint32_t>();
	versionInfo.assetVersion = reader.ReadNumber<int32_t>();
	dataOffset = reader.ReadNumber<uint32_t>();
	if (versionInfo.assetVersion >= 9)
	{
		isBigEndian = (reader.ReadByte() == 0);
	}

	reader.Seek(startOffset + metadataSize);
}
