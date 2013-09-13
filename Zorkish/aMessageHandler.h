#pragma once

#include "MessageDispatcher.h"

//Inherit from the aMessageHandler<MsgType> class to declare yourself as a handler of messages of type MsgType. 
//Implement the Handle(MsgType *message) method to define an action to perform on receipt of a message.
template<class MsgType>
class aMessageHandler {
protected:
	//Automatically registers handler with corresponding dispatcher
	aMessageHandler() {
		MessageDispatcher<MsgType>::GetInstance().RegisterHandler(this);
	}

public:
	//Automatically unregisters the handler from the corresponding dispatcher
	virtual ~aMessageHandler() {
		MessageDispatcher<MsgType>::GetInstance().UnregisterHandler(this);
	}

	virtual void Handle(MsgType *message) = 0; 
};