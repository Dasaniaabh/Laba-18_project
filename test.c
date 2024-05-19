//
// Created by MSI on 19.05.2024.
//
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "libs/data_struct/string/string.h"

void test_strlen() {
    char *s = "Hello, world!";

    assert(strlen1(s) == strlen(s));
    assert(strlen2(s) == strlen(s));
    assert(strlen_(s) == strlen(s));
}

void test_find() {
    char *s = "Hello, world!";

    assert(find(s, s + strlen(s), 'o') == s + 4);
    assert(find(s, s + strlen(s), 'z') == s + strlen(s));
}

void test_findNonSpace() {
    char *s = " Hello, world!";

    assert(findNonSpace(s) == s + 1);
}

void test_findSpace() {
    char *s = "Hello, world!";

    assert(findSpace(s) == s + 6);
}

void test_findNonSpaceReverse() {
    char *s = "Hello, world! ";

    assert(findNonSpaceReverse(s + strlen(s) - 1, s) == s + strlen(s) - 2);
}

void test_findSpaceReverse() {
    char *s = "Hello, world! ";

    assert(findSpaceReverse(s + strlen(s) - 1, s) == s + 5);
}

void test_areEqual() {
    char *s1 = "Hello, world!";
    char *s2 = "Hello, world!";

    assert(areEqual(s1, s2) == 0);
    assert(areEqual(s1, s1 + 1) == 1);
    assert(areEqual(s1 + 1, s1) == -1);
}

void test_copy() {
    char s[] = "Hello, world!";
    char buffer[100];

    assert(copy(s, s + strlen(s), buffer) == buffer + strlen(s));
    assert(strcmp(buffer, s) == 0);
}

void test_copyIf() {
    char s[] = "Hello, world!";
    char buffer[100];

    assert(copyIf(s, s + strlen(s), buffer, isalpha) == buffer + strlen(s) - 1);
    assert(strcmp(buffer, "Helloworld") == 0);
}

void test_copyIfReverse() {
    char s[] = "Hello, world!";
    char buffer[100];

    assert(copyIfReverse(s + strlen(s) - 1, s, buffer, isalpha) == buffer + strlen(s) - 1);
    assert(strcmp(buffer, "dlrow ,olleH") == 0);
}
void test(){
    test_strlen();
    test_find();
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();
    test_areEqual();
    test_copy();
    test_copyIf();
    test_copyIfReverse();

    printf("All tests passed!\n");

}

int main() {
    test();

    return 0;
}

