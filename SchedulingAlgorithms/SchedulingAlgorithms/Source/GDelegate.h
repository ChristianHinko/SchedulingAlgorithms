// Green Team - Robert Squires, Christian Hinkle

#pragma once

template <class TReturnType, class... TParameterTypes>
class GDelegate;



template <class TReturnType, class... TParameterTypes>
bool operator==(const GDelegate<TReturnType, TParameterTypes...>& InDelegateA, const GDelegate<TReturnType, TParameterTypes...>& InDelegateB);


/**
 * Unicast delegate
 * 
 * Invoking member functions on objects are not supported.
 */
template <class TReturnType, class... TParameterTypes>
class GDelegate
{
	template <class TReturnType, class... TParameterTypes>
	friend bool operator==(const GDelegate<TReturnType, TParameterTypes...>&, const GDelegate<TReturnType, TParameterTypes...>&);
public:
	typedef TReturnType(*TFunctionPtrType)(TParameterTypes...);

	GDelegate();

	/** Create a delegate from a function. */
	static GDelegate CreateStatic(const TFunctionPtrType InFunction);

	/** Bind another delegate to us. */
	void Bind(const GDelegate InDelegate);
	/** Bind a function to us. */
	void BindStatic(const TFunctionPtrType InFunction);

	void Execute(TParameterTypes... InParameters) const;

	void Unbind();

protected:
	TFunctionPtrType Function;
};

template <class TReturnType, class ...TParameterTypes>
bool operator==(const GDelegate<TReturnType, TParameterTypes...>& InDelegateA, const GDelegate<TReturnType, TParameterTypes...>& InDelegateB)
{
	return (InDelegateA.Function == InDelegateB.Function);
}


template <class TReturnType, class... TParameterTypes>
GDelegate<TReturnType, TParameterTypes...>::GDelegate()
	: Function(nullptr)
{
}

template <class TReturnType, class... TParameterTypes>
GDelegate<TReturnType, TParameterTypes...> GDelegate<TReturnType, TParameterTypes...>::CreateStatic(const TFunctionPtrType InFunction)
{
	GDelegate Delegate = GDelegate();
	Delegate.Function = InFunction;
	return Delegate;
}

template <class TReturnType, class... TParameterTypes>
void GDelegate<TReturnType, TParameterTypes...>::Bind(const GDelegate InDelegate)
{
	Function = InDelegate.Function;
}

template <class TReturnType, class... TParameterTypes>
void GDelegate<TReturnType, TParameterTypes...>::BindStatic(const TFunctionPtrType InFunction)
{
	Bind(CreateStatic(InFunction));
}

template <class TReturnType, class... TParameterTypes>
void GDelegate<TReturnType, TParameterTypes...>::Execute(TParameterTypes... InParameters) const
{
	Function(InParameters...);
}

template <class TReturnType, class... TParameterTypes>
void GDelegate<TReturnType, TParameterTypes...>::Unbind()
{
	Function = nullptr;
}
