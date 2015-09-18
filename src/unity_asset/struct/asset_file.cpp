#include <cassert>
#include "asset_file.h"

void AssetFile::Read(DataReader& reader)
{
	header.Read(reader);
	size_t startOffset = reader.Tell();
	metaData.Read(reader, header.format);
	size_t endOffset = reader.Tell();

}

bool AssetFile::LoadObject(uint64_t objectID, DataReader& reader, std::function<void(const ObjectInfo&, DataReader&)> func)
{
	auto& objPtr = metaData.objectInfoMap.find(objectID);
	if (objPtr == metaData.objectInfoMap.end()) return false;

	size_t assetFileOffset = reader.Tell();
	auto& objectInfo = objPtr->second;
	int objectOffset = assetFileOffset + header.dataOffset + objectInfo.offset;
	reader.Seek(objectOffset);
	if (func != nullptr) func(objectInfo, reader);
	reader.Seek(assetFileOffset);
	return true;
}

void AssetFile::LoadAllObjects(DataReader& reader, std::function<void(const ObjectInfo&, DataReader&)> func)
{
	size_t assetFileOffset = reader.Tell();
	for (auto& keyValPair : metaData.objectInfoMap)
	{
		auto& objectInfo = keyValPair.second;
		int objectOffset = assetFileOffset + header.dataOffset + objectInfo.offset;
		reader.Seek(objectOffset);
		if (func != nullptr) func(objectInfo, reader);
	}
	reader.Seek(assetFileOffset);
}
