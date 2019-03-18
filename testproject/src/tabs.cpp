/*
 * Some people (And IDEs) like tab characters.
 */

#include <stdio.h>

int tabbedfunc()
{
	int i;
	for (i = 0; i < 10; i++)
	{
		printf("Tabs are\tcool!\n");
	}
	return 0;
}

