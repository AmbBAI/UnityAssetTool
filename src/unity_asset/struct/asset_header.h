#ifndef _ASSET_HEADER_H_
#define _ASSET_HEADER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include "struct/version_info.h"
#include "utils/data_reader.h"

class AssetHeader
{
public:
	VersionInfo versionInfo;

	int32_t metadataSize = 0;
	int fileSize = 0;
	int dataOffset = 0;
	bool isBigEndian = false;

public:
	AssetHeader() = default;

	void Read(DataReader& reader);
};

#endif //!_ASSET_HEADER_H_