
Name: Omar Waseem
NetID: omwll
                                                            MY LITTLE MALLIC Project

Description:

Functions used in memgrind.c(test file):
    - void performComputation()
    - void performComputation2()
    - void performComputation3()
    - int main(int argc, char *argv[])

Test Plan:
    - Used timeofday() to be able to determine the average runtime time in milliseconds for 50 iterations
    - Implemented the 3 test plans documented in the project instructions.
    - Used 3 test functions initialized before the main() function so that they would be called to determine average the run time.

Test Programs:

Test 1 - Allocate 1-byte of storage and then immediately free it 120 times:
    - Allocated 1-byte(8 bits) into mymalloc() and then applied the myfree() function to deallocate it afterwards.
    - Done in a for loop until I have allocated and deallocated 120 times.

Test 2 - Allocate 120 bits of storage and print out values 1 - 120 from my Heap\n
    - Created an object of storage 120 bits in mymalloc() and stored it in the *arr pointer.
    - Used that object to store and print out number 1 - 120 using a for loop.

Test 3 - 
    - Stored 120 1-byte pointers in an array.
    - Made a random value decision maker to decide on 0 or 1 to either allocate or deallocate a random pointer from the array.
    - Continued this program until I allocated 120 times.

