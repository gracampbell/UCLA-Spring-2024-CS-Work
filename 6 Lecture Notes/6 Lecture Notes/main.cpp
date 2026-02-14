using namespace std;
#include <iostream>

int main() {
    
   // Range based for loops, way to loop through a container (using vector here)
    
    vector <int> v = {1,2,3,4,5};
    
    // print vector using regular for loop
    for (int i =0; i < v.size(); i++) {cout <<v[i] << ' ';}
    cout << endl;
    
    //printing vector using range-based for loop
        for(int el: v) {cout << el << ' ';}
    cout << endl;
    
    // syntax:
    // for (type name : container) {.... el....}
    for (int& el : v){el++;}
    
    for(int el: v) {cout << el << ' ';}
    cout << endl;
    
    
    return 0;
    
    
}
