#pragma once

class DoubleLinkAllocator final
{
public:
	enum class Status : unsigned { free, reserved };
	
	struct Header
	{
		Status status : 1;
		size_t length : std::numeric_limits<size_t>::digits - 1U;
	};

	struct Block : Header
	{
#ifdef _WIN64
		enum { size = 32 };
#else
		enum { size = 16 };
#endif
		struct Links
		{
			Block* nextBlock;
			Block* previousBlock;
		};
		union
		{
			Links link;
			char userPart[size - sizeof(Header)];
		};
	};

	explicit DoubleLinkAllocator(size_t sizeInBytes);
	~DoubleLinkAllocator();

	void* Acquire(size_t);
	void Release(void *);

	// remove default copy & move constructors/assignment operators
	DoubleLinkAllocator(const DoubleLinkAllocator &) = delete;
	DoubleLinkAllocator(DoubleLinkAllocator &&) = delete;
	DoubleLinkAllocator & operator= (const DoubleLinkAllocator &) = delete;
	DoubleLinkAllocator & operator= (const DoubleLinkAllocator &&) = delete;

private:
	static void Unlink(Block&);
	static void InsertAfter(Block&, Block&);

	Block* m_pSentinel;
	void* m_pOutOfBounds;

	size_t RoundUpDivision(size_t dividend, size_t divisor) const;
};