#ifndef COMMON_FUNCTIONALITY_ELECTRONIC_COMPONENT_MANAGER_H
#define COMMON_FUNCTIONALITY_ELECTRONIC_COMPONENT_MANAGER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


#include "electronic_component.h"

class ElectronicComponentManager {
public:
    ElectronicComponentManager();

    void SaveElComponentsInLibrary();

    void SaveElComponentsInMachine();

    void ReadElComponentsInMachine();

    void CreateMultipleNewElCompFromData(DataHandler::RawDataContainer &data);

    bool IsElCompAvailable(const std::string &id);

    static DataHandler::RawDataContainer ReturnDataForElCompForHardware(std::vector<std::string> &dataForHw);

    static DataHandler::RawDataContainer ReturnElCompDesign(DataHandler::RawDataContainer &data);

    static DataHandler::RawDataContainer ReturnNeededElCompIds(DataHandler::RawDataContainer &data);

private:

    std::vector<ElectronicComponent> m_availableElComp;

private:

    void CreateElCompFromData(DataHandler::RawDataContainer &data);

    static std::string ConstructPinsString(const DataHandler::PinsCOntainer &pins);

    static DataHandler::RawDataContainer ReturnDataFromElComp(ElectronicComponent &elComp);

    void LoadElectronicComponents();

    static DataHandler::PinsCOntainer CreateContainerOfPins(std::string &data);

    static std::vector<DataHandler::RawDataContainer> CreateElDesignsVector(DataHandler::RawDataContainer &data);

};

#endif //COMMON_FUNCTIONALITY_ELECTRONIC_COMPONENT_MANAGER_H
