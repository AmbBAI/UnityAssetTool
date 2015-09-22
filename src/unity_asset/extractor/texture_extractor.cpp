#include "texture_extractor.h"

void TextureExtractor::Extract(FileWriter& writer, DataReader& reader, size_t length)
{
	uint32_t len = reader.ReadNumber<uint32_t>();
	reader.Skip(len);
	reader.Align(4);

	uint32_t width = reader.ReadNumber<uint32_t>();
	uint32_t height = reader.ReadNumber<uint32_t>();


}
