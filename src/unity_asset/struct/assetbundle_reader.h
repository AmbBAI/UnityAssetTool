#ifndef _ASSETBUNDLE_READER_H_
#define _ASSETBUNDLE_READER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include "utils/data_reader.h"
#include "struct/assetbundle_header.h"
#include "struct/assetbundle_entryinfo.h"
#include "struct/asset_file.h"

class AssetbundleReader
{
public:
	AssetbundleHeader header;
	std::vector<AssetbundleEntryInfo> entryInfos;

protected:
	DataReader dataReader;
	size_t dataOffset = 0;

public:
	AssetbundleReader() = default;

	bool Load(const std::string file);
	std::vector<AssetFile> ReadAssetFiles();

protected:
	bool Read(DataReader& reader);
};

#endif //!_ASSETBUNDLE_READER_H_