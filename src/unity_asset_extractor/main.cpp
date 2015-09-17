#include <cstdint>
#include <cstdlib>
#include <string>
#include <memory>
#include "struct/assetbundle_reader.h"

int main()
{
	FileReader fileReader("test4.6.assetbundle");

	AssetbundleReader assertbundleReader;
	assertbundleReader.ReadHeader(fileReader);
	
	auto headerSize = assertbundleReader.header.headerSize;
	DataReader content = std::move(fileReader.ReadData(headerSize));
	fileReader.Close();

	DataReader dataReader;
	if (assertbundleReader.header.IsCompressed())
		dataReader = content.Decompress();
	else
		dataReader = std::move(content);
	content.Close();

	auto assetFileList = assertbundleReader.ReadAssetFiles(dataReader);
	for (auto& keyValPair : assetFileList)
	{
		auto& entryInfo = keyValPair.first;
		auto& assetFile = keyValPair.second;
		puts(entryInfo.name.c_str());
		assetFile.WriteObjectsToFile(entryInfo.name + " - ", dataReader, entryInfo.offset);
	}
}