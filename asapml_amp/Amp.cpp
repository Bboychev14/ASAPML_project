#include "Amp.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "../common_functionality/data_handler/constants.h"

Amp::Amp()
{
    WriteResourcesIntoMap();
    WriteMinQuantitiesIntoMap();
    //WriteDataFromMapIntoTxtFile(AMP_CONSTANTS::CFG_TXT_FILE_NAME, minQuantities);
}

Amp::~Amp()
{
    WriteDataFromMapIntoTxtFile(AMP_CONSTANTS::CFG_TXT_FILE_NAME, minQuantities);
    WriteDataFromMapIntoTxtFile(AMP_CONSTANTS::INVENTORY_TXT_FILE_NAME, inventoryMaper);
}

//Sets the default minimum quantities into the map.
void Amp::WriteMinQuantitiesIntoMap()
{
    for (const auto& pair : inventoryMaper)
    {
        minQuantities[pair.first] = AMP_CONSTANTS::DEFAULT_MIN_QUANTITIES;
    }
}

//Writes the information from Inventory into a map!
void Amp::WriteResourcesIntoMap()
{
    std::ifstream inventoryFile(AMP_CONSTANTS::INVENTORY_TXT_FILE_NAME);
    if (!inventoryFile)
    {
        std::cerr << AMP_CONSTANTS::UNABLE_TO_OPEN_FILE << std::endl;
    }
    else
    {
        std::string tempInventoryLine;
        while (getline(inventoryFile, tempInventoryLine))
        {
            std::istringstream iss(tempInventoryLine);
            std::string tempId;
            int tempQuantity = 0;
            if (iss >> tempId >> tempQuantity)
            {
                inventoryMaper[tempId] = tempQuantity;
            }
        }
        inventoryFile.close();
    }
}

//Writes data from one of the 2 maps into a txt file(cfg.txt and inventory.txt).
void Amp::WriteDataFromMapIntoTxtFile(const std::string& fileName, const std::map<std::string, int>& data) const
{
    std::ofstream tempTxtFile(fileName);
    for (const auto& pair : data)
    {
        tempTxtFile << pair.first << ' ' << pair.second << std::endl;
    }
    tempTxtFile.close();
}

void Amp::PrintInventory() const
{
    for (const auto& pair : inventoryMaper)
    {
        std::cout << "ID: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}

//Prompts the user to enter new minimum quantity for a certain component.
void Amp::SetMinQuantity()
{
    bool isCorrectId = false;
    int newMinQuantity = 0;
    std::string tempId;
    std::cout << AMP_CONSTANTS::INPUT_COMPONENT_DATA;
    std::cin >> tempId;
    std::cin >> newMinQuantity;
    for (auto& pair : minQuantities)
    {
        if (pair.first == tempId)
        {
            isCorrectId = true;
            minQuantities[tempId] = newMinQuantity;
            //WriteDataFromMapIntoTxtFile(AMP_CONSTANTS::CFG_TXT_FILE_NAME, minQuantities);
        }
    }
    if (!isCorrectId)
    {
        std::cout << AMP_CONSTANTS::WRONG_COMPONENT_DATA << std::endl;
    }
}

//Updates the quantities with the new value.
void Amp::OrderResources(const std::string& id)
{
    inventoryMaper[id] = minQuantities[id];
    std::cout << "Updated the quantity of: " << id << " to: " << minQuantities[id] << std::endl;
    //WriteDataFromMapIntoTxtFile(AMP_CONSTANTS::INVENTORY_TXT_FILE_NAME, inventoryMaper);
}

//Updates the Inventory if there are quantities below the minimum.
void Amp::CheckInventoryForStock()
{
    WriteResourcesIntoMap();
    for (auto& pair : inventoryMaper)
    {
        if (inventoryMaper[pair.first] < minQuantities[pair.first])
        {
            OrderResources(pair.first);
        }
    }
}

//Helper function used in Run().
int Amp::TakeUserChoice() const {
    int userChoice;
    std::cin >> userChoice;
    std::cin.ignore();
    return userChoice;
}

int Amp::Run()
{
    while (true)
    {
        InitializeMenu();
        int userChoice = TakeUserChoice();
        if (userChoice == MenuChoices::PrintStock)
        {
            PrintInventory();
        }
        else if (userChoice == MenuChoices::ChangeMinQuantity)
        {
            SetMinQuantity();
        }
        else if (userChoice == MenuChoices::CheckForStock)
        {
            CheckInventoryForStock();
        }
        else
        {
            return 0;
        }
    }
}

void Amp::InitializeMenu() const
{
    std::cout << AMP_CONSTANTS::PRINT_INVENTORY;
    std::cout << AMP_CONSTANTS::CHANGE_MIN_QUANTITY;
    std::cout << AMP_CONSTANTS::CHECK_INVENTORY_FOR_STOCK;
    std::cout << AMP_CONSTANTS::EXIT_MENU << std::endl;
}