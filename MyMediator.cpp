#include "MyMediator.h"

void MyMediator::on_NOTIF_777(void* data)
{
	printf("MyMediator on_NOTIF_777!\n");
	SEND(NOTIF_123);
}

void MyMediator::on_NOTIF_123(void* data)
{
	printf("MyMediator on_NOTIF_123!\n");
}

void MyMediator::on_NOTIF_333(void* data)
{
	printf("MyMediator on_NOTIF_333!\n");
}

void MyMediator::onRegister()
{
	printf("onRegister\n");
}