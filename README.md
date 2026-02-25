# Electrical Load Monitoring System

This is a simple C++ console application that helps users monitor electrical appliance usage and estimate electricity costs.  
The system allows users to register appliances, calculate energy consumption, and manage records using file storage.

---

## Features

- Register new appliances  
- View all registered appliances  
- Search for a specific appliance  
- Calculate total energy consumption (kWh)  
- Estimate electricity bill using a tariff  
- Save appliance data to a file  
- Load saved data automatically on startup  
- Update appliance details  
- Delete appliances  

---

## How It Works

Each appliance stores:
- Name  
- Power rating (Watts)  
- Daily usage hours  

Energy consumption is calculated using:

Energy (kWh) = (Power × Hours) / 1000

The program stores appliance data in a text file (`appliances.txt`) so that information is not lost when the program closes.

---

## Technologies Used

- C++  
- File handling (`fstream`)  
- Object-Oriented Programming (OOP)  
- Arrays and basic data validation  

---

## How to Compile and Run

Using g++:

```bash
g++ main.cpp -o loadmonitor
./loadmonitor