#pragma once
#ifndef _HULU_LOKI_CHUNK_H_
#define _HULU_LOKI_CHUNK_H_

#include "../gvals.h"

_HULU_BEGIN

struct Chunk
{
	/**
	 * 初始化
	 */
	void Init(size_t blockSize, unsigned char blocks)
	{
		pData_ = new unsigned char[blockSize * blocks];
		firstAvailableBlock_ = 0;
		blocksAvailable_ = blocks;
		unsigned char i = 0;
		unsigned char* p = pData_;
		for (; i != blocks; p += blockSize)
		{
			*p = ++i;
		}
	}

	/**
	 * 释放已配得的内存
	 */
	void Release();

	/**
	 * 分配一个区块
	 */
	void* Allocate(size_t blockSize)
	{
		if (!blocksAvailable_) return nullptr;
		unsigned char* pResult = pData_ + (firstAvailableBlock_ * blockSize);
		firstAvailableBlock_ = *pResult;
		--blocksAvailable_;
		return pResult;
	}

	/**
	 * 归还某个区块
	 */
	void Deallocate(void* p, size_t blockSize)
	{

	}
	
	unsigned char* pData_;
	unsigned char firstAvailableBlock_; // chunk内的第一个可用区块的索引号
	unsigned char blocksAvailable_; // chunk内的可用区块总数
};

_HULU_END

#endif // !_HULU_LOKI_CHUNK_H_
