#ifndef COMMON_FUNCTIONALITY_ORDER_H
#define COMMON_FUNCTIONALITY_ORDER_H

#include "../electonic_component_functionality/electronic_component.h"
#include "../hardware_component_functionality/hardware_component.h" 

class Order {
public:

    Order() : m_orderId(0) {};
    //Constructor for orders with new components
    Order(int orderId, const std::string& client,  const std::string& priority, const std::string& status, const HardwareComponent& hardware);
    //Constructor for orders with already known components
    Order(int orderId, const std::string& client, const std::string& priority, const std::string& status, const std::string& hardware_id);

    const std::string& getClient() const;

    int getOrderId() const;

    const std::string& getPriority() const;

    const std::string& getStatus() const;

    const HardwareComponent& getHardware() const;

    const std::string& getHardwareId() const;

    void setClient(const std::string& client);

    void setOrderId(int orderId);

    void setPriority(const std::string& priority);

    void setStatus(const std::string& status);

    void setHardwareComp(const HardwareComponent& hardware);

    void setHardwareId(const std::string& hardware_id);

private:
    int m_orderId;
    std::string m_client;
    std::string m_priority;
    std::string m_status;

    HardwareComponent m_hardware;
    std::string m_hardware_id; //if hardware component already exists;
};


#endif //COMMON_FUNCTIONALITY_ORDER_H
