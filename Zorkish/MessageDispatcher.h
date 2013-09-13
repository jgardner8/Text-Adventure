#pragma once

#include <vector>
#include <algorithm>
#include "aMessageHandler.h"
#include "MessageSystem.h"
#include "aMessageDispatcher.h"

template<class MsgType>
class aMessageHandler;

//MessageDispatcher<MsgType> is a singleton that handles dispatching messages of 
//	type MsgType to all aMessageHandler<MsgType>
template<class MsgType>
class MessageDispatcher : public aMessageDispatcher {
private:
	std::vector<MsgType*> _messages;
	std::vector<aMessageHandler<MsgType>*> _handlers;

	//Singleton
	MessageDispatcher() {
		MessageSystem::GetInstance().RegisterDispatcher(this);
	}
	~MessageDispatcher() {
		DiscardAll();
	}
	MessageDispatcher(MessageDispatcher const&);
	void operator=(MessageDispatcher const&);

	void DiscardAll() {
		for (MsgType *message : _messages)
			delete message;
		_messages.clear();
	}

public:
	static MessageDispatcher<MsgType>& GetInstance() {
		static MessageDispatcher<MsgType> instance;
		return instance;
	}
	
	void Dispatch(MsgType *message) {
		for (aMessageHandler<MsgType> *handler : _handlers) {
			handler->Handle(message);
		}
	}

	void Enqueue(MsgType *message) {
		_messages.push_back(message);
	}

	virtual void DispatchAll() override {
		for (MsgType *message : _messages) {
			Dispatch(message);
		}
		DiscardAll();
	}

	void RegisterHandler(aMessageHandler<MsgType> *handler) {
		_handlers.push_back(handler);
	}

	void UnregisterHandler(aMessageHandler<MsgType> *handler) {
		std::remove_if(begin(_handlers), end(_handlers), 
			[handler] (aMessageHandler<MsgType> *element) { return handler == element; });
	}
};