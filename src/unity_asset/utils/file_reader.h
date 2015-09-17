#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <cstdint>
#include <string>
#include <cassert>
#include <memory>
#include "utils/data_reader.h"

class FileReader : public DataReader
{
	FILE* filePtr = nullptr;

public:
	static const int gReadStringBufferSize = 1024;

	FileReader() = default;
	explicit FileReader(const std::string& file)
	{
		filePtr = fopen(file.c_str(), "rb");
		assert(filePtr != nullptr);
		if (filePtr != nullptr)
		{
			fseek(filePtr, 0, SEEK_END);
			this->size = ftell(filePtr);
			fseek(filePtr, 0, SEEK_SET);
			assert(this->size > 0);
		}
	}
	FileReader(FileReader&& other) { *this = std::move(other); }
	virtual ~FileReader() { Close(); }
	void Close() override
	{
		if (filePtr != nullptr)
		{
			fclose(filePtr);
			filePtr = nullptr;
		}
		DataReader::Close();
	}

	void Seek(size_t offset) override
	{
		DataReader::Seek(offset);
		fseek(filePtr, this->offset, SEEK_SET);
	}


	std::string ReadString() override
	{
		static char buffer[gReadStringBufferSize];
		//int len = fscanf(filePtr, "%[^\0]s\0", buffer);
		//buffer[len] = '\0';

		int len = 0;
		while (true)
		{
			buffer[len] = fgetc(filePtr);
			if (buffer[len] == '\0') break;
			++len;
			assert(len < gReadStringBufferSize);
		}

		std::string ret = buffer;
		offset = ftell(filePtr);
		return ret;
	}

	void ReadBytes(uint8_t* bytes, size_t size) override
	{
		fread(bytes, 1, size, filePtr);
		offset = ftell(filePtr);
	}

	uint8_t ReadByte() override
	{
		uint8_t ret = (uint8_t)fgetc(filePtr);
		offset = ftell(filePtr);
		return ret;
	}

	FileReader& operator =(FileReader&& other)
	{
		if (this == &other) return *this;
		if (filePtr != nullptr)
		{
			fclose(filePtr);
			filePtr = nullptr;
		}

		filePtr = other.filePtr;
		offset = other.offset;
		size = other.size;
		byteOrder = other.byteOrder;
		fseek(filePtr, offset, SEEK_SET);

		other.filePtr = nullptr;
		other.offset = 0;
		other.size = 0;
		other.byteOrder = ByteOrder_LittleEndian;

		return *this;
	}

	DataReader ReadData(size_t offset = 0, size_t size = 0)
	{
		if (size == 0) size = this->size - offset;
		assert(size > 0);

		size_t originOffset = Tell();

		Seek(offset);
		uint8_t* data = new uint8_t[size];
		ReadBytes(data, size);
		Seek(originOffset);

		return DataReader(data, size);
	}
};

#endif //!_FILE_READER_H_