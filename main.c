//This allows for the standard input and output methods to be used
#include <stdio.h>

//This will shift the alphabet array by the encryption key (numerical)
void arrayShift(int *arr, int shiftFac);

int main() {
    //This is the encryption key (numerical)
    int shiftFac;
    //This is the array storing the ASCII values of the letters of the alphabet
    int alpArr[26];
    
    //This stores the values of the ASCII values of the alphabet into the array
    for(int index = 0; index < 26; index++) {
        alpArr[index] = 65 + index;
    }
    
    //This retrieves the encryption key (numerical) from the user
    scanf("%d", &shiftFac);
    
    shiftFac %= 26;
    //This will shift the ASCII values in the alphabet array by the encryption key
    arrayShift(alpArr, shiftFac);
    
    //This prints the ASCII values in the array after it has been shifted
    for(int i = 0; i < 26; i++) {
        printf("%d\n", alpArr[i]);
    }
}

//This shifts the ASCII values in the alphabet array by the encryption key
void arrayShift(int *arr, int shiftFac) {
    /*This stores the first <encryption key> elements of the alphabet array so 
    they are preserved and may be added back on the end of the shifted array*/
    int tempArr[shiftFac];
    
    //This stores the first <encryption key> elements of the array for preservation
    for(int tempIndex = 0; tempIndex < shiftFac; tempIndex++) {
        tempArr[tempIndex] = arr[tempIndex];
    }
    
    /*This shifts the first 26 - <encryption key> elements of the array so that
    the value <index - shiftFac> does not exceed the maximum index of the array.
    Without this boundary, a segmentation fault would occur*/
    for(int index = 0; index < 26 - shiftFac; index++) {
        arr[index] = arr[index + shiftFac];
    }
    
    /*This sets the last <encryption key> elements of the array (after shift) to
    be the first <encryption key> elements of the array (before shift)*/
    for(int lastIndex = 0; lastIndex < shiftFac; lastIndex++) {
        arr[26-shiftFac + lastIndex] = tempArr[lastIndex];
    }
    
}
