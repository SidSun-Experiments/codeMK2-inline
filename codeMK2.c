//
// Created by sids on 6/12/18.
//
#include <stdio.h>
#include <stdlib.h> // For exit()
//Declaration of functions
int code(char letter);
int encode(int argc, char *argv[]);
int sunCodePassPhrase(int number, int count);
int passPhraseCalculate(char *argv[]);
int decode(int argc, char *argv[]);
unsigned concatenate(unsigned x, unsigned y);
int actCode(int digit);
int writeOutput(long long int encodedMessage,int encodedMessageLength, char *argv[]);
int calculateSunPassPhrase(int passPhrase);
//Functions
int main(int argc, char *argv[])
{
    char input = *argv[1];
    if (input == *"-e"){
        encode(argc,argv);
    } else if (input == *"o"){
        decode(argc,argv);
    }
}
int decode(int argc, char *argv[]){
    FILE *inputCode = fopen(argv[2], "r");
    int a=7260703;
    char codeChar;
    int passPhrase,flag=1,SPP,countPPDigit,tempASCII,codeToDecode;
    long long int decodingOffSet;
    //Loop Control variables
    int i=1,j;
    //Call function to calculate PassPhrase
    passPhrase = passPhraseCalculate(argv);
    //Call function to calculate sunPassPhrase
    SPP = calculateSunPassPhrase(passPhrase);
    codeChar = fgetc(inputCode);
//    if (codeChar != EOF) {
        while (codeChar != EOF) {
            if (codeChar != '-') {
                printf("Current char: %c\n", codeChar);
            codeChar = codeChar - '0'; //converts to int on which we can operate
                if (flag == 1) {
                    codeToDecode = codeChar;
                    flag = 0;
                } else {
                    codeToDecode = concatenate(codeToDecode, codeChar);
                }
                printf("Code: %d\n", codeToDecode);
            } else {
                printf("Aha, next block\n");
//                i = 0;
                flag = 1;
            }
//            if () {
                //printf("%d\n",(int)codeChar);
                codeChar = fgetc(inputCode);
//            } else {
//                printf("Kul\n");
//                i=0;
//            }
        }
//    decodingOffSet =
    return 0;
}
int encode(int argc, char *argv[]){
    FILE *messageFile = fopen(argv[2], "r");
    char messageChar;
    int messageArray[1000];
    char minus = *"-";
    int a=7260703;
    long long int messageIndivisualEncoded;
    int passPhrase,SPP, tempASCII, countPPDigit = 0;
    int messageASCII;
    //Loop control variables
    int n=0,i=0;
    if (messageFile == NULL)
    {
        printf("Please give input File destination \n");
        exit(0);
    }
    //Call passPhrase calculation function
    passPhrase = passPhraseCalculate(argv);
    //Call function for calculations of SPP
    SPP = calculateSunPassPhrase(passPhrase);
    //Start Message calculations
    messageChar = fgetc(messageFile);
    while (messageChar != EOF)
    {
        printf("Char: %c, ASCII: %d\n",messageChar, (int)messageChar);
        messageASCII = (int) messageChar;
        printf("a: %d\n",a);
        printf("messageASCII: %d\n",messageASCII);
        printf("SPP: %d\n",SPP);
        printf("passphrase: %d\n",passPhrase);
        messageIndivisualEncoded =  (long long int) ((a + messageASCII*SPP)/passPhrase);
        tempASCII = messageIndivisualEncoded;
        printf("Message: %lld\n",messageIndivisualEncoded);
        i=0;
        while (tempASCII != 0){
            tempASCII=tempASCII/10;
            i++;
        }
        printf("Calling write out now.\n");
        writeOutput(messageIndivisualEncoded,i,argv);
        i=1; //Reset i to 1
        messageArray[n] = messageIndivisualEncoded;
        messageChar = fgetc(messageFile);
        if(messageChar != EOF){ //I don't know why i wrote this but it works, i guess.. don't touch it!
            n++;
        }
    }
    fclose(messageFile);
    return 0;
}
int writeOutput(long long int encodedMessage,int encodedMessageLength,char *argv[]){
    FILE *outputFile = fopen(argv[4],"a");
    int encodedMessageDigitArray[encodedMessageLength];
    int messageDigit,n=1,i;
    while (encodedMessage!=0){
        messageDigit = encodedMessage % 10;
        encodedMessageDigitArray[encodedMessageLength - n]= messageDigit;
        n++;
        encodedMessage = encodedMessage/10;
    }
    for(i=0;i<encodedMessageLength;i++) {
        fprintf(outputFile, "%d", encodedMessageDigitArray[i]);
        printf("Number: %d",(int)encodedMessageDigitArray[i]);
    }
    fprintf(outputFile,"%c",'-');
    printf("\n");
    fclose(outputFile);
}
/*int code(char letter){
    int ascii = (int) letter;

    printf("%d\n",ascii);
}*/
int sunCodePassPhrase(int number, int count){
    int digit,code,spp = 1,flag = 1, digitArray[count],n=1;
    unsigned int pow = 10;
  //  printf("Count: %d",count);
  //  printf("Got: %d\n",number);
    while (number != 0){
        digit = number % 10;
        digitArray[count-n] = digit; //n must be initialized with 1 as arrays start at 0
        n++;
        number = number/10;
    }
    for (n=0;n<count;n++){
        code = actCode(digitArray[n]);
        if(flag==1){
            spp = code;
            flag = 0;
        } else {
            spp = concatenate(spp, code);
        }
    }
    return spp;
}
unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
}
int actCode(int digit){
    int code;
    switch (digit) {
        case 0:
            code = 0;
            break;
        case 1:
            code = 1;
            break;
        case 2:
            code = 10;
            break;
        case 3:
            code = 11;
            break;
        case 4:
            code = 100;
            break;
        case 5:
            code = 101;
            break;
        case 6:
            code = 110;
            break;
        case 7:
            code = 111;
            break;
        case 8:
            code = 1000;
            break;
        case 9:
            code = 1001;
            break;
        default:
            break;
    }
    return code;
}
int passPhraseCalculate(char *argv[]){
    FILE *passPhraseFile = fopen(argv[3],"r");
    char passPhraseChar;
    int passPhraseASCII,passPhrase, passPhraseDiff,tempASCII,flag=1;
    long long int countPPDigit=0;
    //Start Code for PP calculation
    if (passPhraseFile == NULL) {
        printf("Please Give PassPhrase destination \n");
        exit(0);
    }
    passPhraseChar = fgetc(passPhraseFile);
    while(passPhraseChar != EOF){
        if ((int)passPhraseChar != 10) {
            passPhraseASCII = (int) passPhraseChar;
            tempASCII = passPhraseASCII;
            while (tempASCII != 0){
                tempASCII = tempASCII/10;
                countPPDigit++;
            }
            if (flag == 1) {
                passPhraseDiff = passPhraseASCII;
                flag = 0;
            } else {
                passPhraseDiff = passPhraseDiff - passPhraseASCII;
            }
            passPhraseChar = fgetc(passPhraseFile);

        } else {
            break;
        }
    }
    passPhraseDiff = abs(passPhraseDiff);
    printf("Diff: %d\n",passPhraseDiff);
    printf("Count: %d\n",countPPDigit);
    passPhrase = (passPhraseDiff / countPPDigit);
    printf("Sending: %d",passPhrase);
    return passPhrase;
}
int calculateSunPassPhrase(int passPhrase){
    int tempASCII,countPPDigit,SPP;
    //Start calculations for SPP
    tempASCII = passPhrase;
    countPPDigit = 0;
    while (tempASCII != 0){
        tempASCII = tempASCII/10;
        countPPDigit++;
    }
    SPP = sunCodePassPhrase(passPhrase,countPPDigit);
    return SPP;
}