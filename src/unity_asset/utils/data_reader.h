#ifndef _DATA_READER_H_
#define _DATA_READER_H_

#include <cstdint>
#include <string>
#include <cassert>

enum ByteOrder
{
	ByteOrder_LittleEndian,
	ByteOrder_BigEndian,
};

class DataReader
{
	uint8_t* data = nullptr;
	size_t offset = 0;
	size_t size = 0;
	ByteOrder byteOrder = ByteOrder_LittleEndian;

public:
	DataReader(const std::string& file)
	{
		FILE* fp = fopen(file.c_str(), "rb");
		assert(fp != nullptr);
		if (fp != nullptr)
		{
			fseek(fp, 0, SEEK_END);
			this->size = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			assert(this->size > 0);
			this->data = new uint8_t[size];
			size_t rsize = fread(this->data, 1, size, fp);
			fclose(fp);
		}
	}
	virtual ~DataReader()
	{
		if (data != nullptr)
		{
			delete data;
			data = nullptr;
		}
		offset = 0;
		size = 0;
	}

	void SetByteOrder(ByteOrder byteOrder) { this->byteOrder = byteOrder; }
	ByteOrder GetByteOrder() { return byteOrder; }

	size_t Tell() { return offset; }
	void Seek(size_t offset) { offset = offset; }

	uint8_t* GetPtr()
	{
		return data + offset;
	}

	std::string ReadString()
	{
		std::string ret = (const char*)(data + offset);
		offset += ret.length() + 1;
		return ret;
	}

	void ReadBytes(uint8_t* bytes, size_t size)
	{
		std::memcpy(bytes, data + offset, size);
		offset += size;
	}

	uint8_t ReadByte()
	{
		uint8_t ret = *(data + offset);
		offset += 1;
		return ret;
	}

	template<typename Type>
	Type ReadNumber()
	{
		Type ret = *(Type*)(data + offset);
		offset += sizeof(Type);
		uint8_t* ptr = (uint8_t*)&ret;
		if (byteOrder == ByteOrder_BigEndian) std::reverse(ptr, ptr + sizeof(Type));
		return ret;
	}

};

#endif //!_DATA_READER_H_