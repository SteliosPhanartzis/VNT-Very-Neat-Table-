#include <iostream>
#include "VNT.cpp"
using namespace std;

int main(){
    
    VNT a(10,4);
    for(int i=0;i<40;i++){
        a.add(39- i);
    }
    
    int arr[10]= {2,6,9,0,3,1,8,4,7,5};
    cout<<"Unsorted array is:\n";
    for(int i = 0; i < 10; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    
    a.sort(arr,10);
    cout<<"Sorted Array is:\n";
    for(int i = 0; i < 10; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
	for(int i = 0; i < 40; i++){
		cout << "Min is " << a.getMin() << endl;
	}
	for(int i = 0; i < 40; i++){
		cout << i << ": " << a.find(i) << endl;
	}
    return 0;
}
