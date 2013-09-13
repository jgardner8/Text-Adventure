#pragma once

//Used only to relate all MessageDispatcher<T> by inheritance so that 
//	subtype polymorphism can be used by MessageSystem.
//Remember, templates generate _unrelated_ classes.
class aMessageDispatcher {
public:
	virtual void DispatchAll() = 0;
	virtual void DiscardAll() = 0;
};