#include <stdio.h>
#include <string.h>
#include "libs/data_struct/string/string.h"
#include <ctype.h>
#include <malloc.h>
#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__)
#define MAX_STRING_SIZE 1000

typedef struct {
    char *start;
    char *end;
} WordDescriptor;

typedef struct WordDescriptor {
    char *word;
    int length;
} WordDescriptor2;

typedef struct BagOfWords {
    WordDescriptor words[1000];
    size_t size;
} BagOfWords;

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;


void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}


void deleteSpace(){
    char input[] = "Hello World";
    char output[strlen(input) + 1]; // +1 для завершающего нуля

    copyIf(input, input + strlen(input), output, (bool (*)(char)) notSpace);

    printf("Output: %s\n", output);
    ASSERT_STRING("321Hi", output);
}

void removeAdjacentEqualLetters(char *s) {
    char *destination = s;
    char *source = s;

    while (*source != '\0') {
        *destination++ = *source;
        while (*source == *destination && *source != '\0') {
            source++;
        }
    }

    *destination = '\0';
}


void removeExtraSpaces(char *s) {
    char *destination = s;
    char *source = s;

    while (*source != '\0') {
        while (isspace(*source)) {
            source++;
        }

        while (!isspace(*source) && *source != '\0') {
            *destination++ = *source++;
        }

        if (*source != '\0') {
            *destination++ = ' ';
        }
    }

    *destination = '\0';
}

// Функция для перестановки цифр и букв в слове
char* transformWord(char* word) {

    char* newWord = malloc(strlen(word) + 1);

    char* src = word;
    char* dst = newWord;

    while (*src != '\0') {
        if (isdigit(*src)) {
            *dst++ = *src;
        }

        else {
            *dst++ = ' ';
            while (*src != '\0' && !isdigit(*src)) {
                *dst++ = *src;
                src++;
            }
            src--;
        }
        src++;
    }

    *dst = '\0';

    return newWord;
}

void transformWordTest(){
    char* str = "a1b2c3d4e5";

    char* newStr = malloc(strlen(str) + 1);

    char* src = str;
    char* dst = newStr;

    while (*src != '\0') {

        if (isspace(*src)) {
            *dst++ = *src;
        }

        else {
            char* wordStart = src;
            while (!isspace(*src) && *src != '\0') {
                src++;
            }
            char* wordEnd = src;

            char* transformedWord = transformWord(wordStart);
            dst = copy(transformedWord, transformedWord + strlen(transformedWord), dst);
            free(transformedWord);
        }
        src++;
    }

    *dst = '\0';

    printf("%s\n", newStr);

    // Освобождаем выделенную память
    free(newStr);
}

void digitToStart(char *str) {
    int i = 0;
    int j = 0;
    int k;

    while (str[i]) {
        if (isalpha(str[i])) {
            char temp = str[i];
            for (k = i; str[k] != '\0'; k++) {
                str[k] = str[k + 1];
            }
            str[k - 1] = temp;
            j++;
        } else {
            i++;
        }
    }
}
void digitToStartTest(){
    char str[] = "h3llo w0rld";
    digitToStart(str);
    printf("Transformed String: %s\n", str);
}

char* replaceDigitsWithSpaces(const char* str) {
    int numSpaces = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (isdigit(str[i])) {
            numSpaces += str[i] - '0';
        }
    }

    char* newStr = (char*) malloc(len + numSpaces + 1);
    if (!newStr) {
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isdigit(str[i])) {
            int num = str[i] - '0';
            for (int k = 0; k < num; k++) {
                newStr[j++] = ' ';
            }
        } else {
            newStr[j++] = str[i];
        }
    }
    newStr[j] = '\0';

    return newStr;
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen(w1);
    size_t w2Size = strlen(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    char _stringBuffer[1000]; // Буфер для копирования строки

    char *readPtr, *recPtr;

    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        strcpy(_stringBuffer, source); // Копирование исходной строки в буфер
        readPtr = _stringBuffer;
        recPtr = source;
    }

    while (*readPtr != '\0') {
        if (strncmp(readPtr, word1.start, w1Size) == 0) {
            // Найдено вхождение слова w1, заменяем его на слово w2
            for (size_t i = 0; i < w2Size; i++) {
                *recPtr++ = word2.start[i];
            }
            readPtr += w1Size;
        } else {
            *recPtr++ = *readPtr++;
        }
    }

    *recPtr = '\0'; // Устанавливаем конец строки
}

int areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    if (w1.length != w2.length) {
        return 0;
    }
    for (int i = 0; i < w1.length; i++) {
        if (w1.word[i] != w2.word[i]) {
            return 0;
        }
    }
    return 1;
}

int areWordsLexicographicallyOrdered(char *string) {
    WordDescriptor2  previous_word = {NULL, 0};
    char *word_start = string;
    char *word_end = strchr(string, ' ');
    while (word_end != NULL) {
        WordDescriptor current_word = {word_start, word_end - word_start};
        if (!areWordsEqual(previous_word, current_word) &&
            strcmp(previous_word.word, current_word.word) > 0) {
            return 0;
        }
        previous_word = current_word;
        word_start = word_end + 1;
        word_end = strchr(word_start, ' ');
    }
    WordDescriptor current_word = {word_start, (char *) strlen(word_start)};
    if (!areWordsEqual(previous_word, current_word) &&
        strcmp(previous_word.word, current_word.word) > 0) {
        return 0;
    }
    return 1;
}
void getBagOfWords(BagOfWords *bag, char *s) {
    char *word_start = s;
    char *word_end = strchr(s, ' ');
    bag->size = 0;
    while (word_end != NULL) {
        WordDescriptor word = {word_start, (char *) (word_end - word_start)};
        bag->words[bag->size++] = word;
        word_start = word_end + 1;
        word_end = strchr(word_start, ' ');
    }
    WordDescriptor2 word = {word_start, strlen(word_start)};
    bag->words[bag->size++] = word;
}

void printWordsInReverseOrder(BagOfWords *bag) {
    for (int i = bag->size - 1; i >= 0; i--) {
        WordDescriptor2 word = bag->words[i];
        printf("%.*s\n", word.length, word.word);
    }
}

int isPalindrome(char *s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}

int countPalindromes(char *s) {
    int count = 0;
    char *word_start = s;
    char *word_end = strchr(s, ',');
    while (word_end != NULL) {
        if (isPalindrome(word_start, 0, word_end - word_start - 1)) {
            count++;
        }
        word_start = word_end + 1;
        word_end = strchr(word_start, ',');
    }
    if (isPalindrome(word_start, 0, strlen(word_start) - 1)) {
        count++;
    }
    return count;
}

char *mergeStrings(char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 2);
    char *p1 = s1;
    char *p2 = s2;
    char *p = result;
    while (*p1 != '\0' || *p2 != '\0') {
        if (*p1 != '\0') {
            *p++ = *p1++;
        }
        if (*p2 != '\0') {
            *p++ = *p2++;
        }
        *p++ = ' ';
    }
    *p = '\0';
    return result;
}

void reverseWords(char *s) {
    char *buffer = malloc(strlen(s) + 1);
    char *p = s;
    char *q = buffer;
    while (*p != '\0') {
        while (*p != ' ' && *p != '\0') {
            *q++ = *p++;
        }
        if (*p != '\0') {
            *q++ = ' ';
            p++;
        }
    }
    *q = '\0';
    strcpy(s, buffer);
    free(buffer);
}
WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(
        char *s, WordDescriptor *w) {
    int found = 0;
    while (*s != '\0') {
        if (*s == ' ') {
            if (found) {
                return WORD_FOUND;
            }
        } else if (*s == 'a' || *s == 'A') {
            found = 1;
        }
        s++;
    }
    if (found) {
        return FIRST_WORD_WITH_A;
    } else {
        return NOT_FOUND_A_WORD_WITH_A;
    }
}


void wordDescriptorToString(WordDescriptor2 word, char *destination) {
    strcpy(destination, word.word);
}

BagOfWords *createBagOfWords(char *s) {
    BagOfWords *bag = malloc(sizeof(BagOfWords));
    bag->size = 0;
    bag->words = NULL;

    char *token = strtok(s, " ");
    while (token != NULL) {
        int found = 0;
        for (int i = 0; i < bag->size; i++) {
            if (strcmp(bag->words[i].word, token) == 0) {
                bag->words[i].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            bag->words = realloc(bag->words, (bag->size + 1) * sizeof(WordDescriptor));
            bag->words[bag->size].word = malloc(strlen(token) + 1);
            strcpy(bag->words[bag->size].word, token);
            bag->words[bag->size].count = 1;
            bag->size++;
        }

        token = strtok(NULL, " ");
    }

    return bag;
}
int compareStrings(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}
char* findWordInString(char *s1, char *s2) {
    char *word = strtok(s1, " ");
    while (word != NULL) {
        if (strstr(s2, word) != NULL) {
            return word;
        }
        word = strtok(NULL, " ");
    }
    return NULL;
}

// Функция для получения строки из слов строки s1, которые отличны от последнего слова
void getDifferentWords(char *s1, char *lastWord) {
    char *word = strtok(s1, " ");
    char result[1000] = "";
    int lastWordFound = 0;

    while (word != NULL) {
        if (strcmp(word, lastWord) == 0) {
            lastWordFound = 1;
        } else {
            if (lastWordFound) {
                strcat(result, " ");
            }
            strcat(result, word);
        }
        word = strtok(NULL, " ");
    }

    printf("Result: %s\n", result);
}
int isPalindrome(char *word) {
    int length = strlen(word);
    for (int i = 0; i < length / 2; i++) {
        if (tolower(word[i]) != tolower(word[length - i - 1])) {
            return 0;
        }
    }
    return 1;
}

// Функция для удаления слов-палиндромов из строки
void removePalindromes(char *s) {
    char result[1000] = "";
    char *word = strtok(s, " ");

    while (word != NULL) {
        if (!isPalindrome(word)) {
            strcat(result, word);
            strcat(result, " ");
        }
        word = strtok(NULL, " ");
    }

    printf("Result: %s\n", result);
}

int countWords(char *str) {
    int count = 0;
    int isWord = 0;

    while (*str) {
        if (isalpha(*str)) {
            if (!isWord) {
                count++;
                isWord = 1;
            }
        } else {
            isWord = 0;
        }
        str++;
    }

    return count;
}

// Функция для дополнения строки с меньшим количеством слов словами из строки с большим количеством слов
void appendWords(char *str1, char *str2) {
    int count1 = countWords(str1);
    int count2 = countWords(str2);

    if (count1 < count2) {
        char *temp = str1;
        str1 = str2;
        str2 = temp;

        int tempCount = count1;
        count1 = count2;
        count2 = tempCount;
    }

    // Найти начало последнего слова в строке str2
    char *lastWordStart = str2;
    char *lastWordEnd = str2;
    int wordCount = 0;

    while (*lastWordEnd) {
        if (isalpha(*lastWordEnd)) {
            if (wordCount == count2) {
                lastWordStart = lastWordEnd;
            }
        } else {
            wordCount++;
        }
        lastWordEnd++;
    }

    // Дополнить строку str1 последними словами из str2
    strcat(str1, lastWordStart);

    printf("Result: %s\n", str1);
}

//test method
void test(){
    deleteSpace();
    removeExtraSpaces("httpLLLaQuery");
    removeAdjacentEqualLetters("select  *  from  table");
    transformWordTest();
    digitToStartTest();
}

int checkWordLettersInString(char *word, char *str) {
    int wordLetterCount[26] = {0};
    int strLetterCount[26] = {0};


    for (int i = 0; word[i]; i++) {
        if (isalpha(word[i])) {
            wordLetterCount[tolower(word[i]) - 'a']++;
        }
    }

    // Подсчитываем количество каждой буквы в строке
    for (int i = 0; str[i]; i++) {
        if (isalpha(str[i])) {
            strLetterCount[tolower(str[i]) - 'a']++;
        }
    }

    // Проверяем, входит ли каждая буква слова в строку
    for (int i = 0; i < 26; i++) {
        if (wordLetterCount[i] > strLetterCount[i]) {
            return 0;  // если хотя бы одна буква не входит, возвращаем 0
        }
    }

    return 1;  // если все буквы слова входят, возвращаем 1
}


int main() {
    //start "test" method for testing all methods
    test();

    return 0;
}
