#include "Node.h"
#include "NodeVisitor.h"

Node::Node()
	:Object()
{
}

Node::Node(const Node& node, bool ref_copy)
	:Object(node)
{
	for (NodeList::const_iterator it=node._children.begin();
		it!=node._children.end(); ++it)
	{
		Node* child = 0;
		if (ref_copy)
			child = (*it).get();
		else
			child = dynamic_cast<Node*>((*it)->clone());

		if (child)
			addChild(child);
	}
}

Node::~Node()
{
	for (NodeList::const_iterator it=_children.begin();
		it!=_children.end(); ++it)
	{
		(*it)->removeParent(this);
	}
}

void Node::accept(NodeVisitor& nv)
{
	nv.apply(*this);
}

void Node::traverse(NodeVisitor& nv)
{
	for (NodeList::iterator itr = _children.begin();
		itr != _children.end(); ++itr)
	{
		(*itr)->accept(nv);
	}
}

bool Node::addChild(Node* child)
{
	return insertChild(_children.size(), child);
}

bool Node::insertChild(unsigned int index, Node* child)
{
	if (!child)
		return false;
	else
	{
		if (index >= _children.size())
			_children.push_back(child);
		else
			_children.insert(_children.begin()+index, child);

		child->addParent(this);
		return true;
	}
}

bool Node::removeChildren(unsigned int pos, unsigned int numChildrenToRemove)
{
	if (pos < _children.size() && numChildrenToRemove > 0)
	{
		unsigned int endOfRemoveRange = pos + numChildrenToRemove;
		if (endOfRemoveRange > _children.size())
			endOfRemoveRange = _children.size();

		for (unsigned int i=pos; i<endOfRemoveRange; ++i)
		{
			_children[i]->removeParent(this);
		}

		_children.erase(_children.begin()+pos, _children.begin()+endOfRemoveRange);

		return true;
	}
	else return false;
}

bool Node::replaceChild(Node *origChild, Node* newChild)
{
	if (origChild==NULL || origChild==newChild)
		return false;

	unsigned int pos = getChildIndex(origChild);
	if (pos<_children.size())
	{
		return setChild(pos, newChild);
	}
	return false;
}

bool Node::setChild(unsigned int i, Node* newChild)
{
	if (i<_children.size() && newChild)
	{
		ref_ptr<Node> origNode = _children[i];

		origNode->removeParent(this);

		_children[i] = newChild;

		newChild->addParent(this);

		return true;
	}
	else return false;
}