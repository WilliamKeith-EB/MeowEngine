#include "pch.h"
#include "DoubleLinkAllocator.h"

#include "pch.h"
#include "DoubleLinkAllocator.h"
#include <exception>
#include <cstring>

DoubleLinkAllocator::DoubleLinkAllocator(const size_t sizeInBytes)
{
	const size_t amtOfBlocksNeeded = RoundUpDivision(sizeInBytes, sizeof(Block));
	m_pSentinel = new Block[amtOfBlocksNeeded + 1]; // plus one for the sentinel
	m_pOutOfBounds = m_pSentinel + amtOfBlocksNeeded + 1;

	Block* pFirstBlock = m_pSentinel + 1;
	pFirstBlock->status = Status::free;
	pFirstBlock->length = amtOfBlocksNeeded;
	pFirstBlock->link.nextBlock = m_pSentinel;
	pFirstBlock->link.previousBlock = m_pSentinel;

	m_pSentinel->status = Status::reserved;
	m_pSentinel->length = 1;
	m_pSentinel->link.nextBlock = pFirstBlock;
	m_pSentinel->link.nextBlock = pFirstBlock;
}

DoubleLinkAllocator::~DoubleLinkAllocator()
{
	delete[] m_pSentinel;
}

void* DoubleLinkAllocator::Acquire(size_t nbBytes)
{
	const size_t amtOfBlockNeeded = RoundUpDivision(nbBytes + sizeof(Header), sizeof(Block));
	Block* current = m_pSentinel->link.nextBlock;
	while (true) {

		if (int(current->length) >= amtOfBlockNeeded)
			break;

		// merge code
		Block* pAdjacent = current + current->length;
		if (pAdjacent < m_pOutOfBounds && pAdjacent->status == Status::free) {

			current->length += pAdjacent->length;
			Unlink(*pAdjacent);

			continue;
		}

		if (current == m_pSentinel)
			throw std::exception("Out of memory");

		current = current->link.nextBlock;
	}

	if (current->length > amtOfBlockNeeded) {

		Block* newBlock = current + amtOfBlockNeeded;
		newBlock->length = current->length - amtOfBlockNeeded;
		newBlock->status = Status::free;

		current->length = amtOfBlockNeeded;

		InsertAfter(*current, *newBlock);
	}

	current->status = Status::reserved;

	Unlink(*current);

#ifdef _DEBUG
	std::memset(current->userPart, 0, current->length * sizeof(Block) - sizeof(Header));
#endif

	return current->userPart;
}

void DoubleLinkAllocator::Release(void* pointerToBuffer)
{
	int* ptr = static_cast<int*>(pointerToBuffer);
	Block* newBlock = reinterpret_cast<Block*>(ptr - 1);

	newBlock->status = Status::free;

	InsertAfter(*m_pSentinel, *newBlock);
}

void DoubleLinkAllocator::Unlink(Block& block)
{
	block.link.nextBlock->link.previousBlock = block.link.previousBlock;
	block.link.previousBlock->link.nextBlock = block.link.nextBlock;
}

void DoubleLinkAllocator::InsertAfter(Block& firstBlock, Block& secondBlock)
{
	secondBlock.link.nextBlock = firstBlock.link.nextBlock;
	secondBlock.link.previousBlock = &firstBlock;
	firstBlock.link.nextBlock = &secondBlock;
	secondBlock.link.nextBlock->link.previousBlock = &secondBlock;
}

inline size_t DoubleLinkAllocator::RoundUpDivision(size_t dividend, size_t divisor) const {

	return (dividend + divisor - 1) / divisor;
}
