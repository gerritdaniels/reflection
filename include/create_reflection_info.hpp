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

#ifndef CREATE_REFLECTION_INFO_HPP_
#define CREATE_REFLECTION_INFO_HPP_

#include <boost/mpl/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/push_front.hpp>


namespace reflection {

   class NullType {};

   template <int i_>
   class Int2Type {};


   template <template<int, class> class reflection_info_, int start_, int end_>
   struct create_reflection_info_impl {
      typedef typename reflection_info_<start_, NullType>::present present;

      typedef typename create_reflection_info_impl<reflection_info_, start_ + 1, end_>::result next;

      typedef typename boost::mpl::if_<present, typename boost::mpl::push_front<next, reflection_info_<start_, NullType>>::type, next>::type result;
   };


   template <template<int, class> class reflection_info_, int end_>
   struct create_reflection_info_impl<reflection_info_, end_, end_> {
      typedef boost::mpl::vector<> result;
   };


   template <template<int, class> class reflection_info_, int max_>
   struct create_reflection_info {
      typedef typename create_reflection_info_impl<reflection_info_, 0, max_>::result result;
   };

}

#endif // CREATE_REFLECTION_INFO_HPP_
