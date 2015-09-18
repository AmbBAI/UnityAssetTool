#include <cassert>
#include "asset_header.h"

void AssetHeader::Read(DataReader& reader)
{
	reader.SetByteOrder(ByteOrder_BigEndian);
	metadataSize = reader.ReadNumber<int32_t>();
	fileSize = reader.ReadNumber<uint32_t>();
	format = reader.ReadNumber<int32_t>();
	dataOffset = reader.ReadNumber<uint32_t>();
	if (format >= 9)
	{
		uint32_t unknown0 = reader.ReadNumber<uint32_t>();
	}
}
