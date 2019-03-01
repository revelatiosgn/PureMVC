#pragma once

#include "Mediator.h"
#include "Macro.h"

using namespace std;

class MyMediator : public Mediator
{
public:
	virtual void onRegister() override;

	SUBSCRIBE(NOTIF_777, NOTIF_123, NOTIF_333);
};