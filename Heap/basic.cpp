// BST - > complete bt + (max heap properity || min heap property)
// create heap using array and visualize it as a tree
// in array if the child at the ith po




#include <iostream>
using namespace std;

class Heap{
  public:
    int *arr;
    int capacity;
    int size;

    Heap(int capacity) {
      this->arr = new int[capacity];
      this->capacity = capacity;
      //size = current number of elements in heap
      this->size = 0 ;
    }

    void insert(int val) {
      if(size == capacity) {
        cout << "Heap OverFlow" << endl;
        return;
      }
      //size increase kar jaega
      size++;
      int index = size;
      arr[index] = val;

      ///take the val to its cvorrect position
      while(index > 1) {
        int parentIndex = index/2;
        if(arr[index] > arr[parentIndex]) {
          swap(arr[index], arr[parentIndex]);
          index = parentIndex;
        }
        else {
          break;
        }
      }
    }
  
    void printHeap() {
      for(int i=1; i<=size; i++) {
         cout << arr[i] << " ";
     }
    }

    int deleteFromHeap() {
      int answer = arr[1];
      //replacement
      arr[1] = arr[size];
      //last element ko delete uski original position se
      size--;
      int index = 1;
      while(index < size ) {
          int leftIndex = 2*index;
          int rightIndex = 2*index+1;

          //find out karna h , sabse bada kon
          int largestKaIndex = index;
          //check left child
          if(leftIndex <= size && arr[largestKaIndex] < arr[leftIndex]) {
            largestKaIndex = leftIndex;
          }
          if(rightIndex <= size && arr[largestKaIndex] < arr[rightIndex]) {
            largestKaIndex = rightIndex;
          }
          //no change
          if(index == largestKaIndex) {
            break;
          }
          else {
            swap(arr[index], arr[largestKaIndex]);
            index = largestKaIndex;
          }
      }
      return answer;
    }
};

void heapify(int arr[],int n,int ind){
    int leftKaInd  = ind*2;
    int rightKaInd =  ind*2+1;
    int maxKanode = ind;

    if(leftKaInd<n && arr[leftKaInd]>arr[maxKanode]){
        maxKanode=leftKaInd;
    }
    if(rightKaInd<n && arr[rightKaInd]>arr[maxKanode]){
        maxKanode=rightKaInd;
    }

    if(maxKanode != ind){
        swap(arr[maxKanode],arr[ind]);
        ind = maxKanode;
        heapify(arr,n,ind);
    }
}

void buildHeap(int arr[], int n) {
  for(int index = n/2; index>0; index--) {
    heapify(arr, n, index);
  }
}

void heapSort(int arr[], int n) {
  while(n != 1 ) {
    swap(arr[1], arr[n]);
    n--;
    heapify(arr,n,1);
  }
}


int main() {
  int arr[] = {-1,5,10,20,50,12,13,6};
  int n = 7;
  buildHeap(arr,7);
  
  cout << "printing heap: " << endl;
  for(int i=1; i<=7; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  heapSort(arr, n);
    cout << "printing heap: " << endl;
    for(int i=1; i<=7; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  


  // Heap h(20);
  // //insertion
  // h.insert(10);
  // h.insert(20);
  // h.insert(5);
  // h.insert(11);
  // h.insert(6);

  // cout << "Printing the content of heap: " << endl;
  // h.printHeap();
  // int ans = h.deleteFromHeap();
  // cout << "Answer: " << ans << endl;
  // cout << "Printing the content of heap: " << endl;
  // h.printHeap();
  return 0;
}