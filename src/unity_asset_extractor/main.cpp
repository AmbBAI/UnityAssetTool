#include "utils/file_reader.h"
#include "struct/asset_file.h"
#include "struct/type_tree_database.h"
#include "extractor/extractor.h"
#include "extractor/textasset_extractor.h"

#include "boost/filesystem.hpp"
using namespace boost;

int main(int argc, char *argv)
{
	StringTable::LoadDefaultStringTable("strings.dat");
	TypeTreeDatabase::LoadTypeTreeDatabase(9, "types9.dat");
	TypeTreeDatabase::LoadTypeTreeDatabase(15, "types15.dat");
	//Extractor::RegisterExtractor(ClassID::TextAsset, std::make_shared<TextAssetExtractor>(".txt"));
	//Extractor::RegisterExtractor(ClassID::Shader, std::make_shared<TextAssetExtractor>(".shader"));

	filesystem::path workDir;
	if (argc == 1) workDir = "D:\\Data";
	else workDir = filesystem::path((filesystem::path::value_type*)argv[1]);

	if (!filesystem::exists(workDir))
	{
		printf("%s not exist!", workDir.string().c_str());
		return 0;
	}

	filesystem::path outputDir = workDir;
	outputDir.append("Output/");

	filesystem::recursive_directory_iterator itor(workDir);
	while (itor != filesystem::end(itor))
	{
		filesystem::path path = itor->path();
		printf("%s\n", path.string().c_str());
		++itor;

		if (filesystem::is_directory(path)) continue;

		std::string ext = path.extension().string();
		puts(ext.c_str());
		if (ext == ".dll" || ext == ".png" || ext == ".xml")
		{
			continue;
		}
		else if (ext.find(".split") != ext.npos)
		{

		}
		else
		{
			try
			{
				FileReader fileReader(path.string());
				if (!fileReader.isValid())
				{
					throw std::exception((path.string() + " open fault!").c_str());
				}

				AssetFile assetFile;
				assetFile.Read(fileReader);
				if (!assetFile.IsValid())
				{
					throw std::exception((path.string() + " format not support!").c_str());
				}

				fileReader.Seek(0);
				filesystem::path objectDir = outputDir;
				objectDir.append(path.filename().string() + "/");

				assetFile.LoadAllObjects(fileReader, [&objectDir](const ObjectInfo& objectInfo, DataReader& objectReader)
				{
					//std::string name = extractor->GetObjectName(objectReader);
					//if (name.empty()) name = std::to_string(objectInfo.pathID);
					std::string name = std::to_string(objectInfo.pathID);

					filesystem::path objectFile = objectDir;
					objectFile.append(name + "." + std::to_string(objectInfo.classID));
					filesystem::create_directories(objectDir);
					FileWriter writer(objectFile.string());
					Extractor::DumpBinary(writer, objectReader, objectInfo.length);
					writer.Close();
				});
			}
			catch (std::exception e)
			{
				printf("%s\n", e.what());
			}

		}
	}

}