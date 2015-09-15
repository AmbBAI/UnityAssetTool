#include <cassert>
#include "assetbundle_entryinfo.h"

int AssetbundleEntryInfo::Read(DataReader& reader)
{
	int startOffset = reader.Tell();

	reader.SetByteOrder(ByteOrder_BigEndian);
	name = reader.ReadString();
	offset = reader.ReadNumber<uint32_t>();
	size = reader.ReadNumber<uint32_t>();

	int endOffset = reader.Tell();
	return endOffset - startOffset;
}
