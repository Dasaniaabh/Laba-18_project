//
// Created by MSI on 19.05.2024.
//

#ifndef LABA_18PROJECT_STRING_H
#define LABA_18PROJECT_STRING_H

#include <memory.h>
#include <stdbool.h>


size_t strlen1(char *s);

size_t strlen2(char *s);

size_t strlen_(const char *begin);

char* find(char *begin, char *end, int ch);

char* findNonSpace(char *begin);

char* findSpace(char *begin);

char* findNonSpaceReverse(char *reversedStart, const char *reversedEnd);

char* findSpaceReverse(char *reversedStart, const char *reversedEnd);

int areEqual(char* left, char* right);

char* copy(const char* start, const char* end, char* destination);

char* copyIf(char* start, const char* end, char* destination, bool (*filter)(char));

char* copyIfReverse(char* reversedStart, const char* reversedEnd, char* destination, bool (*filter)(char));

int notSpace(char c);

int strcmp_(const char *str1, const char *str2);



#endif //LABA_18PROJECT_STRING_H
