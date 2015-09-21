#ifndef _ASSETBUNDLE_READER_H_
#define _ASSETBUNDLE_READER_H_

#include "utils/header.h"
#include "utils/data_reader.h"
#include "utils/file_reader.h"
#include "struct/assetbundle_header.h"
#include "struct/assetbundle_entryinfo.h"
#include "struct/asset_file.h"

class AssetbundleReader
{
public:
	AssetbundleHeader header;

public:
	AssetbundleReader() = default;

	bool ReadHeader(DataReader& reader);
	std::vector<std::pair<AssetbundleEntryInfo, AssetFile> > ReadAssetFiles(DataReader& reader);
};

#endif //!_ASSETBUNDLE_READER_H_