#include "../libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	*clean(char **arr)
{
	while (*arr)
		free(*arr);
	free(arr);
	return (NULL);
}

int len(char **strs) {
	size_t i = 0;

	while (strs[i] != NULL)
		i++;
	return i;
}

int main() {
	// Char tests
	printf("Starting char tests...\n");
	for (int i = 0; i < 256; i++) {
		if (isalpha(i) != ft_isalpha(i))
			printf("ft_isalpha() test failed for ascii %d\n", i);
		if (isdigit(i) != ft_isdigit(i))
			printf("ft_isdigit() test failed for ascii %d\n", i);
		if (isalnum(i) != ft_isalnum(i))
			printf("ft_isalnum() test failed for ascii %d\n", i);
		if (isascii(i) != ft_isascii(i))
			printf("ft_isascii() test failed for ascii %d\n", i);
		if (isprint(i) != ft_isprint(i))
			printf("ft_isprint() test failed for ascii %d\n", i);
	}
	
	// strdup test
	printf("Starting strdup test...\n");
	char strduptr[] = "fu892s \tca\va88  w64 we44 f7878wewjh38`~ `dc \0SD";
	char *dup1 = ft_strdup(strduptr);
	char *dup2 = strdup(strduptr);

	if (dup1 == NULL)
		printf("Malloc failed for ft_strdup\n");
	if (dup2 == NULL)
		printf("Malloc failed for strdup\n");

	if (strcmp(dup1, dup2) != 0)
		printf("Failed strdup.\nOriginal: %s\nCopy: %s\nBuiltin Copy: %s\n\n", strduptr, dup1, dup2);

	if (dup1 != NULL) free(dup1);
	if (dup2 != NULL) free(dup2);

	// ft_split test
	printf("Starting ft_split tests...\n");
	char splitstr[] = "cccaijnckla89amccs0sc86cas j888c8c11288cccccc";
	char **split = ft_split(splitstr, 'c');
	int size = len(split);
	if (size != 7)
		printf("ft_split() lenght test failed.\nString introduced: %s\nDelimiter: %c\nLenght expected: 7\nLenght: %d\n\n", splitstr, 'c', size);
	
	for (int i = 0; split[i]; i++) {
		if (i == 0 && strcmp(split[i], "aijn") != 0)
			printf("ft_split pos 0 incorrect, got \"%s\", expected aijn\n", split[i]);
		if (i == 1 && strcmp(split[i], "kla89am") != 0)
			printf("ft_split pos 1 incorrect, got \"%s\", expected kla89am\n", split[i]);
		if (i == 2 && strcmp(split[i], "s0s") != 0)
			printf("ft_split pos 2 incorrect, got \"%s\", expected s0s\n", split[i]);
		if (i == 3 && strcmp(split[i], "86") != 0)
			printf("ft_split pos 3 incorrect, got \"%s\", expected 86\n", split[i]);
		if (i == 4 && strcmp(split[i], "as j888") != 0)
			printf("ft_split pos 4 incorrect, got \"%s\", expected \"as j888\"\n", split[i]);
		if (i == 5 && strcmp(split[i], "8") != 0)
			printf("ft_split pos 5 incorrect, got \"%s\", expected 8\n", split[i]);
		if (i == 6 && strcmp(split[i], "11288") != 0)
			printf("ft_split pos 6 incorrect, got \"%s\", expected 11288\n", split[i]);
	}
	if (size >= 7 && split[7] != NULL)
		printf("ft_split test failed, expected to find NULL at position 7, but found something else.\n\n");
	clean(split);

	// strlen test
	printf("Starting strlen tests...\n");
	char strlen1[] = "";
	char strlen2[] = "sfs t4eg\0gsf";
	char strlen3[] = "hyew3D!`X~";
	
	if (strlen(strlen1) != ft_strlen(strlen1))
		printf("strlen test failed for empty string\n");
	if (strlen(strlen2) != ft_strlen(strlen2))
		printf("strlen test failed for \"%s\"\n", strlen2);
	if (strlen(strlen3) != ft_strlen(strlen3))
		printf("strlen test failed for \"%s\"\n", strlen3);

	// strlcpy test
	
}
