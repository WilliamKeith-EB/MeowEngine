#include "pch.h"
#include "StackAllocator.h"
#include "Locator.h"
#include "Logger.h"

meow::StackAllocator::StackAllocator(size_t size)
{
	m_StackPointer = new char[size]();
	m_OriginalMemory = m_StackPointer;
	m_Size = size;
}

meow::StackAllocator::~StackAllocator()
{
	Reset();
	delete[] m_StackPointer;
}

void* meow::StackAllocator::Acquire(size_t nrOfBytes)
{
	if (GetFreeSpaceAmount() < nrOfBytes) {

		LOGGER.LogError("Frame allocator full when trying to acquire " + std::to_string(nrOfBytes) + " bytes");
		return nullptr;
	}

	void* ptr = static_cast<void*>(m_StackPointer);
	m_StackPointer += nrOfBytes;

	return ptr;
}

void meow::StackAllocator::Reset()
{
	m_StackPointer = m_OriginalMemory;
}

size_t meow::StackAllocator::GetFreeSpaceAmount() const
{
	size_t memory = m_Size - (m_StackPointer - m_OriginalMemory);
	return memory;
}

bool meow::StackAllocator::IsInStack(void* ptr) const {

	return (ptr < m_StackPointer && ptr > m_OriginalMemory);
}