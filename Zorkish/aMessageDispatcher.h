#pragma once

//Used only to relate all MessageDispatcher<MsgType> by inheritance so that subtype polymorphism can be used
//  by MessageSystem. Any methods you want to be callable from MessageSystem must be declared here.
//Remember, templates generate _unrelated_ classes.
class aMessageDispatcher {
public:
	virtual void DispatchAll() = 0;
};