#ifndef _DATA_READER_H_
#define _DATA_READER_H_

#include <cstdint>
#include <string>
#include <cassert>
extern "C" {
#include "LzmaDec.h"
}

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

private:
	DataReader() = default;

public:
	static DataReader Decompress(DataReader& dataReader)
	{
		dataReader.SetByteOrder(ByteOrder_LittleEndian);
		uint8_t* propData = new uint8_t[LZMA_PROPS_SIZE];
		dataReader.ReadBytes(propData, LZMA_PROPS_SIZE);
		SizeT uncompressSize = (SizeT)dataReader.ReadNumber<uint32_t>();
		uint8_t* uncompressData = new uint8_t[uncompressSize];
		dataReader.ReadNumber<uint32_t>(); // finish mode?
		SizeT compressedSize = (SizeT)(dataReader.size - dataReader.offset);
		ELzmaStatus lzmaStatus = LZMA_STATUS_NOT_SPECIFIED;

		static ISzAlloc lzmaAlloc = {
			[](void* p, size_t size) { p = p; return malloc(size); },
			[](void* p, void *address) { p = p; free(address); } };

		LzmaDecode(
			uncompressData, (SizeT*)&uncompressSize,
			dataReader.GetPtr(), (SizeT*)&compressedSize,
			propData, LZMA_PROPS_SIZE,
			LZMA_FINISH_ANY, &lzmaStatus, &lzmaAlloc);

		DataReader retReader;
		retReader.data = uncompressData;
		retReader.offset = 0;
		retReader.size = uncompressSize;
		return retReader;
	}

public:
	explicit DataReader(const std::string& file)
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
	DataReader(DataReader&& other) { *this = std::move(other); }
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
	ByteOrder GetByteOrder() const { return byteOrder; }

	size_t GetSize() const { return size; }
	size_t Tell() const { return offset; }
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

	DataReader& operator =(DataReader&& other)
	{
		if (this == &other) return *this;
		if (data != nullptr)
		{
			delete data;
			data = nullptr;
		}

		data = other.data;
		offset = other.offset;
		size = other.size;
		byteOrder = other.byteOrder;

		other.data = nullptr;
		other.offset = 0;
		other.size = 0;
		other.byteOrder = ByteOrder_LittleEndian;

		return *this;
	}
};

#endif //!_DATA_READER_H_