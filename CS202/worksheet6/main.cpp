#include <iostream>
#include <string>

using namespace std;

template<class type>
class findLarger {
    private:
        type a;
        type b;
    public:
        findLarger();
        findLarger(type, type);
        type calculateLargest(type, type);
};

template<class type>
findLarger<type>::findLarger(){}

template<class type>
findLarger<type>::findLarger(type x, type y):a(x),b(y){}

template<class type>
type findLarger<type>::calculateLargest(type x, type y){
            cout<<"Largest between "<<x<<" and "<<y<<":";
            if(x > y){
                return x;
            }
            else{
                return y;
            }
        }



int main () {
    
    findLarger <int>obj1;
    cout<<obj1.calculateLargest(2,5)<<endl;
    findLarger <double>obj2;
    cout<<obj2.calculateLargest(98.7,24.5)<<endl;
    findLarger <string>obj3;
    cout<<obj3.calculateLargest("Computer","Engineer")<<endl;
    


return 0;



}
