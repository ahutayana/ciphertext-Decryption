#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6262)
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

bool decrypt(const char ciphertext[7676], const char crib[]);
void fillKey(char key[2][26]);
bool isUnique(char key[2][26]);
void printKey(char key[2][26]);
void printDecrypt(const char ciphertext[7676], char plaintext[], char key[2][26]);

void runtest(const char ciphertext[], const char crib[])
{
    cout << "====== " << crib << endl;
    bool result = decrypt(ciphertext, crib);
    cout << "Return value: " << result << endl;
}

int main()
{
    cout.setf(ios::boolalpha); // output bools as "true"/"false"

    runtest("Hirdd ejsy zu drvtry od.\nO'z fodvaaaaaaaaaaaarry.\n", "my secret");
    runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow");
}
void printKey(char key[2][26]) {
    for (int i = 0; i < 26; ++i) {
        cout << key[0][i] << ' ' << key[1][i] << endl;
    }
}

void fillKey(char key[2][26]) {
    for (int i = 0; i < 26; ++i) {
        key[0][i] = 'A' + i;
        key[1][i] = '%';
    }
}

bool isUnique(char key[2][26]) {
    int cribSameCharCount = 0;
    for (int i = 0; i < 26; ++i)//checks for amount of same characters
    {
        if (isalpha(key[1][i])) {
            for (int j = i + 1; j < 26; ++j)
            {
                if (!isalpha(key[1][j]))
                {
                    ++j;
                }
                if (key[1][i] == key[1][j])
                {
                    ++cribSameCharCount;
                    break;
                }
            }
        }
    }

    if (cribSameCharCount > 0)
        return false;

    return true;
}

bool decrypt(const char ciphertext[7676], const char crib[]) {
    char plaintext[200];
    char key[2][26];

    fillKey(key);

    //try to match the crib with a word of the same length
    char tempWord[200] = { '\0' };
    int cipherWordSize = 0;
    bool wordFound = false;
    int k = 0;

    for (int i = 0; i <= strlen(ciphertext); ++i) {
        if (!isalpha(ciphertext[i]) && !wordFound) {
            cipherWordSize = 0;
            wordFound = true;
        }
        else if (isalpha(ciphertext[i]) && k < strlen(crib)) {
            tempWord[k] = ciphertext[i];
            k++;
            cipherWordSize++;
            wordFound = true;
        }
        else if (isalpha(ciphertext[i]) && k >= strlen(crib)) {
            k = 0;
            wordFound = false;
            strcpy(tempWord, "");
        }
        else if (!isalpha(ciphertext[i]) && wordFound) {
            if (strlen(crib) != cipherWordSize) {
                k = 0;
                cipherWordSize = 0;
                wordFound = false;
                strcpy(tempWord, "");
                i--;
            }
            else if (strlen(crib) == cipherWordSize) {
                k = 0;
                for (int l = 0; l < cipherWordSize; ++l) {
                    for (int j = 0; j < 26; ++j) {
                        if (toupper(tempWord[k]) == key[0][j]) {
                            if (key[1][j] != '%' && key[1][j] != toupper(crib[k])) {
                                fillKey(key);
                                k = 0;
                                cipherWordSize = 0;
                                wordFound = false;
                                strcpy(tempWord, "");
                                i--;
                            }
                            key[1][j] = toupper(crib[k]);
                            k++;
                        }
                    }
                }
                if (isUnique(key) && wordFound) {
                    printDecrypt(ciphertext, plaintext, key);
                    return true;
                }
                else {
                    fillKey(key);
                    k = 0;
                    cipherWordSize = 0;
                    wordFound = false;
                    strcpy(tempWord, "");
                    i--;
                }
            }
        }
    }
    return false;
}

void printDecrypt(const char ciphertext[7676], char plaintext[], char key[2][26]) {
    for (int j = 0; j < strlen(ciphertext); ++j) {
        if (isalpha(ciphertext[j]))
        {
            for (int i = 0; i < 26; ++i) {
                if (toupper(ciphertext[j]) == key[0][i] && key[1][i] != '%') {
                    plaintext[j] = key[1][i];
                }
                else if (toupper(ciphertext[j]) == key[0][i] && key[1][i] == '%') {
                    plaintext[j] = tolower(ciphertext[j]);
                }
            }
        }
        else {
            plaintext[j] = ciphertext[j];
        }
    }

    for (int i = 0; i < strlen(ciphertext); ++i) {
        cout << plaintext[i];
    }
}