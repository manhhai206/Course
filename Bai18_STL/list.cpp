#include <iostream>
#include <list>

using namespace std;

int main(){
    
    list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_front(10);
    lst.push_front(20);
    auto i = 0;
    // /* Vòng for cải tiến */
    // for(auto item : lst){
    //     cout <<"node: " <<i++<<", value: " << item <<endl;
    // }

    list<int>::iterator it;

    cout << "List ban dau: "<< endl;

    /* Vòng for sử dụng iterator*/
    for(it = lst.begin();it != lst.end();it++)
    {
        cout << "addr: " <<&(*it)<<" , node: "<<i++ <<" , value: "<<*it<<endl;
    }

    cout << "List sau khi xoa/them " << endl;

    i = 0;
    for(it = lst.begin();it != lst.end();it++)
    {
        if(i ==  1){
            lst.insert(it,50);
        }

        if(i ==  2){
            lst.insert(it,100);
        }

        if(i == 3){
            lst.erase(it);
        }

        i++;
    }

    i = 0;
    for(it = lst.begin();it != lst.end();it++)
    {
        cout << "addr: " <<&(*it)<<" , node: "<<i++ <<" , value: "<<*it<<endl;
    }

    return 0;
}