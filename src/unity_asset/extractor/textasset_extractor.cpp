#include "textasset_extractor.h"

void TextAssetExtractor::Extract(FileWriter& writer, DataReader& reader, size_t length)
{
	uint32_t len = reader.ReadNumber<uint32_t>();
	reader.Skip(len);
	reader.Align(4);

	len = reader.ReadNumber<uint32_t>();
	reader.WriteFile(writer, reader.Tell(), len);
}
