#ifndef COMMON_FUNCTIONALITY_HARDWARE_COMPONENT_H
#define COMMON_FUNCTIONALITY_HARDWARE_COMPONENT_H

#include "..\electonic_component_functionality\electronic_component.h"
#include "..\electonic_component_functionality\electronic_component.cpp"
//each and everyone of us must paste the full path here, because the relative path does not work.
#include <map>

class HardwareComponent {
public:

    HardwareComponent() = default;

    HardwareComponent(
            const std::string &id, Pin &dimensions, DataHandler::RawDataContainer &componentsId, DataHandler::PinsCOntainer &elCompPinPos,
            std::vector<int> &rotations,
            std::vector<DataHandler::PinsCOntainer> &connections
    );

//update const functions and return types!!
    const std::string& GetId() const;

    Pin GetDimensions();

    std::vector<std::string> GetElCompIds();

    std::vector<Pin> GetElCompPinsPositions();

    std::vector<int> GetElCompRotations();

    const size_t getNeededBoard() const;

    std::vector<std::vector<Pin>> GetConnections();

    std::string getMachineFormat() const;


    void SetId(std::string id);

private:
    std::string m_id;
    Pin m_dimensions; //board size m x n
    DataHandler::RawDataContainer m_componentsIds; //el ids
    DataHandler::PinsCOntainer m_componentsPinsPositions; //el coordinates
    std::vector<int> m_elCompRotations; //rotations
    std::vector<DataHandler::PinsCOntainer> m_connections; //pins(x,y)
};

#endif //COMMON_FUNCTIONALITY_HARDWARE_COMPONENT_H
