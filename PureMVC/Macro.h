#pragma once

#include <functional>
#include <map>
#include <memory>
#include <vector>

using namespace std;

typedef int Notification;

#define facade Facade::getInstance()

#define REGISTER_NOTIFICATION(notification) Notification notification = __COUNTER__
#define SEND(name) extern Notification name; facade->send(name)

#define REG_COMMAND(notification, type) extern Notification notification; facade->registerCommand<type>(notification)

#define REG_MEDIATOR(type) facade->registerMediator<type>()
#define REG_MEDIATOR_NAMED(name, type) facade->registerMediator<type>(name)
#define RET_MEDIATOR(type) facade->retrieveMediator<type>()
#define REM_MEDIATOR(type) facade->removeMediator<type>()

#define REG_PROXY(type) facade->registerProxy<type>()
#define RET_PROXY(type) facade->retrieveProxy<type>()

//-----------------------------------------------------------

#define CB_FUNC function<void(void*)>

#define CAT(x,y) CAT_A(x, y)
#define CAT_A(x,y) x##y

#define VA_SIZE(...) INVOKE( VA_GET_SIZE VA_OB INVOKE(VA_SPEC##__VA_ARGS__()), 0, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 VA_CB )

#define VA_OB (
#define VA_CB )
#define VA_SPEC() 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
#define VA_GET_SIZE(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,n,...) n

#define INVOKE( ... ) INVOKE_A( __VA_ARGS__ )
#define INVOKE_A( ... ) __VA_ARGS__
#define VA_FOR(macro, ...) INVOKE( CAT(VA_FOR, VA_SIZE(__VA_ARGS__)) ( macro, (__VA_ARGS__) ) )

#define VA_APPLY(x) x
#define VA_FIRST(a, ...) a
#define VA_WO_FIRST(a, ...) __VA_ARGS__

#define SELF_TYPE &remove_reference<decltype(*this)>::type
#define CREATE_SPTR(callback) sptr = make_shared<CB_FUNC>(bind(SELF_TYPE::CAT(on_, callback), this, placeholders::_1))
#define SUBSCRIBE_CB(callback) facade->insertCallback(callback, sptr)
#define PUSH_CB(callback) extern Notification callback; CREATE_SPTR(callback); _callbacks.push_back(sptr); SUBSCRIBE_CB(callback)
#define CREATE_CB(callback) void CAT(on_, callback)(void* data = nullptr)

#define VA_FOR0(m, x)
#define VA_FOR1(m, x) m(VA_APPLY(VA_FIRST x));
#define VA_FOR2(m, x) m(VA_APPLY(VA_FIRST x)); VA_FOR1(m, (VA_APPLY(VA_WO_FIRST x)))
#define VA_FOR3(m, x) m(VA_APPLY(VA_FIRST x)); VA_FOR2(m, (VA_APPLY(VA_WO_FIRST x)))
#define VA_FOR4(m, x) m(VA_APPLY(VA_FIRST x)); VA_FOR3(m, (VA_APPLY(VA_WO_FIRST x)))
#define VA_FOR5(m, x) m(VA_APPLY(VA_FIRST x)); VA_FOR4(m, (VA_APPLY(VA_WO_FIRST x)))
#define VA_FOR6(m, x) m(VA_APPLY(VA_FIRST x)); VA_FOR5(m, (VA_APPLY(VA_WO_FIRST x)))
#define VA_FOR7(m, x) m(VA_APPLY(VA_FIRST x)); VA_FOR6(m, (VA_APPLY(VA_WO_FIRST x)))
#define VA_FOR8(m, x) m(VA_APPLY(VA_FIRST x)); VA_FOR7(m, (VA_APPLY(VA_WO_FIRST x)))
#define VA_FOR9(m, x) m(VA_APPLY(VA_FIRST x)); VA_FOR8(m, (VA_APPLY(VA_WO_FIRST x)))
#define VA_FOR10(m, x) m(VA_APPLY(VA_FIRST x)); VA_FOR9(m, (VA_APPLY(VA_WO_FIRST x)))

#define SUBSCRIBE(...) protected: \
virtual void subscribe() override \
{ \
	shared_ptr<CB_FUNC> sptr; \
	VA_FOR(PUSH_CB, __VA_ARGS__) \
} \
VA_FOR(CREATE_CB, __VA_ARGS__) \
template<typename T> friend shared_ptr<T> Facade::registerMediator<T>(); \
template<typename T> friend shared_ptr<T> Facade::registerMediator<T>(const string& name)
