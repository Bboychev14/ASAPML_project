#include "../data_handler/file_handler.h"

//how is priority saved as a string
const std::string OrderManager::HIGH_PRIORITY_STR = "high";
const std::string OrderManager::NORMAL_PRIORITY_STR = "normal";
const std::string OrderManager::UNPROCESSED_STATUS = "unprocessed";
const std::string OrderManager::PENDING_STATUS = "pending";
const std::string OrderManager::PRINTING_STATUS = "printing";

OrderManager::OrderManager(const std::string& path) : m_lastGivenIndex(0) {
    //LoadOrders(path);
    //LoadConfigFile();

}

bool OrderManager::voltSort(const Order& one, const Order& two) const
{
    if(one.getStatus() == two.getStatus())
    {
        if(one.getPriority() == NORMAL_PRIORITY_STR && two.getPriority() == HIGH_PRIORITY_STR)
        {
            return false;
        }
        return true;
    }
    else if(one.getStatus() != PENDING_STATUS && two.getStatus() != PRINTING_STATUS)
    {
        return false;
    }
    return true;
}

void OrderManager::getVoltSorted()
{
    std::sort(m_orders.begin(), m_orders.end(), voltSort);
}
OrderManager::ordersContainer& OrderManager::getOrderContainer()
{
    return m_orders;
}

void OrderManager::addOrder(const Order& order)
{
    m_orders.push_back(order);
}

void OrderManager::CreateOrderFromInput(DataHandler::RawDataContainer &data) {
    int orderId = ReturnNewId();
    std::string clientName = DataHandler::SplitReturnRightPart(data[0]);
    std::string priority = DataHandler::SplitReturnRightPart(data[1]);
    std::string status = OrderManager::UNPROCESSED_STATUS;
    std::string hardwareId = DataHandler::SplitReturnRightPart(data[2]);
    addOrder(orderId, clientName, priority, status, hardwareId);
}


void OrderManager::CreateOrderFromLibrary(DataHandler::RawDataContainer &data) {
    int oid = std::stoi(DataHandler::SplitReturnRightPart(data[0]));
    std::string clientName = DataHandler::SplitReturnRightPart(data[1]);
    std::string priority = DataHandler::SplitReturnRightPart(data[2]);
    std::string status = DataHandler::SplitReturnRightPart(data[3]);
    std::string id = DataHandler::SplitReturnRightPart(data[4]);
    addOrder(oid, clientName, priority, status, id);
}

void OrderManager::SaveConfigInfo() const {
    //    std::string confFileName = "./order_manager_cnfg.txt";
    std::string confFileName = "order_manager_cnfg.txt";
    std::fstream confFile(confFileName.c_str(), std::ifstream::out);
    if (!confFile.is_open() || confFile.fail()) {
        std::cout << COMMON_CONSTANTS::UNABLE_TO_OPEN_FAIL_MSG << std::endl;
        confFile.close();
        return;
    }
    confFile << m_lastGivenIndex;
    confFile.close();
}

void OrderManager::PrintOrders() const {
    for (auto &el: getOrders()) {
        DataHandler::RawDataContainer dataForOrder = ReturnDataFromOrder(el);
        std::for_each(dataForOrder.begin(), dataForOrder.end(), [](std::string &string) {
            string.pop_back();
            std::cout << string << std::endl;
        });
    }
}

void OrderManager::PrintOrders(const std::string &userChoice) const {
    for (auto &el: getOrders()) {
        DataHandler::RawDataContainer dataForOrder = ReturnDataFromOrder(el);
        std::for_each(dataForOrder.begin(), dataForOrder.end(), [&el, &userChoice](std::string &string) {
            if (el.getPriority() == userChoice) {
                string.pop_back();
                std::cout << string << std::endl;
            }
        });
    }
}

void OrderManager::SaveOrdersInLibrary(const std::string& path) {
    //        std::string ordersLibName = "../test_data/test_orders.txt.txt";
    std::string ordersLibName = path;
    std::fstream ordersLibSave(ordersLibName.c_str(), std::ifstream::out);
    if (!ordersLibSave.is_open() || ordersLibSave.fail()) {
        std::cout << COMMON_CONSTANTS::UNABLE_TO_OPEN_FAIL_MSG << std::endl;
        ordersLibSave.close();
        return;
    }

    for (auto &el: m_orders) {
        std::vector<std::string> data = ReturnDataFromOrder(el);
        std::for_each(data.begin(), data.end(), [&ordersLibSave](const std::string &string) {
            ordersLibSave << string;
        });
    }
    ordersLibSave.close();
}
//oid = order_id (makes more sense to be just id) !!!order id should be an int, hexed and saved as std::string
//id = hardware_id (makes more sense to be hardware_id) 
DataHandler::RawDataContainer OrderManager::ReturnDataFromOrder(const Order &order) {
    DataHandler::RawDataContainer data;
    data.emplace_back("id: " + std::to_string(order.getOrderId()) + '\n');
    data.emplace_back("client: " + order.getClient() + '\n');
    data.emplace_back("priority: " + order.getPriority() + '\n');
    data.emplace_back("status: " + order.getStatus() + '\n');
    data.emplace_back("hardware_id: " + order.getHardwareId() + '\n');
    data[data.size() - 1].push_back('\n');

    return data;
    //format
    /*
        id: unique int
        client: client_name(std::string)
        priority: low, high(std::string)
        status: unproccessed, pending(std::string)
        hardware_id: string id(std::string)
        /new line
        new id: ...
    */
}

DataHandler::RawDataContainer OrderManager::ReturnDataForOrderFromInput(DataHandler::RawDataContainer &data) {
    auto firstEl = data.begin();
    auto lastEl = DataHandler::ReturnItrToElementByOption(data, "id");
    DataHandler::RawDataContainer dataForOrder(firstEl, lastEl + 1);
    return dataForOrder;
}

void OrderManager::LoadOrders(const std::string& path) {
    //    std::string ordersFileName = "../test_data/test_orders.txt";
    std::string ordersFileName = path;
    FileHandler handler(ordersFileName);
    std::vector<DataHandler::RawDataContainer> fullData;
    handler.ExtractDataForAllObjects(fullData);
    std::for_each(fullData.begin(), fullData.end(), [&](std::vector<std::string> &el) {
        CreateOrderFromLibrary(el);
    });
}

void OrderManager::LoadConfigFile() {
//    std::string confFileName = "./order_manager_cnfg.txt";
    std::string confFileName = "order_manager_cnfg.txt";
    FileHandler handler(confFileName);
    if (!handler.OpenInputFile()) {
        std::cout << COMMON_CONSTANTS::UNABLE_TO_OPEN_FAIL_MSG << std::endl;
        return;
    }
    std::string lastIdString;
    handler.ExtractSingleLine(lastIdString);
    m_lastGivenIndex = std::stoi(lastIdString);
    handler.CloseInputFile();
}

int OrderManager::ReturnNewId() {
    return m_lastGivenIndex++;
}


void OrderManager::addOrder(const int name, const std::string &order_id, const std::string &priority,
                            const std::string &status,
                            const HardwareComponent &hardware) {
    //create new object(Order)
    m_orders.emplace_back(name, order_id, priority, status, hardware);
}


void OrderManager::addOrder(const int order_id, const std::string &name, const std::string &priority,
                            const std::string &status,
                            const std::string &hardware_id) {
    m_orders.emplace_back(order_id, name, priority, status, hardware_id);
}


void OrderManager::removeOrder(const int &order_id) {
    //iterator to order with the same id
    auto it = std::find_if(m_orders.begin(), m_orders.end(), [order_id](const Order &order) {
        return order_id == order.getOrderId();
    });
    //if it finds the order delete it
    if (it != m_orders.end()) {
        std::cout << OHM_CONSTANTS::SUCCESS_DELETE_ORDER_MSG << order_id << '.' << std::endl;
        m_orders.erase(it);
    } else {
        std::cout << OHM_CONSTANTS::FAIL_DELETE_ORDER_MSG << std::endl;
    }
}

const OrderManager::ordersContainer &OrderManager::getOrders() const {
    return m_orders;
}

const OrderManager::ordersContainer &OrderManager::getFilteredOrders() const {
    //orders sorted by priority;
    ordersContainer filtered =m_orders;
    std::sort(filtered.begin(), filtered.end(), sortByPrio); // Not compiling because of sortByPrio
    //check again should be fixed!
    return filtered;
}

bool OrderManager::sortByPrio(const Order &one, const Order &two) const {
    //return (one.getPriority() == NORMAL_PRIORITY_STR && two.getPriority() == HIGH_PRIORITY_STR);
    const std::string& prio_one = one.getPriority();
    const std::string& prio_two = two.getPriority();
    return(prio_one == HIGH_PRIORITY_STR || prio_one == NORMAL_PRIORITY_STR && prio_two == NORMAL_PRIORITY_STR);
}
/*
int main() {

    OrderManager orders;
    orders.addOrder("01","Alex",OrderManager::HIGH_PRIORITY_STR,OrderManager::PENDING_STATUS, "Darlingtion_Pair01");
    orders.addOrder("02","Alex",OrderManager::NORMAL_PRIORITY_STR,OrderManager::UNPROCESSED_STATUS, "Darlingtion_Pair01");
    orders.addOrder("03","Alex",OrderManager::HIGH_PRIORITY_STR,OrderManager::UNPROCESSED_STATUS_STATUS, "Darlingtion_Pair01");
    orders.addOrder("04","Alex",OrderManager::NORMAL_PRIORITY_STR,OrderManager::PENDING_STATUS, "Darlingtion_Pair01");
    OrderManager::ordersContainer filtered = orders.getFilteredOrders();
    for(auto order& : orders)
    {
        std::cout<<order.getOrderId()<<std::endl;
    }

}
*/