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

/* K&R 
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int StrCmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}