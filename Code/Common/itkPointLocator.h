/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkPointLocator.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#ifndef __itkPointLocator_h
#define __itkPointLocator_h

#include "itkObject.h"
#include "itkPoint.h"
#include "itkNumericTraits.h"
#include "itkBoundingBox.h"

ITK_NAMESPACE_BEGIN

/** \class PointLocator
 * \brief Accelerate geometric searches for points.
 *
 * This class accelerates the search for n-dimensional points. The class
 * operates by using a regular n-dimensional hypercube lattice (e.g., a 2D
 * grid, 3D volume, etc.) into which points are inserted. Each hypercube
 * (also called a bucket) contains a list of points that are contained within
 * it.
 *
 * Template parameters for PointLocator:
 *
 * TPointIdentifier =
 *     The type used to access a particular point (i.e., a point's id)
 *
 * TCoordRep =
 *     Numerical type with which to represent each coordinate value.
 *
 * VPointDimension =
 *    Geometric dimension of space.
 * */

template <
  typename TPointIdentifier = unsigned long,
  int VPointDimension = 3,
  typename TCoordRep = float,
  typename TPointsContainer = 
    VectorContainer< TPointIdentifier,Point<VPointDimension,TCoordRep> >
  >
class ITK_EXPORT PointLocator : public Object
{
public:
  /**
   * Standard "Self" typedef.
   */
  typedef PointLocator   Self;
  
  /**
   * Smart pointer typedef support.
   */
  typedef SmartPointer<Self>  Pointer;
  
  /**
   * Method for creation through the object factory.
   */
  itkNewMacro(Self);

  /**
   * Standard part of every itk Object.
   */
  itkTypeMacro(PointLocator, Object);

  /** \typedef PointIdentifier
   * Hold on to the type information specified by the template parameters.
   * PointIdentifier is the type that the point handles are represented by.
   */
  typedef TPointIdentifier   PointIdentifier;
  typedef TCoordRep   CoordRep;
  enum { PointDimension = VPointDimension };
  typedef TPointsContainer PointsContainer;
  typedef typename PointsContainer::Pointer PointsContainerPointer;
  typedef Point< PointDimension , CoordRep >  Point;

  /**
   * Some convenience typedefs.
   */
  typedef BoundingBox<PointIdentifier,PointDimension,
                      CoordRep,PointsContainer> BoundingBoxType;
  typedef BoundingBoxType::Pointer   BoundingBoxPointer;

  /**
   * Set the number of divisions in each axis direction.
   */
  itkSetVectorMacro(Divisions,unsigned long,PointDimension);
  itkGetVectorMacro(Divisions,unsigned long,PointDimension);

  /**
   * Specify the average number of points in each bucket.
   */
  itkSetClampMacro(NumberOfPointsPerBucket,
                   unsigned long,1,ITK_NUMERIC_LIMITS<unsigned long>::max());
  itkGetMacro(NumberOfPointsPerBucket,unsigned long);

  /**
   * Insert all the points contained in the PointsContainer newPts
   * into the locator. Also supply a bounding box in which the points lie.
   * This methods differs from InitIncrementalPointInsertion() in that
   * assumes that all the points are inserted at once.
   */
  void InitPointInsertion(PointsContainer *newPts, BoundingBoxPointer bbox);

  /**
   * Initialize the incremental point insertion process. Incremental point
   * insertion is used to insert points one at a time into the locator. The
   * supplied PointsContainer (newPts) collects the points that can be used
   * by other objects later. Bounds are the box that the points lie in.
   */
  void InitIncrementalPointInsertion(PointsContainer *newPts, BoundingBoxPointer bbox);

#if 0

  /**
   * Given a position x, return the id of the point closest to it. Alternative
   * method requires separate x-y-z values.
   */
  virtual int FindClosestPoint(float x[3]);
  int FindClosestPoint(float x, float y, float z);

  /**
   * Initialize the point insertion process. The newPts is an object
   * representing point coordinates into which incremental insertion methods
   * place their data. Bounds are the box that the points lie in.
   */
  virtual int InitPointInsertion(itkPoints *newPts, float bounds[6], 
				 int estSize);

  /**
   * Incrementally insert a point into search structure with a particular
   * index value. You should use the method IsInsertedPoint() to see whether 
   * this point has already been inserted (that is, if you desire to prevent
   * dulicate points). Before using this method you must make sure that 
   * newPts have been supplied, the bounds has been set properly, and that 
   * divs are properly set. (See InitPointInsertion().)
   */
  virtual void InsertPoint(int ptId, float x[3]);

  /**
   * Incrementally insert a point into search structure. The method returns
   * the insertion location (i.e., point id). You should use the method 
   * IsInsertedPoint() to see whether this point has already been
   * inserted (that is, if you desire to prevent dulicate points).
   * Before using this method you must make sure that newPts have been
   * supplied, the bounds has been set properly, and that divs are 
   * properly set. (See InitPointInsertion().)
   */
  virtual int InsertNextPoint(float x[3]);

  /**
   * Determine whether point given by x[3] has been inserted into points list.
   * Return id of previously inserted point if this is true, otherwise return
   * -1.
   */
  int IsInsertedPoint(float x, float  y, float z)
    {
    float xyz[3];
    xyz[0] = x; xyz[1] = y; xyz[2] = z;
    return this->IsInsertedPoint (xyz);
    };
  virtual int IsInsertedPoint(float x[3]);

  /**
   * Determine whether point given by x[3] has been inserted into points list.
   * Return 0 if point was already in the list, otherwise return 1. If the
   * point was not in the list, it will be ADDED.  In either case, the id of
   * the point (newly inserted or not) is returned in the ptId argument.
   * Note this combines the functionality of IsInsertedPoint() followed
   * by a call to InsertNextPoint().
   */
  virtual int InsertUniquePoint(float x[3], int &ptId);

  /**
   * Given a position x, return the id of the point closest to it. This method
   * is used when performing incremental point insertion.
   */
  virtual int FindClosestInsertedPoint(float x[3]);
#endif

protected:
  PointLocator();
  ~PointLocator();
  PointLocator(const Self&) {}
  void operator=(const Self&) {}

  virtual void PrintSelf(std::ostream& os, Indent indent);

#if 0
  // place points in appropriate buckets
  void GetBucketNeighbors(int ijk[3], int ndivs[3], int level);
  void GetOverlappingBuckets(float x[3], int ijk[3], float dist, int level);
  void GetOverlappingBuckets(float x[3], float dist, int prevMinLevel[3],
                                           int prevMaxLevel[3]);
  void GenerateFace(int face, int i, int j, int k, 
                    itkPoints *pts, itkCellArray *polys);
  float Distance2ToBucket(float x[3], int nei[3]);
  float Distance2ToBounds(float x[3], float bounds[6]);


  float Bounds[6]; // bounds of points
  itkIdList **HashTable; // lists of point ids in buckets
  int NumberOfBuckets; // total size of hash table
  float H[3]; // width of each bucket in x-y-z directions
  itkNeighborPoints *Buckets;

  float InsertionTol2;
  float InsertionLevel; 
#endif

private:
  unsigned long *m_Divisions;
  unsigned long m_NumberOfPointsPerBucket;

  PointsContainerPointer m_Points;

}; // End Class: PointLocator

ITK_NAMESPACE_END
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkPointLocator.txx"
#endif
  
#endif


