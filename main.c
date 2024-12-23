#include "../libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

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

char ft_strmapi_test(unsigned int n, char ch) {
	return (ch + n);
}

void ft_striteri_test(unsigned int i, char *s) {
	*s = 'a' + i;
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

	// ft_substr test
	printf("Starting ft_substr tests...\n");

	char sub[] = "Hi how are you.";
	
	char *subtest1 = ft_substr(sub, 1, 5);
	char *subtest2 = ft_substr(sub, 5, 40);
	char *subtest3 = ft_substr(sub, 5, 2);

	if (subtest1 == NULL)
		printf("ft_substr subtest1 malloc failed.\n");
	if (subtest2 == NULL)
		printf("ft_substr subtest2 malloc failed.\n");
	if (subtest3 == NULL)
		printf("ft_substr subtest3 malloc failed.\n");

	if (subtest1 && strcmp(subtest1, "i how") != 0)
		printf("ft_substr test failed for start %d and len %d.\nIntroduced: %s, Expected: %s, Got: %s\n", 1, 5, sub, "i how", subtest1);
	if (subtest2 && strcmp(subtest2, "w are you.") != 0)
		printf("ft_substr test failed for start %d and len %d.\nIntroduced: %s, Expected: %s, Got: %s\n", 5, 40, sub, "w are you.", subtest2);
	if (subtest3 && strcmp(subtest3, "w ") != 0)
		printf("ft_substr test failed for start %d and len %d.\nIntroduced: %s, Expected: %s, Got: %s\n", 5, 2, sub, "w ", subtest3);

	if (subtest1 != NULL) free(subtest1);
	if (subtest2 != NULL) free(subtest2);
	if (subtest3 != NULL) free(subtest3);

	// ft_strjoin test
	printf("Starting ft_strjoin tests...\n");

	char joint1[] = "";
	char joint2[] = "hola";
	char joint3[] = " que tal";

	char *join1 = ft_strjoin(joint2, joint1);
	char *join2 = ft_strjoin(joint1, joint3);
	char *join3 = ft_strjoin(joint2, joint3);

	if (join1 == NULL)
		printf("ft_strjoin for join1 malloc failed.\n");
	if (join2 == NULL)
		printf("ft_strjoin for join2 malloc failed.\n");
	if (join3 == NULL)
		printf("ft_strjoin for join3 malloc failed.\n");

	if (strcmp(join1, "hola") != 0)
		printf("ft_strjoin test 1 failed, introduced \"%s\" and \"%s\", expected \"%s\" but got \"%s\"\n", joint2, joint1, "hola", join1);
	if (strcmp(join2, " que tal") != 0)
		printf("ft_strjoin test 2 failed, introduced \"%s\" and \"%s\", expected \"%s\" but got \"%s\"\n", joint1, joint3, " que tal", join2);
	if (strcmp(join3, "hola que tal") != 0)
		printf("ft_strjoin test 3 failed, introduced \"%s\" and \"%s\", expected \"%s\" but got \"%s\"\n", joint2, joint3, "hola que tal", join3);

	if (join1 != NULL) free(join1);
	if (join2 != NULL) free(join2);
	if (join3 != NULL) free(join3);

	// ft_strtrim test
	printf("Starting ft_strtrim tests...\n");

	char origin[] = "fsodoowbsha";
	char trim_mat1[] = "shaw";
	char trim_mat2[] = "odo";
	char trim_mat3[] = "afs";
	char trim_mat4[] = "oowbsh";

	char *trim1 = ft_strtrim(origin, trim_mat1);
	char *trim2 = ft_strtrim(origin, trim_mat2);
	char *trim3 = ft_strtrim(origin, trim_mat3);
	char *trim4 = ft_strtrim(origin, trim_mat4);

	if (trim1 == NULL)
		printf("ft_strtrim trim1 malloc failed\n");
	if (trim2 == NULL)
		printf("ft_strtrim trim2 malloc failed\n");
	if (trim3 == NULL)
		printf("ft_strtrim trim3 malloc failed\n");
	if (trim4 == NULL)
		printf("ft_strtrim trim4 malloc failed\n");

	if (strcmp(trim1, origin) != 0)
		printf("ft_strtrim failed, original str \"%s\", trim \"%s\", expected \"%s\", got \"%s\"\n", origin, trim_mat1, origin, trim1);
	if (strcmp(trim2, "fsowbsha") != 0)
		printf("ft_strtrim failed, original str \"%s\", trim \"%s\", expected \"%s\", got \"%s\"\n", origin, trim_mat2, "fsowbsha", trim2);
	if (strcmp(trim3, origin) != 0)
		printf("ft_strtrim failed, original str \"%s\", trim \"%s\", expected \"%s\", got \"%s\"\n", origin, trim_mat3, origin, trim3);
	if (strcmp(trim4, "fsoda") != 0)
		printf("ft_strtrim failed, original str \"%s\", trim \"%s\", expected \"%s\", got \"%s\"\n", origin, trim_mat4, "fsoda", trim4);

	if (trim1 != NULL) free(trim1);
	if (trim2 != NULL) free(trim2);
	if (trim3 != NULL) free(trim3);
	if (trim4 != NULL) free(trim4);

	// ft_atoi test
	printf("Starting ft_atoi tests...\n");

	char atoi1[] = "--8828794788";
	char atoi2[] = "-56745";
	char atoi3[] = "++57895";
	char atoi4[] = "+64765";
	char atoi5[] = "78655";
	char atoi6[] = "   +839t8937";
	char atoi7[] = "+++6334  33";
	char atoi8[] = "  43r";
	char atoi9[] = " \t\v\n\v\v\v\t  \n   -37755_4";
	char atoi10[] = "2147483647";
	char atoi11[] = "-2147483648";

	int builtin1 = atoi(atoi1); int ft1 = ft_atoi(atoi1);
	int builtin2 = atoi(atoi2); int ft2 = ft_atoi(atoi2);
	int builtin3 = atoi(atoi3); int ft3 = ft_atoi(atoi3);
	int builtin4 = atoi(atoi4); int ft4 = ft_atoi(atoi4);
	int builtin5 = atoi(atoi5); int ft5 = ft_atoi(atoi5);
	int builtin6 = atoi(atoi6); int ft6 = ft_atoi(atoi6);
	int builtin7 = atoi(atoi7); int ft7 = ft_atoi(atoi7);
	int builtin8 = atoi(atoi8); int ft8 = ft_atoi(atoi8);
	int builtin9 = atoi(atoi9); int ft9 = ft_atoi(atoi9);
	int builtin10 = atoi(atoi10); int ft10 = ft_atoi(atoi10);
	int builtin11 = atoi(atoi11); int ft11 = ft_atoi(atoi11);

	if (builtin1 != ft1)
		printf("ft_atoi test 1 failed. Input \"%s\", expected: %d, got: %d\n", atoi1, builtin1, ft1);
	if (builtin2 != ft2)
		printf("ft_atoi test 2 failed. Input \"%s\", expected: %d, got: %d\n", atoi2, builtin2, ft2);
	if (builtin3 != ft3)
		printf("ft_atoi test 3 failed. Input \"%s\", expected: %d, got: %d\n", atoi3, builtin3, ft3);
	if (builtin4 != ft4)
		printf("ft_atoi test 4 failed. Input \"%s\", expected: %d, got: %d\n", atoi4, builtin4, ft4);
	if (builtin5 != ft5)
		printf("ft_atoi test 5 failed. Input \"%s\", expected: %d, got: %d\n", atoi5, builtin5, ft5);
	if (builtin6 != ft6)
		printf("ft_atoi test 6 failed. Input \"%s\", expected: %d, got: %d\n", atoi6, builtin6, ft6);
	if (builtin7 != ft7)
		printf("ft_atoi test 7 failed. Input \"%s\", expected: %d, got: %d\n", atoi7, builtin7, ft7);
	if (builtin8 != ft8)
		printf("ft_atoi test 8 failed. Input \"%s\", expected: %d, got: %d\n", atoi8, builtin8, ft8);
	if (builtin9 != ft9)
		printf("ft_atoi test 9 failed. Input \"%s\", expected: %d, got: %d\n", atoi9, builtin9, ft9);
	if (builtin10 != ft10)
		printf("ft_atoi test 10 failed. Input \"%s\", expected: %d, got: %d\n", atoi10, builtin10, ft10);
	if (builtin11 != ft11)
		printf("ft_atoi test 11 failed. Input \"%s\", expected: %d, got: %d\n", atoi11, builtin11, ft11);

	// ft_itoa test
	printf("Starting ft_itoa tests...\n");

	int itoa1 = 2147483647;
	int itoa2 = -2147483648;
	int itoa3 = 4225;
	int itoa4 = -9882674;
	int itoa5 = 0;

	char *itoatest1 = ft_itoa(itoa1);
	char *itoatest2 = ft_itoa(itoa2);
	char *itoatest3 = ft_itoa(itoa3);
	char *itoatest4 = ft_itoa(itoa4);
	char *itoatest5 = ft_itoa(itoa5);

	if (itoatest1 == NULL)
		printf("ft_itoa malloc failed for test 1\n");
	if (itoatest2 == NULL)
		printf("ft_itoa malloc failed for test 2\n");
	if (itoatest3 == NULL)
		printf("ft_itoa malloc failed for test 3\n");
	if (itoatest4 == NULL)
		printf("ft_itoa malloc failed for test 4\n");
	if (itoatest5 == NULL)
		printf("ft_itoa malloc failed for test 5\n");

	if (itoatest1 && strcmp(itoatest1, "2147483647") != 0)
		printf("ft_itoa test 1 failed, introduced %d but got \"%s\"\n", itoa1, itoatest1);
	if (itoatest2 && strcmp(itoatest2, "-2147483648") != 0)
		printf("ft_itoa test 2 failed, introduced %d but got \"%s\"\n", itoa2, itoatest2);
	if (itoatest3 && strcmp(itoatest3, "4225") != 0)
		printf("ft_itoa test 3 failed, introduced %d but got \"%s\"\n", itoa3, itoatest3);
	if (itoatest4 && strcmp(itoatest4, "-9882674") != 0)
		printf("ft_itoa test 4 failed, introduced %d but got \"%s\"\n", itoa4, itoatest4);
	if (itoatest5 && strcmp(itoatest5, "0") != 0)
		printf("ft_itoa test 5 failed, introduced %d but got \"%s\"\n", itoa5, itoatest5);

	if (itoatest1 != NULL) free(itoatest1);
	if (itoatest2 != NULL) free(itoatest2);
	if (itoatest3 != NULL) free(itoatest3);
	if (itoatest4 != NULL) free(itoatest4);
	if (itoatest5 != NULL) free(itoatest5);

	// ft_strmapi test
	printf("Starting ft_strmapi test...\n");

	char mapstr[] = "123";
	char *testmapstr = ft_strmapi(mapstr, &ft_strmapi_test);

	if (testmapstr == NULL)
		printf("ft_strmapi malloc failled.\n");

	if (testmapstr && strcmp(testmapstr, "135") != 0)
		printf("ft_strmapi test failed, introduced \"%s\", expected \"%s\", got \"%s\"\n", mapstr, "135", testmapstr);

	if (testmapstr != NULL) free(testmapstr);

	// ft_striteri test
	printf("Starting ft_striteri test...\n");

	char iteristr[] = "suhdf87sfvc";

	ft_striteri(iteristr, &ft_striteri_test);
	if (strcmp(iteristr, "abcdefghijk") != 0)
		printf("ft_striteri test failed, expected \"abcdefghijk\" but got \"%s\" instead\n", iteristr);

	// 
}
