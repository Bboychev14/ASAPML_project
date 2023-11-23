#include "ohm.h"
#include "../common_functionality/data_handler/constants.h"

int OHM::Run() {
    while (true) {
        InitializeMenu();
        int userChoice = TakeUserChoice();
        if (userChoice == AddNewOrderChoice) {
            AddNewOrder();
        } else if (userChoice == ShowOrdersChoice) {
            ShowOrders();
        } else if (userChoice == ShowSortedOrdersChoice) {
            ShowOrdersByPriority();
        } else if (userChoice == DeleteOrderChoice) {
            DeleteOrder();
        } else if (userChoice == ExitChoice) {
            /// Must be removed from here;
            m_ElCompManager.SaveElComponentsInLibrary();
            m_HWCompManager.SaveHWComponentsInLibrary();
            m_orderManager.SaveOrdersInLibrary();
            m_orderManager.SaveConfigInfo();
            return 0;
        }
    }
}

void OHM::InitializeMenu() {
    std::cout << OHM_CONSTANTS::WELCOMING_MSG;
    std::cout << OHM_CONSTANTS::ADD_ORDER_OPTION_MSG;
    std::cout << OHM_CONSTANTS::SEE_ORDER_OPTION_MSG;
    std::cout << OHM_CONSTANTS::SEE_ORDER_OPTION_BY_MSG;
    std::cout << OHM_CONSTANTS::DELETE_ORDER_MSG;
    std::cout << OHM_CONSTANTS::EXIT_MSG << std::endl;
}

int OHM::TakeUserChoice() {
    int userChoice;
    std::cin >> userChoice;
    std::cin.ignore();
    return userChoice;
}

DataHandler::RawDataContainer OHM::TakeInputForNewOrder() {
    DataHandler::RawDataContainer resultInput;
    std::string curLine;

    do {
        std::getline(std::cin, curLine);
        resultInput.push_back(curLine);
    } while (!curLine.empty());
    resultInput.pop_back();
    return resultInput;
}

void OHM::AddNewOrder() {
    DataHandler::RawDataContainer orderData = TakeInputForNewOrder();
    auto dataForOrder = OrderManager::ReturnDataForOrderFromInput(orderData);
    auto dataForHardwareComp = HardwareComponentManager::ReturnDataForHardwareFromInput(orderData);

    std::string orderHardwareCompId = DataHandler::SplitReturnRightPart(dataForOrder[2]);

    if (!m_HWCompManager.IsHWCompAvailable(orderHardwareCompId) && dataForHardwareComp.empty()) {
        std::cout << OHM_CONSTANTS::INVALID_ORDER_MSG << std::endl;
        return;
    }

    auto dataForHardwareElComponents = ElectronicComponentManager::ReturnDataForElCompForHardware(dataForHardwareComp);
    auto dataForNewElCompDesign = ElectronicComponentManager::ReturnElCompDesign(orderData);
    auto neededElCompIds = ElectronicComponentManager::ReturnNeededElCompIds(dataForNewElCompDesign);

    for (const auto &elComponent: dataForHardwareElComponents) {
        std::string elCompId = DataHandler::SplitReturnLeftPart(elComponent);
        auto elCompWithoutDesign = std::find(neededElCompIds.begin(), neededElCompIds.end(), elCompId);
        if (!m_ElCompManager.IsElCompAvailable(elCompId) && elCompWithoutDesign == neededElCompIds.end()) {
            std::cout << OHM_CONSTANTS::INVALID_ORDER_MSG << std::endl;
            return;
        }
    }

    m_orderManager.CreateOrderFromInput(dataForOrder);
    m_HWCompManager.CreateHWCompFromData(dataForHardwareComp);
    m_ElCompManager.CreateMultipleNewElCompFromData(dataForNewElCompDesign);
    std::cout << OHM_CONSTANTS::ADDED_SUCCESS_ORDER_MSG << std::endl;
}

void OHM::ShowOrders() {
    m_orderManager.PrintOrders();
}

void OHM::ShowOrdersByPriority() {
    std::string userChoice;
    std::cin >> userChoice;
    m_orderManager.PrintOrders(userChoice);
}

void OHM::DeleteOrder() {
    std::string userChoice;
    std::cin >> userChoice;
    m_orderManager.removeOrder(std::stoi(userChoice));
}


