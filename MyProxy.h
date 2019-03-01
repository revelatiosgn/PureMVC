#pragma once

#include "Proxy.h"

class MyProxy : public Proxy
{
public:
	virtual void onRegister() override;
	virtual void onRemove() override;

	void doSomething();
};