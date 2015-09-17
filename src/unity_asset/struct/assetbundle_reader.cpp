#include <cassert>
#include "assetbundle_reader.h"

bool AssetbundleReader::ReadHeader(DataReader& reader)
{
	header.Read(reader);
	return header.IsSignatureValid();
}

std::vector<AssetFile> AssetbundleReader::ReadAssetFiles(DataReader& reader)
{
	size_t dataOffset = reader.Tell();

	reader.SetByteOrder(ByteOrder_BigEndian);
	int fileCount = reader.ReadNumber<int32_t>();

	std::vector<AssetbundleEntryInfo> entryInfos;
	for (int i = 0; i < fileCount; ++i)
	{
		AssetbundleEntryInfo entryInfo;
		entryInfo.Read(reader);
		entryInfos.emplace_back(entryInfo);
	}
	//uint8_t unknown0 = dataReader.ReadByte();
	//uint8_t unknown1 = dataReader.ReadByte();
	//uint8_t unknown2 = dataReader.ReadByte();
	
	std::vector<AssetFile> assetFileList;
	for (auto entryInfo : entryInfos)
	{
		reader.Seek(dataOffset + entryInfo.offset);
		AssetFile assetFile;
		assetFile.name = entryInfo.name;
		assetFile.Read(reader);
		assetFileList.emplace_back(assetFile);
	}

	return assetFileList;
}

