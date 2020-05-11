#include "GetString.h"
#include "Definition.h"
#include "AddString.h"
#include "FilterFunction.h"
#include "Menu.h"
//µ÷Õû°æ±¾

int _main()
{
#ifdef UNICODE
	TPUTS(TEXT("UNICODE VERSION\n"), stdout);
#else
	TPUTS(TEXT("ASCII VERSION\n"), stdout);
#endif

	while (1)
	{
		DrawMenu();
		size_t uOption = Switch();
		SystemClsLoop();
		if (uOption == TCHARSIGN('9'))
		{
			break;
		}
	}
	system("pause");
}