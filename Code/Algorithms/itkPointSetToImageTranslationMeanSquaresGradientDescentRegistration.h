/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkPointSetToImageTranslationMeanSquaresGradientDescentRegistration.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#ifndef __itkPointSetToImageTranslationMeanSquaresGradientDescentRegistration_h
#define __itkPointSetToImageTranslationMeanSquaresGradientDescentRegistration_h

#include "itkRegistrationMethod.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkMeanSquaresPointSetToImageMetric.h"
#include "itkGradientDescentOptimizer.h"
#include "itkImage.h"
#include "itkImageMapper.h"
#include "itkTranslationTransform.h"
#include "itkPointSet.h"

namespace itk
{

/**
 *  Traits class that defines the different types to be
 *  used by this registration method.
 *
 *  It is expected that the reference will be an itk::Image and the
 *  target will be an itk::PointSet or an itk::Mesh class
 */
template <class TReference, class TTarget>
class ITK_EXPORT
PointSetToImageTranslationMeanSquaresGradientDescentRegistrationTraits 
{
public:
  /**  Type of the reference. */
  typedef TReference  ReferenceType;

  /**  Type of the target. */
  typedef TTarget TargetType;

  /** Image dimensions and parameters dimension. */
  enum { ImageDimension = ReferenceType::ImageDimension };

  /**  Type of the point used to represent coordinates in space */
  typedef typename TargetType::PointType   PointType;
    
  /**  Type used to represent space coordinates */
  typedef typename PointType::CoordRepType      CoordinatesType;
 
  /**  Type of the transformation. */
  typedef TranslationTransform< CoordinatesType, 
                                ImageDimension > TransformationType;

  /** Parameters dimension. */
  enum { ParametersDimension = TransformationType::ParametersDimension };

  /**  Type of the parameters. */
  typedef typename TransformationType::ParametersType   ParametersType;
                                  
  /**  Type of the mapper. */
  typedef ImageMapper<ReferenceType,TransformationType>  MapperType;

  /**  Type of the metric. */
  typedef MeanSquaresPointSetToImageMetric<TargetType,MapperType>  MetricType;

  /**  Type of the optimizer.  */
  typedef GradientDescentOptimizer<MetricType>           OptimizerType;
};

/** \class PointSetToImageTranslationMeanSquaresGradientDescentRegistration
 * \brief Base class for registration methods
 *
 * This Class define the generic interface for a registration method.
 * The basic elements of a registration method are:
 *   - Metric to compare the reference and the target
 *   - Transformation used to register the reference against the target
 *   - Optimization method used to search for the best transformation
 * 
 * This class registers a PointSet with an Image.
 * the Image is considered the Reference given that is the one that is
 * mapped under the transformation each time a value is required.
 *
 * \ingroup PointSetToImageRegistration
 */
template <class TReference, class TTarget>
class ITK_EXPORT PointSetToImageTranslationMeanSquaresGradientDescentRegistration 
: public RegistrationMethod< 
            PointSetToImageTranslationMeanSquaresGradientDescentRegistrationTraits<TReference,TTarget> >
{
public:
  /** Standard class typedefs. */
  typedef PointSetToImageTranslationMeanSquaresGradientDescentRegistration Self;
  typedef PointSetToImageTranslationMeanSquaresGradientDescentRegistrationTraits<TReference,TTarget>  Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(PointSetToImageTranslationMeanSquaresGradientDescentRegistration, RegistrationMethod);

  /**  Type of the reference. */
  typedef TReference  ReferenceType;

  /**  Type of the target. */
  typedef TTarget TargetType;

  /**  Type of the parameters. */
  typedef typename Superclass::ParametersType ParametersType;

  /**  Type of the transformation. */
  typedef typename Superclass::TransformationType TransformationType;
   
  /**  Type of the mapper. */
  typedef typename Superclass::MapperType    MapperType;

  /**  Type of the metric. */
  typedef typename Superclass::MetricType   MetricType;

  /**  Type of the optimizer.  */
  typedef typename Superclass::OptimizerType       OptimizerType;
   
  /** Image dimensions. */
  enum { ImageDimension = ReferenceType::ImageDimension,
         ParametersDimension = ImageDimension };

  /** Method that initiates the registration. */
  void StartRegistration(void);

protected:
  PointSetToImageTranslationMeanSquaresGradientDescentRegistration();
  virtual ~PointSetToImageTranslationMeanSquaresGradientDescentRegistration();

private:
  PointSetToImageTranslationMeanSquaresGradientDescentRegistration(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  
  ParametersType             m_Parameters;

};


} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPointSetToImageTranslationMeanSquaresGradientDescentRegistration.txx"
#endif

#endif



