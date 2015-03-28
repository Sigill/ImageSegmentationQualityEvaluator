#include "itkImageFileReader.h"
#include "itkLabelOverlapMeasuresImageFilter.h"
#include "itkMaskedLabelOverlapMeasuresImageFilter.h"
#include "image_loader.h"

#include <iomanip>
#include "itkNumericTraits.h"

#include "yaml-cpp/yaml.h"

typedef unsigned char              PixelType;
typedef itk::Image< PixelType, 3 > ImageType;

typedef ImageLoader<ImageType> ImageLoaderType;

int LabelOverlapMeasures( char * argv[] )
{
  ImageType::Pointer image1 = ImageLoaderType::load(argv[1]);
  ImageType::Pointer image2 = ImageLoaderType::load(argv[2]);

  typedef itk::LabelOverlapMeasuresImageFilter< ImageType > FilterType;
  typename FilterType::Pointer filter = FilterType::New();
  filter->SetSourceImage( image1 );
  filter->SetTargetImage( image2 );
  filter->Update();

  YAML::Emitter yaml;

  yaml << YAML::BeginMap;
  yaml << YAML::Key << "total_overlap" << YAML::Value << filter->GetTotalOverlap();
  yaml << YAML::Key << "union_overlap" << YAML::Value << filter->GetUnionOverlap();
  yaml << YAML::Key << "mean_overlap" << YAML::Value << filter->GetMeanOverlap();
  yaml << YAML::Key << "vol_sim" << YAML::Value << filter->GetVolumeSimilarity();
  yaml << YAML::Key << "false_neg" << YAML::Value << filter->GetFalseNegativeError();
  yaml << YAML::Key << "false_pos" << YAML::Value << filter->GetFalsePositiveError();
  yaml << YAML::Key << "classes" << YAML::Value << YAML::BeginMap; // Classes

  typename FilterType::MapType labelMap = filter->GetLabelSetMeasures();
  typename FilterType::MapType::const_iterator it;
  for( it = labelMap.begin(); it != labelMap.end(); ++it )
    {
    if( (*it).first == 0 )
      {
      continue;
      }

    int label = (*it).first;

    std::ostringstream os;
    os << std::setfill('0') << std::setw(6) << label;

    yaml << YAML::Key << os.str() << YAML::Value;

    yaml << YAML::BeginMap; // Detail of the class
    yaml << YAML::Key << "target_overlap" << YAML::Value << filter->GetTargetOverlap(label);
    yaml << YAML::Key << "union_overlap" << YAML::Value << filter->GetUnionOverlap(label);
    yaml << YAML::Key << "mean_overlap" << YAML::Value << filter->GetMeanOverlap(label);
    yaml << YAML::Key << "vol_sim" << YAML::Value << filter->GetVolumeSimilarity(label);
    yaml << YAML::Key << "false_neg" << YAML::Value << filter->GetFalseNegativeError(label);
    yaml << YAML::Key << "false_pos" << YAML::Value << filter->GetFalsePositiveError(label);

    yaml << YAML::Key << "source" << YAML::Value << (*it).second.m_Source;
    yaml << YAML::Key << "target" << YAML::Value << (*it).second.m_Target;
    yaml << YAML::Key << "union" << YAML::Value << (*it).second.m_Union;
    yaml << YAML::Key << "intersection" << YAML::Value << (*it).second.m_Intersection;
    yaml << YAML::Key << "source_comp" << YAML::Value << (*it).second.m_SourceComplement;
    yaml << YAML::Key << "target_comp" << YAML::Value << (*it).second.m_TargetComplement;

    yaml << YAML::EndMap; // Detail of the class
    }
  yaml << YAML::EndMap; // Classes

  yaml << YAML::EndMap;

  std::cout << yaml.c_str();

  return EXIT_SUCCESS;
}

int MaskedLabelOverlapMeasures( char * argv[] )
{
  ImageType::Pointer image1 = ImageLoaderType::load(argv[1]);
  ImageType::Pointer image2 = ImageLoaderType::load(argv[2]);
  ImageType::Pointer image3 = ImageLoaderType::load(argv[3]);

  typedef itk::MaskedLabelOverlapMeasuresImageFilter<ImageType> FilterType;
  typename FilterType::Pointer filter = FilterType::New();
  filter->SetSourceImage( image1 );
  filter->SetTargetImage( image2 );
  filter->SetMaskImage( image3 );
  filter->SetInsidePixelValue(itk::NumericTraits< PixelType >::max());
  filter->Update();

  YAML::Emitter yaml;
  yaml.SetStringFormat(YAML::DoubleQuoted);

  yaml << YAML::BeginMap;
  yaml << YAML::Key << "total_overlap" << YAML::Value << filter->GetTotalOverlap();
  yaml << YAML::Key << "union_overlap" << YAML::Value << filter->GetUnionOverlap();
  yaml << YAML::Key << "mean_overlap" << YAML::Value << filter->GetMeanOverlap();
  yaml << YAML::Key << "vol_sim" << YAML::Value << filter->GetVolumeSimilarity();
  yaml << YAML::Key << "false_neg" << YAML::Value << filter->GetFalseNegativeError();
  yaml << YAML::Key << "false_pos" << YAML::Value << filter->GetFalsePositiveError();
  yaml << YAML::Key << "classes" << YAML::Value << YAML::BeginMap; // Classes

  typename FilterType::MapType labelMap = filter->GetLabelSetMeasures();
  typename FilterType::MapType::const_iterator it;
  for( it = labelMap.begin(); it != labelMap.end(); ++it )
    {
    if( (*it).first == 0 )
      {
      continue;
      }

    int label = (*it).first;

    std::ostringstream os;
    os << std::setfill('0') << std::setw(6) << label;

    yaml << YAML::Key << os.str() << YAML::Value;

    yaml << YAML::BeginMap; // Detail of the class
    yaml << YAML::Key << "target_overlap" << YAML::Value << filter->GetTargetOverlap(label);
    yaml << YAML::Key << "union_overlap" << YAML::Value << filter->GetUnionOverlap(label);
    yaml << YAML::Key << "mean_overlap" << YAML::Value << filter->GetMeanOverlap(label);
    yaml << YAML::Key << "vol_sim" << YAML::Value << filter->GetVolumeSimilarity(label);
    yaml << YAML::Key << "false_neg" << YAML::Value << filter->GetFalseNegativeError(label);
    yaml << YAML::Key << "false_pos" << YAML::Value << filter->GetFalsePositiveError(label);

    yaml << YAML::Key << "source" << YAML::Value << (*it).second.m_Source;
    yaml << YAML::Key << "target" << YAML::Value << (*it).second.m_Target;
    yaml << YAML::Key << "union" << YAML::Value << (*it).second.m_Union;
    yaml << YAML::Key << "intersection" << YAML::Value << (*it).second.m_Intersection;
    yaml << YAML::Key << "source_comp" << YAML::Value << (*it).second.m_SourceComplement;
    yaml << YAML::Key << "target_comp" << YAML::Value << (*it).second.m_TargetComplement;

    yaml << YAML::EndMap; // Detail of the class
    }
  yaml << YAML::EndMap; // Classes

  yaml << YAML::EndMap;

  std::cout << yaml.c_str();

  return EXIT_SUCCESS;
}

int main( int argc, char *argv[] )
{
  if( (argc != 3) && (argc != 4) )
    {
    std::cerr << "Usage: " << argv[0] << " segmentation groundtruth [mask]" << std::endl;
    return EXIT_FAILURE;
    }

    if(argc == 3)
      LabelOverlapMeasures(argv);
    else
      MaskedLabelOverlapMeasures(argv);

  return EXIT_SUCCESS;
}
