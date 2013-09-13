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
	std::list<TrackedMessage<MsgType>> _blackboard;
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

	//Pruning the board currently uses an inefficient O(n^3) algorithm. It's a good thing it's not used much.
	void PruneBoard() {
		std::list<aMessageHandler<MsgType>*> readers;
		bool allRead = true;
		for (auto trackedMsg : _blackboard) {
			readers = trackedMsg.readers();
			for (auto handler : _handlers) {
				if (!std::find_if(begin(readers), end(readers), 
				[handler] (aMessageHandler<MsgType*> element) { return handler == element; })) {
					allRead = false;
					break;
				}
			}
			if (allRead) {
				std::remove_if(begin(_blackboard), end(_blackboard), 
					[trackedMsg] (element) { return trackedMsg == element; })
			}
			allRead = true;
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
		_blackboard.push_back(TrackedMessage<MsgType>(message));
	}

	std::vector<MsgType*> Read(aMessageHandler<MsgType> *handler) {
		std::vector<MsgType*> messages;
		for (auto trackedMsg : _blackboard)
			messages.push_back(trackedMsg.Read(handler));
		PruneBoard();
		return messages;
	}
	///

	void RegisterHandler(aMessageHandler<MsgType> *handler) {
		_handlers.push_back(handler);
	}

	void UnregisterHandler(aMessageHandler<MsgType> *handler) {
		std::remove_if(begin(_handlers), end(_handlers), 
			[handler] (aMessageHandler<MsgType> *element) { return handler == element; });
	}
};