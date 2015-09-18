#ifndef _ASSET_FILE_H_
#define _ASSET_FILE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include "utils/data_reader.h"
#include "struct/asset_header.h"
#include "struct/asset_metadata.h"

class AssetFile
{
public:
	AssetHeader header;
	AssetMetaData metaData;

public:
	AssetFile() = default;

	void Read(DataReader& reader);
	
	bool LoadObject(uint64_t objectID, DataReader& reader, std::function<void(const ObjectInfo&, DataReader&)> func);
	void LoadAllObjects(DataReader& reader, std::function<void(const ObjectInfo&, DataReader&)> func);
};

#endif //!_ASSET_FILE_H_