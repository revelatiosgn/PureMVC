#pragma once

#include "Macro.h"

class Mediator;
class Command;
class Proxy;

class Facade
{
public:
	static Facade* getInstance();

	void insertCallback(Notification notification, shared_ptr<CB_FUNC> sptr);
	void send(Notification notification, void* data = nullptr);

	template<typename T>
	shared_ptr<T> registerMediator()
	{
		shared_ptr<T> mediator(new T);
		_mediators[typeid(T).name()] = mediator;
		mediator->subscribe();
		mediator->onRegister();

		return mediator;
	}

	template<typename T>
	shared_ptr<T> registerMediator(const string& name)
	{
		shared_ptr<T> mediator(new T);
		_mediators[name] = mediator;
		mediator->subscribe();
		mediator->onRegister();

		return mediator;
	}

	template<typename T>
	shared_ptr<T> retrieveMediator()
	{
		return static_pointer_cast<T>(_mediators[typeid(T).name()]);
	}

	template<typename T>
	void removeMediator()
	{
		auto mediator = _mediators.find(typeid(T).name());
		if (mediator != _mediators.end())
		{
			mediator->second->onRemove();
			_mediators.erase(mediator);
		}
	}

	template<typename T>
	void registerCommand(Notification notification)
	{
		_commands[notification] = shared_ptr<T>(new T);
	}

	template<typename T>
	shared_ptr<T> registerProxy()
	{
		shared_ptr<T> proxy(new T);
		_proxies[typeid(T).name()] = proxy;
		proxy->onRegister();

		return proxy;
	}

	template<typename T>
	shared_ptr<T> retrieveProxy()
	{
		return static_pointer_cast<T>(_proxies[typeid(T).name()]);
	}

	template<typename T>
	void removeProxy()
	{
		auto proxy = _proxies.find(typeid(T).name());
		if (proxy != _proxies.end())
		{
			proxy->second->onRemove();
			_proxies.erase(proxy);
		}
	}

private:
	static Facade* _instance;

	map<string, shared_ptr<Mediator>> _mediators;
	map<Notification, shared_ptr<Command>> _commands;
	map<string, shared_ptr<Proxy>> _proxies;

	multimap<Notification, weak_ptr<CB_FUNC>> _callbacks;

	int _sendCount = 0;
};