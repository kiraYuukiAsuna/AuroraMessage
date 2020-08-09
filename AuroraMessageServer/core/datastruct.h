#pragma once

#include<atomic>
#include"../internet/internet.h"

struct Parameter {
	Network* ptr_net;
	std::atomic<bool>* state;
	Parameter() {
		ptr_net = nullptr;
		state = nullptr;
	}
};
