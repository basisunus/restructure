#include "Observer.h"

Observer::Observer()
{
}

Observer::~Observer()
{
}

ObserverSet::ObserverSet(const Referenced* observedObject):
	_observedObject(const_cast<Referenced*>(observedObject))
{
}

ObserverSet::~ObserverSet()
{
}

void ObserverSet::addObserver(Observer* observer)
{
	ObserverInfo obs_info;
	obs_info.observer = observer;
	obs_info.expression = "";
	_observers.push_back(obs_info);
}

void ObserverSet::removeObserver(Observer* observer)
{
	for (Observers::iterator itr = _observers.begin();
		itr != _observers.end(); ++itr)
	{
		if ((*itr).observer == observer)
			_observers.erase(itr);
	}
	//_observers.erase(observer);
}

Referenced* ObserverSet::addRefLock()
{
	if (!_observedObject) return 0;

	int refCount = _observedObject->ref();
	if (refCount == 1)
	{
		_observedObject->unref_nodelete();
		return 0;
	}

	return _observedObject;
}

void ObserverSet::signalObjectDeleted(void* ptr)
{
	for (Observers::iterator itr = _observers.begin();
		itr != _observers.end(); ++itr)
	{
		(*itr).observer->objectDeleted(ptr);
	}

	_observedObject = 0;
}

void ObserverSet::signalObjectChanged(void* ptr)
{
	for (Observers::iterator itr = _observers.begin();
		itr != _observers.end(); ++itr)
	{
		(*itr).observer->objectChanged(ptr, (*itr).expression);
	}
}