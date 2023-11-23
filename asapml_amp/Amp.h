#pragma once

#include <map>
#include <string>

class Amp
{
public:
    Amp();
    ~Amp();
    int Run();

private:
    void WriteResourcesIntoMap();
    void WriteMinQuantitiesIntoMap();
    void WriteDataFromMapIntoTxtFile(const std::string& fileName, const std::map<std::string, int>& data) const;
    int TakeUserChoice() const;
    void InitializeMenu() const;

    std::map<std::string, int> minQuantities;
    std::map<std::string, int> inventoryMaper;
    void PrintInventory() const;
    void CheckInventoryForStock();
    void SetMinQuantity();
    void OrderResources(const std::string& id);

    enum MenuChoices
    {
        PrintStock = 1,
        ChangeMinQuantity,
        CheckForStock
    };
};
