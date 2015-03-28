# ImageSegmentationQualityEvaluator

Simple tools used to evaluate the quality of image segmentation algorithms according to a groundtruth image.

## How to use

Both tools work only on 2D and 3D images with an `unsigned char` pixel type. All types of images supported by ITK are accepted. You can also specify a directory, in which cases all bmp, jpeg or png images in it will be sorted and loaded in order to build a 3D image.

Both tools print theirs results to stdout using a YAML format.

### HausdorffDistanceComputer

Computes the Hausdorff distance between two binary images.

    $ ./HausdorffDistanceComputer -h
    Usage: ./HausdorffDistanceComputer segmentation groundtruth

See http://www.itk.org/Doxygen/html/classitk_1_1HausdorffDistanceImageFilter.html for more informations about the Hausdorff distance.

### LabelOverlapComputer

Compute overlap measures between two labelled images (where a pixel value represents the pixel's class). It supports from 2 to 256 classes.

This tool accepts an optional mask image that will restrict the region of interest.

    $ ./LabelOverlapComputer -h
    Usage: ./LabelOverlapComputer segmentation groundtruth [mask]

See http://www.itk.org/Doxygen/html/classitk_1_1LabelOverlapMeasuresImageFilter.html for more informations about overlap measures.

## How to build

Run CMake, and during the "configure" step, set the `ITK_DIR` variable to the `lib/cmake/ITK-X.Y/` directory of your ITK installation.

## LICENSE

The `itkMaskedLabelOverlapMeasuresImageFilter.h` and `itkMaskedLabelOverlapMeasuresImageFilter.hxx` files are licensed under the Apache License, Version 2.0. See the `LICENSE-Apache-2.0.txt` file for more details.

Other files are released under MIT License. See the `LICENSE-MIT.txt` file for more details.
