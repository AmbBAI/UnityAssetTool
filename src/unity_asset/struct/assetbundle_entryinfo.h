#ifndef _ASSETBUNDLE_ENTRY_INFO_H_
#define _ASSETBUNDLE_ENTRY_INFO_H_

#include <cstdint>
#include <string>
#include <utility>
#include "utils/data_reader.h"

struct AssetbundleEntryInfo
{
public:
	std::string name;
	uint32_t offset = 0;
	uint32_t size = 0;

public:
	AssetbundleEntryInfo() = default;

	int Read(DataReader& reader);
};

#endif //!_ASSETBUNDLE_HEADER_H_