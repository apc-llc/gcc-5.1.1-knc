
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_JTree$EmptySelectionModel__
#define __javax_swing_JTree$EmptySelectionModel__

#pragma interface

#include <javax/swing/tree/DefaultTreeSelectionModel.h>
#include <gcj/array.h>

extern "Java"
{
  namespace javax
  {
    namespace swing
    {
        class JTree$EmptySelectionModel;
      namespace tree
      {
          class TreePath;
      }
    }
  }
}

class javax::swing::JTree$EmptySelectionModel : public ::javax::swing::tree::DefaultTreeSelectionModel
{

public: // actually protected
  JTree$EmptySelectionModel();
public:
  static ::javax::swing::JTree$EmptySelectionModel * sharedInstance();
  virtual void setSelectionPaths(JArray< ::javax::swing::tree::TreePath * > *);
  virtual void addSelectionPaths(JArray< ::javax::swing::tree::TreePath * > *);
  virtual void removeSelectionPaths(JArray< ::javax::swing::tree::TreePath * > *);
private:
  static const jlong serialVersionUID = -5815023306225701477LL;
public: // actually protected
  static ::javax::swing::JTree$EmptySelectionModel * sharedInstance__;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_JTree$EmptySelectionModel__