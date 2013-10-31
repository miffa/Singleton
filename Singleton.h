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
	class CLock;
	
	template<typename T>
	class Singleton
	{
	public:
		typedef T object_t;
		typedef Singleton<T> parent_t;
	protected:
		Singleton()
		{
		}
	private:
	#ifdef _GET_INSTANCE_2_
		~Singleton()
		{
			if (object_ != NULL)
			{
				delete object_;
			}
			object_ = NULL;
		}
	#endif

	#ifdef _GET_INSTANCE_3_
		~Singleton()
		{
			lock.enter();
			if ( NULL != object_)
			{
				delete object_;
			}
			object_ = NULL;
			lock.leave();
		}
	#endif

	#ifdef _GET_INSTANCE_1_
		~Singleton()
		{}
	#endif

	private:
		Singleton(const Singleton& rhs)
		{}
		Singleton& operator = (const Singleton& rhs)
		{}
	public:
		#ifdef _GET_INSTANCE_1_	
			static T& getInstance()	 //return class object reference,single thread safe
			{
				static T object_;	
				return object_;
			}
		#endif 

		#ifdef _GET_INSTANCE_2_
			static T* getInstance()	 //return class object point,single thread safe
			{
				if (object_ == NULL)
				{
					object_ = new T;
				}
				return object_;
			}
			static void atExit()
			{
				if (object_ != NULL)
				{
					delete object_;
				}
				object_ = NULL;
			}
		#endif
		#ifdef _GET_INSTANCE_3_	//return class object or point,multithread safe
			static T* getInstance()
			{
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
		#ifdef _GET_INSTANCE_3_
			libccplus::CLock lock;
		#endif
	};
}
#endif
