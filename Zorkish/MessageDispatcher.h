#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include "MessageSystem.h"
#include "aMessageDispatcher.h"
#include "TrackedMessage.h"

template<class MsgType>
class aMessageHandler;

//MessageDispatcher<MsgType> is a singleton that handles dispatching messages of 
//	type MsgType to all aMessageHandler<MsgType>
template<class MsgType>
class MessageDispatcher : public aMessageDispatcher {
private:
	std::vector<MsgType*> _messages;
	std::list<TrackedMessage<MsgType>*> _blackboard;
	std::vector<aMessageHandler<MsgType>*> _handlers;

	//Singleton
	MessageDispatcher() {
		MessageSystem::GetInstance().RegisterDispatcher(this);
	}
	~MessageDispatcher() {
		DiscardAll();
		for (auto trackedMsg : _blackboard)
			delete trackedMsg;
		_blackboard.clear();
	}
	MessageDispatcher(MessageDispatcher const&);
	void operator=(MessageDispatcher const&);

	void DiscardAll() {
		for (MsgType *message : _messages)
			delete message;
		_messages.clear();
	}

	//Removes messages that have been read by all desired recipients.
	void PruneBoard() {
		std::vector<TrackedMessage<MsgType>*> toErase;

		for (auto trackedMsg : _blackboard) {
			if (trackedMsg->readers().size() == _handlers.size())
				toErase.push_back(trackedMsg);
		}

		for (auto trackedMsg : toErase) {
			_blackboard.erase( std::remove(begin(_blackboard), end(_blackboard), trackedMsg) , end(_blackboard));
			delete trackedMsg;
		}
	}

public:
	static MessageDispatcher<MsgType>& GetInstance() {
		static MessageDispatcher<MsgType> instance;
		return instance;
	}
	
	///Messages
	void Dispatch(MsgType *message) {
		for (auto *handler : _handlers) {
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
	///

	///Blackboard
	void Write(MsgType *message) {
		_blackboard.push_back(new TrackedMessage<MsgType>(message));
	}

	std::vector<MsgType*> Read(aMessageHandler<MsgType> *handler) {
		PruneBoard(); //this happens at the start so we don't delete any messages we're returning.
		std::vector<MsgType*> messages;
		for (auto trackedMsg : _blackboard) {
			if (MsgType *message = trackedMsg->Read(handler))
				messages.push_back(message);
		}
		return messages;
	}
	///

	void RegisterHandler(aMessageHandler<MsgType> *handler) {
		_handlers.push_back(handler);
	}

	void UnregisterHandler(aMessageHandler<MsgType> *handler) {
		_handlers.erase( std::remove(begin(_handlers), end(_handlers), handler), end(_handlers));
	}
};