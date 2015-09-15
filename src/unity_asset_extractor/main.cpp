#include <cstdint>
#include <cstdlib>
#include <string>
#include <memory>
#include "struct/assetbundle_reader.h"

int main()
{
	DataReader in("test5.1_lzma.assetbundle");
	AssetbundleReader asserbundleReader;
	asserbundleReader.Read(in);
}