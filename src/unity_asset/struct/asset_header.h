#ifndef _ASSET_HEADER_H_
#define _ASSET_HEADER_H_

#include "utils/header.h"
#include "utils/data_reader.h"

class AssetHeader
{
public:
	int32_t format = 0;
	int32_t metadataSize = 0;
	uint32_t fileSize = 0;
	uint32_t dataOffset = 0;

public:
	AssetHeader() = default;

	void Read(DataReader& reader);
};

#endif //!_ASSET_HEADER_H_