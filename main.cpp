#include "Macro.h"
#include "Mediator.h"
#include "Facade.h"
#include "MyMediator.h"
#include "MyCommand.h"
#include "MyProxy.h"

#include <functional>
#include <map>
#include <conio.h>

using namespace std;

void test()
{
	printf("TEST\n");
}

int main()
{
	REG_COMMAND(MY_COMMAND, MyCommand);
	REG_MEDIATOR(MyMediator);

	SEND(NOTIF_777);
	SEND(NOTIF_123);

	SEND(MY_COMMAND);

	SEND(NOTIF_777);
	SEND(NOTIF_123);

	auto med = RET_MEDIATOR(MyMediator);

	REG_PROXY(MyProxy);
	auto proxy = RET_PROXY(MyProxy);
	proxy->doSomething();

	REG_MEDIATOR_NAMED("MED1", MyMediator);
	REG_MEDIATOR_NAMED("MED2", MyMediator);

	SEND(NOTIF_123);

	_getch();

    return 0;
}

