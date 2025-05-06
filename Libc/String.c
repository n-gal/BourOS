#include "String.h"

/**
 * K&R implementation
 */
void IntToAscii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    Reverse(str);
}

int AsciiToInt(const char *s) {
    int value = 0;
    for (int i = 0; s[i] >= '0' && s[i] <= '9'; i++) {
        value = value * 10 + (s[i] - '0');
    }
    return value;
}

/* K&R */
void Reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = StrLen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
int StrLen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void Append(char s[], char n) {
    int len = StrLen(s);
    s[len] = n;
    s[len+1] = '\0';
}

int Backspace(char s[]) {
    int len = StrLen(s);
    if(len > 0)
    {
        s[len-1] = '\0';
        return 1;
    }
    return 0;
}

void ToLowerCase(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32;
        }
    }
}

int StrCmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int StrCmpCI(char s1[], char s2[]) {
    int i;

    char s1l[255];
    StrCopy(s1l, s1);
    ToLowerCase(s1l);

    char s2l[255];
    StrCopy(s2l, s2);
    ToLowerCase(s2l);

    for (i = 0; s1l[i] == s2l[i]; i++) {
        if (s1l[i] == '\0') return 0;
    }
    return s1l[i] - s2l[i];
}

void StrCat(char *dest, const char *src, int destBufSize){
    int destLen = StrLen(dest);
    int srcLen = StrLen(src);
    if (destLen + srcLen + 1 > destBufSize)
        return;

    for(int i = 0; i < StrLen(src); i ++){
        dest[destLen + i] = src[i];
    }
}

void CommandSeparate(char string[], char *command, char *args){
    int foundSpace = 0;
    int spaceIndex = 0;
    for(int i = 0; i < StrLen(string); i++){
        if(string[i] == ' ' && foundSpace == 0){
            foundSpace = 1;
            spaceIndex = i;
            for(int j = 0; j < i; j++){
                command[j] = string[j];
            }
            command[i] = '\0';
        }
        if(foundSpace)
        {
            args[i - spaceIndex - 1] = string[i];
            if(i == StrLen(string) - 1){
                args[i - spaceIndex] = '\0';
            }
        }
    }
    if(foundSpace == 0)
    {
        StrCopy(command, string);
        args[0] = '\0';
    }
}

void StrCopy(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}