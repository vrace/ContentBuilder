#include "ContentBuilder.h"
#include "ContentBundle.h"

#include "zlib/zip.h"

ContentBundle::ContentBundle(const std::string& bundleName)
	: _internal(NULL)
{
	zipFile zip;

	zip = zipOpen(bundleName.c_str(), APPEND_STATUS_CREATE);

	if (zip)
		_internal = zip;
}

ContentBundle::~ContentBundle()
{
	if (_internal)
		Finalize();
}

bool ContentBundle::Ready() const
{
	return !!_internal;
}

ContentBundleFile* ContentBundle::Append(const std::string& filename)
{
	ContentBundleFile* out = NULL;

	if (!_currentFile)
	{
		std::auto_ptr<ContentBundleFile> file;
		file.reset(new ContentBundleFile(_internal, filename));

		if (file->Ready())
		{
			out = &*file;
			_currentFile = file.release();
		}
	}

	return out;
}

bool ContentBundle::Close(ContentBundleFile* file)
{
	bool ret = false;

	if (file && _currentFile == file)
	{
		if (file->Close())
		{
			delete _currentFile;
			_currentFile = NULL;

			ret = true;
		}
	}

	return ret;
}

bool ContentBundle::Finalize()
{
	bool ret = true;

	if (_currentFile)
	{
		if (_currentFile->Close())
		{
			delete _currentFile;
			_currentFile = NULL;
		}
		else
		{
			ret = false;
		}
	}

	if (_internal)
	{
		zipFile zip = reinterpret_cast<zipFile>(_internal);
		ret = ret && (zipClose(zip, NULL) == ZIP_OK);

		_internal = NULL;
	}

	return ret;
}
