#include "image_loader.h"
#include "itkHausdorffDistanceImageFilter.h"

#include <iomanip>
#include "itkNumericTraits.h"

#include "yaml-cpp/yaml.h"

typedef unsigned char              PixelType;
typedef itk::Image< PixelType, 3 > ImageType;

typedef ImageLoader<ImageType> ImageLoaderType;

int HausdorffDistanceMeasures( int , char * argv[] )
{
	ImageType::Pointer image1 = ImageLoaderType::load(argv[1]);
	ImageType::Pointer image2 = ImageLoaderType::load(argv[2]);

	typedef itk::HausdorffDistanceImageFilter<ImageType, ImageType> FilterType;
	typename FilterType::Pointer filter = FilterType::New();
	filter->SetUseImageSpacing(false);
	filter->SetInput1( image1 );
	filter->SetInput2( image2 );
	filter->Update();

	YAML::Emitter yaml;

	yaml << YAML::BeginMap;
	yaml << YAML::Key << "hausdorff_dist" << YAML::Value << filter->GetHausdorffDistance();
	yaml << YAML::Key << "hausdorff_avg_dist" << YAML::Value << filter->GetAverageHausdorffDistance();

	yaml << YAML::EndMap;

	std::cout << yaml.c_str();

	return EXIT_SUCCESS;
}

int main( int argc, char *argv[] )
{
	if( argc != 3 )
	{
		std::cerr << "Usage: " << argv[0] << " segmentation groundtruth" << std::endl;
		return EXIT_FAILURE;
	}

	HausdorffDistanceMeasures( argc, argv );

	return EXIT_SUCCESS;
}
