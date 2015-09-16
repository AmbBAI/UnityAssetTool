#ifndef _ASSET_METADATA_H_
#define _ASSET_METADATA_H_

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include "utils/data_reader.h"
#include "struct/unity_version.h"
#include "struct/type_tree.h"
#include "struct/object_info.h"

class AssetMetaData
{
	TypeTree typeTree;
	std::map<uint64_t, ObjectInfo> objectInfoMap;

public:
	AssetMetaData() = default;

	void Read(DataReader& reader, int format);
};

#endif //!_ASSET_METADATA_H_