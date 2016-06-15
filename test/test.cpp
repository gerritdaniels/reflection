/*
 * Copyright (C) 2016 by Gerrit Daniels <gerrit.daniels@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>

#include <reflection.hpp>

class SimpleClass {

   REFLECTION(SimpleClass,
      ((private, int, count))
      ((protected, std::string, name))
   )

   REFLECTED_SERIALIZATION()

   SimpleClass() {}

   virtual ~SimpleClass() {}

   SimpleClass(const int& count, const std::string& name) : count(count), name(name) {}
};

BOOST_CLASS_EXPORT(SimpleClass)

class SecondBaseClass {

   REFLECTION(SecondBaseClass,
      ((private, std::string, text))
   )

   REFLECTED_SERIALIZATION()

   SecondBaseClass() {}

   virtual ~SecondBaseClass() {}

   SecondBaseClass(const std::string& text) : text(text) {}
};

BOOST_CLASS_EXPORT(SecondBaseClass)

class DerivedClass : public SimpleClass, public SecondBaseClass {

   REFLECTION(DerivedClass,
      ((public, SimpleClass))
      ((public, SecondBaseClass))
      ((private, float, factor))
   )

   REFLECTED_SERIALIZATION()

   DerivedClass() {}

   DerivedClass(const int& count, const std::string& name, const std::string& text, const float& factor)
         : SimpleClass(count, name), SecondBaseClass(text), factor(factor) {}
};

BOOST_CLASS_EXPORT(DerivedClass)

class SecondDerivedClass : public SimpleClass {

   REFLECTION(SecondDerivedClass,
      ((public, SimpleClass))
      ((private, bool, flag))
   )

   REFLECTED_SERIALIZATION()

   SecondDerivedClass() {}

   SecondDerivedClass(const int& count, const std::string& name, const bool& flag)
         : SimpleClass(count, name), flag(flag) {}

};

BOOST_CLASS_EXPORT(SecondDerivedClass)

class Container {

   REFLECTION(Container,
      ((public, std::vector<std::shared_ptr<SimpleClass>>, objects))
   )

   REFLECTED_SERIALIZATION()

};

//******************************************************************************

int main() {

   Container container;

   container.objects.push_back(std::shared_ptr<SimpleClass>(new SimpleClass(1, "Gerrit")));
   container.objects.push_back(std::shared_ptr<SimpleClass>(new DerivedClass(2, "Paul", "Some text", 1.0)));
   container.objects.push_back(std::shared_ptr<SimpleClass>(new SecondDerivedClass(3, "Toon", true)));
   container.objects.push_back(container.objects[0]);

   boost::archive::xml_oarchive oa(std::cout);
   oa << BOOST_SERIALIZATION_NVP(container);
}
