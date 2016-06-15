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

#ifndef REFLECTION_HPP_
#define REFLECTION_HPP_

#include <typeinfo>

#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/pop_front.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/mpl/bool.hpp>

#include <create_reflection_info.hpp>
#include <serialize_base_classes.hpp>
#include <serialize_members.hpp>

#define BOOST_PP_VARIADICS 1

#define CREATE_BASE_CLASS(index_, ConcreteClass, BaseClassTuple_) \
public: \
   template <class Dummy_> \
   struct base_class_reflection_info<index_, Dummy_> { \
      typedef boost::mpl::true_ present; \
      typedef BOOST_PP_TUPLE_ELEM(1, BaseClassTuple_) Type; \
      static const char* type() { return typeid(BOOST_PP_TUPLE_ELEM(1, BaseClassTuple_)).name(); }\
      static constexpr const char* access = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, MemberTuple_)); \
   }; \


#define CREATE_MEMBER(index_, ConcreteClass_, MemberTuple_) \
BOOST_PP_TUPLE_ELEM(0, MemberTuple_): \
   BOOST_PP_TUPLE_ELEM(1, MemberTuple_) BOOST_PP_TUPLE_ELEM(2, MemberTuple_); \
public: \
   static BOOST_PP_TUPLE_ELEM(1, MemberTuple_) ConcreteClass_::* get_member_ptr(reflection::Int2Type<index_>) { \
      return &ConcreteClass_::BOOST_PP_TUPLE_ELEM(2, MemberTuple_); \
   } \
   template <class Dummy_> \
   struct member_reflection_info<index_, Dummy_> { \
      typedef boost::mpl::true_ present; \
      typedef BOOST_PP_TUPLE_ELEM(1, MemberTuple_) Type; \
      static const char* type() { return typeid(BOOST_PP_TUPLE_ELEM(1, MemberTuple_)).name(); }\
      static constexpr const char* access = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, MemberTuple_)); \
      static constexpr const char* name = BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(2, MemberTuple_)); \
      static Type& get(ConcreteClass_& containing) { \
         return containing.* ConcreteClass_::get_member_ptr(reflection::Int2Type<index_>()); \
      } \
      static const Type& get(const ConcreteClass_& containing) { \
         return containing.* ConcreteClass_::get_member_ptr(reflection::Int2Type<index_>()); \
      } \
   }; \


#define CREATE_MEMBER_2 CREATE_BASE_CLASS


#define CREATE_MEMBER_3 CREATE_MEMBER


#define CREATE_MEMBER_OR_BASE_CLASS(index_, ConcreteClass, Member_) \
   BOOST_PP_CAT(CREATE_MEMBER_, BOOST_PP_TUPLE_SIZE(Member_))(index_, ConcreteClass, Member_) \


#define CREATE_MEMBERS_0(ConcreteClass_, Members_) \


#define CREATE_MEMBERS_1(ConcreteClass_, Members_) \
   CREATE_MEMBER_OR_BASE_CLASS(0, ConcreteClass_, BOOST_PP_SEQ_ELEM(0, Members_)) \


#define CREATE_MEMBERS_2(ConcreteClass_, Members_) \
   CREATE_MEMBER_OR_BASE_CLASS(0, ConcreteClass_, BOOST_PP_SEQ_ELEM(0, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(1, ConcreteClass_, BOOST_PP_SEQ_ELEM(1, Members_)) \


#define CREATE_MEMBERS_3(ConcreteClass_, Members_) \
   CREATE_MEMBER_OR_BASE_CLASS(0, ConcreteClass_, BOOST_PP_SEQ_ELEM(0, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(1, ConcreteClass_, BOOST_PP_SEQ_ELEM(1, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(2, ConcreteClass_, BOOST_PP_SEQ_ELEM(2, Members_)) \


#define CREATE_MEMBERS_4(ConcreteClass_, Members_) \
   CREATE_MEMBER_OR_BASE_CLASS(0, ConcreteClass_, BOOST_PP_SEQ_ELEM(0, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(1, ConcreteClass_, BOOST_PP_SEQ_ELEM(1, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(2, ConcreteClass_, BOOST_PP_SEQ_ELEM(2, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(3, ConcreteClass_, BOOST_PP_SEQ_ELEM(3, Members_)) \


#define CREATE_MEMBERS_5(ConcreteClass_, Members_) \
   CREATE_MEMBER_OR_BASE_CLASS(0, ConcreteClass_, BOOST_PP_SEQ_ELEM(0, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(1, ConcreteClass_, BOOST_PP_SEQ_ELEM(1, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(2, ConcreteClass_, BOOST_PP_SEQ_ELEM(2, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(3, ConcreteClass_, BOOST_PP_SEQ_ELEM(3, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(4, ConcreteClass_, BOOST_PP_SEQ_ELEM(4, Members_)) \


#define CREATE_MEMBERS_6(ConcreteClass_, Members_) \
   CREATE_MEMBER_OR_BASE_CLASS(0, ConcreteClass_, BOOST_PP_SEQ_ELEM(0, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(1, ConcreteClass_, BOOST_PP_SEQ_ELEM(1, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(2, ConcreteClass_, BOOST_PP_SEQ_ELEM(2, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(3, ConcreteClass_, BOOST_PP_SEQ_ELEM(3, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(4, ConcreteClass_, BOOST_PP_SEQ_ELEM(4, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(5, ConcreteClass_, BOOST_PP_SEQ_ELEM(5, Members_)) \


#define CREATE_MEMBERS_7(ConcreteClass_, Members_) \
   CREATE_MEMBER_OR_BASE_CLASS(0, ConcreteClass_, BOOST_PP_SEQ_ELEM(0, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(1, ConcreteClass_, BOOST_PP_SEQ_ELEM(1, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(2, ConcreteClass_, BOOST_PP_SEQ_ELEM(2, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(3, ConcreteClass_, BOOST_PP_SEQ_ELEM(3, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(4, ConcreteClass_, BOOST_PP_SEQ_ELEM(4, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(5, ConcreteClass_, BOOST_PP_SEQ_ELEM(5, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(6, ConcreteClass_, BOOST_PP_SEQ_ELEM(6, Members_)) \


#define CREATE_MEMBERS_8(ConcreteClass_, Members_) \
   CREATE_MEMBER_OR_BASE_CLASS(0, ConcreteClass_, BOOST_PP_SEQ_ELEM(0, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(1, ConcreteClass_, BOOST_PP_SEQ_ELEM(1, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(2, ConcreteClass_, BOOST_PP_SEQ_ELEM(2, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(3, ConcreteClass_, BOOST_PP_SEQ_ELEM(3, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(4, ConcreteClass_, BOOST_PP_SEQ_ELEM(4, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(5, ConcreteClass_, BOOST_PP_SEQ_ELEM(5, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(6, ConcreteClass_, BOOST_PP_SEQ_ELEM(6, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(7, ConcreteClass_, BOOST_PP_SEQ_ELEM(7, Members_)) \


#define CREATE_MEMBERS_9(ConcreteClass_, Members_) \
   CREATE_MEMBER_OR_BASE_CLASS(0, ConcreteClass_, BOOST_PP_SEQ_ELEM(0, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(1, ConcreteClass_, BOOST_PP_SEQ_ELEM(1, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(2, ConcreteClass_, BOOST_PP_SEQ_ELEM(2, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(3, ConcreteClass_, BOOST_PP_SEQ_ELEM(3, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(4, ConcreteClass_, BOOST_PP_SEQ_ELEM(4, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(5, ConcreteClass_, BOOST_PP_SEQ_ELEM(5, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(6, ConcreteClass_, BOOST_PP_SEQ_ELEM(6, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(7, ConcreteClass_, BOOST_PP_SEQ_ELEM(7, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(8, ConcreteClass_, BOOST_PP_SEQ_ELEM(8, Members_)) \


#define CREATE_MEMBERS_10(ConcreteClass_, Members_) \
   CREATE_MEMBER_OR_BASE_CLASS(0, ConcreteClass_, BOOST_PP_SEQ_ELEM(0, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(1, ConcreteClass_, BOOST_PP_SEQ_ELEM(1, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(2, ConcreteClass_, BOOST_PP_SEQ_ELEM(2, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(3, ConcreteClass_, BOOST_PP_SEQ_ELEM(3, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(4, ConcreteClass_, BOOST_PP_SEQ_ELEM(4, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(5, ConcreteClass_, BOOST_PP_SEQ_ELEM(5, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(6, ConcreteClass_, BOOST_PP_SEQ_ELEM(6, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(7, ConcreteClass_, BOOST_PP_SEQ_ELEM(7, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(8, ConcreteClass_, BOOST_PP_SEQ_ELEM(8, Members_)) \
   CREATE_MEMBER_OR_BASE_CLASS(9, ConcreteClass_, BOOST_PP_SEQ_ELEM(9, Members_)) \


#define CREATE_MEMBERS_IMPL(nb, ConcreteClass_, Members_) \
   BOOST_PP_CAT(CREATE_MEMBERS_, nb)(ConcreteClass_, Members_) \


#define REFLECTION(ConcreteClass_, Members_) \
public: \
   template <int i_, class Dummy_> \
   struct member_reflection_info { \
      typedef boost::mpl::false_ present; \
   }; \
   template <int i_, class Dummy_> \
   struct base_class_reflection_info { \
      typedef boost::mpl::false_ present; \
   }; \
   CREATE_MEMBERS_IMPL(BOOST_PP_SEQ_SIZE(Members_), ConcreteClass_, Members_) \
   typedef typename reflection::create_reflection_info<ConcreteClass_::member_reflection_info, BOOST_PP_SEQ_SIZE(Members_)>::result members; \
   typedef typename reflection::create_reflection_info<ConcreteClass_::base_class_reflection_info, BOOST_PP_SEQ_SIZE(Members_)>::result base_classes; \


#define REFLECTED_SERIALIZATION_IMPLEMENTATION() { \
      reflection::serialize_base_classes<base_classes>(*this, archive, version); \
      reflection::serialize_members<members>(*this, archive, version); \
   } \


#define REFLECTED_SERIALIZATION() \
   friend class boost::serialization::access; \
   template <class Archive_> \
   void serialize(Archive_& archive, const unsigned int version) \
   REFLECTED_SERIALIZATION_IMPLEMENTATION() \


#define REFLECTED_SERIALIZATION_DECLARATION() \
   friend class boost::serialization::access; \
   template <class Archive_> \
   void serialize(Archive_& archive, const unsigned int version); \


#define REFLECTED_SERIALIZATION_DEFINITION(ConcreteClass_) \
   template <class Archive_> \
   void ConcreteClass_::serialize(Archive_& archive, const unsigned int version) \
   REFLECTED_SERIALIZATION_IMPLEMENTATION() \


#endif // REFLECTION_HPP_