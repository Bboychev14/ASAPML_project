#include "order.h"


Order::Order(const int orderId, const std::string &client, const std::string &priority, const std::string &status,
             const HardwareComponent &hardware) : m_orderId(0) {
    setOrderId(orderId);
    setClient(client);
    setPriority(priority);
    setStatus(status);
    setHardwareComp(hardware);
}

Order::Order(const int orderId, const std::string &client, const std::string &priority, const std::string &status,
             const std::string &hardware_id) : m_orderId(0) {
    setOrderId(orderId);
    setClient(client);
    setPriority(priority);
    setStatus(status);
    setHardwareId(hardware_id);
}

const std::string &Order::getClient() const {
    return m_client;
}

int Order::getOrderId() const {
    return m_orderId;
}

const std::string &Order::getPriority() const {
    return m_priority;
}

const std::string &Order::getStatus() const {
    return m_status;
}

const HardwareComponent &Order::getHardware() const {
    return m_hardware;
}

const std::string &Order::getHardwareId() const {
    return m_hardware_id;
}

void Order::setClient(const std::string &client) {
    m_client = client;
}

void Order::setOrderId(const int orderId) {
    m_orderId = orderId;
}

void Order::setPriority(const std::string &priority) {
    m_priority = priority;
}

void Order::setStatus(const std::string &status) {
    m_status = status;
}

void Order::setHardwareComp(const HardwareComponent &hardware) {
    m_hardware = hardware;
}

void Order::setHardwareId(const std::string &hardware_id) {
    m_hardware_id = hardware_id;
}