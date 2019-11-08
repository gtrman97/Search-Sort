#include <iostream>
#include <string>
#include <string.h>

#define ARRAY_SIZE 12
#define NAME_SIZE 32

using namespace std;

void printArrays(int[], char[][NAME_SIZE]);
void bubbleSortArrays(int[], char[][NAME_SIZE]);
void swapParallel(int*, int*, char*, char*);
string findName(char[][NAME_SIZE], int);  //write this
int binSearch(int*, int, int, int);  //write this

void printArrays(int ids[], char names[][NAME_SIZE]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << ids[i] << ": " << names[i] << endl;
    }
}

void swapParallel(int *id1, int *id2, char *n1, char *n2) {
    int temp = *id1;
    *id1 = *id2;
    *id2 = temp;

    char tempname[NAME_SIZE];
    // put value of n1 into tempname
    strncpy(tempname, n1, NAME_SIZE);
    // put value of n2 into n1
    strncpy(n1, n2, NAME_SIZE);
    // put value of tempname into n2
    strncpy(n2, tempname, NAME_SIZE);
}

void bubbleSortArrays(int ids[], char names[][NAME_SIZE]) {
    int i, j;
    bool swap = true;
    for (i = 0; i < ARRAY_SIZE - 1 && swap; i++) {
        // Flag - It is put in place because if the inner loop goes through
        // the whole array and no swapping is needed, then the swap flag
        // will remain false and the outer for loop will not iterate again
        // saving time and being a more efficient program / algorithm.
        swap = false;
        for (j = 0; j < ARRAY_SIZE - i - 1; j++) {
            if (ids[j] > ids[j + 1]) {
                // must put address operator in front of ids because it's an int array,
                // address operator not needed for names because we want whole name
                // not just one letter of the name.
                swapParallel(&ids[j], &ids[j + 1], names[j], names[j + 1]);
                swap = true;
            }
        }
    }
}

string findName(char names[][NAME_SIZE], int index){
	string name = "";
	if(index >= 0 && index < ARRAY_SIZE){
		name = names[index];
	}
	return name;
}

int binSearch(int ids[], int low, int high, int id){
	int found = -1; 
    if (high >= low) { 
        int mid = low + (high - low) / 2; 

        // if found in the middle then we're done, and we don't need to look anymore.
        if (ids[mid] == id){
            found = mid; 
		} else {
            // if the middle value is greater than the value we are searching for
            // then we throw away the right half of the array.
            // The low value stays the same while the high value is reset to
            // mid - 1, not mid because we already determined it wasn't mid above.
	        if (ids[mid] > id) {
	            found = binSearch(ids, low, mid - 1, id);

	        // if the middle value is less than the value we are searching for
	        // then we throw away the left half of the array.
	        // The high value stays the same while low value is pushed up to
	        // mid + 1, not mid because we already determined it wasn't mid above.
			} else {
		        found = binSearch(ids, mid + 1, high, id); 
			}
      	} 
	}
    return found; 
}

int main(int argc, char** argv) {

    int ids[ARRAY_SIZE] = {40, 12, 5, 55, 32, 98, 49, 50, 8, 1, 9, 29};
    char names[ARRAY_SIZE][NAME_SIZE] = {
        "Joe",
        "Daisy",
        "Bob",
        "Mary",
        "Julie",
        "Fred",
        "Sam",
        "Art",
        "Peggy",
        "Dan",
        "Roy",
        "Jane"
    };


    printArrays(ids, names);
    cout << endl;

    bubbleSortArrays(ids, names);

    printArrays(ids, names);
    cout << endl;

    string foundName = "";

    //testing all known ids
    for (int i = 0; i < ARRAY_SIZE; i++) {
        foundName = findName(names, binSearch(ids, 0, ARRAY_SIZE, ids[i]));
        if (foundName.length()) {
            cout << "found " << foundName << endl;
        } else {
            cout << foundName << "not found" << endl;
        }
    }

    //testing unknown
    foundName = findName(names, binSearch(ids, 0, ARRAY_SIZE, 99));
    foundName.length() ? cout << "Found! " << foundName : cout << "not found";
    cout << endl;

    foundName = findName(names, binSearch(ids, 0, ARRAY_SIZE, -1));
    foundName.length() ? cout << "Found! " << foundName : cout << "not found";
    cout << endl;
    
    return 0;
}
