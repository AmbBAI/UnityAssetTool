#include <cstdint>
#include <cstdlib>
#include <string>
#include <memory>
#include "struct/assetbundle_reader.h"

int main()
{
	AssetbundleReader asserbundleReader;
	asserbundleReader.Load("test5.1.assetbundle");
	auto assetFileList = asserbundleReader.ReadAssetFiles();
}