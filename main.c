
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

void caesarCipher(void);

void unknownCaesar(char *toDec, int toDecLength, char *alpArr);

int main() {
    caesarCipher();
    
    return 0;
}

void caesarCipher(void) {
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
    
    //This is used to convert the file stream into a string
    int tempInd = 0;
    
    //This stores the message into the code[] string
    while(!feof(input)) {
        
        //This adds the characters in message.txt into a string
        code[tempInd] = fgetc(input);
        tempInd++;
    }

    //This is the length of code[]
    int codeLength = sizeof(code);
    
    
    //This stores the values of the ASCII values of the alphabet into the array
    for(int index = 0; index < 26; index++) {
        alpArr[index] = 65 + index;
    }
    
    //This allows the choice of encryption or decryption
    printf("Type 0 to encrypt and 1 to decrypt: ");
    scanf("%d", &encOrDec);
    
    
    //If encryption was selected
    if(!encOrDec) {
        //This retrieves the encryption key (numerical) from the user
        printf("Please input an encryption key: ");
        scanf("%d", &shiftFac);
        
        /*This converts the encryption key to be the equivalent positive value 
        (i.e. -3 is the same as 22)*/
        shiftFac = abs(26 + shiftFac)%26;
        printf("%c", shiftFac);
        
        //This will shift the ASCII values in the alphabet array by the encryption key
        arrayShiftEn(alpArr, shiftFac);
        
        //This will encrypt the message
        tranMessage(code, codeLength, alpArr);

        //Print the encrypted message
        printf("%s\n", code);
         
    } else { //Otherwise
        //Allows the choice to decrypt with or without a key
        int keyReq;
        printf("Type 0 to decrypt without a known key or 1 to decrypt with one: ");
        scanf("%d", &keyReq);
        
        //If the key is required
        if(keyReq) {
            //This retrieves the encryption key (numerical) from the user
            printf("Please input an encryption key: ");
            scanf("%d", &shiftFac);
            
            /*This converts the encryption key to be the equivalent positive value 
            (i.e. -3 is the same as 22)*/
            shiftFac = abs(26 + shiftFac)%26;
            
            //This will shift the ASCII values in the alphabet array by the encryption key
            arrayShiftDe(alpArr, shiftFac);
            
            //This will decrypt the message
            tranMessage(code, codeLength, alpArr);
        
            printf("%s\n", code);
        } else { //If the key is not required
            //Decrypt without the key
            unknownCaesar(code, codeLength, alpArr);
        }
        
    }
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
        if(toTran[i] >= 65 && toTran[i] <= 91) {
            toTran[i] = encKey[toTran[i] - 65];
        }
    }
}


//This will decrypt a message using caesar cipher without a known key.
void unknownCaesar(char *toDec, int toDecLength, char *alpArr) {
    //This stores an unaltered copy of the array so that the original message isn't lost
    char toDecCopy[toDecLength];
    
    //This will allow the encryption key to be reset after each attempt
    char alpArrCopy[26];
    
    //This resets the encryption key for multiple attempts to be allowed
    int alpArrLength = 26;
    for(int alpInd = 0; alpInd < alpArrLength; alpInd++) {
        alpArrCopy[alpInd] = alpArr[alpInd];
    }

    //This resests back to the original message for multiple attempts
    for(int ind = 0; ind < toDecLength; ind++) {
        toDecCopy[ind] = toDec[ind];
    }
    
    //These are to take an educated guess at a solution if all else fails
    int mostE = 0, mostEKey = 0, solved = 0;
    
    //This runs the translation function on the message with all 26 possible cipehr keys
    for(char count = 0; count < 26; count++) {
        int eCount = 0;

        //Try decryption with a certain key
        arrayShiftDe(alpArr, count);
        tranMessage(toDecCopy, toDecLength, alpArr);
        
        //This looks for the words 'THE' and 'AND' to verify if decryption has worked
        for(int testInd = 0; testInd < toDecLength - 2; testInd++) {
            //If the word 'THE' is found, print the solution
            if(toDecCopy[testInd] == 'T' && toDecCopy[testInd + 1] == 'H' && toDecCopy[testInd + 2] == 'E') {
                printf("%s \n", toDecCopy);
                solved = 1;
                
            } else
            //If the word 'AND' is found, print the solution
            if(toDecCopy[testInd] == 'A' && toDecCopy[testInd + 1] == 'N' && toDecCopy[testInd + 2] == 'D') {
                solved = 1;
                
            } else {
                //Otherwise determine how often the letter 'E' occurs
                for(int index = 0; index < toDecLength; index++) {
                    if(toDecCopy[index] == 'E')
                        eCount++;
                        
                }
                
                //Record what key yielded the most 'E's
                if(eCount > mostE) {
                    mostE = eCount;
                    mostEKey = count;
                    
                }
            }
        }
        
        //Resets the alphabet for a new key to be used
        for(int i  = 0; i < 26; i++)
            alpArr[i] = alpArrCopy[i];
            
        //Resets the message for a new key to be used
        for(int i = 0; i < toDecLength; i++)
            toDecCopy[i] = toDec[i];
    }
    
    //If no solution has been determined
    if(!solved) {
        
        //Assume that the correct answer is the key which yields the most 'E's
        arrayShiftDe(alpArr, mostEKey);
        tranMessage(toDecCopy, toDecLength, alpArr);
        
        //Print the answer
        printf("%s\n", toDecCopy);
    }
}