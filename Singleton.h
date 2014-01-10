/**
* Copyright(c) 2013 libcc shaoyuan
* All rights reserved
* @file: defines.h
* @datetime：2013-10-31
*/
#pragma once
#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include "lock.h"

/*******************************************************************************
* @brief:单例模式
* @author：shaoyuan19443@gmail.com
* @datetime：2013-10-31
* @version：verson-1.0
* @note:If it works, that's what I write, if not, I do not know who wrote it.
*******************************************************************************/
namespace libccplus
{
	using namespace libccplus;
	class Lock;
	
	template<typename T>
	class Singleton
	{
	public:
		typedef T object_t;
		typedef Singleton<T> parent_t;
	protected:
		Singleton()
		{}
	#ifdef _GET_INSTANCE_OBJECT_POINT_SAFE_
		~Singleton()
		{
			if ( object_ != nullptr )
			{
				lock.enter();
				delete object_;
				object_ = NULL;
				lock.leave();
			}
		}
	#endif

	#ifdef _GET_INSTANCE_OBJECT_REFERENCE_
		~Singleton()
		{}
	#endif

	private:
		DISALLOW_COPY_AND_ASSIGN(Singleton);
	public:
		#ifdef _GET_INSTANCE_OBJECT_REFERENCE_	
			static T& getInstance()	 //return class object reference,single thread safe
			{
				static T object_;	
				return object_;
			}
		#endif 

		#ifdef _GET_INSTANCE_OBJECT_POINT_SAFE_	//return class object or point,multithread safe
			static T* getInstance()
			{
				if ( object_ != nullptr )
				{
					return object_;
				}

				lock.enter();
				if (object_ == NULL)
				{
					object_ =  new T;
				}
				lock.leave();
				return object_;
			}
		#endif

	private:
		static T* object_;
		#ifdef _GET_INSTANCE_OBJECT_POINT_SAFE_
			libccplus::Lock lock;
		#endif
	};
}
#endif
