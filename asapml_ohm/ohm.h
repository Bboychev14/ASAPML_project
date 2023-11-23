#ifndef OHM_H
#define OHM_H

#include "../common_functionality/order_functionality/order_manager.h"
#include "../common_functionality/electonic_component_functionality/electronic_component_manager.h"
#include "../common_functionality/hardware_component_functionality/hardware_component_manager.h"
#include "../common_functionality\data_handler\data_handler.h"


class OHM {
public:

    int Run();

private:

    enum MenuChoices {
        AddNewOrderChoice,
        ShowOrdersChoice,
        ShowSortedOrdersChoice,
        DeleteOrderChoice,
        ExitChoice
    };
    OrderManager m_orderManager;
    HardwareComponentManager m_HWCompManager;
    ElectronicComponentManager m_ElCompManager;

private:
    static void InitializeMenu();

    static int TakeUserChoice();

    static DataHandler::RawDataContainer TakeInputForNewOrder();

    void AddNewOrder();

    void ShowOrders();

    void ShowOrdersByPriority();

    void DeleteOrder();

};

#endif