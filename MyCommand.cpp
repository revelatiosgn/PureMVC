#include "MyCommand.h"
#include "Macro.h"
#include "Facade.h"

void MyCommand::execute(void* data)
{
	printf("MyCommand EXEC\n");

	SEND(NOTIF_333);
}