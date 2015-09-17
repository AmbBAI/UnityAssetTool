#include <cassert>
#include "asset_file.h"

void AssetFile::Read(DataReader& reader)
{
	header.Read(reader);
	size_t startOffset = reader.Tell();
	metaData.Read(reader, header.format);
	size_t endOffset = reader.Tell();

}
