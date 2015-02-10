#define OBJ_XML \
"<Object>\n" \
"	<Value name=\"size\" type=\"unsigned long\" default=\"0\"/>\n" \
"	<Value name=\"display\" type=\"bool\" default=\"true\"/>\n" \
"	<Value name=\"threshold\" type=\"double\" default=\"0.0\"/>\n" \
"	<Value name=\"position\" type=\"Vec3d\" default=\"\"/>\n" \
"	<Value name=\"color\" type=\"Color3d\">\n" \
"		<v1 v=\"1.0\"/>\n" \
"		<v2 v=\"0.0\"/>\n" \
"		<v3 v=\"0.0\"/>\n" \
"	</Value>\n" \
"	<Value name=\"function\" type=\"ValueSet\">\n" \
"		<Value name=\"p1\" type=\"long\" default=\"1\"/>\n" \
"		<Value name=\"p2\" type=\"double\" default=\"\"/>\n" \
"	</Value>\n" \
"</Object>\n"

#include "Reference/Object.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class TestClass
{
public:
	TestClass() {}
	~TestClass() {}

	vector<ref_ptr<Object> > _obj_list;
};

int main (void)
{
/*	tinyxml2::XMLError err;
	tinyxml2::XMLDocument doc;
	ostringstream os;
	os << OBJ_XML;
	string str_xml = os.str();
	err = doc.Parse(str_xml.c_str(), str_xml.length());
	if (err == 0)
	{
		Object* temp_obj1 = new Object();
		ref_ptr<Object> obj1 = temp_obj1;
		obj1->buildFromXml(doc);
	}
*/
	TestClass* tc = new TestClass();

	Object* temp_obj1 = new Object();
	temp_obj1->addValue("display", bool(true));
	temp_obj1->addValue("size", (unsigned long)(0));
	temp_obj1->addValue("threshold", double(0.0));
	temp_obj1->addValue("position", Vec3d());
	temp_obj1->addValue("color", Color3d(1.0, 0.0, 0.0));
	tc->_obj_list.push_back(temp_obj1);

	temp_obj1->setValue("size", (unsigned long)(20));

	Object* temp_obj2 = temp_obj1->clone();
	temp_obj2->addValue("friend", temp_obj1);
	tc->_obj_list.push_back(temp_obj2);

	delete tc;

	return 0;
}
