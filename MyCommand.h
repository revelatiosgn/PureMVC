#pragma once

#include "Command.h"

using namespace std;

class MyCommand : public Command
{
public:
	virtual void execute(void* data) override;
};