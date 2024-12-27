#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(){
     
     map<int,string> testmap;


    /****************************************
     * Hoạt động theo kiểu Key-Value
     * Object testmap được khởi tại tại Stack
     * Key-Value được lưu ở Heap
     * Key phải khác nhau
     * Key được tự động sắp xếp theo thứ tự theo bảng mã ASCI
     *************************************** */
    //testmap[string key ] = string value;
    testmap[1] =  "Hai";    // Cách khai báo 
    testmap[2] = "Ha"; 

    // for(auto item: testmap){
    //     cout <<"Key: " << item.first << " , Value:  " <<item.second <<endl;
    // }

    testmap.insert({4,"Ho"});   // Có thể dùng insert để khai báo
    testmap.insert({3,"Hoang"});
    testmap.erase(3);

    map<int, string>::iterator it;
    
    for(it = testmap.begin(); it != testmap.end(); it++){
        cout <<"Key: " << (*it).first << " , Value: " <<(*it).second <<endl;
    }


    return 0;
}