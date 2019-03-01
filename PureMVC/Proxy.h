#pragma once

#include "Facade.h"

class Proxy
{
protected:
	virtual void onRegister() {}
	virtual void onRemove() {}
};