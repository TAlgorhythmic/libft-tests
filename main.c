#include "../libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	clean(char **arr)
{
	int i = 0;

	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int len(char **strs) {
	size_t i = 0;

	while (strs[i] != NULL)
		i++;
	return i;
}

int check(int i1, int i2) {
	return (i1 == i2 || (i1 > 0 && i2 > 0));
}

int main() {
	// Char tests
	printf("Starting char tests...\n");
	for (int i = 0; i < 256; i++) {
		if (!check(isalpha(i), ft_isalpha(i)))
			printf("ft_isalpha() test failed for ascii %d\n", i);
		if (!check(isdigit(i), ft_isdigit(i)))
			printf("ft_isdigit() test failed for ascii %d\n", i);
		if (!check(isalnum(i), ft_isalnum(i)))
			printf("ft_isalnum() test failed for ascii %d\n", i);
		if (!check(isascii(i), ft_isascii(i)))
			printf("ft_isascii() test failed for ascii %d\n", i);
		if (!check(isprint(i), ft_isprint(i)))
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
	if (split == NULL)
		printf("Malloc failed.\n");
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
	printf("Starting strlcpy tests...\n");

	char buff1[4];
	char buff2[12];
	char buff2small[3];
	char buff3[12];
	char buff3small[5];

	size_t buff1res = ft_strlcpy(buff1, strlen1, 4);
	size_t buff2res = ft_strlcpy(buff2, strlen2, 12);
	size_t buff2smallres = ft_strlcpy(buff2small, strlen2, 3);
	size_t buff3res = ft_strlcpy(buff3, strlen3, 12);
	size_t buff3smallres = ft_strlcpy(buff3small, strlen3, 5);

	if (buff1res != 0 || strcmp(buff1, strlen1) != 0)
		printf("strlcpy test failed for empty string with buffer size 4\n");
	if (buff2res != 8 || strcmp(buff2, strlen2) != 0)
		printf("strlcpy test failed for \"%s\" with buffer size 12\nExpected ->\nResult: 8\nDest: sfs t4eg\n\nGot instead ->\nResult: %d\nDest: %s\n\n", strlen2, (int)buff2res, buff2);
	if (buff2smallres != 8 || strcmp(buff2small, "sf") != 0)
		printf("strlcpy test failed for \"%s\" with buffer size 3\nExpected ->\nResult: 8\nDest: sf\n\nGot instead ->\nResult: %d\nDest: %s\n\n", strlen2, (int)buff2smallres, buff2small);
	if (buff3res != 10 || strcmp(buff3, strlen3) != 0)
		printf("strlcpy test failed for \"%s\" with buffer size 12\nExpected ->\nResult: 10\nDest: hyew3d!`X~\n\nGot instead ->\nResult: %d\nDest: %s\n\n", strlen3, (int)buff3res, buff3);
	if (buff3smallres != 10 || strcmp(buff3small, "hyew") != 0)
		printf("strlcpy test failed for \"%s\" with buffer size 5\nExpected ->\nResult: 10\nDest: hyew\n\nGot instead ->\nResult: %d\nDest: %s\n\n", strlen3, (int)buff3smallres, buff3small);

	// strlcat test
	printf("Starting strlcat tests...\n");

	char cat1[3] = "e";
	char cat2[15] = "eri";
	char cat3[11] = "eomae";

	size_t size_exp1t = strlen(cat1) + strlen(strlen1);
	size_t res1t = ft_strlcat(cat1, strlen1, 3);
	if (size_exp1t != res1t)
		printf("ft_strlcat lenght test failed, check the return value.");
	if (strcmp(cat1, "e") != 0)
		printf("ft_strlcat test failed for appending an empty string to \"e\", result: %s\n", cat1);

	size_t size_exp1 = strlen(cat1) + strlen(strlen3);
	size_t res1 = ft_strlcat(cat1, strlen3, 3);
	if (size_exp1 != res1)
		printf("ft_strlcat lenght test failed, check the return value.");
	if (strcmp(cat1, "eh") != 0)
		printf("ft_strlcat test failed for appending \"hyew3D!`X~\" to \"e\" with buff size 3, result: %s\n", cat1);

	size_t size_exp2 = strlen(cat2) + strlen(strlen3);
	size_t res2 = ft_strlcat(cat2, strlen3, 15);
	if (size_exp2 != res2)
		printf("ft_strlcat lenght test failed, check the return value.");
	if (strcmp(cat2, "erihyew3D!`X~") != 0)
		printf("ft_strlcat test failed for appending \"hyew3D!`X~\" to \"eri\" with buff size 15, result: %s\n", cat2);

	size_t size_exp3 = strlen(cat3) + strlen(strlen3);
	size_t res3 = ft_strlcat(cat3, strlen3, 11);
	if (size_exp3 != res3)
		printf("ft_strlcat lenght test failed, check the return value.");
	if (strcmp(cat3, "eomaehyew3") != 0)
		printf("ft_strlcat test failed for appending \"hyew3D!`X~\" to \"eomae\" with buff size 11, result: %s\n", cat3);

	// ft_strchr test
	printf("Starting ft_strchr tests...\n");

	char strtest[] = "gwsei762lkkls";
	if (strchr(strtest, 'c') != ft_strchr(strtest, 'c'))
		printf("ft_strchr test failed, expected NULL but found something else\n");
	if (strcmp(strchr(strtest, 's'), ft_strchr(strtest, 's')) != 0)
		printf("ft_strchr test failed, expected \"%s\" but found \"%s\"\n", strchr(strtest, 's'), ft_strchr(strtest, 's'));

	// ft_strrchr test
	printf("Starting ft_strrchr tests...\n");

	if (strchr(strtest, 'c') != ft_strchr(strtest, 'c'))
		printf("ft_strchr test failed, expected NULL but found something else\n");
	if (strcmp(strchr(strtest, 'k'), ft_strchr(strtest, 'k')) != 0)
		printf("ft_strchr test failed, expected \"%s\" but found \"%s\"\n", strchr(strtest, 'k'), ft_strchr(strtest, 'k'));

	// ft_strncmp test
	printf("Starting ft_strncmp tests...\n");

	if (strncmp(strtest, "gwsei762lkkls", 10) != ft_strncmp(strtest, "gwsei762lkkls", 10))
		printf("ft_strncmp test failed, result differs.");
	if (strncmp("1234567", "12347", 4) != ft_strncmp("1234567", "12347", 4))
		printf("ft_strncmp test failed, result differs.\nExpected: %d\nGot: %d\n", strncmp("1234567", "12347", 4), ft_strncmp("1234567", "12347", 4));

	// ft_strnstr test
	printf("Starting ft_strnstr tests...\n");

	if (ft_strnstr(strtest, "sei6", 8) != NULL)
		printf("ft_strnstr test failed, origin = %s, introduced = sei6, len = 4, expected NULL but found something else.", strtest);
	if (strcmp(ft_strnstr(strtest, "sei7", 7), "sei762lkkls") != 0)
		printf("ft_strnstr test failed, origin = %s, introduced = sei7, len = 7, expected %s but found something else.", strtest, "sei762lkkls");
	if (ft_strnstr(strtest, "sei7", 4) != NULL)
		printf("ft_strnstr test failed, origin = %s, introduced = sei7, len = 4, expected NULL but found something else.", strtest);
	if (strcmp(ft_strnstr(strtest, "sei76", 89), "sei762lkkls") != 0)
		printf("ft_strnstr test failed, origin = %s, introduced = sei76, len = 89, expected %s but found something else.", strtest, "sei762lkkls");

	// 
}
