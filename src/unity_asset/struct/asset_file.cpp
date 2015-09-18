#include <cassert>
#include "asset_file.h"

void AssetFile::Read(DataReader& reader)
{
	header.Read(reader);
	size_t startOffset = reader.Tell();
	metaData.Read(reader, header.format);
	size_t endOffset = reader.Tell();

}

void AssetFile::WriteObjectsToFile(const std::string& folder, DataReader& reader, size_t assetFileOffset)
{
	for (auto& keyValPair : metaData.objectInfoMap)
	{
		std::string path =  folder + std::to_string(keyValPair.first);
		auto& objectInfo = keyValPair.second;
		int objectOffset = assetFileOffset + header.dataOffset + objectInfo.offset;
		reader.WriteFile(path, objectOffset, objectInfo.length);
	}
}
