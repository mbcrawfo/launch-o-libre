#pragma once
#include "types.h"

class IComponent {
protected:
	StrongObjectPtr parent;
public:
	virtual ~IComponent() = default;
	virtual void initialize() = 0;
	virtual void update(const float deltaMs){}
	virtual void destroy(){}
};
