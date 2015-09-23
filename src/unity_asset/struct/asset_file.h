#ifndef _ASSET_FILE_H_
#define _ASSET_FILE_H_

#include "utils/header.h"
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

	bool Read(DataReader& reader);
	bool IsValid() { return header.format == 9 || header.format == 15; }
	
	bool LoadObject(uint64_t objectID, DataReader& reader, std::function<void(const ObjectInfo&, DataReader&)> func);
	void LoadAllObjects(DataReader& reader, std::function<void(const ObjectInfo&, DataReader&)> func);
};

#endif //!_ASSET_FILE_H_