#ifndef __CONTENT_TYPE_H__
#define __CONTENT_TYPE_H__

#include "ContentBundle.h"
#include "tinyxml/tinyxml.h"

class ContentType
{
public:

	ContentType();
	virtual ~ContentType();

	virtual bool Build(ContentBundle& bundle, TiXmlElement& desc) = 0;
};

#endif
