#include "StdTypes.h"
#include "Utils.h"
#include "Sec_Dia.h"



int main(void)
{
	
	SecDia_Init();
	while (1)
	{
		SecDia_Runnable();
	}
}

