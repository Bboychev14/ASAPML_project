#ifndef COMMON_FUNCTIONALITY_HARDWARE_COMPONENT_MANAGER_H
#define COMMON_FUNCTIONALITY_HARDWARE_COMPONENT_MANAGER_H

#include "hardware_component.h"


class HardwareComponentManager {
public:
    HardwareComponentManager();

    void CreateHWCompFromData(DataHandler::RawDataContainer &data);

    void saveHWComponentsInMachine();

    void readHWComponentsInMachine();

    void SaveHWComponentsInLibrary();

    static std::vector<std::string> ReturnDataFromHwComp(HardwareComponent &hwComp);

    bool IsHWCompAvailable(const std::string &id);

    std::vector<std::string> GetAllIDs() const;

    const HardwareComponent& getHWComponent(const int id) const;

    void RemoveHWComponent(const std::string &id); //used to remove hardware from collection: ex. Used in production.txt

    static DataHandler::RawDataContainer ReturnDataForHardwareFromInput(DataHandler::RawDataContainer &data);

private:
    std::vector<HardwareComponent> m_availableHardwareComp;


private:
    static void ConstructDataForHwComponents(DataHandler::RawDataContainer &data, HardwareComponent &el);

    static void ConstructDataForHwConnections(DataHandler::RawDataContainer &data, HardwareComponent &el);

    void LoadHWComponents();

    static DataHandler::RawDataContainer ReturnDataForComponentsOfHW(DataHandler::RawDataContainer &dataForHw);

    static void
    FillDataForHWComp(DataHandler::RawDataContainer &componentsIds, DataHandler::PinsCOntainer &componentsPinsPositions,
                      std::vector<int> &rotations, DataHandler::RawDataContainer &data);

    static std::vector<DataHandler::PinsCOntainer> CreateConnectionsContainer(const std::string &data);


};

#endif //COMMON_FUNCTIONALITY_HARDWARE_COMPONENT_MANAGER_H
