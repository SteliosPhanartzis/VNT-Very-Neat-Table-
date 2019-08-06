#include <iostream>
#include <cmath>
using namespace std;

template <class T>
//SM
class SM{
private:
	private:
		int colLow, colHigh, rowLow, rowHigh;
		T **pM;
public:
 	// default constructor
 	// allows for writing things like SA a;
	SM(){
		colLow = 0;
		colHigh = -1;
		rowLow = 0;
		colHigh = -1;
		pM=NULL;
	}

 	// single parameter constructor lets us
 	// create a square matrix
	SM(int side){
		colLow=0; colHigh=side-1;
		rowLow=0; rowHigh=side-1;		
		pM = new T*[side];
		for(int i = 0; i < side; i++){
			pM[i] = new T[side];
		}
 	}

	//Overloaded constructors
	//2 parameters
	SM(int r, int c){
		colLow=0; colHigh=c-1;
		rowLow=0; rowHigh=r-1;
		pM = new T*[r];
		for(int i = 0; i < r; i++){
			pM[i] = new T[c];
		}
	}

	
	//4 parameters
	SM(int cL, int cH, int rL, int rH){
		if((cH-cL+1)<=0 || (rH-rL+1)<=0){
			cout<< "constructor error in bounds definition"<<endl;
			exit(1);
		}
		colLow=cL; colHigh=cH;
		rowLow=rL; rowHigh=rH;
		pM= new T*[rH-rL+1];
		for(int i = 0; i < (rowHigh-rowLow+1); i++){
			pM[i] = new T[colHigh-colLow+1];
		}
	}
 	
	// copy constructor for pass by value and
	// initialization
	SM(const SM & s){
		int sizeRow=s.rowHigh-s.rowLow+1;
		int sizeCol=s.colHigh-s.colLow+1;
		rowLow = s.rowLow; rowHigh = s.rowHigh;
		colLow = s.colLow; colHigh = s.colHigh;
		pM= new T*[sizeRow];
		for(int i=0; i<sizeRow; i++)
			pM[i]= new T[sizeCol];
		for(int i=0; i<sizeRow; i++)
			for(int j=0; j<sizeCol; j++)
				pM[i][j] = s.pM[i][j];
	}
 	
	// destructor
 	~SM(){
 		for(int i=0; i<rowHigh-rowLow;i++)
 			delete [] pM[i];
 		delete [] pM;
 	}
 	
 

	// overloaded assignment lets us assign
	// one SA to another
	SM & operator=(const SM & s){
		if(this==&s)
			return *this;
		for(int i=0; i<rowHigh-rowLow;i++)
 			delete [] pM[i];
 		delete [] pM;
 		
 		colLow=s.colLow; colHigh=s.colHigh;
		rowLow=s.rowLow; rowHigh=s.rowHigh;
		int sizeRow=s.rowHigh-s.rowLow+1;
		int sizeCol=s.colHigh-s.colLow+1;
 		
		pM=new T*[sizeRow];
		for(int i=0; i<sizeRow; i++)
			pM[i]= new T[sizeCol];
		for(int i=0; i<sizeRow; i++)
			for(int j=0; j<sizeCol; j++)
				pM[i][j] = s.pM[i][j];
		return *this;
	}
	
	class dim {
    private:
        T* p;
        int low, high;
    public:
        dim(T* in, int l, int h){
            low= l; high= h;
            p= in;
        }
        
        T& operator[](int i) {
            if(i<low || i>high){
                cout<<"index "<<i<<" out of range"<<endl;
                exit(1);
            }
            return p[i-low];
        }
    };
    
	//overloaded [] lets us write
 	//SA x(10,20); x[15]= 100;
 	dim operator[](int i){
	 	if(i<rowLow || i>rowHigh){
			cout<< "index "<<i<<" out of range"<<endl;
		 	exit(1);
		}
        dim param(pM[i-rowLow],colLow, colHigh);
		return param;
	}
	// overloads << so we can directly print SAs
	template <class K>
	friend ostream& operator<<(ostream& os, const SM<K> s);
	
	//Matrix multiplication
	SM operator*(const SM & s){
		if((colHigh-colLow) != (s.rowHigh-s.rowLow)){
			cout<<"The columns of the first matrix must match the rows of the second.\n";
			exit(1);
		}
		SM product((colHigh-colLow),(s.rowHigh-s.rowLow));
		for(int i = 0; i < product.colHigh; i++){
			for(int j = 0; j < product.rowHigh; j++){
				product[i][j]=0;
				for(int k = 0; k < product.colHigh; k++){
					product[i][j] += pM[i][k] * s.pM[k][j];
				}
			}
		}
		return product;
	}
	
	//Get Methods
	int getRLow(){
		return rowLow;
	}
	int getRHigh(){
		return rowHigh+1;
	}
	int getCLow(){
		return colLow;
	}
	int getCHigh(){
		return colHigh+1;
	}
};

template <class T>
ostream& operator<<(ostream& os, const SM<T> s){
	int sizeRow=s.rowHigh-s.rowLow+1;
	int sizeCol=s.colHigh-s.colLow+1;
	for(int i=0; i<sizeRow; i++){
		for(int j=0; j<sizeCol; j++)
			cout<<s.pM[i][j]<< " ";
		cout << endl;
	}
	return os;
}; 

class VNT {
private:
    int row, col;
    SM<int> matrix;
public:
    
    // default constructor
    VNT(){
        row=0; col=0;
        matrix = SM<int>();
    }
    // overloaded constructors
    VNT(int s){
        row=s; col=s;
        matrix=SM<int>(s,s);
        for (int i = 0; i < s; ++i)
            for (int j = 0; j < s; ++j)
                matrix[i][j] = INT_MAX;
    }

    VNT(int r, int c){
        row=r; col=c;
        matrix=SM<int>(r,c);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                matrix[i][j] = INT_MAX;
    }
    void add(int n){
        if (matrix[row - 1][col - 1] < INT_MAX) {
			cout << "VNT is full";
			return;
        }
        //Append value to end of matrix
        matrix[row - 1][col - 1] = n;
        
        for(int i = row - 1; i > 0; i--){
        	//Swap max of ith row, and max of (i-1)th row
        	if (matrix[i - 1][col-1] > matrix[i][col - 1])
                swap(matrix[i - 1][col-1],matrix[i][col - 1]);
			for(int j = col - 1; j > 0; j--){
				//If i = 1, sort 0th row
				if (i == 1 && (matrix[i - 1][j - 1] > matrix[i - 1][j]))
                    swap(matrix[i - 1][j - 1], matrix[i - 1][j]);
                //Sort values of ith row
				if(matrix[i][j-1] > matrix[i][j])
        			swap(matrix[i][j-1],matrix[i][j]);
			}
		}
    }

    int getMin(){
        if (matrix[0][0] == INT_MAX) {
            cout << "VNT is Empty" << endl;
            return INT_MAX;
        }
        
        int min = matrix[0][0];

        for (int i = 0;i < row; i++) {
            for(int j = 0; j < col; j++) {
				if(j < col-1)
					matrix[i][j] = matrix[i][j+1];
				else if (i<row-1)
					matrix[i][j] = matrix[i+1][0];
            }
        }
        matrix[row - 1][col - 1] = INT_MAX;
        return min;
    }
    
    void sort(int arr[],int s){
   		VNT in(s,1);
		for(int j = 0; j < s; j++){
			for(int i = j; i < s; i++)
				in.add(arr[i]);
			for(int i = j; i < s; i++)
				arr[i]=in.getMin();
		}
	}
	bool find(int n){
		if(n < matrix[0][0]){
			return false;
		}
		else if(n == matrix[0][0]){
			return true;
		}

		int maxrow = row-1, minrow = 0;
		int maxcol = col-1, mincol = 0;
		
		//Locate possible rows
		while(matrix[minrow][col-1] < n && matrix[maxrow][0] > n){
			++minrow;
			--maxrow;
		}
		while(matrix[minrow][maxcol] > n && matrix[maxrow][mincol] < n){
			++mincol;
			--maxcol;
		}

		for(int i = minrow; i <= maxrow; ++i){
			for(int j = mincol; j <= maxcol; ++j){
				if(matrix[i][j] == n){
					return true;
				}
			}
		}
		return false;
	}
};

//test main
//int main(){
//    
//    VNT a(10,4);
//    for(int i=0;i<40;i++){
//        a.add(39- i);
//    }
//    
//    int arr[10]= {2,6,9,0,3,1,8,4,7,5};
//    cout<<"Unsorted array is:\n";
//    for(int i = 0; i < 10; i++)
//        cout<<arr[i]<<" ";
//    cout<<endl;
//    
//    a.sort(arr,10);
//    cout<<"Sorted Array is:\n";
//    for(int i = 0; i < 10; i++)
//        cout<<arr[i]<<" ";
//    cout<<endl;
//	for(int i = 0; i < 40; i++){
//		cout << "Min is " << a.getMin() << endl;
//	}
//	for(int i = 0; i < 40; i++){
//		cout << i << ": " << a.find(i) << endl;
//	}
//    return 0;
//}
