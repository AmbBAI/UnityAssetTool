#ifndef _ASSET_FILE_H_
#define _ASSET_FILE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <utility>
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

	void WriteObjectsToFile(std::string& folder, DataReader& reader, size_t assetFileOffset = 0);
};

#endif //!_ASSET_FILE_H_