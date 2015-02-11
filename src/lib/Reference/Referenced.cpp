#include "Referenced.h"
#include "Observer.h"

Referenced::Referenced():
  _observerSet(0),
  _refCount(0),
  _refStr("")
{
}

Referenced::Referenced(const Referenced&):
  _observerSet(0),
  _refCount(0),
  _refStr("")
{
}

Referenced::~Referenced()
{
	signalObserversAndDelete(true, false);

	if (_observerSet)
		static_cast<ObserverSet*>(_observerSet)->unref();
}

ObserverSet* Referenced::getOrCreateObserverSet() const
{
	if (!_observerSet)
	{
		_observerSet = new ObserverSet(this);
		static_cast<ObserverSet*>(_observerSet)->ref();
	}
	return static_cast<ObserverSet*>(_observerSet);
}

void Referenced::addObserver(Observer* observer) const
{
	getOrCreateObserverSet()->addObserver(observer);
	observer->_observees.push_back(const_cast<Referenced*>(this));
}

void Referenced::removeObserver(Observer* observer) const
{
	getOrCreateObserverSet()->removeObserver(observer);
}

void Referenced::signalObserversAndDelete(bool signalDelete, bool doDelete) const
{
	ObserverSet* observerSet = static_cast<ObserverSet*>(_observerSet);

	if (observerSet && signalDelete)
	{
		observerSet->signalObjectDeleted(const_cast<Referenced*>(this));
	}

	if (doDelete)
	{
		delete this;
	}
}

void Referenced::notifyObserversOfChange() const
{
	ObserverSet* observerSet = static_cast<ObserverSet*>(_observerSet);

	if (observerSet)
	{
		observerSet->signalObjectChanged(const_cast<Referenced*>(this));
	}

}

int Referenced::unref_nodelete() const
{
	return --_refCount;
}