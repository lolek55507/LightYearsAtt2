#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
	Object::Object()
		: mIsPendingDestory{false}
	{
	}
	Object::~Object()
	{
		// LOG("object Destroyed");
	}
	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		mIsPendingDestory = true;

	}
	weak<Object> Object::GetWeakRef() 
	{
		return weak_from_this();
	}
	weak<const Object> Object::GetWeakRef() const
	{
		return weak_from_this();
	}
}