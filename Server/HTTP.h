#pragma once
#include <iostream>

class HTTP {

public:

	void write_GET_message();
	void write_error_message();

	void elaborateMessage();

protected:
	std::string receivedMsg;
	std::string toSendMsg;
	
};