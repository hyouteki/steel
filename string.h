#ifndef STEEL_STRING_H_
#define STEEL_STRING_H_

#include <string.h>
#include <ctype.h>

size_t Steel_String_Trim(char **text);
char *Steel_String_FetchNEatUntil(char **text, char delim);
void Steel_String_EatFront(char **text, size_t count);
void Steel_String_EatFrontIf(char **text, int (*when)(int));
char *Steel_String_FetchIf(char *text, int (*when)(int));
int Steel_String_StartsWith(char *text, char *prefix);
void Steel_String_RemoveTrailing(char **text, char delim);

size_t Steel_String_Trim(char **text) {
	char *start = *text;
	size_t col = 0;
	while (isspace(*start)) {
		col++;
		start++;
	}
	char *end = *text + strlen(*text)-1;
    while (end > *text && isspace(*end)) end--;
    *(end+1) = 0;
	*text = start;
	return col;
}

char *Steel_String_FetchNEatUntil(char **text, char delim) {
	char *start = *text;
	size_t i = 0;
	while (*start != delim && i < strlen(*text)) {
		start++;
		i++;
	}
	char *res = strndup(*text, i);
	*text = start;
	return res;
}


void Steel_String_EatFront(char **text, size_t count) {
	if (strlen(*text) <= count) **text = 0;
	else *text += count; 
}

void Steel_String_EatFrontIf(char **text, int (*when)(int)) {
	char *start = *text;
	while (when(*start)) start++;
	*text = start;
}

char *Steel_String_FetchIf(char *text, int (*when)(int)) {
	size_t i = 0, len = strlen(text);
	while (i < len && when(*(text+i))) i++;
	char *res = (char *)malloc(sizeof(char)*(i+1));
	strncpy(res, text, i);
	res[i] = 0;
	return res;
}

int Steel_String_StartsWith(char *text, char *prefix) {
	if (strlen(text) < strlen(prefix)) return 0;
	for (size_t i = 0; i < strlen(prefix); ++i)
		if (text[i] != prefix[i]) return 0;
	return 1;
}

void Steel_String_RemoveTrailing(char **text, char delim) {
	char *end = *text + strlen(*text)-1;
    while (end > *text && *end == delim) end--;
    *(end+1) = 0;
}

#endif // STEEL_STRING_H_
