#pragma once
#include "../common_functionality/order_functionality/order_manager.h"
#include "../common_functionality/electonic_component_functionality/electronic_component_manager.h"
#include "../common_functionality/hardware_component_functionality/hardware_component_manager.h"
#include <utility>

class Bit{
public:
    Bit();
    static const std::string PRODUCTION_PATH;
    static const std::string HARDWARE_PATH;
    static const std::string ELECTRONIC_PATH;
    static const std::string JOBS_PATH;

    void getHW_IDs();
    const HardwareComponent& getHW(const int ID) const;
    void print() const; //print proccess
    void output(const std::vector<std::vector<char>>& matrix) const;
    void cutBoard(const std::vector<std::vector<char>>& matrix, size_t width, size_t height);
    void calculatePinPositions(const HardwareComponent& target, std::vector<std::pair<size_t, size_t>>& positions);

private:
    OrderManager m_orders_manager; //change constructors for objects here
    HardwareComponentManager m_hardware_manager;
    ElectronicComponentManager m_electronic_manager;
    std::vector<int> hw_IDs;
    void loadData();
};

const std::string Bit::PRODUCTION_PATH = "../data/production.txt";
const std::string Bit::HARDWARE_PATH = "../data/HW_machine.txt";
const std::string Bit::ELECTRONIC_PATH = "..data/EL_Machine.txt";
const std::string Bit::JOBS_PATH = "../data/printing_jobs.txt";