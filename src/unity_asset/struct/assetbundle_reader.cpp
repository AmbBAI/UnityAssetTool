#include <cassert>
#include "assetbundle_reader.h"

int AssetbundleReader::Read(DataReader& reader)
{
	header.Read(reader);

	reader.SetByteOrder(ByteOrder_BigEndian);
	int fileCount = reader.ReadNumber<int32_t>();

	entryInfos.clear();
	for (int i = 0; i < fileCount; ++i)
	{
		AssetbundleEntryInfo entryInfo;
		entryInfo.Read(reader);
		entryInfos.emplace_back(entryInfo);
	}
	
	return 0;
}
