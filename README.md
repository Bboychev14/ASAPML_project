# ASAPML_project
ASAPML is a collection of interconnected and interacting programs that are an abstract simulation of a software system for
process automation for ordering and manufacturing hardware components. It consists of the following programs:

● ASAPML Ω (Ohm - Order “Harmony” Manager)
    - Program for making orders from customers. Customers have the option to place an order for a specific hardware component
(giving a blueprint file describing the design of the component). Orders are saved to a raw order file.

● ASAPML Amp (Asset Monitoring Program)
    - Inventory management program. To make a given hardware component, many concrete ones are needed
electronic components (resistors, transistors, chips, ..). The goal of inventory management software is to automate
keeping track of available resources (electronic components), and placing orders for the required quantities and types of electronic
components as well as accepts them.

● ASAPML Bit (Bitwise Integration Transfer)
    - A program that simulates the operation of a machine for printing hardware components. Accepts a request file for
print/solder/.., prints for a certain time and instead of communicating with a real machine that actually prints
physical hardware components, creates files representing individual physical hardware components (finished product).

● ASAPML Volt (Virtual Operations and Logistics Tool)
    - A program-conductor (controller, scheduler) that orchestrates the entire process in an efficient way.
Communicates with other applications via files (in the current version).