#pragma once

#include "Macro.h"
#include "Facade.h"

class Mediator
{
public:
	virtual void onRegister() {}
	virtual void onRemove() {}

protected:
	vector<shared_ptr<CB_FUNC>> _callbacks;

	virtual void subscribe() {}

	template<typename T> friend shared_ptr<T> Facade::registerMediator<T>();
	template<typename T> friend shared_ptr<T> Facade::registerMediator<T>(const string& name);
};