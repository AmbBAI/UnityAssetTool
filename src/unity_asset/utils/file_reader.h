#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include "utils/header.h"
#include "utils/data_reader.h"

class FileReader : public DataReader
{
	FILE* filePtr = nullptr;

public:
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

	bool isValid() { return filePtr != nullptr; }

	void Seek(size_t offset) override
	{
		DataReader::Seek(offset);
		fseek(filePtr, this->offset, SEEK_SET);
	}


	std::string ReadString() override
	{
		std::vector<char> buffer;

		int len = 0;
		while (true)
		{
			char c = fgetc(filePtr);
			buffer.emplace_back(c);
			if (c == '\0') break;
			++len;
		}

		std::string ret = &buffer[0];
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

	bool WriteFile(std::string file, size_t offset, size_t size) override
	{
		data = new uint8_t[size];
		ReadBytes(data, size);
		bool result = DataReader::WriteFile(file, 0, size);
		delete data;
		data = nullptr;
		return result;
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