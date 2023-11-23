#include "electronic_component.h"
#include <iostream>

ElectronicComponent::ElectronicComponent(const std::string &id, const Pin &dimensions,const DataHandler::PinsCOntainer &pins)
        : m_id(id),
          m_dimensions(dimensions),
          m_pins(pins) {}

std::string ElectronicComponent::GetId() {
    return m_id;
}

Pin ElectronicComponent::GetDimensions() {
    return m_dimensions;
};

DataHandler::PinsCOntainer ElectronicComponent::GetPins() {
    return m_pins;
};

std::string ElectronicComponent::getMachineFormat() const
{
    std::string result(m_id); //copies el. comp. id to result
    result.append(": ");    // "id: "
    result.append(m_dimensions.getMachineFormat()); // "id: (width(u8)height(u8))"
    for(const auto &pins : m_pins)
    {
        result.push_back(' ');
        result.append(pins.getMachineFormat());
    }
    return result;
}
/*
int main()
{
    ElectronicComponent el("2N3904", {7,3}, {{1,1}, {3,1}, {5,1}});
    std::cout<<el.getMachineFormat();
}*/