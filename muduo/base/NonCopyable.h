//  (C) Copyright Beman Dawes 1999-2003. Distributed under the Boost
//  //  Software License, Version 1.0. (See accompanying file
//  //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  //  See http://www.boost.org/libs/utility for documentation.

#ifndef MUDUO_BASE_NONCOPYABLE_H
#define MUDUO_BASE_NONCOPYABLE_H

namespace muduo
{
	//  Private copy constructor and copy assignment ensure classes derived from
	//  //  class noncopyable cannot be copied.
	//
	//  //  Contributed by Dave Abrahams
	class noncopyable
	{
		public:
			noncopyable() {}
			~noncopyable() {}
			noncopyable(const noncopyable& ) = delete; /* since c++11 */
			noncopyable& operator=(const noncopyable& ) = delete; /* since c++11 */
	};

} // namespace muduo


#endif
