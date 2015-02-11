//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
//  FluoRender -- new structure tests
//
// -- Object Tests
//
// Primary Author: Brig Bagley (brig@sci.utah.edu)
//
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//
//  Copyright (C) 2014, Brig Bagley
//  Scientific Computing & Imaging Institute
//
//  University of Utah
//  //
//  //  Permission is  hereby  granted, free  of charge, to any person
//  //  obtaining a copy of this software and associated documentation
//  //  files  ( the "Software" ),  to  deal in  the  Software without
//  //  restriction, including  without limitation the rights to  use,
//  //  copy, modify,  merge, publish, distribute, sublicense,  and/or
//  //  sell copies of the Software, and to permit persons to whom the
//  //  Software is  furnished  to do  so,  subject  to  the following
//  //  conditions:
//  //
//  //  The above  copyright notice  and  this permission notice shall
//  //  be included  in  all copies  or  substantial  portions  of the
//  //  Software.
//  //
//  //  THE SOFTWARE IS  PROVIDED  "AS IS",  WITHOUT  WARRANTY  OF ANY
//  //  KIND,  EXPRESS OR IMPLIED, INCLUDING  BUT NOT  LIMITED  TO THE
//  //  WARRANTIES   OF  MERCHANTABILITY,  FITNESS  FOR  A  PARTICULAR
//  //  PURPOSE AND NONINFRINGEMENT. IN NO EVENT  SHALL THE AUTHORS OR
//  //  COPYRIGHT HOLDERS  BE  LIABLE FOR  ANY CLAIM, DAMAGES OR OTHER
//  //  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  //  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
//  //  USE OR OTHER DEALINGS IN THE SOFTWARE.
//  //-------------------------------------------------------------------
//  //-------------------------------------------------------------------
#include "Object.h"
#include "gtest/gtest.h"
#include <vector>

// for leak test on Windows
//#ifdef WIN32
//#include <vld.h>
//#endif

using namespace std;

// Tests min/max Angles of regular tet
TEST(Object, Constructor) {
   //creating first object
   Object *obj1 = new Object();
   //declaring a list of objects
   vector<ref_ptr<Object>> obj_list;
   //add the first object to the list
   obj_list.push_back(obj1);
   ASSERT_EQ(1, obj_list.size());
   ASSERT_TRUE(obj_list[0]->isSameKindAs(obj1));
   ASSERT_STREQ("Object", obj_list[0]->className());
   unsigned int id = 10;
   obj_list[0]->setId(id);
   ASSERT_EQ(id, obj_list[0]->getId());

   bool bval = false;
   //adding a boolean value to the first object
   ASSERT_TRUE(obj_list[0]->addValue("bval", bval));
   bool bval2;
   ASSERT_TRUE(obj_list[0]->getValue("bval", bval2));
   ASSERT_EQ(bval, bval2);
   bval = true;
   //changing the boolean value to the first object
   ASSERT_TRUE(obj_list[0]->setValue("bval", bval));
   ASSERT_TRUE(obj_list[0]->getValue("bval", bval2));
   ASSERT_EQ(bval, bval2);

   //creating a second object by cloning the first one
   Object* obj2 = obj_list[0]->clone();
   //adding the second object to the list
   obj_list.push_back(obj2);
   ASSERT_EQ(2, obj_list.size());
   //confirming the values of the second object are the same as the first
   ASSERT_TRUE(obj_list[1]->getValue("bval", bval2));
   ASSERT_EQ(bval, bval2);

   //sync the boolean value
   ASSERT_TRUE(obj_list[0]->syncValue("bval", (obj_list[1]).get()));
   ASSERT_TRUE(obj_list[1]->syncValue("bval", (obj_list[0]).get()));
   bval = false;
   ASSERT_TRUE(obj_list[0]->setValue("bval", bval));
   ASSERT_TRUE(obj_list[1]->getValue("bval", bval2));
   ASSERT_EQ(bval, bval2);
   bval = true;
   ASSERT_TRUE(obj_list[1]->setValue("bval", bval));
   ASSERT_TRUE(obj_list[0]->getValue("bval", bval2));
   ASSERT_EQ(bval, bval2);

   //adding the first object as a value to the second
   ASSERT_TRUE(obj_list[1]->addValue("friend", obj_list[0].get()));
   Object* obj;
   //confirming the value has been added
   ASSERT_TRUE(obj_list[1]->getValue("friend", (Referenced**)&obj));
   ASSERT_EQ(obj1, obj);
   //erasing the first object
   obj_list.erase(obj_list.begin());
   //confirming the value pointing to the first object is reset
   ASSERT_TRUE(obj_list[0]->getValue("friend", (Referenced**)&obj));
   ASSERT_EQ(0, obj);
}
