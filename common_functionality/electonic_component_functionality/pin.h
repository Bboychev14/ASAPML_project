#ifndef COMMON_FUNCTIONALITY_PIN_H
#define COMMON_FUNCTIONALITY_PIN_H
#include "../machine_formater.cpp"
#include <string>

class Pin {
public:

    Pin();

    Pin(unsigned width_point, unsigned height_point);

    unsigned GetWidth() const;
    unsigned GetHeight() const;
    std::string getMachineFormat() const;


private:

    unsigned m_width_point;
    unsigned m_height_point;

};

#endif //COMMON_FUNCTIONALITY_PIN_H
