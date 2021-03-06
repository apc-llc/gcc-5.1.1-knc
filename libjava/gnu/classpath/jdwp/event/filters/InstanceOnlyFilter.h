
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_classpath_jdwp_event_filters_InstanceOnlyFilter__
#define __gnu_classpath_jdwp_event_filters_InstanceOnlyFilter__

#pragma interface

#include <java/lang/Object.h>
extern "Java"
{
  namespace gnu
  {
    namespace classpath
    {
      namespace jdwp
      {
        namespace event
        {
            class Event;
          namespace filters
          {
              class InstanceOnlyFilter;
          }
        }
        namespace id
        {
            class ObjectId;
        }
      }
    }
  }
}

class gnu::classpath::jdwp::event::filters::InstanceOnlyFilter : public ::java::lang::Object
{

public:
  InstanceOnlyFilter(::gnu::classpath::jdwp::id::ObjectId *);
  virtual ::gnu::classpath::jdwp::id::ObjectId * getInstance();
  virtual jboolean matches(::gnu::classpath::jdwp::event::Event *);
private:
  ::gnu::classpath::jdwp::id::ObjectId * __attribute__((aligned(__alignof__( ::java::lang::Object)))) _instance;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_classpath_jdwp_event_filters_InstanceOnlyFilter__
