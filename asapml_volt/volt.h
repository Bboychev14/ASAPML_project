#pragma once
#include "../common_functionality/order_functionality/order_manager.h"
#include "../common_functionality/electonic_component_functionality/electronic_component_manager.h"
#include "../common_functionality/hardware_component_functionality/hardware_component_manager.h"
#include "../common_functionality/data_handler/data_handler.h"
#include <stdexcept>
#include <map>
#include <algorithm>


class Volt
{
private:
    OrderManager m_order_manager;
    OrderManager m_production_manager;
    OrderManager m_jobs_manager;
    HardwareComponentManager m_hardware_manager;
    ElectronicComponentManager m_electronic_manager;
    std::map<std::string, size_t> m_inventory_map; //map of invetory identical to amp

public:
    Volt();

    static const std::string ORDER_PATH;
    static const std::string HISTORY_PATH;
    static const std::string PRODUCTION_PATH;
    static const std::string INVENTORY_PATH;
    static const std::string JOBS_PATH;

    static const std::string HARDWARE_PATH;
    static const std::string ELECTRONIC_PATH;

    //void loadLibraries();

    void readOrders(); //read orders from orders.txt(deserealize)
    void saveToHistory(); //add to history.txt when order is completed
    void saveToJobs(); //saves to print jobs
    void updateOrders(); //read'n delete ready orders in production delete in orders.txt

    void proccessOrders(); //take orders and leave it pending or printing

    void loadInvetory(); //reads inventory;
    void saveMapToInvetory() const; //saves new inventory

    bool checkInventory(const std::string& id, size_t count); //check for component availability
    const size_t getBoardSize(const Pin& coords) const; //figures out what board HW needs
};

const std::string Volt::ORDER_PATH = "../data/orders.txt";
const std::string Volt::HISTORY_PATH = "../data/history.txt";
const std::string Volt::PRODUCTION_PATH = "../data/production.txt";
const std::string Volt::INVENTORY_PATH = "../data/inventory.txt";
const std::string Volt::JOBS_PATH = "../data/jobs.txt";
const std::string Volt::HARDWARE_PATH = "../data/HardwareComponentsLibrary.txt";
const std::string Volt::ELECTRONIC_PATH = "../data/ElectronicComponentsLibrary.txt";