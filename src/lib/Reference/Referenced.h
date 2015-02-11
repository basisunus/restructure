#ifndef FL_REFERENCED
#define FL_REFERENCED 1

#include <string>

class Observer;
class ObserverSet;

class Referenced
{
public:

	Referenced();

	Referenced(const Referenced&);

	inline Referenced& operator = (const Referenced&) { return *this; }

	inline int ref() const;

	inline int unref() const;

	int unref_nodelete() const;

	inline int referenceCount() const { return _refCount; }

	ObserverSet* getObserverSet() const
	{
		return static_cast<ObserverSet*>(_observerSet);
	}

	ObserverSet* getOrCreateObserverSet() const;

	void addObserver(Observer* observer) const;

	void removeObserver(Observer* observer) const;

	virtual const char* className() const { return "Referenced";}

	const std::string& getRefStr() const { return _refStr; }

protected:

	virtual ~Referenced();

	void signalObserversAndDelete(bool signalDelete, bool doDelete) const;

	void notifyObserversOfChange() const;

	std::string _refStr;

	mutable int _refCount;

	mutable void* _observerSet;
};

inline int Referenced::ref() const
{
	return ++_refCount;
}

inline int Referenced::unref() const
{
	int newRef;
	newRef = --_refCount;
	bool needDelete = (newRef == 0);

	if (needDelete)
	{
		signalObserversAndDelete(true, true);
	}

	return newRef;
}

#endif