#include "electronic_component_manager.h"
#include "../data_handler/file_handler.h"

ElectronicComponentManager::ElectronicComponentManager() {
    //LoadElectronicComponents(path);
}

void ElectronicComponentManager::CreateElCompFromData(DataHandler::RawDataContainer &data) {
    std::string id = DataHandler::SplitReturnRightPart(data[0]);
    unsigned width = static_cast<unsigned>(std::stoi(DataHandler::SplitReturnRightPart(data[1])));
    unsigned height = static_cast<unsigned>(std::stoi(DataHandler::SplitReturnRightPart(data[2])));
    Pin dimensions(width, height);
    std::vector<Pin> pins = CreateContainerOfPins(data[3]);
    m_availableElComp.emplace_back(id, dimensions, pins);
}

void ElectronicComponentManager::ReadElComponentsInMachine()
{
    std::string library_path = "../data/EL_Machine.txt";
    std::ifstream machine_library(library_path);
    if (!machine_library.is_open() || machine_library.fail()) {
        std::cout << COMMON_CONSTANTS::UNABLE_TO_OPEN_FAIL_MSG << std::endl;
        machine_library.close();
        return;
    }
    std::string data;
    while(getline(machine_library, data))
    {
        if(data.empty())
        {
            countinue;
        }
        std::string temp_ID = data.substr(0, data.find(':'))
        data = data.substr(data.find(':') + 2);
        std::stringstream ss(data);
        size_t number;
        DataHandler::PinsCOntainer temp_pins;
        ss >> number;
        Pin temp_dimensions(getPin(number));
        while(ss >> number)
        {
            v.push_back(getPin(number));
        }
        m_availableElComp.push_back(ElectronicComponent(temp_ID, temp_dimensions, temp_pins));
    }
}

void ElectronicComponentManager::SaveElComponentsInMachine()
{
    std::string library_path = "../data/EL_Machine.txt";
    std::ofstream machine_library(library_path);
    if (!machine_library.is_open() || machine_library.fail()) {
        std::cout << COMMON_CONSTANTS::UNABLE_TO_OPEN_FAIL_MSG << std::endl;
        machine_library.close();
        return;
    }
    std::string data;
    for(auto el : m_availableElComp)
    {
        data.append(el.getMachineFormat());
        data.push_back('\n');
    }
    machine_library << data;
    machine_library.close();
}

void ElectronicComponentManager::SaveElComponentsInLibrary() {
    //        std::string elCompLibName = "../test_data/test_el_comp_lib.txt";
    std::string elCompLibName = "test_el_comp_lib.txt";
    std::fstream elCompLib(elCompLibName.c_str(), std::fstream::out);
    if (!elCompLib.is_open() || elCompLib.fail()) {
        std::cout << COMMON_CONSTANTS::UNABLE_TO_OPEN_FAIL_MSG << std::endl;
        elCompLib.close();
        return;
    }
    for (auto el: m_availableElComp) {
        std::vector<std::string> data = ReturnDataFromElComp(el);
        std::for_each(data.begin(), data.end(), [&elCompLib](const std::string &el) {
            elCompLib << el;
        });
    }
    elCompLib.close();
    SaveElComponentsInMachine();
}

DataHandler::RawDataContainer ElectronicComponentManager::ReturnDataFromElComp(ElectronicComponent &elComp) {
    std::vector<std::string> data;
    data.emplace_back("id: " + elComp.GetId() + '\n');
    data.emplace_back("width: " + std::to_string(elComp.GetDimensions().GetWidth()) + '\n');
    data.emplace_back("height: " + std::to_string(elComp.GetDimensions().GetHeight()) + '\n');
    data.emplace_back(ConstructPinsString(elComp.GetPins()) + '\n');
    return data;
}

std::string ElectronicComponentManager::ConstructPinsString(const DataHandler::PinsCOntainer &pins) {
    std::string result = "pins: ";
    char bracedOne = '(';
    char bracedTwo = ')';
    char semiColon = ',';

    for (auto el: pins) {
        result += bracedOne + std::to_string(el.GetWidth()) + semiColon + std::to_string(el.GetHeight()) + bracedTwo +
                  semiColon;
    }
    result[result.size() - 1] = '\n';
    return result;
}


void ElectronicComponentManager::CreateMultipleNewElCompFromData(DataHandler::RawDataContainer &data) {
    if (data.empty()) {
        return;
    }
    std::vector<DataHandler::RawDataContainer> newDesigns = CreateElDesignsVector(data);
    for (auto &design: newDesigns) {
        CreateElCompFromData(design);
    }
}

bool ElectronicComponentManager::IsElCompAvailable(const std::string &id) {
    auto foundEl = std::find_if(m_availableElComp.begin(), m_availableElComp.end(), [&id](ElectronicComponent el) {
        return el.GetId() == id;
    });
    return foundEl != m_availableElComp.end();
}

DataHandler::RawDataContainer
ElectronicComponentManager::ReturnDataForElCompForHardware(DataHandler::RawDataContainer &dataForHw) {
    auto firstEl = DataHandler::ReturnItrToElementByOption(dataForHw, "components");
    auto lastEl = DataHandler::ReturnItrToElementByOption(dataForHw, "connections");
    std::vector<std::string> dataForComponents;
    if (firstEl == dataForHw.end() || lastEl == dataForHw.end()) {
        return dataForComponents;
    }
    dataForComponents.assign(firstEl + 1, lastEl);
    return dataForComponents;
}

DataHandler::RawDataContainer ElectronicComponentManager::ReturnElCompDesign(DataHandler::RawDataContainer &data) {
    auto firstEl = DataHandler::ReturnItrToElementByOption(data, "connections");
    std::vector<std::string> elCompDes;

    if (firstEl == data.end()) {
        return elCompDes;
    }
    elCompDes.assign(firstEl + 1, data.end());
    return elCompDes;
}

DataHandler::RawDataContainer ElectronicComponentManager::ReturnNeededElCompIds(DataHandler::RawDataContainer &data) {
    std::vector<std::string> designsIDs;

    for (const auto &line: data) {
        std::string infoType = DataHandler::SplitReturnLeftPart(line);
        if (infoType == "id") {
            designsIDs.emplace_back(line.substr(line.find(':') + 2));
        }
    }
    return designsIDs;
}

void ElectronicComponentManager::LoadElectronicComponents(const std::string& path) {
    //        std::string fileName = "../test_data/test_el_comp_lib.txt";
    std::string fileName = "../data/ElectronicComponentsLibrary.txt";
    FileHandler handler(path);
    std::vector<std::vector<std::string>> fullData;
    handler.ExtractDataForAllObjects(fullData);
    std::for_each(fullData.begin(), fullData.end(), [&](std::vector<std::string> &el) {
        CreateElCompFromData(el);
    });
}

DataHandler::PinsCOntainer ElectronicComponentManager::CreateContainerOfPins(std::string &data) {
    std::vector<std::string> pinsStrings = DataHandler::ReturnNumericData(data);
    std::vector<Pin> result;
    for (size_t i = 0; i < pinsStrings.size(); i += 2) {
        result.emplace_back(std::stoi(pinsStrings[i]), std::stoi(pinsStrings[i + 1]));
    }
    return result;
}


std::vector<DataHandler::RawDataContainer>
ElectronicComponentManager::CreateElDesignsVector(DataHandler::RawDataContainer &data) {
    auto firstEl = data.begin();
    auto lastEl = DataHandler::ReturnItrToElementByOption(data, "pins");

    std::vector<DataHandler::RawDataContainer> designs;
    while (firstEl != data.end()) {
        designs.emplace_back(firstEl, lastEl + 1);
        firstEl = lastEl + 1;
        lastEl = std::find_if(firstEl, data.end(), [](std::string &el) -> bool {
            std::string infoType = DataHandler::SplitReturnLeftPart(el);
            return infoType == "pins";
        });
    }
    return designs;
}

