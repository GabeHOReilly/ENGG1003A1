
//This allows for the standard input and output methods to be used
#include <stdio.h>

//This allows for the absolute value function to be used
#include <stdlib.h>

//This allows for manipulation of strings without manual characterwise modifications
#include <string.h>

//This will shift the alphabet array by the encryption key (numerical)
void arrayShiftEn(char *arr, char shiftFac);

//This will shift the alphabet array by the encryption key (numerical)
void arrayShiftDe(char *arr, char shiftFac);

//This will encrypt the message using the encryption key
void tranMessage(char *toTran, int toTranLen, char *encKey);

//This will run if the user specifies the use of a caesar cipher
void caesarCipher(void);

//This will run if decrypting a caesar cipher without the key
void unknownCaesar(char *toDec, int toDecLength, char *alpArr);

//This will decrypt a substitution cipher with a known key
void subCipher(void);

//Gives a ratio between 0 and 1 for the amount of english to total words in the first 5
float wordsCorrect(char *message, int messageLength);

//Verifies if a word is within the 10000 most commonly used words
int isWord(char *toTest, int toTestLenght);

int main() {
    int rotOrSub;
    printf("Type 0 for Caesar or 1 for substitution: ");
    scanf("%d", &rotOrSub);
    
    if(!rotOrSub) {
        caesarCipher();
    } else {
        subCipher();
    }

    
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
    if(ferror(input)) {
        printf("Error opening file");
        return;
    }
    
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
        
        //This will shift the ASCII values in the alphabet array by the encryption key
        arrayShiftEn(alpArr, shiftFac);
        
        //This will encrypt the message
        tranMessage(code, codeLength, alpArr);

        //Open the file for writing
        FILE *output;
        output = fopen("\output.txt");
        
        //If it cannot open, abort
        if(ferror(output)) {
                printf("Error opening file");
                return;
        }
        //Otherwise print the message
        fprintf(output, "%s", code);
        fclose(output);
         
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
        
            printf("%s \n", code);
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

    //This resets back to the original message for multiple attempts
    for(int ind = 0; ind < toDecLength; ind++) {
        toDecCopy[ind] = toDec[ind];
    }
    
    //Allows the output to be written to a file
    FILE *output = fopen("\output.txt", "w");
    
    //This runs the translation function on the message with all 26 possible cipehr keys
    for(char count = 0; count < 26; count++) {
        
        //Try decryption with a certain key
        arrayShiftDe(alpArr, count);
        tranMessage(toDecCopy, toDecLength, alpArr);
        
        //If 2 of the first 5 words are english
        if(wordsCorrect(toDecCopy, toDecLength) >= 0.4) {
            
            //Assume the message is correct
            fprintf(output, "%s", toDecCopy);
            fclose(output);
            return;
        } 
            
        
        //Resets the alphabet for a new key to be used
        for(int i  = 0; i < 26; i++)
            alpArr[i] = alpArrCopy[i];
            
        //Resets the message for a new key to be used
        for(int i = 0; i < toDecLength; i++)
            toDecCopy[i] = toDec[i];
    }
    
}

//This will encrypt or decrypt a substitution cipher given a key
void subCipher(void) {
    int encOrDec;
    //Opens the message to be encrpted and decrypted
    FILE *input = fopen("\subMessage.txt", "r");
    
    //This will be used to determine the length of the message to enable conversion to a string
    int messageLength = 1;
    
    //Finds the amount of characters in the message
    while(!feof(input)) {
        messageLength++;
        fgetc(input);
    }
    
    //Resets the file pointer position to the beginning
    fseek(input, 0, SEEK_SET);
    
    /*Creates a string with the amount of characters as the original message. Also creates a
    string to contain the key*/
    char message[messageLength], messageKey[26];
    
    //Initialises 2 variables to 0 for indexing below
    int tempInd1 = 0, tempInd2 = 0;
    
    //While the message file still contains more letters
    while(!feof(input)) {
        //Add another letter from the message file into the message string
        message[tempInd1] = fgetc(input);
        if(message[tempInd1] < 123 && message[tempInd1] > 96)
            message[tempInd1] -= 32;
        //Increment this index to enable the next character to be added
        tempInd1++;
    }
    
    //Provides the option of encryption and decryption
    printf("Type 0 to encrypt and 1 to decrypt: ");
    scanf("%d", &encOrDec);
    
    //If encrypting
    if(!encOrDec) {
        //Opens the key for encryption and decryption
        FILE *key;
        key = fopen("\subKey.txt", "r");
        
        //If there is an error opening the file, abort
        if(ferror(key)) {
            printf("Error opening file");
            return;
        }
        
        //While the key file still contains more letters
        while(!feof(key)) {
            //Add another letter from the key file into the key string
            messageKey[tempInd2] = fgetc(key);
            //Increment this index to enable the next character to be added
            tempInd2++;
        }
        //printf("%s \n", messageKey);
        //Cycle through every character in the message string
        for(int i = 0; i < messageLength; i++) {
            //Check if the character is a capital letter
            if(message[i] < 91 && message[i] > 64) {
                //Replace the character with its substitution
                message[i] = messageKey[message[i]%65];
                printf("%s \n", message);
            }
            
        }
        //Print the message and close the file
        FILE *output;
        output= fopen("\output.txt", "w");
        if(ferror(output)) {
            printf("Error opening file");
            return;
        }
        fprintf(output, "%s", message);
        fclose(output);
    } else {
        //Stores whether a key is needed
        int keyReq;
        printf("Type 0 to decrypt without a key or 1 to decrypt with one: ");
        scanf("%d", &keyReq);
        if(keyReq) {
            //Opens the key for encryption and decryption
            FILE *key = fopen("\subKey.txt", "r");
            
            //While the key file still contains more letters
            while(!feof(key)) {
                //Add another letter from the key file into the key string
                messageKey[tempInd2] = fgetc(key);
                //Increment this index to enable the next character to be added
                tempInd2++;
            }
            //Cycle through every character in the message string
            for(int i = 0; i < messageLength; i++) {
                for(int keyInd = 0; keyInd < 26; keyInd++){
                
                    //Check if the character is a capital letter
                    if(message[i] == messageKey[keyInd]) {
                        //Replace the character with its substitution
                        message[i] = 65 + keyInd;
                        break;
                    }
                }
            }
            
            //Open the file, print the message and close the file
            FILE *output;
            output = fopen("\output.txt", "w");
            if(ferror(output)) {
                printf("Error in opening file");
                return;
            }
            fprintf(output, "%s", message);
            fclose(output);

        } else {//If a key is required
            //Stores the amount of each letter encountered
            char letterCount[26];
            
            //Keeps a copy of the original message to make comparison and modification much simpler (avoids errors when reading and modifying)
            char messageCopy[messageLength];
            //Copies the original message
            strcpy(messageCopy, message);
            
            //Determines the amount of letters that show up more frequently than any given letter
            char moreFrequent[26];
            
            //Initialises all elements of these arrays to 0 for incrementation
            for(int i = 0; i < 26; i++) {
                letterCount[i] = 0;
                moreFrequent[i] = 0;
            }
            
            
            //Whenever a letter is encountered, increment how often that letter has appeared
            for(int i = 0; i < messageLength; i++) {
                if(message[i] < 91 && message[i] > 64)
                    letterCount[message[i]%65]++;
            }
            
            //These are ordered from the most frequent to the least frequent for common english use
            char letterOcc[] = "ETAOINSRHDLUCMFYWGPBVKXQJZ";
            
            //Cycles through and compares the frequency with which letters appear in the message
            for(int ind = 0; ind < 26; ind++) {
                for(int i = ind+1; i < 26; i++) {
                    
                    //If one letter is more frequent than another, increment the amount of letters which appear more frequently than the other one
                    if(letterCount[ind] > letterCount[i])
                        moreFrequent[i]++;
                    else //Otherwise increment the amount of letters more frequent than the first letter
                        moreFrequent[ind]++;
                }
                
            }

            //Cycle through the message
            for(int i = 0; i < messageLength; i++) {
                for(int ind = 0; ind < 26; ind++) {
                    //If the character is a capital letter
                    if(message[i] == ind + 65) {
                        //Convert this letter to the letter in the same frequency position in the letterOcc string (i.e. normal english)
                        messageCopy[i] = letterOcc[moreFrequent[ind]];
                        //Quit the for loop to avoid modifying this character again
                        break;
                    }
                }
                
            }
            //Opens the file for writing
            FILE *output;
            output = fopen("\output.txt", "w");
            
            //If it cannot open, quit
            if(ferror(output)) {
                printf("Error in opening file");
                return;
            }
            
            //Otherwise print the message
            fprintf(output, "%s", messageCopy);
            fclose(output);
        }
        
    }

}


//Determines a ratio of english to total words within the first 5 words
float wordsCorrect(char *message, int messageLength) {
    //Stores the amount of 'spaces' (non letters) in the message
    int spaces = 0;
    
    //Looks at each character
    for(int i = 0; i < messageLength; i++) {
        
        //Records the amount of spaces encountered
        if(message[i] > 90 || message[i] < 65) {
            spaces++;
            
        }
    }
    
    //Stores the positions of the spaces
    int spacePos[spaces];
    //Used as an index for spacePos
    int spaceInd = 0;
    
    //For each character in the word
    for(int i = 0; i < messageLength; i++) {
        //Check if it's a letter
        if(message[i] < 65 || message[i] > 90) {
            //Stores the position if it is not a lettter
            spacePos[spaceInd] = i;
            spaceInd++;
        }
    }
    //Stores the amount of words to be tested to verify if decryption has worked
    int wordsToTest;
    
    //Set this to be spaces + 1 with an upper bound of 4 words
    if(spaces < 4)
        wordsToTest = spaces + 4;
    else
        wordsToTest = 4;
        
    //Stores the first 5 words with a maximum length of 30 characters each
    char currWord[wordsToTest][30];
    
    //Stores the amount of english words and declares wordLength for use later
    int wordCount = 0, wordLength;
    
    //Cycle through the words
    for(int i = 0; i < wordsToTest; i++) {
        if(i == 0) {//For the first word, set its length to the amount of characters before the first space
            wordLength = spacePos[0];
        } else {//For the rest, set their lengths to the distance from one space to the next
            wordLength = spacePos[i] - spacePos[i-1] - 1;
        }
    


        //Takes the message word by word
        for(int currLet = 0; currLet < wordLength; currLet++) {
            //If it is not the first word, take the space position as a reference point and store the letters
            if(i != 0) {
                currWord[i][currLet] = message[spacePos[i-1] + currLet + 1];
            } else {//If it is the first word, store the letters
                currWord[i][currLet] = message[currLet];
                
            }

        }
        
        //If currWord[i] is a word, add it to the wordcount
        wordCount += isWord(currWord[i], wordLength);
    }

    //Return the ratio of english to total words in the first 5  
    return (float)(wordCount)/wordsToTest;
}


//Determines if toTest is a word
int isWord(char *toTest, int toTestLength) {
    
    //Opens the dictionary file for word comparison
    FILE *wordList = fopen("\wordlist.txt", "r");
    
    //Make a new string to store the words from the dictionary file
    char currWord[toTestLength];
    
    //While there are still more words in the dictionary file
    while(!feof(wordList)) {
        
        //Read a word
        fscanf(wordList, "%s", &currWord);
        
            //If the word from the dictionary is the same as toTest
            if(!strcmp(toTest, currWord)){
                
                //Return that it is a word
                return 1;
            }

    }
    
    //If no word matches, assume that it is not a word
    return 0;
}