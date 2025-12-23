// =========================================
// Parking Lot Management System (Optimized)
// Uses unordered_set for free slots + waiting queues
// Language: C++ (OOP Design)
// =========================================

#include <bits/stdc++.h>
using namespace std;

// -------- Vehicle (Abstract Class) --------
class Vehicle {
protected:
    string number;
public:
    Vehicle(string num) { number = num; }
    virtual string getType() const = 0;
    string getNumber() const { return number; }
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
public:
    Car(string num) : Vehicle(num) {}
    string getType() const override { return "Car"; }
};

class Bike : public Vehicle {
public:
    Bike(string num) : Vehicle(num) {}
    string getType() const override { return "Bike"; }
};

// -------- Parking Slot --------
class ParkingSlot {
    int slotId;
    string type; // Car / Bike
    bool occupied;

public:
    ParkingSlot(int id, string t) {
        slotId = id;
        type = t;
        occupied = false;
    }

    int getSlotId() const { return slotId; }
    string getType() const { return type; }
    bool isOccupied() const { return occupied; }

    void park() { occupied = true; }
    void free() { occupied = false; }
};

// -------- Ticket --------
class Ticket {
    int ticketId;
    int slotId;
    string vehicleNumber;
    time_t entryTime;

public:
    Ticket(int tid, int sid, string vnum) {
        ticketId = tid;
        slotId = sid;
        vehicleNumber = vnum;
        entryTime = time(nullptr);
    }

    int getSlotId() const { return slotId; }
    time_t getEntryTime() const { return entryTime; }
    string getVehicleNumber() const { return vehicleNumber; }
};

// -------- Parking Lot (Core Class) --------
class ParkingLot {
    vector<ParkingSlot> slots;

    unordered_set<int> freeCarSlots;   // slot IDs
    unordered_set<int> freeBikeSlots;  // slot IDs

    queue<Vehicle*> waitingCars;
    queue<Vehicle*> waitingBikes;

    unordered_map<string, Ticket> activeTickets;
    int ticketCounter;

    ParkingSlot& getSlotById(int id) {
        return slots[id - 1]; // slotId starts from 1
    }

public:
    ParkingLot(int carSlots, int bikeSlots) {
        int id = 1;
        for (int i = 0; i < carSlots; i++) {
            slots.push_back(ParkingSlot(id, "Car"));
            freeCarSlots.insert(id);
            id++;
        }
        for (int i = 0; i < bikeSlots; i++) {
            slots.push_back(ParkingSlot(id, "Bike"));
            freeBikeSlots.insert(id);
            id++;
        }
        ticketCounter = 1;
    }

    void parkVehicle(Vehicle* v) {
        if (v->getType() == "Car") {
            if (!freeCarSlots.empty()) {
                int slotId = *freeCarSlots.begin();
                freeCarSlots.erase(slotId);

                ParkingSlot& slot = getSlotById(slotId);
                slot.park();

                Ticket t(ticketCounter++, slotId, v->getNumber());
                activeTickets[v->getNumber()] = t;
                cout << "Car parked at slot " << slotId << endl;
            } else {
                waitingCars.push(v);
                cout << "No car slot free. Car added to waiting queue." << endl;
            }
        }
        else { // Bike
            if (!freeBikeSlots.empty()) {
                int slotId = *freeBikeSlots.begin();
                freeBikeSlots.erase(slotId);

                ParkingSlot& slot = getSlotById(slotId);
                slot.park();

                Ticket t(ticketCounter++, slotId, v->getNumber());
                activeTickets[v->getNumber()] = t;
                cout << "Bike parked at slot " << slotId << endl;
            } else {
                waitingBikes.push(v);
                cout << "No bike slot free. Bike added to waiting queue." << endl;
            }
        }
    }

    void removeVehicle(string vehicleNumber) {
        if (activeTickets.find(vehicleNumber) == activeTickets.end()) {
            cout << "Vehicle not found." << endl;
            return;
        }

        Ticket t = activeTickets[vehicleNumber];
        int slotId = t.getSlotId();
        ParkingSlot& slot = getSlotById(slotId);
        slot.free();

        time_t exitTime = time(nullptr);
        double hours = difftime(exitTime, t.getEntryTime()) / 3600;
        int fee = max(1, (int)ceil(hours)) * 20;

        if (slot.getType() == "Car") {
            freeCarSlots.insert(slotId);
            if (!waitingCars.empty()) {
                Vehicle* next = waitingCars.front(); waitingCars.pop();
                parkVehicle(next);
            }
        } else {
            freeBikeSlots.insert(slotId);
            if (!waitingBikes.empty()) {
                Vehicle* next = waitingBikes.front(); waitingBikes.pop();
                parkVehicle(next);
            }
        }

        activeTickets.erase(vehicleNumber);
        cout << "Vehicle removed from slot " << slotId << ". Fee: Rs " << fee << endl;
    }

    void displayStatus() {
        cout << "\n--- Parking Status ---\n";
        for (auto& slot : slots) {
            cout << "Slot " << slot.getSlotId() << " (" << slot.getType() << ") : ";
            cout << (slot.isOccupied() ? "Occupied" : "Free") << endl;
        }
        cout << "Waiting Cars: " << waitingCars.size() << endl;
        cout << "Waiting Bikes: " << waitingBikes.size() << endl;
    }
};

// -------- Main Function --------
int main() {
    int carSlots, bikeSlots;

    cout << "Enter number of Car slots: ";
    cin >> carSlots;
    cout << "Enter number of Bike slots: ";
    cin >> bikeSlots;

    ParkingLot lot(carSlots, bikeSlots);

    while (true) {
       cout << "\n1. Park Car\n2. Park Bike\n3. Remove Vehicle\n4. Display Status\n5. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string num;
            cout << "Enter Car Number: ";
            cin >> num;
            lot.parkVehicle(new Car(num));
        }
        else if (choice == 2) {
            string num;
            cout << "Enter Bike Number: ";
            cin >> num;
            lot.parkVehicle(new Bike(num));
        }
        else if (choice == 3) {
            string num;
            cout << "Enter Vehicle Number: ";
            cin >> num;
            lot.removeVehicle(num);
        }
        else if (choice == 4) {
            lot.displayStatus();
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
    return 0;
}
