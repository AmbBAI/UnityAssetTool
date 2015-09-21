#include "assetbundle_header.h"

const std::string AssetbundleHeader::signatureWeb = "UnityWeb";
const std::string AssetbundleHeader::signatureRaw = "UnityRaw";

int AssetbundleHeader::Read(DataReader& reader)
{
	int startOffset = reader.Tell();

	reader.SetByteOrder(ByteOrder_BigEndian);
	signature = reader.ReadString();
	streamVersion = reader.ReadNumber<uint32_t>();
	playerVersion = reader.ReadString();
	engineVersion = reader.ReadString();
	minimumStreamedBytes = reader.ReadNumber<int32_t>();
	headerSize = reader.ReadNumber<int32_t>();
	numberOfLevelsToDownload = reader.ReadNumber<int32_t>();
	int numberOfLevels = reader.ReadNumber<int32_t>();
	levelByteEnd.clear();
	for (int i = 0; i < numberOfLevels; ++i)
	{
		levelByteEnd.emplace_back(reader.ReadNumber<uint32_t>(), reader.ReadNumber<uint32_t>());
	}

	completeFileSize = reader.ReadNumber<int32_t>();
	fileInfoHeaderSize = reader.ReadNumber<int32_t>();
	reader.ReadByte(); // no use

	int endOffset = reader.Tell();
	assert(endOffset - startOffset == headerSize);
	return headerSize;
}
