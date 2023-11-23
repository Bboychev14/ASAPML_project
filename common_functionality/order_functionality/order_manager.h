#ifndef COMMON_FUNCTIONALITY_ORDER_MANAGER_H
#define COMMON_FUNCTIONALITY_ORDER_MANAGER_H

#include "order.h"

class OrderManager {
public:
    using ordersContainer = std::vector<Order>;

    OrderManager() = default;

    OrderManager(const std::string& path = "../data/orders.txt");

    void CreateOrderFromInput(DataHandler::RawDataContainer &data);

    void SaveConfigInfo() const;

    static std::vector<std::string> ReturnDataForOrderFromInput(DataHandler::RawDataContainer &data);

    void SaveOrdersInLibrary(const std::string& path = "../data/orders.txt");

    void PrintOrders() const;

    void PrintOrders(const std::string &userChoice) const;

    //add order with new components
    void addOrder(int name, const std::string &order_id, const std::string &priority, const std::string &status,
                  const HardwareComponent &hardware);

    //add order with known components
    void addOrder(int order_id, const std::string &name, const std::string &priority, const std::string &status,
                  const std::string &hardware_id);

    void addOrder(const Order& order);


    //remove order by ID(as it should be unique)
    void removeOrder(const int &order_id);

    //get orders not sorted for printing
    const ordersContainer &getOrders() const;

    //get orders sorted by priority;
    const ordersContainer &getFilteredOrders() const;

    ordersContainer& getOrderContainer();

    //function to load orders from orders.txt
    void LoadOrders(const std::string& path);
    //path included to work with production.txt and history.txt

    void getVoltSorted();

private:

    //vector of orders
    int m_lastGivenIndex{};

    ordersContainer m_orders;
    //change if priority is saved differently
    static const std::string HIGH_PRIORITY_STR;
    static const std::string NORMAL_PRIORITY_STR;
    static const std::string UNPROCESSED_STATUS;
    static const std::string PENDING_STATUS;
    static const std::string PRINTING_STATUS;
private:
    // Loading orders from orders.txt
    

    void LoadConfigFile();

    void CreateOrderFromLibrary(DataHandler::RawDataContainer &data);

    static std::vector<std::string> ReturnDataFromOrder(const Order &order);

    int ReturnNewId();


    bool sortByPrio(const Order &one, const Order &two) const;
    bool voltSort(const Order& one, const Order& two) const;

};

#endif //COMMON_FUNCTIONALITY_ORDER_MANAGER_H
