#include "volt.h"

Volt::Volt()
{
    readOrders();
    proccessOrders();
    updateOrders();
}

void Volt::readOrders()
{
    m_order_manager.LoadOrders(); //no path = ../data/orders.txt
    m_jobs_manager.LoadOrders(JOBS_PATH);
    m_production_manager.LoadOrders(PRODUCTION_PATH);
}

void Volt::saveToHistory()
{
    m_production_manager.SaveOrdersInLibrary(HISTORY_PATH);
}

void Volt::updateOrders()
{
    OrderManager::ordersContainer production = m_production_manager.getOrders();
    for(size_t i = 0; i < production.size(); i++)
    {
        m_order_manager.removeOrder(production[i].getOrderId());
    }
    saveToHistory();
    m_order_manager.SaveOrdersInLibrary();
    std::fstream updated_production(PRODUCTION_PATH, std::ios::trunc | std::ios::in);
    if(updated_production)
    {
        updated_production.close();
    }
    else if(!updated_production)
    {
        throw std::runtime_error("production.txt couldn't be opened!");
    }
    updated_production.close();
}

void Volt::loadInvetory()
{
    std::fstream inventoryFile(INVENTORY_PATH);
    if(!inventoryFile)
    {
        throw std::runtime_error("Unable to open inventory.txt");
    }
    else
    {
        
        std::string tempInventoryLine;
        while(getline(inventoryFile, tempInventoryLine))
        {
            std::istringstream iss(tempInventoryLine);
            std::string tempId;
            size_t tempQuantity;
            if(iss >> tempId >> tempQuantity)
            {
                m_inventory_map[tempId] = tempQuantity;
            }
        }
    }
    inventoryFile.close();
}

bool Volt::checkInventory(const std::string& id, size_t count)
{
    
    for(auto& pair : m_inventory_map)
    {
        if(pair.first == id)
        {
            if(count > pair.second)
            {
                return false; //not enough in stock
            }
            else
            {
                pair.second -= count;
                return true; //has enough stock
            }
        }
        else
        {
            m_inventory_map[id] = 0; //add to inventory
            return false; //new component
        }
    }

}

void Volt::saveMapToInvetory() const
{
    std::ofstream inventory_file(INVENTORY_PATH, std::ios::trunc);
    for(const auto& pair : m_inventory_map)
    {
        inventory_file << pair.first << ' ' <<pair.second;
    }
    inventory_file.close();
}

const size_t Volt::getBoardSize(const Pin& coords) const
{
    size_t max;
    size_t width = coords.GetWidth();
    size_t height = coords.GetHeight();
    if(width > height)
    {
        max = width;
    }
    else
    {
        max = height;
    }
    size_t rem = max % 8;
    if(rem != 0)
    {
        return (max + 8 - rem);
    }
    return max;
}

void Volt::saveToJobs()
{
    m_jobs_manager.SaveOrdersInLibrary(JOBS_PATH);
}


void Volt::proccessOrders()
{
    m_order_manager.getVoltSorted();
    loadInvetory(); //read invetory.txt load it into map
    OrderManager::ordersContainer orders = m_order_manager.getOrderContainer();
    for(size_t i = 0; i < orders.size(); i++)
    {
        if(orders[i].getStatus() != "printing")
        {
            bool stock_flag = true;
            std::string hw_id = orders[i].getHardwareId();
            HardwareComponent hw = m_hardware_manager.getHWComponent(hw_id);
            DataHandler::RawDataContainer el_IDs = hw.GetElCompIds();
            std::map<std::string, size_t> order_components;
            for(size_t j = 0; j < el_IDs.size(); i++)
            {
                if(order_components.find(el_IDs[j]) != order_components.end())
                {
                    order_components[el_IDs[j]] = order_components[el_IDs[j]] + 1;
                }
                else
                {
                    order_components[el_IDs[j]] = 1;
                }
            }
            size_t board = getBoardSize(hw.GetDimensions());
            order_components[std::to_string(board)] = 1;
            for(const auto& pair : order_components)
            {
                if(!checkInventory(pair.first, pair.second))
                {
                    stock_flag = false;
                    break;
                }
            }
            if(stock_flag)
            {
                orders[i].setStatus("printing");
                m_jobs_manager.addOrder(orders[i]);
            }
            else
            {
                orders[i].setStatus("pending");
            }
        }
    }
    saveToJobs();
    saveMapToInvetory();
}