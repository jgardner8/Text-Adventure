#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include "aMessageHandler.h"
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

	//Pruning the board currently uses an inefficient O(n^3) algorithm. It's a good thing it's not used much.
	void PruneBoard() {
		std::list<aMessageHandler<MsgType>*> readers;
		std::list<TrackedMessage<MsgType>*> toErase;
		bool allRead = true;
		for (auto trackedMsg : _blackboard) {
			readers = trackedMsg->readers();
			for (auto handler : _handlers) {
				if (std::find(begin(readers), end(readers), handler) == end(readers)) {
					allRead = false;
					break;
				}
			}
			if (allRead) {
				toErase.push_back(trackedMsg);
			}
			allRead = true;
		}

		for (auto trackedMsg : toErase) {
			delete trackedMsg;
			_blackboard.erase( std::remove(begin(_blackboard), end(_blackboard), trackedMsg) , end(_blackboard));
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