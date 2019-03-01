#pragma once

class Command
{
public:
	virtual void execute(void* data) = 0;
};