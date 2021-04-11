#pragma once
#include <iostream>

class HTTP {

public:

	std::string write_ok_message();

	std::string write_error_message();

protected:
	std::string receivedMsg;
	std::string toSendMsg;
	
};