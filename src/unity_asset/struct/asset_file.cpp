#include <cassert>
#include "asset_file.h"

void AssetFile::Read(DataReader& reader)
{
	header.Read(reader);
	metaData.Read(reader, header.format);

	reader.SetByteOrder(ByteOrder_LittleEndian);

}
