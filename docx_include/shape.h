#ifndef SHAPE_H
#define SHAPE_H

#include "docx_global.h"
#include "length.h"

namespace DocxUtils {
class CT_Inline;
class Run;
class ImagePart;

class DOCX_EXPORT InlineShape
{
public:
    InlineShape(CT_Inline *inlinev);    
    Length width() const;
    void setWidth(const DocxUtils::Length &width);
    Length height() const;
    void setHeight(const DocxUtils::Length &height);

    virtual ~InlineShape();

private:
    CT_Inline* m_inline;

};

}
#endif // SHAPE_H
