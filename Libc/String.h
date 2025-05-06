#ifndef STRINGS_H
#define STRINGS_H

void IntToAscii(int n, char str[]);
void Reverse(char s[]);
int StrLen(char s[]);
int Backspace(char s[]);
void ToLowerCase(char s[]);
void Append(char s[], char n);
int StrCmp(char s1[], char s2[]);
int StrCmpCI(char s1[], char s2[]);
int AsciiToInt(const char *s);
void CommandSeparate(char string[], char *command, char *args);
void StrCopy(char *dest, char *src);
void StrCat(char *dest, const char *src, int destBufSize);


#endif