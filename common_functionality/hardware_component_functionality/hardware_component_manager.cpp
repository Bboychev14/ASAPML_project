#include "hardware_component_manager.h"
#include "../data_handler/file_handler.h"

HardwareComponentManager::HardwareComponentManager() {
    //LoadHWComponents();
}
//machine format needed
void HardwareComponentManager::CreateHWCompFromData(DataHandler::RawDataContainer &data) {
    if (data.empty()) {
        return;
    }
    

    std::string id = DataHandler::SplitReturnRightPart(data[0]);
    unsigned width = std::stoi(DataHandler::SplitReturnRightPart(data[1]));
    unsigned height = std::stoi(DataHandler::SplitReturnRightPart(data[2]));
    std::vector<std::string> componentsContainer = ReturnDataForComponentsOfHW(data); //el components needed
    //el components need to be saved in machine level format

    Pin dimensions(width, height);
    std::vector<std::string> componentsIds;
    std::vector<Pin> componentsPinsPositions;
    std::vector<int> rotations;
    FillDataForHWComp(componentsIds, componentsPinsPositions, rotations, componentsContainer);
    std::vector<std::vector<Pin>> connections = CreateConnectionsContainer(data[data.size() - 1]);
    m_availableHardwareComp.emplace_back(id, dimensions, componentsIds, componentsPinsPositions, rotations,
                                         connections);
}

std::vector<std::string> HardwareComponentManager::GetAllIDs() const
{
    std::vector<std::string> result;
    for(size_t i = 0 ; i < m_availableHardwareComp.size(); i++)
    {
        result.push_back(m_availableHardwareComp[i].GetId());
    }
    return result;
}

const HardwareComponent& HardwareComponentManager::getHWComponent(const std::string& id) const
{
    for(size_t i = 0; i < m_availableHardwareComp.size(); i++)
    {
        if(m_availableHardwareComp[i].GetId() == id)
        {
            return m_availableHardwareComp[i];
        }
    }
}

void HardwareComponentManager::readHWComponentsInMachine()
{
    std::string library_path = "../../data/HW_machine.txt";
    std::ifstream library(library_path);
    if (!library.is_open() || library.fail()) {
        std::cout << COMMON_CONSTANTS::UNABLE_TO_OPEN_FAIL_MSG << std::endl;
        library.close();
        return;
    }
    std::string data;
    while(getline(library, data))
    {
        if(data.empty())
        {
            continue;
        }
        std::string temp_ID;
        std::string dimensions;
        DataHandler::RawDataContainer temp_componentsID;
        DataHandler::PinsCOntainer temp_elCompPinPos;
        std::vector<int> temp_rotations;
        std::vector<DataHandler::PinsCOntainer> temp_connections;
        std::copy(data.begin(), data.begin() + data.find(':'), temp_ID);
        std::copy(data.find(':') + 2, data.end() - 1, dimensions);
        size_t sti;
        dimensions = dimensions.substr(sti + 1);
        Pin temp_dimensions(std::stoi(dimensions, &sti), std::stoi(dimensions));
        do
        {
            getline(library, data);
            std::string temp_El_ID;
            std::copy(data.begin() + 1, data.find(':'), temp_El_ID);
            data = data.substr(data.find(':') + 1);
            size_t size;
            size_t dec = std::stoi(data, &size);
            size_t count  = dec;
            data = data.substr(size);
            for(size_t i = 0; i < count; i++)
            {
                temp_componentsID.push_back(temp_El_ID); //multiple el id's
                dec = std::stoi(data, &size);
                data = data.substr(size);
                temp_elCompPinPos.push_back(getPin(dec));
                dec = std::stoi(data, &size);
                data = data.substr(size);
                temp_rotations.push_back(dec);
            }
        } while (data[0] == '\t');
        getline(library, data);
        std::stringstream ss(data);
        char ch;
        int num1, num2;
        while(ss >> ch >> num1 >> ch >> num2)
        {  
            temp_connections.push_back(num1, num2);
            ss>>ch;
        }
        m_availableHardwareComp.push_back(HardwareComponent(temp_ID, temp_dimensions, temp_componentsID, temp_elCompPinPos, temp_rotations, temp_connections));
    }
}

void HardwareComponentManager::saveHWComponentsInMachine()
{
    std::string library_path = "../data/HW_machine.txt";
    std::ofstream library(library_path);
    if (!library.is_open() || library.fail()) {
        std::cout << COMMON_CONSTANTS::UNABLE_TO_OPEN_FAIL_MSG << std::endl;
        library.close();
        return;
    }
    std::string data;
    for(auto &el : m_availableHardwareComp)
    {
        data.append(el.getMachineFormat());
        data.push_back('\n');
        data.push_back('\n');
    }
    library << data;
    library.close();
}


//HW blueprint format

void HardwareComponentManager::SaveHWComponentsInLibrary() {
    //        std::string hwCompLibName = "../test_data/test_hard_comp_lib.txt";
    std::string hwCompLibName = "test_hard_comp_lib.txt";
    std::fstream hwCompLib(hwCompLibName.c_str(), std::ifstream::out);
    if (!hwCompLib.is_open() || hwCompLib.fail()) {
        std::cout << COMMON_CONSTANTS::UNABLE_TO_OPEN_FAIL_MSG << std::endl;
        hwCompLib.close();
        return;
    }
    for (auto &el: m_availableHardwareComp) {
        std::vector<std::string> data = ReturnDataFromHwComp(el);
        std::for_each(data.begin(), data.end(), [&hwCompLib](const std::string &el) {
            hwCompLib << el;
        });
    }
    hwCompLib.close();
    saveHWComponentsInMachine();
}
//current format
    /*
        id : 2NDSA321
        width : size_t
        height : size_t
        components :
        el id: (x,y(coordinates)),r(int rotation)
        /new line
        el id: (x,y(coordinates)),r(int rotation)
        /new line
        connections: (int(width).int(height),int(width).int(height), ...),
        /new line
        
    */
DataHandler::RawDataContainer HardwareComponentManager::ReturnDataFromHwComp(HardwareComponent &hwComp) {
    std::vector<std::string> data;
    data.emplace_back("id: " + hwComp.GetId() + '\n');
    data.emplace_back("width: " + std::to_string(hwComp.GetDimensions().GetWidth()) + '\n');
    data.emplace_back("height: " + std::to_string(hwComp.GetDimensions().GetHeight()) + '\n');
    data.emplace_back("components: \n");
    ConstructDataForHwComponents(data, hwComp);
    ConstructDataForHwConnections(data, hwComp);
    data[data.size() - 1].push_back('\n');
    return data;
}

void
HardwareComponentManager::ConstructDataForHwComponents(DataHandler::RawDataContainer &data, HardwareComponent &hcEl) {
    for (size_t i = 0; i < hcEl.GetElCompIds().size(); i++) {
        data.emplace_back(
                hcEl.GetElCompIds()[i] + ": " + '(' + std::to_string(hcEl.GetElCompPinsPositions()[i].GetWidth()) +
                ',' + std::to_string(hcEl.GetElCompPinsPositions()[i].GetHeight()) + ")," +
                std::to_string(hcEl.GetElCompRotations()[i]) + '\n');
    }
}

void
HardwareComponentManager::ConstructDataForHwConnections(DataHandler::RawDataContainer &data, HardwareComponent &hcEl) {
    std::string currString = "connections:";
    for (auto &el: hcEl.GetConnections()) {
        std::string tmpString = " (";
        for (auto el2: el) {
            tmpString += std::to_string(el2.GetWidth()) + "." + std::to_string(el2.GetHeight()) + ",";
        }
        tmpString.pop_back();
        tmpString += "),";
        currString += tmpString;
    }
    currString.pop_back();

    data.emplace_back(currString + "\n");
}


bool HardwareComponentManager::IsHWCompAvailable(const std::string &id) {
    auto foundEl = std::find_if(m_availableHardwareComp.begin(), m_availableHardwareComp.end(),
                                [&id](HardwareComponent el) {
                                    return el.GetId() == id;
                                });
    return foundEl != m_availableHardwareComp.end();
}

DataHandler::RawDataContainer
HardwareComponentManager::ReturnDataForHardwareFromInput(DataHandler::RawDataContainer &data) {
    auto firstEl = DataHandler::ReturnItrToElementByOption(data, "id");
    auto lastEl = DataHandler::ReturnItrToElementByOption(data, "connections");
    DataHandler::RawDataContainer dataHW;
    if (firstEl == data.end() || lastEl == data.end()) {
        return dataHW;
    }
    dataHW.assign(firstEl, lastEl + 1);
    return dataHW;
}

void HardwareComponentManager::LoadHWComponents() {
//        std::string HWCompLibName = "../test_data/test_hard_comp_lib.txt";
    std::string HWCompLibName = "test_hard_comp_lib.txt";
    FileHandler handler(HWCompLibName);
    std::vector<DataHandler::RawDataContainer> fullData;
    handler.ExtractDataForAllObjects(fullData);
    std::for_each(fullData.begin(), fullData.end(), [&](std::vector<std::string> &el) {
        CreateHWCompFromData(el);
    });
}

DataHandler::RawDataContainer
HardwareComponentManager::ReturnDataForComponentsOfHW(DataHandler::RawDataContainer &dataForHw) {
    auto firstEl = DataHandler::ReturnItrToElementByOption(dataForHw, "components");
    auto lastEl = DataHandler::ReturnItrToElementByOption(dataForHw, "connections");
    DataHandler::RawDataContainer dataForComponents;
    if (firstEl == dataForHw.end() || lastEl == dataForHw.end()) {
        return dataForComponents;
    }
    std::copy(firstEl + 1, lastEl, std::back_inserter(dataForComponents));
    return dataForComponents;
}


void HardwareComponentManager::FillDataForHWComp(DataHandler::RawDataContainer &componentsIds,
                                                 DataHandler::PinsCOntainer &componentsPinsPositions,
                                                 std::vector<int> &rotations, DataHandler::RawDataContainer &data) {
    for (auto &line: data) {
        componentsIds.emplace_back(DataHandler::SplitReturnLeftPart(line));
        std::string importantPart = DataHandler::SplitReturnRightPart(line);
        DataHandler::RawDataContainer extractedData = DataHandler::ReturnNumericData(importantPart);
        componentsPinsPositions.emplace_back(std::stoi(extractedData[0]), std::stoi(extractedData[1]));
        rotations.push_back(std::stoi(extractedData[2]));
    }
}

std::vector<DataHandler::PinsCOntainer> HardwareComponentManager::CreateConnectionsContainer(const std::string &data) {
    std::string importantPart = DataHandler::SplitReturnRightPart(data);
    char delimiter = ' ';
    std::istringstream split(importantPart);
    DataHandler::RawDataContainer splitDataConnections;
    for (std::string each; std::getline(split, each, delimiter); splitDataConnections.push_back(each));
    std::vector<std::vector<Pin>> connections;
    for (auto el: splitDataConnections) {
        DataHandler::RawDataContainer someData = DataHandler::ReturnNumericData(el);
        std::vector<Pin> currConnections;
        for (size_t i = 0; i < someData.size(); i += 2) {
            currConnections.emplace_back(std::stoi(someData[i]), std::stoi(someData[i + 1]));
        }
        connections.push_back(currConnections);
    }
    return connections;
}