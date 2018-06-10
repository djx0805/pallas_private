#pragma once
#include "Event.h"
#include <vector>
#include <mutex>
#include "ref_ptr.h"
namespace pallas
{
    class EventQueue : public Referenced
    {
    public:
        EventQueue() {}
        virtual ~EventQueue() {}
        //
        void Push(Event* pevent) {
            std::lock_guard<std::mutex> lock(mMutex);
            //
            mEvents.push_back(pevent);
        }

		Event* Pop() {
            std::lock_guard<std::mutex> lock(mMutex);
            //
            if (mEvents.empty())
                return nullptr;
            //
            ref_ptr<Event> pe = mEvents[0];
			mEvents.erase(mEvents.begin());
            return pe.release();
        }

		bool Empty() {
			std::lock_guard<std::mutex> lock(mMutex);
			//
			return mEvents.empty();
		}
    private:
        std::vector<ref_ptr<Event>> mEvents;
        std::mutex mMutex;
    };
}