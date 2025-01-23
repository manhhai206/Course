#include "RoomManager.hpp"
#include "UI.hpp"

using namespace std;

void RoomManager::addRoom(const string& roomNumber, const string& roomType, const string& bedCount, const string& price) {
    if (roomNumber.empty() || roomType.empty() || bedCount.empty() || price.empty()) {
        UI::showMessage("All fields are required.");
        return;
    }

    for (const auto& room : roomlist) {
        if (room.getRoomNumber() == roomNumber) { 
            UI::showMessage("Room number " + roomNumber + " already exists.");
            return;
        }
    }

    Room newRoom(roomNumber, roomType, bedCount, price); 
    roomlist.push_back(newRoom);
    UI::showMessage("Room " + roomNumber + " added to the room list.");
}

void RoomManager::editRoom(const string& roomNumber, const string& newRoomType, const string& newBedCount, const string& newPrice) 
{
    for (auto& room : roomlist) 
    {
        if (room.getRoomNumber() == roomNumber) 
        {
            room.setRoomType(newRoomType);
            room.setBedCount(newBedCount);
            room.setPrice(newPrice);
            UI::showMessage("Room updated successfully.");
            return;
        }
    }
    UI::showMessage("Room not found.");
}

void RoomManager::deleteRoom(const string& roomNumber) {
    for (auto it = roomlist.begin(); it != roomlist.end(); ++it) {
        if (it->getRoomNumber() == roomNumber) {
            roomlist.erase(it);
            UI::showMessage("Room deleted successfully.");
            return;
        }
    }
    UI::showMessage("Room not found.");
}

void RoomManager::listRooms() const {
    if (roomlist.empty()) {
        UI::showMessage("No rooms available.");
        return;
    }

    for (const auto& room : roomlist) {
        UI::showMessage("Room Number: " + room.getRoomNumber() +
                        ", Room Type: " + room.getRoomType() +
                        ", Bed Count: " + room.getBedCount() +
                        ", Price: " + room.getPrice());
    }
}

