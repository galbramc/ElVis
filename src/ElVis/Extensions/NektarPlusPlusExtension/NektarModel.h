///////////////////////////////////////////////////////////////////////////////
//
// The MIT License
//
// Copyright (c) 2006 Scientific Computing and Imaging Institute,
// University of Utah (USA)
//
// License for the specific language governing rights and limitations under
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef ELVIS_NEKTAR_MODEL_H
#define ELVIS_NEKTAR_MODEL_H


#include <SpatialDomains/MeshGraph3D.h>
#include <MultiRegions/ExpList.h>
#include <MultiRegions/ExpList3D.h>

#include <LibUtilities/LinearAlgebra/NekVector.hpp>

#include <ElVis/Core/Model.h>
#include <ElVis/Core/Float.h>
#include <ElVis/Core/InteropBuffer.hpp>
#include <ElVis/Core/FaceDef.h>
#include <ElVis/Core/Util.hpp>

#include <ElVis/Extensions/NektarPlusPlusExtension/Declspec.h>

namespace ElVis
{
    namespace NektarPlusPlusExtension
    {
        class NektarModel : public Model
        {
            public:
                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT explicit NektarModel(const std::string& modelPrefix);
                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual ~NektarModel();

                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT void InitializeWithGeometryAndField(const std::string& geomFileName,
                    const std::string& fieldFileName);

                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT Nektar::SpatialDomains::MeshGraph3DSharedPtr GetMesh() const { return m_graph; }
                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT Nektar::MultiRegions::ExpList3DSharedPtr GetExpansion() const { return m_globalExpansion; }

            protected:
                virtual std::vector<optixu::GeometryGroup> DoGetCellGeometry(Scene* scene, optixu::Context context, CUmodule module);

                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual void DoGetFaceGeometry(Scene* scene, optixu::Context context, CUmodule module, optixu::Geometry& faces);

                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual int DoGetNumberOfBoundarySurfaces() const;
                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual void DoGetBoundarySurface(int surfaceIndex, std::string& name, std::vector<int>& faceIds);

                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT void DoCalculateExtents(ElVis::WorldPoint &,ElVis::WorldPoint &);
                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual unsigned int DoGetNumberOfPoints() const;
                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual WorldPoint DoGetPoint(unsigned int id) const;
                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual const std::string& DoGetPTXPrefix() const;

                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual void DoSetupCudaContext(CUmodule module) const;
                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual const std::string& DoGetCUBinPrefix() const;
                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual unsigned int DoGetNumberOfElements() const
                {
                    return 0;
                }

                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual int DoGetNumFields() const
                {
                    return 1;
                }

                NEKTAR_PLUS_PLUS_EXTENSION_EXPORT virtual FieldInfo DoGetFieldInfo(unsigned int index) const
                {
                    FieldInfo result;
                    result.Name = "Default";
                    result.Id = 0;
                    result.Shortcut = "";
                    return result;
                }

            private:
                NektarModel(const NektarModel& rhs);

                static const std::string HexahedronIntersectionProgramName;
                static const std::string HexahedronPointLocationProgramName;
                static const std::string HexahedronBoundingProgramName;

                NektarModel& operator=(NektarModel& rhs);

                virtual void DoMapInteropBufferForCuda();
                virtual void DoUnMapInteropBufferForCuda();

                void SetupOptixCoefficientBuffers(optixu::Context context, CUmodule module);
                void SetupOptixVertexBuffers(optixu::Context context, CUmodule module);

                template<typename FaceContainer>
                void AddFaces(const FaceContainer& faces, ElVisFloat3* minBuffer, ElVisFloat3* maxBuffer, ElVisFloat4* faceVertexBuffer, FaceDef* faceDefs, ElVisFloat4* normalBuffer)
                {
                    int faceIndex = 0;
                    typedef typename FaceContainer::const_iterator Iterator;
                    for(Iterator iter = faces.begin(); iter != faces.end(); ++iter)
                    {
                        
                        WorldPoint minExtent(std::numeric_limits<ElVisFloat>::max(), std::numeric_limits<ElVisFloat>::max(), std::numeric_limits<ElVisFloat>::max());
                        WorldPoint maxExtent(-std::numeric_limits<ElVisFloat>::max(), -std::numeric_limits<ElVisFloat>::max(), -std::numeric_limits<ElVisFloat>::max());

                        boost::shared_ptr<Nektar::SpatialDomains::Geometry2D> geom = boost::dynamic_pointer_cast<Nektar::SpatialDomains::Geometry2D>( (*iter).second );
                        
                        for(int i = 0; i < geom->GetNumVerts(); ++i)
                        {
                            Nektar::SpatialDomains::VertexComponentSharedPtr rawVertex = geom->GetVertex(i);
                            WorldPoint v(rawVertex->x(), rawVertex->y(), rawVertex->z());
                            minExtent = CalcMin(minExtent, v);
                            maxExtent = CalcMax(maxExtent, v);

                            faceVertexBuffer[4*faceIndex+i] = MakeFloat4(v);

                            if( geom->GetNumVerts() == 3 && i == 2 )
                            {
                                faceVertexBuffer[4*faceIndex+i+1] = MakeFloat4(v);
                            }
                        }

                        // There is no proof that OptiX can't handle degenerate boxes,
                        // but just in case...
                        if( minExtent.x() == maxExtent.x() )
                        {
                            minExtent.SetX(minExtent.x() - .0001);
                            maxExtent.SetX(maxExtent.x() + .0001);
                        }

                        if( minExtent.y() == maxExtent.y() )
                        {
                            minExtent.SetY(minExtent.y() - .0001);
                            maxExtent.SetY(maxExtent.y() + .0001);
                        }

                        if( minExtent.z() == maxExtent.z() )
                        {
                            minExtent.SetZ(minExtent.z() - .0001);
                            maxExtent.SetZ(maxExtent.z() + .0001);
                        }

                        minBuffer[faceIndex] = MakeFloat3(minExtent);
                        maxBuffer[faceIndex] = MakeFloat3(maxExtent);

                        faceDefs[faceIndex].Type = ePlanar;

                        Nektar::SpatialDomains::ElementFaceVectorSharedPtr elements = m_graph->GetElementsFromFace(geom);
                        assert(elements->size() <= 2 );
                        for(int elementId = 0; elementId < elements->size(); ++elementId)
                        {
                            faceDefs[faceIndex].CommonElements[elementId].Id = (*elements)[elementId]->m_Element->GetGlobalID();
                            faceDefs[faceIndex].CommonElements[elementId].Type = (*elements)[elementId]->m_Element->GetGeomShapeType();
                        }
                        
                        
                        // TODO - Normal.
                        ++faceIndex;

                    }
                }
                
                template<typename T>
                optixu::GeometryInstance CreateGeometryForElementType(optixu::Context context, CUmodule module, const std::string& variablePrefix)
                {
                    unsigned int numElements = m_graph->GetAllElementsOfType<T>().size();

                    optixu::Geometry geometry = context->createGeometry();
                    geometry->setPrimitiveCount(numElements);

                    optixu::GeometryInstance instance = context->createGeometryInstance();
                    instance->setGeometry(geometry);

                    m_deviceHexPlaneBuffer.SetContextInfo(context, module);
                    m_deviceHexPlaneBuffer.SetDimensions(numElements*8);
                    //FloatingPointBuffer hexPlaneBuffer("HexPlaneBuffer", 4);
                    //hexPlaneBuffer.Create(context, RT_BUFFER_INPUT, numElements*8);
                    //context[hexPlaneBuffer.Name().c_str()]->set(*hexPlaneBuffer);
                    ElVisFloat* hexPlaneData = static_cast<ElVisFloat*>(m_deviceHexPlaneBuffer.map());
                    
                    m_deviceHexVertexIndices.SetContextInfo(context, module);
                    m_deviceHexVertexIndices.SetDimensions(numElements*8);
                    //optixu::Buffer vertexIndexBuffer = context->createBuffer(RT_BUFFER_INPUT, RT_FORMAT_UNSIGNED_INT, numElements*8);
                    //context["HexVertexIndices"]->set(vertexIndexBuffer);
                    unsigned int* coefficientIndicesData = static_cast<unsigned int*>(m_deviceHexVertexIndices.map());

                    typedef typename std::map<int, boost::shared_ptr<T> >::const_iterator IterType;
                    unsigned int i = 0;
                    for(IterType iter = m_graph->GetAllElementsOfType<T>().begin(); iter != m_graph->GetAllElementsOfType<T>().end(); ++iter)
                    {
                        // TODO - Check the correspondence between vertex id and global id.
                        boost::shared_ptr<T> hex = (*iter).second;
                        for(unsigned int j = 0; j < 8; ++j)
                        {
                            unsigned int vid = hex->GetVid(j);
                            coefficientIndicesData[i*8 + j] = vid;
                        }

                        BOOST_AUTO(v0, m_graph->GetVertex(hex->GetVid(0)));
                        BOOST_AUTO(v1, m_graph->GetVertex(hex->GetVid(1)));
                        BOOST_AUTO(v2, m_graph->GetVertex(hex->GetVid(2)));
                        BOOST_AUTO(v3, m_graph->GetVertex(hex->GetVid(3)));
                        BOOST_AUTO(v4, m_graph->GetVertex(hex->GetVid(4)));
                        BOOST_AUTO(v5, m_graph->GetVertex(hex->GetVid(5)));
                        BOOST_AUTO(v6, m_graph->GetVertex(hex->GetVid(6)));
                        BOOST_AUTO(v7, m_graph->GetVertex(hex->GetVid(7)));

                        Nektar::NekVector<double> faceNormals[6];

                        Nektar::NekVector<double> d1 = Nektar::createVectorFromPoints(*v3, *v0);
                        Nektar::NekVector<double> d2 = Nektar::createVectorFromPoints(*v1, *v0);
                        faceNormals[0] = d1.Cross(d2);

                        d1 = Nektar::createVectorFromPoints(*v5, *v4);
                        d2 = Nektar::createVectorFromPoints(*v7, *v4);
                        faceNormals[1] = d1.Cross(d2);

                        d1 = Nektar::createVectorFromPoints(*v6, *v7);
                        d2 = Nektar::createVectorFromPoints(*v3, *v7);
                        faceNormals[2] = d1.Cross(d2);

                        d1 = Nektar::createVectorFromPoints(*v7, *v4);
                        d2 = Nektar::createVectorFromPoints(*v0, *v4);
                        faceNormals[3] = d1.Cross(d2);

                        d1 = Nektar::createVectorFromPoints(*v0, *v4);
                        d2 = Nektar::createVectorFromPoints(*v5, *v4);
                        faceNormals[4] = d1.Cross(d2);

                        d1 = Nektar::createVectorFromPoints(*v1, *v5);
                        d2 = Nektar::createVectorFromPoints(*v6, *v5);
                        faceNormals[5] = d1.Cross(d2);

                        for(unsigned int c = 0; c < 6; ++c)
                        {
                            faceNormals[c].Normalize();
                        }

                        ElVisFloat D[6];
                        D[0] = -(faceNormals[0].x()*(*v0).x() + faceNormals[0].y()*(*v0).y() +
                            faceNormals[0].z()*(*v0).z());

                        D[1] = -(faceNormals[1].x()*(*v4).x() + faceNormals[1].y()*(*v4).y() +
                            faceNormals[1].z()*(*v4).z());


                        D[2] = -(faceNormals[2].x()*(*v3).x() + faceNormals[2].y()*(*v3).y() +
                            faceNormals[2].z()*(*v3).z());

                        D[3] = -(faceNormals[3].x()*(*v4).x() + faceNormals[3].y()*(*v4).y() +
                            faceNormals[3].z()*(*v4).z());

                        D[4] = -(faceNormals[4].x()*(*v4).x() + faceNormals[4].y()*(*v4).y() +
                            faceNormals[4].z()*(*v4).z());

                        D[5] = -(faceNormals[5].x()*(*v5).x() + faceNormals[5].y()*(*v5).y() +
                            faceNormals[5].z()*(*v5).z());

                        for(unsigned int c = 0; c < 6; ++c)
                        {
                            int indexBase = i*8*4 + 4*c;
                            hexPlaneData[indexBase] = faceNormals[c].x();
                            hexPlaneData[indexBase + 1] = faceNormals[c].y();
                            hexPlaneData[indexBase + 2] = faceNormals[c].z();
                            hexPlaneData[indexBase + 3] = D[c];
                            //std::cout << "(" << hexPlaneData[indexBase] << ", " << hexPlaneData[indexBase+1] << ", " << hexPlaneData[indexBase+2] << ", " << hexPlaneData[indexBase+3] << ")" << std::endl;
                        }
                        ++i;
                    }
                    m_deviceHexVertexIndices.unmap();
                    m_deviceHexPlaneBuffer.unmap();

                    m_deviceNumberOfModes.SetContextInfo(context, module);
                    m_deviceNumberOfModes.SetDimensions(numElements*3);
                    //optixu::Buffer numberOfModesBuffer = context->createBuffer(RT_BUFFER_INPUT, RT_FORMAT_UNSIGNED_INT3, numElements*3);
                    //context["NumberOfModes"]->set(numberOfModesBuffer);
                    unsigned int* modesData = static_cast<unsigned int*>(m_deviceNumberOfModes.map());

                    i = 0;
                    for(IterType iter = m_graph->GetAllElementsOfType<T>().begin(); iter != m_graph->GetAllElementsOfType<T>().end(); ++iter)
                    {
                        // TODO - Check the correspondence between vertex id and global id.
                        boost::shared_ptr<T> hex = (*iter).second; 
                        BOOST_AUTO(localExpansion, m_globalExpansion->GetExp(hex->GetGlobalID()));

                        modesData[i*3] = localExpansion->GetBasis(0)->GetNumModes();
                        modesData[i*3+1] = localExpansion->GetBasis(1)->GetNumModes();
                        modesData[i*3+2] = localExpansion->GetBasis(2)->GetNumModes();
                        ++i;
                    }

                    m_deviceNumberOfModes.unmap();

                    const unsigned int VerticesForEachFace[] = 
                    {0, 1, 2, 3, 
                    4, 5, 6, 7,
                    3, 2, 6, 7,
                    0, 4, 7, 3,
                    0, 1, 5, 4, 
                    1, 5, 6, 2 };

                    m_deviceHexVertexFaceIndex.SetContextInfo(context, module);
                    m_deviceHexVertexFaceIndex.SetDimensions(6);

                    //std::string vertex_face_indexName = variablePrefix + "vertex_face_index";
                    //optixu::Buffer vertexFaceBuffer = context->createBuffer(RT_BUFFER_INPUT, RT_FORMAT_UNSIGNED_INT4, 6);
                    //instance[vertex_face_indexName.c_str()]->set(vertexFaceBuffer);
                    unsigned int* vertexFaceBufferData = static_cast<unsigned int*>(m_deviceHexVertexFaceIndex.map()); 
                    std::copy(VerticesForEachFace, VerticesForEachFace + 4*6, vertexFaceBufferData);
                    m_deviceHexVertexFaceIndex.unmap();

                    return instance;

                }

                Nektar::SpatialDomains::MeshGraph3DSharedPtr m_graph;
                Nektar::MultiRegions::ExpList3DSharedPtr m_globalExpansion;
                LibUtilities::SessionReaderSharedPtr m_session;

                optixu::Program m_hexGeometryIntersectionProgram;
                optixu::Program m_hexPointLocationProgram;

                ElVis::InteropBuffer<ElVisFloat4> m_deviceVertexBuffer;
                ElVis::InteropBuffer<ElVisFloat> m_deviceCoefficientBuffer;
                ElVis::InteropBuffer<unsigned int> m_deviceCoefficientIndexBuffer;
                
                ElVis::InteropBuffer<unsigned int> m_deviceHexVertexIndices;
                ElVis::InteropBuffer<ElVisFloat4> m_deviceHexPlaneBuffer;
                ElVis::InteropBuffer<uint4> m_deviceHexVertexFaceIndex;
                ElVis::InteropBuffer<uint3> m_deviceNumberOfModes;

                ElVis::InteropBuffer<ElVisFloat4> FaceVertexBuffer;
                ElVis::InteropBuffer<ElVisFloat4> FaceNormalBuffer;

        };
    }

}


#endif //ELVIS_NEKTAR_MODEL_H
