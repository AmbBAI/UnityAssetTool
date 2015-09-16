#include <cassert>
#include "assetbundle_reader.h"

bool AssetbundleReader::Load(const std::string file)
{
	DataReader fileReader(file);
	if (fileReader.GetSize() <= 0) return false;

	return Read(fileReader);
}

bool AssetbundleReader::Read(DataReader& reader)
{
	header.Read(reader);
	if (!header.IsSignatureValid()) return false;

	if (header.IsCompressed())
	{
		dataReader = DataReader::Decompress(reader);
	}
	else
	{
		dataReader = std::move(reader);
	}
	dataOffset = dataReader.Tell();

	dataReader.SetByteOrder(ByteOrder_BigEndian);
	int fileCount = dataReader.ReadNumber<int32_t>();

	entryInfos.clear();
	for (int i = 0; i < fileCount; ++i)
	{
		AssetbundleEntryInfo entryInfo;
		entryInfo.Read(dataReader);
		entryInfos.emplace_back(entryInfo);
	}

	//uint8_t unknown0 = dataReader.ReadByte();
	//uint8_t unknown1 = dataReader.ReadByte();
	//uint8_t unknown2 = dataReader.ReadByte();

	//assert(header.fileInfoHeaderSize == dataReader.Tell() - dataOffset);
	//dataReader.Seek(dataOffset + header.fileInfoHeaderSize);
	return true;
}

std::vector<AssetFile> AssetbundleReader::ReadAssetFiles()
{
	std::vector<AssetFile> assetFileList;
	for (auto entryInfo : entryInfos)
	{
		dataReader.Seek(dataOffset + entryInfo.offset);
		AssetFile assetFile;
		assetFile.Read(dataReader);
		assetFileList.emplace_back(assetFile);
	}

	return assetFileList;
}

