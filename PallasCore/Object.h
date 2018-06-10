#pragma once
#include "Referenced.h"
#include "ref_ptr.h"
#include <string>

namespace pallas
{
   class Object : public Referenced
   {
   public:
       Object() {
           mID = std::to_string(long long(this));
       }

       inline void SetName(const char* name) {
           mName = name;
       }
      inline std::string GetName() {
           return mName;
       }

       inline void SetID(const char* id) {
           mID = id;
       }
      inline std::string GetID() {
           return mID;
       }
   protected:
       virtual ~Object(){}
   protected:
       std::string mName;
       std::string mID;
   };
}
