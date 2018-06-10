#pragma once
#include "RenderTarget.h"
#include "EventQueue.h"
#include <unordered_map>
namespace pallas
{
    class RenderWindow : public RenderTarget
    {
	public:
		class Setting
		{
			friend class RenderWindow;
		public:

		private:

		};
    public:
		static RenderWindow* Create(Setting windowSetting);
	public:
        virtual ~RenderWindow() {}
        //
        virtual void BindEventQueue(EventQueue* peventQueue) {
            mEventQueue = peventQueue;
        }
        virtual EventQueue* GetEventQueue() {
            return mEventQueue.get();
        }
		//
		virtual void AddWindowEventHander(GUIEventHandler* handler) {
			mWindowEventHandlers.push_back(handler);
		}
		virtual void RemoveWindowEventHandler(GUIEventHandler* handler) {
			for (auto itr = mWindowEventHandlers.begin(); itr != mWindowEventHandlers.end(); ++itr) {
				if (itr->get()->GetID() == handler->GetID()) {
					mWindowEventHandlers.erase(itr);
					break;
				}
			}
		}

		virtual void DispatchEvents() {
			while (!mEventQueue->Empty()) {
				auto pevent = ref_ptr<Event>(mEventQueue->Pop());
				for (auto itr_handler : mWindowEventHandlers) {
					if (itr_handler->Handle(pevent.get()))
						break;
				}
			}
		}
		virtual RenderWindow* asRenderWindow() override {
			return this;
		}
	protected:
		RenderWindow() {}
    protected:
        ref_ptr<EventQueue> mEventQueue;
		std::vector<ref_ptr<GUIEventHandler>> mWindowEventHandlers;
    };
}