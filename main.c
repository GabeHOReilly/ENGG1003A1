//This allows for the standard input and output methods to be used
#include <stdio.h>

//This allows for the absolute value function to be used
#include <stdlib.h>

//This will shift the alphabet array by the encryption key (numerical)
void arrayShiftEn(char *arr, char shiftFac);

//This will shift the alphabet array by the encryption key (numerical)
void arrayShiftDe(char *arr, char shiftFac);

//This will encrypt the message using the encryption key
void tranMessage(char *toTran, int toTranLen, char *encKey);

int main() {
    //This is the encryption key (numerical)
    char shiftFac;
    //This is the array storing the ASCII values of the letters of the alphabet
    char alpArr[26];
    //This is used for the choice of encryption or decryption
    char encOrDec;
    
    /*This is used to store the file length as to minimise the space required for
      the storage of the message as a string*/
    int fileLength = 1;
    
    //This is the encrypted message, read from message.txt
    FILE *input;
    input = fopen("\message.txt", "r");
    
    /*This determines the length of the file by adding 1 every time the file pointer
    position is incremented until the end of file*/
    while(!feof(input)) {
        fileLength++;
        fgetc(input);
    }
    
    //This creates a string with the same amout of characters as message.txt
    char code[fileLength];
    
    //This resets the file pointer position
    fseek(input, 0, SEEK_SET);
    
    //This stores the message into the code[] string
    while(!feof(input)) {
        /*This was defined as a static int here TEMPORARILY (to avoid having to come
          up with a reasonable and meaningful name)*/
         
        //TODO update this to be more readable
/*********************************************************************************/
        static int i = 0;
        code[i] = fgetc(input);
        i++;
/*********************************************************************************/
    }

    //This is the length of code[]
    int codeLength = sizeof(code);
    
    //This stores the values of the ASCII values of the alphabet into the array
    for(int index = 0; index < 26; index++) {
        alpArr[index] = 65 + index;
    }
    
    //This retrieves the encryption key (numerical) from the user
    printf("Please input an encryption key: ");
    scanf("%d", &shiftFac);
    
    /*This converts the encryption key to be the equivalent positive value 
    (i.e. -3 is the same as 22)*/
    shiftFac = abs(26 + shiftFac)%26;
    printf("%c", shiftFac);
    
    //This allows the choice of encryption or decryption
    printf("Type 0 to encrypt and 1 to decrypt: ");
    scanf("%d", &encOrDec);
    
    //If the user wishes to encrypt
    if(!encOrDec) {
        //This will shift the ASCII values in the alphabet array by the encryption key
        arrayShiftEn(alpArr, shiftFac);
    } else { /*Otherwise
        This will shift the ASCII values in the alphabet array by the encryption key*/
        arrayShiftDe(alpArr, shiftFac);
    }
    
    //This will encrypt a given string
    tranMessage(code, codeLength, alpArr);

    printf("%s\n", code);
    
}

//This shifts the ASCII values in the alphabet array by the encryption key
void arrayShiftEn(char *arr, char shiftFac) {
    
    /*This stores the first <encryption key> elements of the alphabet array so 
    they are preserved and may be added back on the end of the shifted array*/
    char tempArr[shiftFac];
    
    //This stores the first <encryption key> elements of the array for preservation
    for(int tempIndex = 0; tempIndex < shiftFac; tempIndex++) {
        tempArr[tempIndex] = arr[tempIndex];
    }
    
    /*This shifts the first 26 - <encryption key> elements of the array so that
    the value <index-shiftFac> does not exceed the maximum index of the array.
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

//This shifts the ASCII values in the alphabet array by the encryption key
void arrayShiftDe(char *arr, char shiftFac) {
    shiftFac = 26 - shiftFac;
    
    /*This stores the first <encryption key> elements of the alphabet array so 
    they are preserved and may be added back on the end of the shifted array*/
    char tempArr[shiftFac];
    
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

//This will encrypt or decrypt a given message by a character-based encryption key
void tranMessage(char *toTran, int toTranLen, char *encKey) {
    
    //For every letter in the message
    for(int i = 0; i < toTranLen; i++) {
        //Change it to the new letter under the encryption key, ignoring spaces
        if(toTran[i] != ' ') {
            toTran[i] = encKey[toTran[i] - 65];
        }
    }
}
