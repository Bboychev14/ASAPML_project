#include "pin.h"

Pin::Pin() : m_width_point(0), m_height_point(0) {};

Pin::Pin(const unsigned width_point, const unsigned  height_point) :
        m_width_point(width_point),
        m_height_point(height_point) {}

unsigned Pin::GetWidth() const {
    return m_width_point;
};
unsigned Pin::GetHeight() const {
    return m_height_point;
};

std::string Pin::getMachineFormat() const
{
    return std::to_string(bitCombiner(m_width_point, m_height_point));
}