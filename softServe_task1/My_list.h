#ifndef MY_LIST_H
#define MY_LIST_H
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>

void StringListInit(char*** list);
void StringListDestroy(char*** list);
void StringListAdd(char*** lisr, char* str);
void StringListRemove(char*** list, const char* str);
int StringListSize(char** list);
int StringListIndexOf(char** list, char* str);
void ShiftStringList(char*** list, int index);
void StringListRemoveDuplicates(char*** list);
void StringListReplaceInStrings(char** list, char* before, char* after);
void StringListChangeStr(char** str, char* before, char* word);
int getNewLen(char** str, char* before, char* word);
void StringListSort(char** list);
int StringListGetMin(char** list, int start, int count);
void SwapStr(char** str1, char** str2);

#endif 

