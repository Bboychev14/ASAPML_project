#ifndef S05_PROJECT_TEAM_SNABSQUAD_CONSTANTS_H
#define S05_PROJECT_TEAM_SNABSQUAD_CONSTANTS_H
#include <iostream>

namespace OHM_CONSTANTS {
    const std::string WELCOMING_MSG = "Welcome to ASAPML\n";
    const std::string ADD_ORDER_OPTION_MSG = "To add new order press 0.\n";
    const std::string SEE_ORDER_OPTION_MSG = "To see all orders press 1.\n";;
    const std::string SEE_ORDER_OPTION_BY_MSG = "To see all orders sorted by priority press 2.\n";
    const std::string DELETE_ORDER_MSG = "To delete order by id, press 3.\n";
    const std::string EXIT_MSG = "To exit press 4.";
    const std::string INVALID_ORDER_MSG = "Invalid order";
    const std::string ADDED_SUCCESS_ORDER_MSG = "Order successfully added!!";
    const std::string SUCCESS_DELETE_ORDER_MSG = "Successfully deleted order ";
    const std::string FAIL_DELETE_ORDER_MSG = "We don't have order with that ID.";
}

namespace COMMON_CONSTANTS {
    const std::string UNABLE_TO_OPEN_FAIL_MSG = "Can't open file.";
    const char COLON_CHAR = ':';
    const char NEW_LINE_CHAR = '\n';
    const char PARENTHESES_LEFT_CHAR = '(';
    const char PARENTHESES_RIGHT_CHAR = ')';
    const char COMMA_CHAR = ',';
}

namespace AMP_CONSTANTS
{
    const int DEFAULT_MIN_QUANTITIES = 14;
    const std::string PRINT_INVENTORY = "To print current Inventory press 1.\n";
    const std::string CHANGE_MIN_QUANTITY = "To change the minimum quantity of a resource press 2.\n";;
    const std::string CHECK_INVENTORY_FOR_STOCK = "To check Inventory for stock press 3.\n";
    const std::string EXIT_MENU = "To exit press any other key.";
    const std::string UNABLE_TO_OPEN_FILE = "Couldn't open the requested file!";
    const std::string INPUT_COMPONENT_DATA = "Enter the ID of the product and the new minimum quantity: ";
    const std::string WRONG_COMPONENT_DATA = "There is no product with such ID!\n";
    const std::string CFG_TXT_FILE_NAME = "../asapml_amp/cfg_amp.txt";
    const std::string INVENTORY_TXT_FILE_NAME = "../data/inventory.txt";
}


#endif //S05_PROJECT_TEAM_SNABSQUAD_CONSTANTS_H
