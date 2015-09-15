#include <cassert>
#include "assetbundle_reader.h"

int AssetbundleReader::Read(DataReader& reader)
{
	header.Read(reader);
	if (!header.IsSignatureValid()) return -1;

	if (header.IsCompressed())
	{
		ReadBodyData(DataReader::Decompress(reader));
	}
	else
	{
		ReadBodyData(reader);
	}
	
	return 0;
}

void AssetbundleReader::ReadBodyData(DataReader& reader)
{
	reader.SetByteOrder(ByteOrder_BigEndian);
	int fileCount = reader.ReadNumber<int32_t>();

	entryInfos.clear();
	for (int i = 0; i < fileCount; ++i)
	{
		AssetbundleEntryInfo entryInfo;
		entryInfo.Read(reader);
		entryInfos.emplace_back(entryInfo);
	}
}
