
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_java_awt_color_ColorLookUpTable__
#define __gnu_java_awt_color_ColorLookUpTable__

#pragma interface

#include <java/lang/Object.h>
#include <gcj/array.h>

extern "Java"
{
  namespace gnu
  {
    namespace java
    {
      namespace awt
      {
        namespace color
        {
            class ColorLookUpTable;
        }
      }
    }
  }
  namespace java
  {
    namespace awt
    {
      namespace color
      {
          class ICC_Profile;
      }
    }
  }
}

class gnu::java::awt::color::ColorLookUpTable : public ::java::lang::Object
{

public:
  ColorLookUpTable(::java::awt::color::ICC_Profile *, jint);
private:
  void readClut16(JArray< jbyte > *);
  void readClut8(JArray< jbyte > *);
public: // actually package-private
  virtual JArray< jfloat > * lookup(JArray< jfloat > *);
private:
  JArray< jfloat > * LabtoXYZ(JArray< jfloat > *);
  JArray< jfloat > * XYZtoLab(JArray< jfloat > *);
  static JArray< jfloat > * D50;
public: // actually package-private
  jint __attribute__((aligned(__alignof__( ::java::lang::Object)))) nIn;
  jint nOut;
  jint nInTableEntries;
  jint nOutTableEntries;
  jint gridpoints;
  jint nClut;
  JArray< JArray< jdouble > * > * inTable;
  JArray< JArray< jshort > * > * outTable;
  JArray< jdouble > * clut;
  JArray< JArray< jfloat > * > * inMatrix;
  jboolean useMatrix;
  JArray< jint > * multiplier;
  JArray< jint > * offsets;
  jboolean inputLab;
  jboolean outputLab;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_java_awt_color_ColorLookUpTable__
