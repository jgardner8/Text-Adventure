#pragma once

#include <vector>
#include "aMessageDispatcher.h"
#include "MessageDispatcher.h"

template<class MsgType>
class aMessageHandler;

//MessageSystem is a singleton that provides the public interface used to queue and dispatch messages. 
//It stores a pointer to all of the aMessageDispatcher<MsgType> singleton objects (one per MsgType)
//	and simply forwards messages to the correct aMessageDispatcher.
class MessageSystem {
template<class MsgType> //there's only one MessageSystem; the template refers to the MessageDispatcher friend.
friend class MessageDispatcher; //gives access to RegisterDispatcher
private:
	std::vector<aMessageDispatcher*> _dispatchers;

	//Singleton
	MessageSystem() { }
	MessageSystem(MessageSystem const&);
	void operator=(MessageSystem const&); 

	//Used by MessageDispatcher<MsgType> to notify the MessageSystem that a new
	//MessageDispatcher has been instantiated to dispatch messages of type MsgType. 
	void RegisterDispatcher(aMessageDispatcher *dispatcher) {
		_dispatchers.push_back(dispatcher);
	}

public:
	static MessageSystem& GetInstance() {
		static MessageSystem instance;
		return instance;
	}
	
	//Immediately dispatch a message.
	//Dispatch doesn't require memory to be allocated for the message.
	template<class MsgType>
	void Dispatch(MsgType *message) {
		MessageDispatcher<MsgType>::GetInstance().Dispatch(message);
	}

	//Add a message to the message queue, to be dispatched on next DispatchAll() call.
	//Memory should be allocated for a queued message using new. 
	//This class takes ownership and responsibility for deletion.
	template<class MsgType>
	void Enqueue(MsgType *message) {
		MessageDispatcher<MsgType>::GetInstance().Enqueue(message);
	}

	//Dispatch all messages in queue to recipients. 
	void DispatchAll() {
		for (aMessageDispatcher *dispatcher : _dispatchers)
			dispatcher->DispatchAll();
	}

	//Write a message onto the blackboard.
	//Memory should be allocated for your message using new. 
	//This class takes ownership and responsibility for deletion.
	template<class MsgType>
	void Write(MsgType *message) {
		MessageDispatcher<MsgType>::GetInstance().Write(message);
	}

	//Get all messages concerning you from the blackboard.
	//Once they've been read you won't be able to read them again!
	//Providing a nullptr allows anonymous usage of the blackboard; be careful not to keep reading the same messages.
	template<class MsgType>
	std::vector<MsgType*> Read(aMessageHandler<MsgType> *handler=nullptr) {
		return MessageDispatcher<MsgType>::GetInstance().Read(handler);
	}
};