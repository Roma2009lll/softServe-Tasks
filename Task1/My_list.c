#include"My_list.h"

int main(void)
{
	char** my_list = NULL;
	return 0;
}

void StringListInit(char*** list)
{
	if (list == NULL)
	{
		return;
	}
	*list = (char**)malloc(sizeof(char*));
	if (*list == NULL) {
		return;
	}
	(*list)[0] = NULL;
}

void StringListDestroy(char*** list)
{
	if (list == NULL || *list == NULL)
	{
		return;
	}
	int i = 0;
	while ((*list)[i] != NULL) {
		free((*list)[i]);
		(*list)[i] = NULL;
		i++;
	}
	free(*list);
	*list = NULL;
}

void StringListAdd(char*** list, char* str)
{
	if (list == NULL || *list == NULL || str == NULL)
	{
		return;
	}
	int count = StringListSize(*list);
	char** tempPtr = (char**)realloc(*list, sizeof(char*) * (count + 2));
	if (tempPtr == NULL)
	{
		return;
	}
	*list = tempPtr;
	char* newStr = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	if (newStr == NULL)
	{
		return;
	}
	strcpy(newStr, str);
	(*list)[count] = newStr;
	(*list)[count + 1] = NULL;
}

void StringListRemove(char*** list, const char* str)
{
	int i = 0;
	while ((*list)[i] != NULL)
	{
		if ((strcmp((*list)[i], str) == 0))
		{
			free((*list)[i]);
			ShiftStringList(list, i);
		}
		else
		{
			i++;
		}
	}
	int new_count = StringListSize(*list);
	char** tempPtr = (char**)realloc(*list, sizeof(char*) * (new_count + 1));
	if (tempPtr != NULL)
	{
		*list = tempPtr;
	}
}

int StringListSize(char** list)
{
	if (list == NULL)
	{
		return 0;
	}
	int count = 0;
	while (list[count] != NULL)
	{
		count++;
	}
	return count;
}

int StringListIndexOf(char** list, char* str) {
	int i = 0;
	while (list[i] != NULL)
	{
		if ((strcmp(list[i], str) == 0))
		{
			return i;
		}
		else {
			i++;
		}
	}
	return -1;
}

void ShiftStringList(char*** list, int index)
{
	while ((*list)[index] != NULL) {
		(*list)[index] = (*list)[index + 1];
		index++;
	}
}

void StringListRemoveDuplicates(char*** list) {
	int write_index = 0;
	for (int i = 0; (*list)[i] != NULL; i++)
	{
		int is_duplicate = 0;
		for (int j = 0; j < write_index; j++)
		{
			if (strcmp((*list)[i], (*list)[j]) == 0)
			{
				is_duplicate = 1;
				break;
			}
		}
		if (is_duplicate)
		{
			free((*list)[i]);
		}
		else
		{
			(*list)[write_index] = (*list)[i];
			write_index++;
		}
	}
	(*list)[write_index] = NULL;
	char** tempPtr = (char**)realloc(*list, sizeof(char*) * (write_index + 1));
	if (tempPtr == NULL)
	{
		return;
	}
	*list = tempPtr;
}

void StringListReplaceInStrings(char** list, char* before, char* after)
{
	int i = 0;
	while (list[i] != NULL)
	{
		StringListChangeStr(&list[i], before, after);
		i++;
	}
}

void StringListChangeStr(char** str, char* before, char* word)
{
	char* it = *str;
	int new_size = getNewLen(str, before, word);
	char* new_word = (char*)malloc(sizeof(char) * new_size);
	if (new_word == NULL)
	{
		return;
	}
	char* new_word_start = new_word;
	char* match;
	while ((match = strstr(it, before)) != NULL)
	{
		while (it < match)
		{
			*new_word++ = *it++;
		}
		char* w = word;
		while (*w != '\0')
		{
			*new_word++ = *w++;
		}
		it = match + strlen(before);
	}
	while (*it != '\0')
	{
		*new_word++ = *it++;
	}
	*new_word = '\0';
	free(*str);
	*str = new_word_start;
}

int getNewLen(char** str, char* before, char* word)
{
	int before_len = strlen(before);
	int word_len = strlen(word);
	int str_len = strlen(*str);
	char* it = *str;
	char* match;
	int count = 0;
	while ((match = strstr(it, before)) != NULL)
	{
		count++;
		it = match + before_len;
	}
	return str_len + count * (word_len - before_len) + 1;
}

void StringListSort(char** list)
{
	int count = StringListSize(list);
	for (int i = 0; i < count; i++)
	{
		int index = StringListGetMin(list, i, count);
		SwapStr(&list[i], &list[index]);
	}
}

int StringListGetMin(char** list, int start, int count)
{
	int index = start;
	for (int i = start + 1; i < count; i++)
	{
		if (strcmp(list[i], list[index]) < 0)
		{
			index = i;
		}
	}
	return index;
}

void SwapStr(char** str1, char** str2)
{
	char* temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}