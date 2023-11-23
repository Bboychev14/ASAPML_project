#ifndef COMMON_FUNCTIONALITY_ELECTRONIC_COMPONENT_H
#define COMMON_FUNCTIONALITY_ELECTRONIC_COMPONENT_H

#include <string>
#include <vector>
#include <utility>
#include "pin.h"
#include "pin.cpp"
#include "../data_handler/data_handler.h"
  

class ElectronicComponent {
public:

    ElectronicComponent() = default;

    ElectronicComponent(const std::string &id, const Pin &dimensions,const  DataHandler::PinsCOntainer &pins);

    std::string GetId();

    Pin GetDimensions();

    DataHandler::PinsCOntainer GetPins();

    std::string getMachineFormat() const; // returns machine-level formated string for the component


private:
    std::string m_id;
    Pin m_dimensions;
    DataHandler::PinsCOntainer m_pins;
};


#endif //COMMON_FUNCTIONALITY_ELECTRONIC_COMPONENT_H
