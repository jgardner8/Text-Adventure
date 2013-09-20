#pragma once

//Used only to relate all MessageDispatcher<MsgType> by inheritance so that subtype polymorphism can be used
//  by MessageSystem. Any methods you want to be callable from MessageSystem must be declared here.
//Remember, templates generate _unrelated_ classes.
//
//At the moment this class is only used by MessageSystem.DispatchAll(), so the system could be simplified greatly
//  if that method is removed. See the comments on that method as to why it's been retained. 
class aMessageDispatcher {
public:
	virtual void DispatchAll() = 0;
};