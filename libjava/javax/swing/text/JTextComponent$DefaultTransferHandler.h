
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_text_JTextComponent$DefaultTransferHandler__
#define __javax_swing_text_JTextComponent$DefaultTransferHandler__

#pragma interface

#include <javax/swing/TransferHandler.h>
#include <gcj/array.h>

extern "Java"
{
  namespace java
  {
    namespace awt
    {
      namespace datatransfer
      {
          class Clipboard;
          class DataFlavor;
          class Transferable;
      }
    }
  }
  namespace javax
  {
    namespace swing
    {
        class JComponent;
      namespace text
      {
          class JTextComponent;
          class JTextComponent$DefaultTransferHandler;
      }
    }
  }
}

class javax::swing::text::JTextComponent$DefaultTransferHandler : public ::javax::swing::TransferHandler
{

public: // actually package-private
  JTextComponent$DefaultTransferHandler(::javax::swing::text::JTextComponent *);
public:
  virtual jboolean canImport(::javax::swing::JComponent *, JArray< ::java::awt::datatransfer::DataFlavor * > *);
  virtual void exportToClipboard(::javax::swing::JComponent *, ::java::awt::datatransfer::Clipboard *, jint);
  virtual jint getSourceActions();
  virtual jboolean importData(::javax::swing::JComponent *, ::java::awt::datatransfer::Transferable *);
public: // actually package-private
  ::javax::swing::text::JTextComponent * __attribute__((aligned(__alignof__( ::javax::swing::TransferHandler)))) this$0;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_text_JTextComponent$DefaultTransferHandler__
