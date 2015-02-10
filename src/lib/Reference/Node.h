#ifndef FL_NODE
#define FL_NODE 1

#include "Object.h"

#include <vector>

class Node;
class NodeVisitor;

typedef std::vector<Node*> ParentList;

typedef std::vector<ref_ptr<Node> > NodeList;

class Node : public Object
{
public:

	Node();

	Node(const Node&);

	virtual Object* clone() const { return new Node(*this); }

	virtual bool isSameKindAs(const Object* obj) const { return dynamic_cast<const Node*>(obj)!=NULL; }

	virtual const char* className() const { return "Node"; }

	virtual void accept(NodeVisitor& nv);
	virtual void traverse(NodeVisitor& nv);

	/* parents
	*/
	inline const ParentList& getParents() const { return _parents; }

	inline ParentList getParents() { return _parents; }

	inline const Node* getParent(unsigned int i) const { return _parents[i]; }

	inline Node* getParent(unsigned int i) { return _parents[i]; }

	inline unsigned int getNumParents() const { return static_cast<unsigned int>(_parents.size()); }

	/* children
	*/
	virtual bool addChild(Node* child);

	virtual bool insertChild(unsigned int index, Node* child);

	inline bool removeChild(Node* child)
	{
		unsigned int pos = getChildIndex(child);
		if (pos < _children.size()) return removeChildren(pos, 1);
		else return false;
	}

	inline bool removeChild(unsigned int pos)
	{
		if (pos < _children.size()) return removeChildren(pos, 1);
		else return false;
	}

	virtual bool removeChildren(unsigned int pos, unsigned int numChildrenToRemove);

	virtual bool replaceChild(Node *origChild, Node* newChild);

	inline unsigned int getNumChildren() const { return static_cast<unsigned int>(_children.size()); }

	virtual bool setChild(unsigned int i, Node* node);

	inline Node* getChild(unsigned int i) { return _children[i].get(); }

	inline const Node* getChild(unsigned int i) const {return _children[i].get(); }

	inline bool containsNode(const Node* node) const
	{
		for (NodeList::const_iterator itr=_children.begin();
			itr!=_children.end(); ++itr)
		{
			if (itr->get()==node) return true;
		}
		return false;
	}

	inline unsigned int getChildIndex(const Node* node) const
	{
		for (unsigned int childNum=0; childNum<_children.size(); ++childNum)
		{
			if (_children[childNum]==node) return childNum;
		}
		return static_cast<unsigned int>(_children.size());
	}

protected:

	virtual ~Node();

	void addParent(Node* node);
	void removeParent(Node* ndoe);

	//virtual void childRemoved(unsigned int, unsigned int);
	//virtual void childInserted(unsigned int);

	ParentList _parents;

	NodeList _children;
};

#endif
