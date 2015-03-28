#ifndef IMAGE_LOADER_HXX
#define IMAGE_LOADER_HXX

#include "image_loader.h"

#include "itkImageFileReader.h"
#include "itkImageSeriesReader.h"

#include <ostream>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

template < typename TImageType >
typename ImageLoader< TImageType >::ImagePointer
ImageLoader< TImageType >
::load(const std::string filename)
{
	try {
		boost::filesystem::path path(filename);

		if(boost::filesystem::exists(path)) {
			typename ImageType::Pointer img;

			if(boost::filesystem::is_directory(path))
			{
				img = loadImageSerie(filename);
			} else {
				img = loadImage(filename);
			}

			return img;
		} else {
			std::stringstream err;
			err << "\"" << filename << "\" does not exists";

			throw ImageLoadingException(err.str());
		}
	} catch(boost::filesystem::filesystem_error &ex) {
		std::stringstream err;
		err << filename << " cannot be read (" << ex.what() << ")" << std::endl;
		throw ImageLoadingException(err.str());
	}
}

template < typename TImageType >
typename ImageLoader< TImageType >::ImagePointer
ImageLoader< TImageType >
::loadImage(const std::string filename)
{
	typedef itk::ImageFileReader< ImageType > ImageReader;
	typename ImageReader::Pointer reader = ImageReader::New();

	reader->SetFileName(filename);

	try {
		reader->Update();
	} catch( itk::ExceptionObject &ex ) {
		std::stringstream err;
		err << "ITK is unable to load the image \"" << filename << "\" (" << ex.what() << ")";

		throw ImageLoadingException(err.str());
	}

	return reader->GetOutput();
}

template < typename TImageType >
typename ImageLoader< TImageType >::ImagePointer
	ImageLoader< TImageType >
::loadImageSerie(const std::string filename)
{
	typedef itk::ImageSeriesReader< ImageType > ImageSeriesReader;
	typename ImageSeriesReader::Pointer reader = ImageSeriesReader::New();

	typename ImageSeriesReader::FileNamesContainer filenames;

	try {
		boost::filesystem::path path(filename);
		boost::filesystem::directory_iterator end_iter;
		boost::regex pattern(".*\\.((?:png)|(?:bmp)|(?:jpe?g))", boost::regex::icase);

		for( boost::filesystem::directory_iterator dir_iter(path) ; dir_iter != end_iter ; ++dir_iter)
		{
			boost::smatch match;
			if( !boost::regex_match( dir_iter->path().filename().string(), match, pattern ) ) continue;

			filenames.push_back(boost::filesystem::absolute(dir_iter->path()).string());
		}
	} catch(boost::filesystem::filesystem_error &ex) {
		std::stringstream err;
		err << filename << " cannot be read (" << ex.what() << ")" << std::endl;

		throw ImageLoadingException(err.str());
	}

	std::sort(filenames.begin(), filenames.end());

	reader->SetFileNames(filenames);

	try {
		reader->Update();
	} catch( itk::ExceptionObject &ex ) {
		std::stringstream err;
		err << "ITK is unable to load the image serie located in \"" << filename << "\" (" << ex.what() << ")";

		throw ImageLoadingException(err.str());
	}

	return reader->GetOutput();
}

#endif /* IMAGE_LOADER_HXX */
