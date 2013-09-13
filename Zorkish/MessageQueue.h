#pragma once

#include <list>
#include "aMessageDispatcher.h"
#include "MessageDispatcher.h"

//MessageQueue is a singleton that provides the public interface used to queue and dispatch messages. 
//It stores a pointer to all of the aMessageDispatcher<MsgType> singleton objects (one per MsgType)
//	and simply forwards messages to the correct aMessageDispatcher.
class MessageQueue {
template<class MsgType> //there's only one MessageQueue; the template refers to the MessageDispatcher friend.
friend class MessageDispatcher; //gives access to RegisterDispatcher
private:
	std::list<aMessageDispatcher*> _dispatchers;

	//Singleton
	MessageQueue() { }
	MessageQueue(MessageQueue const&);
	void operator=(MessageQueue const&); 

	//Used by MessageDispatcher<MsgType> to notify the MessageQueue that a new
	//MessageDispatcher has been instantiated to dispatch messages of type MsgType. 
	void RegisterDispatcher(aMessageDispatcher *dispatcher) {
		_dispatchers.push_back(dispatcher);
	}

public:
	static MessageQueue& GetInstance() {
		static MessageQueue instance;
		return instance;
	}
	
	//Memory should be allocated for a queued message using new.
	template<class MsgType>
	void Queue(MsgType *message) {
		MessageDispatcher<MsgType>::GetInstance().Queue(message);
	}

	//Dispatch doesn't require memory to be allocated for the message.
	template<class MsgType>
	void Dispatch(MsgType *message) {
		MessageDispatcher<MsgType>::GetInstance().Dispatch(message);
	}

	void DispatchAll() {
		for (aMessageDispatcher *dispatcher : _dispatchers)
			dispatcher->DispatchAll();
	}

	void DiscardAll() {
		for (aMessageDispatcher *dispatcher : _dispatchers)
			dispatcher->DiscardAll();
	}
};