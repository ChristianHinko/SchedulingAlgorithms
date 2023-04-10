// Green Team - Robert Squires, Christian Hinkle

#pragma once

#include <vector>


template <class TReturnType, class... TParameterTypes>
class GDelegate;



/**
 * Multicast delegate
 * 
 * Invoking member functions on objects are not supported.
 */
template <class... TParameterTypes>
class GMulticastDelegate
{
public:
	GMulticastDelegate();

	void Broadcast(TParameterTypes... InParameters) const;

	/** Add a delegate to the invocation list to be invoked when broadcasted. */
	void Add(const GDelegate<void, TParameterTypes...>& InDelegate);
	/** Add a function to the invocation list to be invoked when broadcasted. */
	void AddStatic(const typename GDelegate<void, TParameterTypes...>::TFunctionPtrType InFunction);

	/** Remove from the invocation list. */
	bool Remove(const GDelegate<void, TParameterTypes...>& InDelegate);
	/** Remove from the invocation list by function pointer. */
	bool RemoveStatic(const typename GDelegate<void, TParameterTypes...>::TFunctionPtrType InFunction);

protected:
	std::vector<GDelegate<void, TParameterTypes...>> InvocationList;
};


#include "GDelegate.h"
#include <algorithm>


template <class... TParameterTypes>
GMulticastDelegate<TParameterTypes...>::GMulticastDelegate()
{

}

template <class... TParameterTypes>
void GMulticastDelegate<TParameterTypes...>::Broadcast(TParameterTypes... InParameters) const
{
	for (const GDelegate<void, TParameterTypes...>& Delegate : InvocationList)
	{
		Delegate.Execute(InParameters...);
	}
}

template <class... TParameterTypes>
void GMulticastDelegate<TParameterTypes...>::Add(const GDelegate<void, TParameterTypes...>& InDelegate)
{
	InvocationList.push_back(InDelegate);
}

template <class... TParameterTypes>
void GMulticastDelegate<TParameterTypes...>::AddStatic(const typename GDelegate<void, TParameterTypes...>::TFunctionPtrType InFunction)
{
	Add(GDelegate<void, TParameterTypes...>(InFunction));
}

template <class... TParameterTypes>
bool GMulticastDelegate<TParameterTypes...>::Remove(const GDelegate<void, TParameterTypes...>& InDelegate)
{
	typename std::vector<GDelegate<void, TParameterTypes...>>::iterator FoundDelegate = std::find(InvocationList.begin(), InvocationList.end(), InDelegate);

	if (FoundDelegate != InvocationList.end())
	{
		InvocationList.erase(FoundDelegate);
		return true;
	}

	return false;
}

template <class... TParameterTypes>
bool GMulticastDelegate<TParameterTypes...>::RemoveStatic(const typename GDelegate<void, TParameterTypes...>::TFunctionPtrType InFunction)
{
	return Remove(GDelegate<void, TParameterTypes...>(InFunction));
}
