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

#ifndef SERIALIZE_BASE_CLASSES_HPP_
#define SERIALIZE_BASE_CLASSES_HPP_

#include <boost/mpl/for_each.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>

namespace reflection {

   template <class ConcreteClass_, class Archive_>
   struct serialize_base_class {

      ConcreteClass_& containing;
      Archive_& archive;

      serialize_base_class(ConcreteClass_& containing, Archive_& archive) : containing(containing), archive(archive) {}

      template <class T_>
      void operator()(T_& x) {
         archive & boost::serialization::make_nvp(T_::type(), boost::serialization::base_object<typename T_::Type>(containing));
      };
   };

   template <class Vector_, class ConcreteClass_, class Archive_>
   void serialize_base_classes(ConcreteClass_& containing, Archive_& archive, const unsigned int version) {
      boost::mpl::for_each<Vector_>(serialize_base_class<ConcreteClass_, Archive_>(containing, archive));
   }

};


#endif // SERIALIZE_BASE_CLASSES_HPP_