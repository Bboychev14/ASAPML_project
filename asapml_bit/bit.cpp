#include "bit.h"

Bit::Bit()
{
    m_orders_manager(PRODUCTION_PATH);
    HardwareComponentManager m_hardware_manager;
    ElectronicComponentManager m_electronic_manager;
    loadData();
    getHW_IDs();
}

void Bit::loadData(const std::string& path)
{
    m_hardware_manager.readHWComponentsInMachine();
    m_electronic_manager.ReadElComponentsInMachine();
}

void Bit::getHW_IDs()
{
    OrderManager::ordersContainer orders = m_orders_manager.getOrders();
    for(auto order&: orders)
    {
        hw_IDs.pop_back(order.getOrderId());
    }
}

const HardwareComponent& Bit::getHW(const int ID) const
{
    return m_hardware_manager.getHWComponent(ID);
}

void Bit::output(const std::vector<std::vector<char>>& matrix) const
{
    for(int i = 0; i < matrix.size())
    {
        for(int j = 0; j < matrix[i].size())
        {
            std::cout<<matrix[i][j];
        }
        std::cout<<'\n';
    }
}

void Bit::cutBoard(const std::vector<std::vector<char>>& matrix, size_t width, size_t height)
{
    matrix.resize(width, std::vector<char>(height, '*'));
}
/*
void Bit::transformCoordinates(const HardwareComponent& target)
{
    for(size_t i = 0; i < target.GetElCompIds(); i++)
    {

    }

}*/
/*
void Bit::calculatePinPositions(const HardwareComponent& target, std::vector<std::pair<size_t, size_t>>& positions)
{
    DataHandler::PinsCOntainer obj_positions = target.GetElCompPinsPositions();
    std::vector<int> obj_rotations = target.GetElCompRotations();
    std::vector<DataHandler::PinsCOntainer> target_pins = target.GetConnections();
    for(size_t i = 0; i < target_pins.size(); i += 2)
    {
        size_t first_obj = target_pins[i].GetWidth();
        size_t first_pin = target_pins[i].GetHeight();
        size_t second_obj = target_pins[i+1].GetWidth();
        size_t second_pin = target_pins[i+1].GetHeight();

    }
}

vector.size() = number of connections * 2
pin.getWidth() = which electronic component
pin.getHeight() = which pin in electronic component above
*/
void Bit::print(const int ID) const
{
    size_t steps = 1;
    HardwareComponent target = getHW(ID);
    std::vector<std::vector<char>> matrix(target.getNeededBoard(), std::vector<char>(target.getNeededBoard(), '*'));
    std::cout<<"Step "<<steps<<":\n";
    steps++;
    output(matrix);
    cutBoard(matrix, target.GetDimensions().GetWidth(), target.GetDimensions().GetHeight());
    std::cout<<"Step "<<steps<<"(cut the board):\n";
    steps++;
    output(matrix);
    
    std::pair<size_t, size_t> pin_positions;
    calculatePinPositions(target, pin_positions);
}

