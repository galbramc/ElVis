////////////////////////////////////////////////////////////////////////////////
//
//  File: hoPyramid.h
//
//
//  The MIT License
//
//  Copyright (c) 2006 Division of Applied Mathematics, Brown University (USA),
//  Department of Aeronautics, Imperial College London (UK), and Scientific
//  Computing and Imaging Institute, University of Utah (USA).
//
//  License for the specific language governing rights and limitations under
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included
//  in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//  Description:
//
//
////////////////////////////////////////////////////////////////////////////////

//#ifndef __PYRAMID_H__
//#define __PYRAMID_H__
//
//#include "FiniteElementPolyhedra.h"
//#include "Points.hpp"
//#include "Vector.hpp"
//
//#define NUM_PYRAMID_VERTICES 5
//#define NUM_PYRAMID_FACES 5
//
//class Pyramid : public PolyhedronWithVertices<NUM_PYRAMID_VERTICES>
//{
//  public:
//      Pyramid(FILE* in, bool reverseBytes=false);
//      virtual ~Pyramid();
//
//      virtual ElVis::TensorPoint transformReferenceToTensor(const ElVis::ReferencePoint& p);
//      virtual ElVis::ReferencePoint transformTensorToReference(const ElVis::TensorPoint& p);
//      virtual ElVis::WorldPoint transformReferenceToWorld(const ElVis::ReferencePoint& p);
//
//      virtual IntervalTensorPoint transformReferenceToTensor(const IntervalReferencePoint& p);
//      virtual IntervalReferencePoint transformTensorToReference(const IntervalTensorPoint& p);
//      virtual IntervalWorldPoint transformReferenceToWorld(const IntervalReferencePoint& p);
//
//      virtual bool findIntersectionWithGeometryInWorldSpace(rt::Ray& ray, double& min, double& max);
//
//      virtual void calculateNormal(const ElVis::TensorPoint& p, ElVis::WorldVector* n);
//
//      virtual void writeElement(FILE* outFile);
//
//      // Writes the geometry in vtk format.
//      virtual void writeElementGeometryForVTK(const char* fileName);
//      virtual void writeElementForVTKAsCell(const char* fileName);
//      virtual void outputVertexOrderForVTK(std::ofstream& outFile,int startPoint=0);
//      virtual int vtkCellType();
//
//  protected:
//      // The functions are used for the numerical computations needed
//      // to transform a point to reference space.
//      //
//      // This function calculates the jacobian of f (where f is the
//      // transform from reference to world space).  (r,s,t) is the
//      // point where we will evaluate the Jacobian, J is the output.
//      // This code was largely generated by Maple (with some slight
//      // hand tuning).
//      void getWorldToReferenceJacobian(double r, double s, double t, double* J);
//
//      void calculateInverseJacobian(double r, double s, double t, double* inverse);
//
//      void calculateFaceNormals();
//
//      // Holds the normals for each face of the hex.
//      // This is needed to help us intersect the plane that
//      // each face belongs to without calculating it each time.
//      ElVis::WorldVector faceNormals[NUM_PYRAMID_FACES];
//
//      // For each normal, the D which will give us the plane
//      // equation.
//      double D[NUM_PYRAMID_FACES];
//
//      bool intersectsFacePlane(const rt::Ray& ray, int face, double& min, double& max);
//};
//
//
//#endif
