#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."


int main(int argc, char *argv[]) {
	int i;
	char *dir;
	int a = 0;
	int b = 100;
	dir = dirname(realpath(argv[0], NULL));
	setlocale (LC_ALL, "");
	bindtextdomain ("guess", LOCALE_PATH);
	textdomain ("guess");
	const char *yes = _("yes");
	const char *no = _("no");
	printf(_("The game has begun\n"));
	printf(_("Use only `%s` and `%s` for answer\n"), yes, no);
	while (a != b) {
		int middle = (b - a) / 2 + a;
		char answer[80];
		printf(_("Number more than %d?\n>"), middle);
		scanf("%s", answer);

		if (!strcmp(answer, yes)) {
			a = middle + 1;
		} else if (!strcmp(answer, no)) {
			b = middle;
		}
		else {
			printf(_("Incorrect input\n"));
			printf(_("Use only `%s` and `%s` for answer\n"), yes, no);
		}
	}
	printf(_("Your number is %d\n"), a);
	return 0;
}
