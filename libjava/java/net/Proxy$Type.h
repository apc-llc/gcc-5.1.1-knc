
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __java_net_Proxy$Type__
#define __java_net_Proxy$Type__

#pragma interface

#include <java/lang/Enum.h>
#include <gcj/array.h>

extern "Java"
{
  namespace java
  {
    namespace net
    {
        class Proxy$Type;
    }
  }
}

class java::net::Proxy$Type : public ::java::lang::Enum
{

  Proxy$Type(::java::lang::String *, jint);
public:
  static JArray< ::java::net::Proxy$Type * > * values();
  static ::java::net::Proxy$Type * valueOf(::java::lang::String *);
  static ::java::net::Proxy$Type * DIRECT;
  static ::java::net::Proxy$Type * HTTP;
  static ::java::net::Proxy$Type * SOCKS;
private:
  static const jlong serialVersionUID = -2231209257930100533LL;
  static JArray< ::java::net::Proxy$Type * > * ENUM$VALUES;
public:
  static ::java::lang::Class class$;
};

#endif // __java_net_Proxy$Type__
