#ifndef ROOM_HPP
#define ROOM_HPP

#include "Account.hpp"
#include <vector>
#include <string>

using namespace std;

class Room
{
    private:
        string roomNumber_;     /**< Số phòng */
        string roomType_;       /**< Loại phòng */
        string bedCount_;       /**< Số giường */
        string price_;          /**< Giá phòng */

    public:
        /* Contructor */
        Room(const string& roomNumber, const string& roomType, const string& bedCount, const string& price)
            : roomNumber_(roomNumber), roomType_(roomType), bedCount_(bedCount), price_(price) {}

        //Getter
        string getRoomNumber() const { return roomNumber_; }
        string getRoomType() const { return roomType_; }
        string getBedCount() const { return bedCount_; }
        string getPrice() const { return price_; }

        // Setter
        void setRoomType(const string& newRoomType) { roomType_ = newRoomType; }
        void setBedCount(const string& newBedCount) { bedCount_ = newBedCount; }
        void setPrice(const string& newPrice) { price_ = newPrice; }
};

class RoomManager 
{
    private:
        vector<Room> roomlist;

    public:
        /* Thêm nhân viên với ID tự động */
        void addRoom(const string& roomNumber, const string& roomType, const string& bedCount, const string& price);

        /* Sửa thông tin nhân viên dựa theo ID */
        void editRoom(const string&roomNumber, const string& newRoomType, const string& newBedCount, const string& newPrice);

        void deleteRoom(const string& roomNumber);

        void listRooms() const;
};

#endif 