#pragma once
#include <atomic>

namespace pallas
{
	/** Base class for providing reference counted objects.*/
	class  Referenced
	{
		template<class T> friend class ref_ptr;
	public:
		Referenced(){}
		Referenced(const Referenced&) {}
		inline Referenced& operator = (const Referenced&) { return *this; }
	protected:
		virtual ~Referenced() {}
	private:
		/** Increment the reference count by one, indicating that
		this object has another pointer which is referencing it.*/
		inline int ref() const
		{
			mRefCount++;
			return mRefCount.load();
		}

		/** Decrement the reference count by one, indicating that
		a pointer to this object is no longer referencing it.  If the
		reference count goes to zero, it is assumed that this object
		is no longer referenced and is automatically deleted.*/
		inline int unref() const
		{
			if (mRefCount.load() == 0)
				return 0;
			//
			int newRef = mRefCount--;
			if (newRef == 0)
				delete this;
			//
			return newRef;
		}

		/** Decrement the reference count by one, indicating that
		a pointer to this object is no longer referencing it.  However, do
		not delete it, even if ref count goes to 0.  Warning, unref_nodelete()
		should only be called if the user knows exactly who will
		be responsible for, one should prefer unref() over unref_nodelete()
		as the latter can lead to memory leaks.*/
		int unref_nodelete() const
		{
			if(mRefCount.load() > 0)
			    mRefCount--;
			return mRefCount;
		}

		/** Return the number of pointers currently referencing this object. */
		inline int referenceCount() const { return mRefCount.load(); }
	private:
		mutable std::atomic<int>   mRefCount = 0;
	};
}