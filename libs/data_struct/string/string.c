//
// Created by MSI on 19.05.2024.
//

#include <corecrt.h>
#include"string.h"
#include <ctype.h>

#define CHAR_SIZE sizeof(char)

size_t strlen1(char *s) {
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

size_t strlen2(char *s) {
    int i = 0;
    while (*s != '\0') {
        i++;
        s++;
    }
    return i;
}

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

char *findNonSpace(char *begin) {
    while (isspace(*begin)) {
        begin++;
    }

    return begin;
}
char* findSpace(char *begin){
    while(!isspace(*begin)){
        begin++;
    }
    return begin;
}

char* findNonSpaceReverse(char *reversedStart, const char *reversedEnd) {
    while (isspace(*reversedStart) && reversedStart != reversedEnd) {
        reversedStart--;
    }

    return reversedStart;
}
char* findSpaceReverse(char *reversedStart, const char *reversedEnd){
    while(!isspace(*reversedStart)&&reversedStart!=reversedEnd){
        reversedStart--;
    }
    return reversedStart;
}

int areEqual(char* left, char* right) {
    while (*left++ == *right++);

    if (*left > *right) return 1;

    return (*left == *right) ? 0 : -1;
}
char* copy(const char* start, const char* end, char* destination) {
    size_t length = end - start;

    memcpy(destination, start, CHAR_SIZE * length);

    return destination + length;
}

char* copyIf(char* start, const char* end, char* destination, bool (*filter)(char)) {
    while(start != end) {
        if (filter(*start)) {
            memcpy(destination++, start, CHAR_SIZE);
        }

        start++;
    }

    return destination;
}

char* copyIfReverse(char* reversedStart, const char* reversedEnd, char* destination, bool (*filter)(char)) {
    while(reversedStart != reversedEnd) {
        if (filter(*reversedStart)) {
            memcpy(destination++, reversedStart, CHAR_SIZE);
        }

        reversedStart--;
    }

    return destination;
}

int notSpace(char c) {
    return c != ' ';
}

int strcmp_(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] == str2[i]) {
        if (str1[i] == '\0' || str2[i] == '\0') {
            break;
        }
        i++;
    }
    return str1[i] - str2[i];
}

