#include "Facade.h"
#include "Mediator.h"
#include "Command.h"

Facade* Facade::_instance = nullptr;

Facade* Facade::getInstance()
{
	if (!_instance)
		_instance = new Facade;

	return _instance;
}

void Facade::send(Notification notification, void* data)
{
	_sendCount++;

	auto command = _commands.find(notification);
	if (command != _commands.end())
		command->second->execute(data);

	auto it = _callbacks.find(notification);
	while (it != _callbacks.end() && it->first == notification)
	{
		auto sptr = it->second.lock();
		if (sptr)
			(*sptr)(data);

		it++;
	}

	_sendCount--;

	if (_sendCount == 0)
	{
		auto it = _callbacks.begin();
		while (it != _callbacks.end())
		{
			if (it->second.expired())
				it = _callbacks.erase(it);
			else
				it++;
		}
	}
}

void Facade::insertCallback(Notification notification, shared_ptr<CB_FUNC> sptr)
{
	_callbacks.insert(make_pair(notification, sptr));
}
