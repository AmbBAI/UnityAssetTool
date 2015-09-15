#ifndef _ASSET_METADATA_H_
#define _ASSET_METADATA_H_

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include "struct/unity_version.h"
#include "utils/data_reader.h"

class AssetMetaData
{
public:
	AssetMetaData() = default;

	void Read(DataReader& reader);
};

#endif //!_ASSET_METADATA_H_