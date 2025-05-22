#include <stdio.h>
#include <stdlib.h>
#define USIZE size_t

char *
die(void) {
	perror("numlns");
	return NULL;
}

char *
append(char *str, USIZE *str_size, USIZE *str_alloc, char c) {
	str[(*str_size)++] = c;
	if (*str_size >= *str_alloc) {
		*str_alloc *= 2;
		str = realloc(str, *str_alloc);
		if (!str) return die();
	}
	return str;
}

char *
getln(FILE *f) {
	int c;
	char *str;
	USIZE str_size, str_alloc;
	str = malloc((str_alloc = 256));
	if (!str) return die();
	str_size = 0;
	while ((c = getc(f)) != EOF || (!feof(f) && !ferror(f))) {
		append(str, &str_size, &str_alloc, c);
		if (c == '\n') return append(str, &str_size, &str_alloc, '\0');
	}
	return NULL;
}

int main(void) {
	char *str;
	USIZE line = 0;
	while ((str = getln(stdin))) {
		printf("%lld\t%s", ++line, str);	
		free(str);
	}
	return 0;
}
