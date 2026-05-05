#include <iostream>
#include <vector>

using namespace std;

void greedySelectionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        // The greedy choice: find the absolute minimum in the remaining unsorted portion
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
        }
        
        cout << "Pass " << i + 1 << ": ";
        for (int k : arr) cout << k << " ";
        cout << "\n";
    }
}

int main() {
    int n;
    cout << "===========================================\n";
    cout << "   GREEDY SEARCH APPLICATION: SELECTION SORT\n";
    cout << "===========================================\n";
    cout << "Enter the number of elements: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter the " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "\nInitial Array: ";
    for (int k : arr) cout << k << " ";
    cout << "\n\n--- [ SORTING PROCESS ] ---\n";
    
    greedySelectionSort(arr);
    
    cout << "\nFinal Sorted Array: ";
    for (int k : arr) cout << k << " ";
    cout << "\n===========================================\n";
    
    return 0;
}