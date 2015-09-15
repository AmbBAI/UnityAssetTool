#ifndef _ASSETBUNDLE_READER_H_
#define _ASSETBUNDLE_READER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include "utils/data_reader.h"
#include "struct/assetbundle_header.h"
#include "struct/assetbundle_entryinfo.h"

class AssetbundleReader
{
public:
	AssetbundleHeader header;
	std::vector<AssetbundleEntryInfo> entryInfos;

public:
	AssetbundleReader() = default;

	int Read(DataReader& reader);
};

#endif //!_ASSETBUNDLE_READER_H_