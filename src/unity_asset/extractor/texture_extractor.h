#ifndef _TEXTURE_EXTRACTOR_H_
#define _TEXTURE_EXTRACTOR_H_

#include "utils/header.h"
#include "utils/data_reader.h"
#include "extractor/extractor.h"

class TextureExtractor : Extractor
{
public:
	TextureExtractor() = default;

	void Extract(FileWriter& writer, DataReader& reader, size_t length) override;
};

#endif //!_TEXTURE_EXTRACTOR_H_