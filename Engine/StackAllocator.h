#pragma once

class StackAllocator
{
public:
	StackAllocator(const StackAllocator& other) = delete;
	StackAllocator(StackAllocator&& other) noexcept = delete;
	StackAllocator& operator=(const StackAllocator& other) = delete;
	StackAllocator& operator=(StackAllocator&& other) noexcept = delete;

	explicit StackAllocator(size_t sizeInBytes);
	~StackAllocator();

	void* Acquire(size_t nbBytes);
	void Reset();

	size_t GetFreeSpaceAmount() const;
	bool IsInStack(void* ptr) const;

private:
	char* m_StackPointer;
	char* m_OriginalMemory;
	size_t m_Size;
};