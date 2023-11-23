#ifndef S05_PROJECT_TEAM_SNABSQUAD_FILE_HANDLER_H
#define S05_PROJECT_TEAM_SNABSQUAD_FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include "../electonic_component_functionality/electronic_component_manager.h"
#include "../order_functionality/order_manager.h"
#include "../data_handler/constants.h"
#include "../data_handler/data_handler.h"

class FileHandler {
public:
    explicit FileHandler(std::string filename) : m_fileName(std::move(filename)) {};


    bool OpenInputFile() {
        m_inputFile.open(m_fileName.c_str(), std::ifstream::in);
        return m_inputFile.is_open() && !m_inputFile.fail();
    }

    bool OpenOutputFile() {
        m_outputFile.open(m_fileName.c_str(), std::fstream::out);
        return m_outputFile.is_open() && !m_outputFile.fail();
    }

    void CloseInputFile() {
        m_inputFile.close();
    }

    void CloseOutputFile() {
        m_outputFile.close();
    }

    void ExtractSingleLine(std::string &curLine) {
        std::getline(m_inputFile, curLine);
    }


    void ExtractDataForAllObjects(std::vector<DataHandler::RawDataContainer> &fullDataContainer) {
        if (!OpenInputFile()) {
            std::cout << COMMON_CONSTANTS::UNABLE_TO_OPEN_FAIL_MSG << std::endl;
            CloseInputFile();
            return;
        }
        while (m_inputFile) {
            std::vector<std::string> currentObjectData;
            ExtractDataForObject(currentObjectData);
            if (currentObjectData.empty()) {
                break;
            }
            fullDataContainer.push_back(currentObjectData);
        }
        CloseInputFile();
    }


private:
    std::string m_fileName;
    std::ifstream m_inputFile;
    std::ofstream m_outputFile;
private:
    void ExtractDataForObject(std::vector<std::string> &currentObjectData) {
        std::string curLine;
        while (true) {
            ExtractSingleLine(curLine);
            if (curLine.empty()) {
                break;
            }
            currentObjectData.push_back(curLine);
        }
    }


};

#endif //S05_PROJECT_TEAM_SNABSQUAD_FILE_HANDLER_H
