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
	//Memory should be allocated for your message using new. 
	//This class takes ownership and responsibility for deletion.
	TrackedMessage(MsgType *message) {
		_message = message;
	}

	~TrackedMessage() {
		delete _message;
	}

	//TODO: change all of find_ifs to finds
	bool HasRead(aMessageHandler<MsgType> *handler) {
		return std::find(begin(_readers), end(_readers), handler) != end(_readers);
	}

	//If you're a handler, providing a pointer to yourself will stop you receiving the
	//	same messages twice. A nullptr allows anonymous usage of the blackboard.
	MsgType* Read(aMessageHandler<MsgType> *handler) {
		if (handler) {
			if (HasRead(handler))
				return nullptr;
			_readers.push_back(handler);
		}
		return _message;
	}

	const std::list<aMessageHandler<MsgType>*>& readers() { return _readers; }
};