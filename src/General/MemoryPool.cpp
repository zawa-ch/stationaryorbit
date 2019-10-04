#include "General/Memory"

StationaryOrbit::MemoryPool::MemoryPool()
    : _data(NULL)
    , _length(0)
{
}

StationaryOrbit::MemoryPool::MemoryPool(const MemoryPool& value)
    : MemoryPool(value._length)
{
}

StationaryOrbit::MemoryPool::MemoryPool(size_t size)
{
}

StationaryOrbit::MemoryPool::~MemoryPool()
{
}

void* StationaryOrbit::MemoryPool::Allocate(size_t size)
{
    uint8_t* data = (uint8_t*)operator new(size);
    for(size_t i = 0; i < size; i++)
    {
        data[i] = uint8_t();
    }
    return data;
}

void StationaryOrbit::MemoryPool::Deallocate(void* location)
{
}

void StationaryOrbit::MemoryPool::Reallocate(size_t size)
{
}

void StationaryOrbit::MemoryPool::Expand(size_t size)
{
}

void StationaryOrbit::MemoryPool::Shrink(size_t size)
{
}

StationaryOrbit::MemoryPool& StationaryOrbit::MemoryPool::operator=(const MemoryPool& value)
{
}