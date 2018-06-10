#pragma once
#include <memory>

namespace pallas
{
	class Reference;
	//
	template<typename T>
	class shared_ptr
	{
	public:
		shared_ptr() {
			data = nullptr;
		}

		shared_ptr(std::nullptr_t) {
			data = nullptr;
		}

		shared_ptr(T* v) {
			data = std::shared_ptr<Reference>(dynamic_cast<Reference*>(v));
		}

		shared_ptr(const shared_ptr& v) {
			data = v.data;
		}

		shared_ptr& operator=(const shared_ptr& v) {
			data = v.data;
			return *this;
		}

		T* get() {
			return (T*)data.get();
		}

		T& operator*() {
			return *((T*)data);
		}

		T* operator->() {
			return (T*)data.get();
		}

		bool operator==(std::nullptr_t) {
			return data == nullptr;
		}

		bool operator!=(std::nullptr_t) {
			return data != nullptr;
		}
	private:
		std::shared_ptr<Reference> data;
	};

	template<typename T>
	class unique_ptr
	{
	public:
		unique_ptr() {
			data = nullptr;
		}

		unique_ptr(std::nullptr_t) {
			data = nullptr;
		}

		unique_ptr(T* v) {
			data = std::unique_ptr<Reference>((Reference*)v);
		}

		unique_ptr(const unique_ptr& v) {
			data = v.data;
		}

		unique_ptr& operator=(const unique_ptr& v) {
			data = v.data;
			return *this;
		}

		T* get() {
			return (T*)data.get();
		}

		T& operator*() {
			return *((T*)data);
		}

		T* operator->() {
			return (T*)data.get();
		}

		bool operator==(std::nullptr_t) {
			return data == nullptr;
		}

		bool operator!=(std::nullptr_t) {
			return data != nullptr;
		}
	private:
		std::unique_ptr<Reference> data;
	};

	class Reference
	{
		friend class std::_Ref_count<Reference>;
		friend class std::shared_ptr<Reference>;
		friend class std::unique_ptr<Reference>;
		friend class shared_ptr<Reference>;
	public:
		Reference() {};
	protected:
		virtual ~Reference() {}
	};
}
