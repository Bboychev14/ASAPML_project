#include "hardware_component.h"


const std::string& HardwareComponent::GetId() const {
    return m_id;
}

Pin HardwareComponent::GetDimensions() {
    return m_dimensions;
};

const size_t HardwareComponent::getNeededBoard() const
{
    size_t max;
    size_t width = m_dimensions.GetWidth();
    size_t height = m_dimensions.GetHeight();
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

DataHandler::RawDataContainer HardwareComponent::GetElCompIds() {
    return m_componentsIds;
};

DataHandler::PinsCOntainer HardwareComponent::GetElCompPinsPositions() {
    return m_componentsPinsPositions;
};

std::vector<int> HardwareComponent::GetElCompRotations() {
    return m_elCompRotations;
};

std::vector<DataHandler::PinsCOntainer> HardwareComponent::GetConnections() {
    return m_connections;
};

std::string HardwareComponent::getMachineFormat() const
{
    std::string data;
    data.append(m_id);
    data.append(": ");
    data.append(m_dimensions.getMachineFormat());
    std::map<std::string, std::pair<int, std::string>> el_comps; 
    for(size_t i = 0; i < m_componentsIds.size(); i++)
    {
        if(el_comps.find(m_componentsIds[i]) == el_comps.end())
        {
            el_comps[m_componentsIds[i]] = {1, m_componentsPinsPositions[i].getMachineFormat() + " " + std::to_string(m_elCompRotations[i])};
        }
        else
        {
            el_comps[m_componentsIds[i]].first += 1;
            el_comps[m_componentsIds[i]].second += " " + m_componentsPinsPositions[i].getMachineFormat() + " " + std::to_string(m_elCompRotations[i]);
        }
    }
    for(auto it = el_comps.begin(); it != el_comps.end(); ++it)
    {
        data.append("\n\t");
        data.append(it->first);
        data.append(": ");
        data.append(std::to_string(it->second.first));
        data.push_back(' ');
        data.append(it->second.second);
    }
    data.push_back('\n');
    for(size_t i = 0; i < m_connections.size(); i++)
    {
        for(size_t k = 0; k < m_connections[i].size(); k++)
        {
            data.push_back('(');
            data.append(std::to_string(m_connections[i][k].GetWidth()));
            data.push_back(',');
            data.append(std::to_string(m_connections[i][k].GetHeight()));
            data.push_back(')');
            if(i + 1 != m_connections.size() || k + 1 != m_connections[i].size())
            {
                data.append(", ");
            }
        }
        
    }
    return data;
}


HardwareComponent::HardwareComponent(const std::string &id, Pin &dimensions, DataHandler::RawDataContainer &componentsId,
                                     DataHandler::PinsCOntainer &elCompPinPos, std::vector<int> &rotations,
                                     std::vector<DataHandler::PinsCOntainer> &connections) :
        m_id(id), m_dimensions(dimensions), m_componentsIds(std::move(componentsId)),
        m_componentsPinsPositions(std::move(elCompPinPos)), m_elCompRotations(rotations),
        m_connections(std::move(connections)) {};


void HardwareComponent::SetId(std::string id) {
    m_id = std::move(id);
}

/*
int main()
{
    std::string id = "Darlington_Pair_0";
    Pin dimensions(11, 7);
    DataHandler::RawDataContainer componentsId{"2N3904", "2N3904"};
    DataHandler::PinsCOntainer elCompPinPos{{0,0}, {10,0}};
    std::vector<int> rotations{0, 1};
    std::vector<DataHandler::PinsCOntainer> connections{{{1,3}, {2,2}}, {{1,1}, {2,1}}};
    HardwareComponent hw(id, dimensions, componentsId, elCompPinPos, rotations, connections);
    std::cout<<hw.getMachineFormat();
}*/
/*
    Darlington_Pair_0: 1803
        2N3904: 2 0 0 10 1
    (1,3), (2,2), (1,1), (2,1)
*/