#include <stdint.h>
#include <iostream>
#include "electonic_component_functionality/pin.h"

using u8 = uint8_t;
using u16 = uint16_t;

u16 bitCombiner(const u8 a, const u8 b)
{
    return (b << 8) | a;
}

u8 getLowerByte(const u16 value)
{
    return static_cast<u8>(value);
}

u8 getUpperByte(const u16 value)
{
    return static_cast<u8>(value >> 8);
}

std::pair<int,int> getPair(const u16 value)
{
    std::pair<int,int> result;
    result.second = getLowerByte(value);
    result.first =  getUpperByte(value);
    
    return result; 
}

Pin getPin(const u16 value)
{
    std::pair<int,int> result;
    result.second = getLowerByte(value);
    result.first =  getUpperByte(value);
    
    return Pin(result.first, result.second); 
}