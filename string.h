#ifndef STEEL_STRING_H_
#define STEEL_STRING_H_

#include <string.h>
#include <ctype.h>

void Steel_String_Trim(char **);
char *Steel_String_FetchUntil(char **, char);
void Steel_String_RemoveSpecial(char **, int (*)(char));
int Steel_String_StartsWith(char *, char *);
void Steel_String_RemoveTrailing(char **, char);

void Steel_String_Trim(char **text) {
	char *start = *text;
	while (isspace(*start)) start++;
	char *end = *text + strlen(*text)-1;
    while (end > *text && isspace(*end)) end--;
    *(end+1) = 0;
	*text = start;
}

char *Steel_String_FetchUntil(char **text, char delim) {
	char *start = *text;
	int i = 0;
	while (*start != delim && i < strlen(*text)) {
		start++;
		i++;
	}
	char *res = strndup(*text, i);
	*text = start;
	return res;
}

void Steel_String_RemoveSpecial(char **text, int (*isSpecial)(char)) {
	char *start = *text;
	while (isSpecial(*start)) start++;
	*text = start;
}

int Steel_String_StartsWith(char *text, char *prefix) {
	if (strlen(text) < strlen(prefix)) return 0;
	for (int i = 0; i < strlen(prefix); ++i)
		if (text[i] != prefix[i]) return 0;
	return 1;
}

void Steel_String_RemoveTrailing(char **text, char delim) {
	char *end = *text + strlen(*text)-1;
    while (end > *text && *end == delim) end--;
    *(end+1) = 0;
}

#endif STEEL_STRING_H_
