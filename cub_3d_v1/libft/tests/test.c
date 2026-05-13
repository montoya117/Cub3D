/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:26:28 by alemonto          #+#    #+#             */
/*   Updated: 2025/05/13 17:21:51 by alemonto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h> 

// Function to print names
void print_test_name(const char *name) {
    ft_putstr_fd("Test for: ", 1);
    ft_putstr_fd((char *)name, 1);
    ft_putchar_fd('\n', 1);
}

// Function to print split res
void print_split_result(char **result)
{
    int i = 0;
    while (result && result[i])
    {
		printf("result[%d]:", i);
        printf("%s\n", result[i]);
        free(result[i]);
        i++;
    }
    free(result);
}

// Function striteri
void shift_index_iteri(unsigned int i, char *c)
{
    *c = *c + i;
}

// Function for ft_strmapi
char shift_index(unsigned int i, char c)
{
    if (c >= 'a' && c <= 'z')
        return ((c - 'a' + i) % 26 + 'a');
    return c;
}


// FUcntions for lst's

// Function to print some...
void print_content(void *content)
{
    if (content)
    {
        ft_putstr_fd((char *)content, 1);
        ft_putchar_fd('\n', 1);
    }
}

void print_list(t_list *lst)
{
    while (lst)
    {
        ft_putstr_fd((char *)lst->content, 1);
        ft_putchar_fd('\n', 1);
        lst = lst->next;
    }
}

// Function to be used by ft_lstmap
void *to_uppercase(void *content)
{
    if (!content)
        return (NULL);
    char *str = (char *)content;
    size_t len = strlen(str);
    char *upper = malloc(len + 1);
    if (!upper)
        return (NULL);
    size_t i = 0;
    while (str[i])
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            upper[i] = str[i] - 32;
        else
            upper[i] = str[i];
        i++;
    }
    upper[i] = '\0';
    return (upper);
}

// MAIN TEST

int main(void) {

    // Part One Tests
    ft_putstr_fd("Test Part 1:\n", 1);
    ft_putstr_fd("-------------------\n", 1);
	ft_putchar_fd('\n', 1);

    // ft_toupper
    print_test_name("ft_toupper");
    ft_putnbr_fd(ft_toupper('a'), 1);
    ft_putchar_fd(' ', 1);
    ft_putnbr_fd(ft_toupper('z'), 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: 65 90

    // ft_tolower
    print_test_name("ft_tolower");
    ft_putnbr_fd(ft_tolower('A'), 1);
    ft_putchar_fd(' ', 1);
    ft_putnbr_fd(ft_tolower('Z'), 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: 97 122

    // ft_isprint
    print_test_name("ft_isprint");
    ft_putnbr_fd(ft_isprint(' '), 1);
    ft_putchar_fd(' ', 1);
    ft_putnbr_fd(ft_isprint('\t'), 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: 1 0

    // ft_isascii
    print_test_name("ft_isascii");
    ft_putnbr_fd(ft_isascii(127), 1);
    ft_putchar_fd(' ', 1);
    ft_putnbr_fd(ft_isascii(128), 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: 1 0

    // ft_isdigit
    print_test_name("ft_isdigit");
    ft_putnbr_fd(ft_isdigit('5'), 1);
    ft_putchar_fd(' ', 1);
    ft_putnbr_fd(ft_isdigit('a'), 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: 1 0

    // ft_isalnum
    print_test_name("ft_isalnum");
    ft_putnbr_fd(ft_isalnum('a'), 1);
    ft_putchar_fd(' ', 1);
    ft_putnbr_fd(ft_isalnum('#'), 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: 1 0

    // ft_isalpha
    print_test_name("ft_isalpha");
    ft_putnbr_fd(ft_isalpha('a'), 1);
    ft_putchar_fd(' ', 1);
    ft_putnbr_fd(ft_isalpha('5'), 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: 1 0

    // ft_atoi
    print_test_name("ft_atoi");
    ft_putnbr_fd(ft_atoi("42"), 1);
    ft_putchar_fd('\n', 1);
    ft_putnbr_fd(ft_atoi("-123"), 1);
    ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_atoi("2147483650"), 1); // INT_MAX
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_atoi("-2147483651"), 1); // INT_MIN
    ft_putchar_fd('\n', 1); // Output: 42 -123

    // ft_strncmp
    print_test_name("ft_strncmp");
    ft_putnbr_fd(ft_strncmp("test\200", "test\0", 6), 1);
    ft_putchar_fd('\n', 1);
    ft_putnbr_fd(ft_strncmp("abcdef", "abc\375xx", 5), 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: -1 0

    // ft_strlen
    print_test_name("ft_strlen");
    ft_putnbr_fd(ft_strlen("hello"), 1);
    ft_putchar_fd(' ', 1);
    ft_putnbr_fd(ft_strlen(""), 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: 5 0

    // ft_strlcpy
    print_test_name("ft_strlcpy");
    char dest1[10] = "";
    size_t len1 = ft_strlcpy(dest1, "hello", 3);
    ft_putstr_fd(dest1, 1);
    ft_putstr_fd(" (len: ", 1);
    ft_putnbr_fd(len1, 1);
    ft_putstr_fd(")\n", 1);
    ft_putchar_fd('\n', 1);
	// Output: he (len: 5)

    // ft_strlcat
    print_test_name("ft_strlcat");
    char dest2[20] = "hello ";
    size_t len2 = ft_strlcat(dest2, "world", 7);
    ft_putstr_fd(dest2, 1);
    ft_putstr_fd(" (len: ", 1);
    ft_putnbr_fd(len2, 1);
    ft_putstr_fd(")\n", 1);
	// Output: hello w (len: 11)

    // Test 1: Small dest, large src, limited size
    char dest3[15] = "Foo";
    size_t len3 = ft_strlcat(dest3, "BarBazQux", 10);
    ft_putstr_fd(dest3, 1);
    ft_putstr_fd(" (len: ", 1);
    ft_putnbr_fd(len3, 1);
    ft_putstr_fd(")\n", 1);

    // Test 2: Empty dest, short src, exact size
    char dest4[10] = "";
    size_t len4 = ft_strlcat(dest4, "Zap", 4);
    ft_putstr_fd(dest4, 1);
    ft_putstr_fd(" (len: ", 1);
    ft_putnbr_fd(len4, 1);
    ft_putstr_fd(")\n", 1);

    ft_putchar_fd('\n', 1);

    // ft_strchr
    print_test_name("ft_strchr");
    ft_putstr_fd(ft_strchr("hello", 'l'), 1);
    ft_putchar_fd(' ', 1);
    ft_putstr_fd((char *)ft_strchr("hello", 'z'), 1);
	ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: llo NULL

    // ft_strrchr
    print_test_name("ft_strrchr");
    ft_putstr_fd(ft_strrchr("safety", 't'), 1);
    ft_putchar_fd(' ', 1);
    ft_putstr_fd((char *)ft_strrchr("safety", 'z'), 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: ty NULL

    // ft_strnstr
    print_test_name("ft_strnstr");
    ft_putstr_fd(ft_strnstr("banana", "ana", 5),1);
    ft_putchar_fd('\n',1);
    ft_putstr_fd(ft_strnstr("banana", "xyz", 5),1);
    ft_putchar_fd('\n',1);
	ft_putstr_fd(ft_strnstr("banana", "ban", 5), 1);
	ft_putchar_fd('\n',1);
	ft_putstr_fd(ft_strnstr("banana", "ana", 6), 1);
    ft_putchar_fd('\n',1);
	ft_putchar_fd('\n', 1);

    // ft_memset
    print_test_name("ft_memset");
    char buffer3[11] = "1234567890";
    ft_memset(buffer3, 'X', 10);
    ft_putstr_fd("Result 1: ", 1);
    ft_putstr_fd(buffer3, 1);
    ft_putchar_fd('\n', 1);
    char buffer4[6] = "12345";
    ft_memset(buffer4, 'Y', 5);
    ft_putstr_fd("Result 2: ", 1);
    ft_putstr_fd(buffer4, 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1);

	// Output: Result 1: XXXXXXXXXX Result 2: YYYYY

    // ft_bzero 
    print_test_name("ft_bzero");
    char buffer1[20] = "Hello, World!";
    ft_putstr_fd("Before:   ", 1);
    ft_putstr_fd(buffer1, 1);
    ft_putchar_fd('\n', 1);
    ft_bzero(buffer1, 10);
    ft_putstr_fd("Result 1: ", 1);
    ft_putstr_fd(buffer1, 1);
    ft_putchar_fd('\n', 1);
    char buffer2[20] = "Test123";
    ft_putstr_fd("Before:   ", 1);
    ft_putstr_fd(buffer2, 1);
    ft_putchar_fd('\n', 1);
    ft_bzero(buffer2, 4);
    ft_putstr_fd("Result 2: ", 1);
    ft_putstr_fd(buffer2 + 4, 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); 
	
	// ft_memcpy
    print_test_name("ft_memcpy");
	char src5[] = "HelloWorld";
	char dest5[11] = "----------";
	ft_memcpy(dest5, src5, 10);
	ft_putstr_fd("Result 1: ", 1);
	ft_putstr_fd(dest5, 1);
	ft_putchar_fd('\n', 1);

	char src6[] = "42";
	char dest6[5] = "0000";
	ft_memcpy(dest6, src6, 2);
	ft_putstr_fd("Result 2: ", 1);
	ft_putstr_fd(dest6, 1);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd('\n', 1);
	
	// ft_memmove
    print_test_name("ft_memmove");
	// Non-overlapping example
    char src7[] = "1234567890";
    char dest7[11] = "----------";
    ft_memmove(dest7, src7, 10);
    ft_putstr_fd("Result 1: ", 1);
    ft_putstr_fd(dest7, 1);
    ft_putchar_fd('\n', 1);
	// Overlapping example (dest starts *inside* src)
    char src8[] = "abcdefghij";
    ft_memmove(src8 + 2, src8, 8);
    ft_putstr_fd("Result 2: ", 1);
    ft_putstr_fd(src8, 1);
    ft_putchar_fd('\n', 1);
    // Overlap near the middle
    char src9[20] = "abcdefghijklmno";
    ft_memmove(src9 + 5, src9, 16);
    ft_putstr_fd("Result 2: ", 1);
    ft_putstr_fd(src9, 1);  
    ft_putchar_fd('\n', 1);  
    ft_putchar_fd('\n', 1);
	// Result 1: "1234567890" (simple copy)
	// Result 2: "ababcdefgh"
	// Result 3: "abcdeabcdefghij"
	
	// ft_memcmp
	print_test_name("ft_memcmp");

    char a1[] = "abcde";
    char a2[] = "abcde";
    ft_putnbr_fd(ft_memcmp(a1, a2, 5), 1);
    ft_putchar_fd('\n', 1);

    char b1[] = "abcde";
    char b2[] = "abzde";
    ft_putnbr_fd(ft_memcmp(b1, b2, 5), 1); // Should print negative
    ft_putchar_fd('\n', 1);

    char c1[] = "abzde";
    char c2[] = "abcde";
    ft_putnbr_fd(ft_memcmp(c1, c2, 5), 1); // Should print positive
    ft_putchar_fd('\n', 1);

    char d1[] = "abcdef";
    char d2[] = "abcdee";
    ft_putnbr_fd(ft_memcmp(d1, d2, 6), 1); // Should print positive
    ft_putchar_fd('\n', 1);

    ft_putchar_fd('\n', 1);
	// Output: 
	// 0 negative positive positive

	// ft_memchr
	print_test_name("ft_memchr");

	char test1[] = "HelloWorld42";
	void *result1 = ft_memchr(test1, 'W', 12);
	ft_putstr_fd("Result 1: ", 1);
	if (result1)
		ft_putstr_fd((char *)result1, 1);  // Should print "World42"
	else
		ft_putstr_fd("NULL", 1);
	ft_putchar_fd('\n', 1);

	char test2[] = "42Barcelona";
	void *result2 = ft_memchr(test2, 'z', 11);
	ft_putstr_fd("Result 2: ", 1);
	if (result2)
		ft_putstr_fd((char *)result2, 1);
	else
		ft_putstr_fd("NULL", 1);  // 'z' not found, should print "NULL"
	ft_putchar_fd('\n', 1);
	ft_putchar_fd('\n', 1);
	
	// Output:
	// "World42"
	// "NULL"
	
	// Functions with malloc
	ft_putstr_fd("Functions with malloc:\n", 1);
    ft_putstr_fd("-------------------\n", 1);
	ft_putchar_fd('\n', 1);

	// ft_calloc
	print_test_name("ft_calloc");
	// Test 1: Testing calloc with an array of 5 integers
    int *arr = (int *)ft_calloc(5, sizeof(int));
    if (arr)
    {
        ft_putnbr_fd(arr[0], 1); // Should print 0
        ft_putchar_fd(' ', 1);
        ft_putnbr_fd(arr[1], 1); // Should print 0
        ft_putchar_fd(' ', 1);
        ft_putnbr_fd(arr[2], 1); // Should print 0
        ft_putchar_fd(' ', 1);
        ft_putnbr_fd(arr[3], 1); // Should print 0
        ft_putchar_fd(' ', 1);
        ft_putnbr_fd(arr[4], 1); // Should print 0
        ft_putchar_fd(' ', 1);
    }
    ft_putchar_fd('\n', 1);
    free(arr);

    // Test 2: Testing calloc with a string of 10 characters
    char *str = (char *)ft_calloc(10, sizeof(char));
    if (str)
    {
        ft_putchar_fd(str[0] ? str[0] : '0', 1); // Should print '0'
        ft_putchar_fd(str[1] ? str[1] : '0', 1); // Should print '0'
        ft_putchar_fd(str[2] ? str[2] : '0', 1); // Should print '0'
        ft_putchar_fd(str[3] ? str[3] : '0', 1); // Should print '0'
        ft_putchar_fd(str[4] ? str[4] : '0', 1); // Should print '0'
        ft_putchar_fd(str[5] ? str[5] : '0', 1); // Should print '0'
        ft_putchar_fd(str[6] ? str[6] : '0', 1); // Should print '0'
        ft_putchar_fd(str[7] ? str[7] : '0', 1); // Should print '0'
        ft_putchar_fd(str[8] ? str[8] : '0', 1); // Should print '0'
        ft_putchar_fd(str[9] ? str[9] : '0', 1); // Should print '0'
    }
    ft_putchar_fd('\n', 1);
    free(str);

    // Test 3: Testing calloc with zero memory
    void *zero_alloc = ft_calloc(0, 10);  // Should return NULL
	if (zero_alloc == NULL)
	{
		ft_putstr_fd("NULL (Expected: NULL)\n", 1);  // This will print if zero_alloc is NULL
	}
	else
	{
		ft_putstr_fd("Not NULL (Something went wrong)\n", 1);  // In case something goes wrong
	}
	ft_putchar_fd('\n', 1);

	// ft_strdup
    print_test_name("ft_strdup");
    char *dup = ft_strdup("test");
    ft_putstr_fd(dup, 1);
    free(dup);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1);

	// Output: test
	

    // PART TWO
    ft_putstr_fd("Test Part 2:\n", 1);
    ft_putstr_fd("-------------------\n", 1);
	ft_putchar_fd('\n', 1);

    // ft_putchar_fd
    print_test_name("ft_putchar_fd");
    ft_putchar_fd('X', 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); 
	// Output: X

    // ft_putstr_fd
    print_test_name("ft_putstr_fd");
    ft_putstr_fd("Hello string", 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: Hello string

    // ft_putendl_fd
    print_test_name("ft_putendl_fd");
    ft_putendl_fd("Line with endl", 1);
    ft_putchar_fd('\n', 1); // Output: Line with endl\n

    // ft_putnbr_fd
    print_test_name("ft_putnbr_fd");
    ft_putnbr_fd(12345, 1);
    ft_putchar_fd(' ', 1);
    ft_putnbr_fd(-678, 1);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: 12345 -678

    // ft_substr
    print_test_name("ft_substr");
    char *sub1 = ft_substr("hello world School", 6, 5);
    ft_putstr_fd(sub1, 1);
    free(sub1);
    ft_putchar_fd(' ', 1);
    char *sub2 = ft_substr("hello world School", 12, 6);
    ft_putstr_fd(sub2, 1);
    free(sub2);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: world School

    // ft_strjoin
    print_test_name("ft_strjoin");
    char *joined = ft_strjoin("Hello, World! ", "42 Lib");
    ft_putstr_fd(joined, 1);
    free(joined);
    ft_putchar_fd('\n', 1);
    ft_putchar_fd('\n', 1); // Output: Hello, World! 42 Lib
	
	// ft_itoa
    print_test_name("ft_itoa");
    
    char *result3;

    result3 = ft_itoa(42);
    ft_putstr_fd(result3, 1);
    free(result3);
    ft_putchar_fd('\n', 1);

    result3 = ft_itoa(-42);
    ft_putstr_fd(result3, 1);
    free(result3);
    ft_putchar_fd('\n', 1);

    result3 = ft_itoa(0);
    ft_putstr_fd(result3, 1);
    free(result3);
    ft_putchar_fd('\n', 1);

	result3 = ft_itoa(-987654);
    ft_putstr_fd(result3, 1);
    free(result3);
    ft_putchar_fd('\n', 1);
	ft_putchar_fd('\n', 1);

	// ft_strmapi
	
	print_test_name("ft_strmapi");

	char *mapped = ft_strmapi("abcxyz", shift_index);
	ft_putstr_fd(mapped, 1);
	free(mapped);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd('\n', 1);
	// output : aceace
	
	// ft_striteri
	print_test_name("ft_striteri");

    char str3[] = "abcxyz";
    ft_striteri(str3, shift_index_iteri);
    ft_putstr_fd(str3, 1);
    ft_putchar_fd('\n', 1);

	// ft_strtrim

	print_test_name("ft_strtrim");
	char    *result4;

	result4 = ft_strtrim("   Hello World!   ", " ");
	ft_putstr_fd(result4, 1);
	free(result4);
	ft_putchar_fd('\n', 1);

	result4 = ft_strtrim("---42---", "-");
	ft_putstr_fd(result4, 1);
	free(result4);
	ft_putchar_fd('\n', 1);

	result4 = ft_strtrim("...trimmed...", ".");
	ft_putstr_fd(result4, 1);
	free(result4);
	ft_putchar_fd('\n', 1);

	result4 = ft_strtrim("no trimming here", "");
	ft_putstr_fd(result4, 1);
	free(result4);
	ft_putchar_fd('\n', 1);

	result4 = ft_strtrim("allcute", "aclotu");
	ft_putstr_fd(result4, 1);
	free(result4);
	ft_putchar_fd('\n', 1);

	// ft_split

	print_test_name("ft_split");
    char **result5;

    result5 = ft_split("Hello World 42", ' ');
    print_split_result(result5);
	ft_putchar_fd('\n', 1);

    result5 = ft_split(",,,split,,,this,,,", ',');
    print_split_result(result5);
	ft_putchar_fd('\n', 1);

    result5 = ft_split("oneword", ' ');
    print_split_result(result5);
	ft_putchar_fd('\n', 1);

    result5 = ft_split("", ' ');
    print_split_result(result5);
	ft_putchar_fd('\n', 1);

    result5 = ft_split("   ", ' ');
    print_split_result(result5);
	ft_putchar_fd('\n', 1);

    result5 = ft_split("split this string", 't');
    print_split_result(result5);
	ft_putchar_fd('\n', 1);

	// BONUS PART
    ft_putstr_fd("Test BONUS PART:\n", 1);
    ft_putstr_fd("-------------------\n", 1);
	ft_putchar_fd('\n', 1);
	
	// ft_lstnew & ft_lstclear & ft_lstadd_front & ft_lstadd_back
    print_test_name("ft_lst*.c");
	
	// Create  nodes using ft_lstnew
    t_list *head = ft_lstnew(ft_strdup("First node"));
    t_list *second = ft_lstnew(ft_strdup("Second node"));
	t_list *first = ft_lstnew(ft_strdup("First new node"));
	t_list *third = ft_lstnew(ft_strdup("To Be the Last node"));
	
	if (!head || !second || !first || !third) {
    ft_putstr_fd("Memory allocation failed\n", 2);
    return (1);
	}
	// Linking the nodes
    head->next = second;  // head points to second node
	ft_lstadd_front(&head, first);
	ft_lstadd_back(&head, third);
	
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Original list:\n", 1);
    print_list(head);
	// Now that list is ready, you can:
	t_list *last_node = ft_lstlast(head);
	int	size = ft_lstsize(head);
	ft_putstr_fd("Size: ", 1);
	ft_putnbr_fd(size, 1);
	ft_putchar_fd('\n', 1);

	// delete a single node
	// Find node before last_node
	t_list *prev = head;
	while (prev && prev->next != last_node)
		prev = prev->next;

	// Unlink it
	if (prev)
		prev->next = NULL;
	// Safely delete
	ft_lstdelone(last_node, free);
	
	ft_putchar_fd('\n', 1);
    ft_putstr_fd("List after delete last one:\n", 1);
    print_list(head);
	int size2 = ft_lstsize(head);
	ft_putstr_fd("Size: ", 1);
    ft_putnbr_fd(size2, 1);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd('\n', 1);

	// Traverse using ft_lstiter
    ft_putstr_fd("List content using ft_lstiter:\n", 1);
    ft_lstiter(head, print_content);
    ft_putchar_fd('\n', 1);

	// Traverse the list manually using a while loop
    ft_putstr_fd("List content using manual traversal:\n", 1);
    t_list *current = head;  // Start from head
    while (current != NULL) 
	{
		ft_putstr_fd((char *)current->content, 1); // Print the content of each node
		ft_putchar_fd('\n', 1);
        current = current->next;  // Move to the next node
    }
	
	ft_putchar_fd('\n', 1);
	// New list for ft_lstmap test
	ft_putstr_fd("List before ft_lstmap:\n", 1);
    print_list(head);
	
	// Create mapped list
    t_list *new_list = ft_lstmap(head, &to_uppercase, free);
    if (!new_list)
    {
        ft_putstr_fd("ft_lstmap failed.\n", 2);
        ft_lstclear(&head, free);
        return (1);
    }

    ft_putstr_fd("\nMapped list (uppercase):\n", 1);
    print_list(new_list);
    
	// Free all nodes using ft_lstclear
    ft_lstclear(&head, free);
    ft_lstclear(&new_list, free);
    ft_putchar_fd('\n', 1);

    return (0);
}
