#pragma once
#ifndef _HULU_LOKI_CHUNK_H_
#define _HULU_LOKI_CHUNK_H_

#include "../gvals.h"

_HULU_BEGIN

struct Chunk
{
	/**
	 * ��ʼ��
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
	 * �ͷ�����õ��ڴ�
	 */
	void Release();

	/**
	 * ����һ������
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
	 * �黹ĳ������
	 */
	void Deallocate(void* p, size_t blockSize)
	{

	}
	
	unsigned char* pData_;
	unsigned char firstAvailableBlock_; // chunk�ڵĵ�һ�����������������
	unsigned char blocksAvailable_; // chunk�ڵĿ�����������
};

_HULU_END

#endif // !_HULU_LOKI_CHUNK_H_
