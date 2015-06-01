#ifndef __CONTENT_BUNDLE_H__
#define __CONTENT_BUNDLE_H__

#include "ContentBuilder.h"
#include "ContentBundleFile.h"

class ContentBundle
{
public:

	ContentBundle(const std::string& bundleName);
	~ContentBundle();

	bool Ready() const;

	ContentBundleFile* Append(const std::string& filename);
	bool Close(ContentBundleFile* file);

	bool Finalize();

private:

	ContentBundle();
	ContentBundle(const ContentBundle&);
	ContentBundle& operator= (const ContentBundle&);

private:

	void* _internal;
	ContentBundleFile* _currentFile;
};

#endif
