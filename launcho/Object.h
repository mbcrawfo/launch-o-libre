#pragma once

<<<<<<< HEAD
#include "types.h"
=======
#include "types.h"
#include <map>
#include <memory>

ObjectID INVALID_OBJECT_ID = 0;
class Object
{
private:
	ObjectID id;
	std::map<ComponentTypeID, StrongComponentPtr> components;


public:
	Object(ObjectID myID)
	{
		id = myID;
		
	}

	bool init()
	{
		return false;
	}

	void update(float deltaMS)
	{
	}

	void destroy()
	{

	}

	void addComponent(StrongComponentPtr component)
	{

	}

	template<typename ComponentType>
	std::weak_ptr<ComponentType> getComponent()
	{
		return std::weak_ptr<ComponentType>();
	}
};
>>>>>>> upstream/master
