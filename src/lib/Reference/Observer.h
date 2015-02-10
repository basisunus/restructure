#ifndef FL_OBSERVER
#define FL_OBSERVER 1

#include "Referenced.h"
#include <vector>
#include <string>

class Observer
{
public:
	Observer();
	virtual ~Observer();

	virtual void objectDeleted(void*) {}
	virtual void objectChanged(void*, const std::string &exp) {}
};

struct ObserverInfo 
{
	Observer* observer;
	std::string expression;
};

class ObserverSet : public Referenced
{
public:

	ObserverSet(const Referenced* observedObject);

	Referenced* getObservedObject() { return _observedObject; }
	const Referenced* getObservedObject() const { return _observedObject; }

	Referenced* addRefLock();

	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

	void signalObjectDeleted(void* ptr);
	void signalObjectChanged(void* ptr);

	typedef std::vector<ObserverInfo> Observers;
	Observers& getObservers() { return _observers; }
	const Observers& getObservers() const { return _observers; }

	virtual const char* className() const { return "ObserverSet"; }

protected:

	ObserverSet(const ObserverSet& rhs): Referenced(rhs) {}
	ObserverSet& operator = (const ObserverSet&) {return *this; }
	virtual ~ObserverSet();

	Referenced* _observedObject;
	Observers _observers;
};

#endif