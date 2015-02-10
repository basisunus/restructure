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
#ifdef WIN32
#include <vld.h>
#endif

using namespace std;

// Tests min/max Angles of regular tet
TEST(Object, Constructor) {
   Object *obj1 = new Object();
   vector<ref_ptr<Object>> obj_list;
   obj_list.push_back(obj1);
   ASSERT_EQ(1, obj_list.size());
   ASSERT_TRUE(obj_list[0]->isSameKindAs(obj1));
   ASSERT_STREQ("Object", obj_list[0]->className());
   unsigned int id = 10;
   obj_list[0]->setId(id);
   ASSERT_EQ(id, obj_list[0]->getId());

   bool bval = false;
   ASSERT_TRUE(obj_list[0]->addValue("bval", bval));
   bool bval2;
   ASSERT_TRUE(obj_list[0]->getValue("bval", bval2));
   ASSERT_EQ(bval, bval2);
   bval = true;
   ASSERT_TRUE(obj_list[0]->setValue("bval", bval));
   ASSERT_TRUE(obj_list[0]->getValue("bval", bval2));
   ASSERT_EQ(bval, bval2);

   Object* obj2 = obj_list[0]->clone();
   obj_list.push_back(obj2);
   ASSERT_EQ(2, obj_list.size());
   ASSERT_TRUE(obj_list[1]->getValue("bval", bval2));
   ASSERT_EQ(bval, bval2);
   ASSERT_TRUE(obj_list[1]->addValue("friend", obj_list[0].get()));
   Object* obj;
   ASSERT_TRUE(obj_list[1]->getValue("friend", (Referenced**)&obj));
   ASSERT_EQ(obj1, obj);
   obj_list.erase(obj_list.begin());
   ASSERT_TRUE(obj_list[0]->getValue("friend", (Referenced**)&obj));
   ASSERT_EQ(0, obj);
}
