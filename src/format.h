#ifndef __VIDE_FORMAT_H_
#define __VIDE_FORMAT_H_

#include "buffer.h"

class Format
{
 protected:

 public:
    Format();
    virtual ~Format();

    virtual bool tokenise(Buffer* buffer);
    virtual bool tokenise(Line* line);
};

class SimpleFormat : public Format
{
 protected:

 public:
    SimpleFormat();
    virtual ~SimpleFormat();

    virtual bool tokenise(Line* line);
};

#endif
