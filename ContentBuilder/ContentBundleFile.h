#ifndef __CONTENT_BUNDLE_FILE_H__
#define __CONTENT_BUNDLE_FILE_H__

#include "ContentBuilder.h"

class ContentBundleFile
{
public:

	ContentBundleFile(void* bundle, const std::string& filename);
	~ContentBundleFile();

	bool Ready() const;
	bool Write(const void* buffer, size_t size);
	bool Close();

private:

	ContentBundleFile();
	ContentBundleFile(const ContentBundleFile&);
	ContentBundleFile& operator= (const ContentBundleFile&);

private:

	void* _internal;
};

#endif
