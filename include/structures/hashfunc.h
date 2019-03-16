#ifndef HASHFUNC_H_INCLUDED
#define HASHFUNC_H_INCLUDED

#include <string>
#include "include/aliases.h"


namespace slice {


template<typename T>
struct Hash final
{
    Hash() = delete;
    uint operator()(const T& key, uint tableSize) const;
};



// TODO у Седжвика посмортеть как реализовать
template<>
struct Hash<std::string>
{
    // TODO арифм. переполнение исправить, есть вариант с помощью XOR, SHL, SHR.
    uint operator()(const std::string& key, uint tableSize) const
    {
        uint _hash = 0;
        uint a = 127;
        for (size_t i = 0, length = key.length(); i < length; ++i)
        {
            _hash = (a * _hash + static_cast<uint>(key[i])) % tableSize;
        }
        return _hash;
    }
};



template<>
struct Hash<int>
{
    uint operator()(int key, uint tableSize) const
    {
        return static_cast<uint>(key) % tableSize;
    }
};



template<>
struct Hash<double>
{
    ulong operator()(double key, uint tableSize) const
    {
        data.input = key;
        return ((data.output >> SHIFT) | (data.output << SHIFT)) % tableSize;
    }

private:
    static const short SHIFT = sizeof(double) * 8 / 2;

    mutable union
    {
        double input;
        ulong output;
    } data;
};



template<>
struct Hash<float>
{
    uint operator()(float key, uint tableSize) const
    {
        data.input = key;
        return ((data.output >> SHIFT) | (data.output << SHIFT)) % tableSize;
    }

private:
    static const short SHIFT = sizeof(float) * 8 / 2;

    mutable union
    {
        float input;
        uint output;
    } data;
};

} // end of namespace "slice"


#endif // HASHFUNC_H_INCLUDED
