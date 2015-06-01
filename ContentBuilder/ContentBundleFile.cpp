#include "ContentBundleFile.h"
#include "zlib/zip.h"

ContentBundleFile::ContentBundleFile(void* bundle, const std::string& filename)
	: _internal(NULL)
{
	zipFile zip = reinterpret_cast<zipFile>(bundle);

	if (zip)
	{
		if (zipOpenNewFileInZip(
				zip,
				filename.c_str(),
				NULL,
				NULL,
				0,
				NULL,
				0,
				NULL,
				Z_DEFLATED,
				Z_DEFAULT_COMPRESSION) == ZIP_OK)
		{
			_internal = zip;
		}
	}
}

ContentBundleFile::~ContentBundleFile()
{
	if (_internal)
		Close();
}

bool ContentBundleFile::Ready() const
{
	return !!_internal;
}

bool ContentBundleFile::Write(const void* buffer, size_t size)
{
	bool ret = false;

	if (_internal)
	{
		zipFile zip = reinterpret_cast<zipFile>(_internal);
		ret = (zipWriteInFileInZip(zip, buffer, size) == ZIP_OK);
	}

	return ret;
}

bool ContentBundleFile::Close()
{
	bool ret = false;

	if (_internal)
	{
		zipFile zip = reinterpret_cast<zipFile>(_internal);
		ret = (zipCloseFileInZip(zip) == ZIP_OK);

		_internal = NULL;
	}

	return ret;
}
