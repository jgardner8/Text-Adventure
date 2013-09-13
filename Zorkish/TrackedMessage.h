#pragma once

#include <list>
#include <algorithm>

template<class MsgType>
class aMessageHandler;

//Pairs a message together with the MessageHandlers that have read it. 
//This is used to ensure that a MessageHandler doesn't read the same message multiple 
//	times from a blackboard, and also to ensure messages are deleted from the blackboard.
template<class MsgType>
class TrackedMessage {
private:
	MsgType *_message;
	std::list<aMessageHandler<MsgType>*> _readers;

public:
	TrackedMessage(MsgType *message) {
		_message = message;
	}

	bool HasRead(aMessageHandler<MsgType> *handler) {
		return std::find_if(begin(_readers), end(_readers),
			[handler] (aMessageHandler<MsgType> *element) { return element == handler; });
	}

	MsgType* Read(aMessageHandler<MsgType> *handler) {
		if (HasRead(handler))
			return nullptr;
		_readers.push_back(handler);
		return _message;
	}

	const std::list<aMessageHandler<MsgType>*>& readers() { return _readers; }
};