//
// Shapes.cpp
//
//  Created by Warren R. Carithers 2018/04/19.
//  Based on earlier versions by Warren R. Carithers and Joe Geigel.
//  Copyright 2018 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Jietong Chen
//

#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

using namespace std;

#include "Canvas.h"
#include "Shapes.h"
#include "Object.h"

/*
** The quad
*/

//
// The quad is parallel to the XY plane with the front face
// pointing down the +Z axis
//

//
// Each group of three values specifies a quad vertex
//
float quadVertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f
};

int quadVerticesLength = sizeof(quadVertices) / sizeof(float);

//
// Each pair of values specifies a vertex's texture coordinates
//

float quadUV[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
};

//
// Because the quad faces +Z, all the normals are (0,0,1)
//
float quadNormals[] = {
        0.0f, 0.0f,  1.0f,
        0.0f, 0.0f, -1.0f
};

int quadNormalsLength = sizeof(quadNormals) / sizeof(float);

//
// Each group of three entries specifies a triangle for the quad
//
int quadElements[] = {
    0, 0, 0,  1, 1, 0,  2, 2, 0,
    2, 2, 0,  1, 1, 0,  3, 3, 0,
    0, 0, 1,  2, 2, 1,  1, 1, 1,
    1, 1, 1,  2, 2, 1,  3, 3, 1
};

int quadElementsLength = sizeof(quadElements) / sizeof(int);

//
// makeQuad() - create a quad object
//
static void makeQuad( Canvas &C ) {
    int i;

    for( i = 0; i < quadElementsLength - 8; i += 9 ) {
        // Calculate the base indices of the three vertices
        int point1 = 3 * quadElements[ i ];     // slots 0, 1, 2
        int point2 = 3 * quadElements[ i + 3 ]; // slots 3, 4, 5
        int point3 = 3 * quadElements[ i + 6 ]; // slots 6, 7, 8

        glm::vec3 p1 = glm::vec3( quadVertices[ point1 + 0 ],
                                  quadVertices[ point1 + 1 ],
                                  quadVertices[ point1 + 2 ] );

        glm::vec3 p2 = glm::vec3( quadVertices[ point2 + 0 ],
                                  quadVertices[ point2 + 1 ],
                                  quadVertices[ point2 + 2 ] );

        glm::vec3 p3 = glm::vec3( quadVertices[ point3 + 0 ],
                                  quadVertices[ point3 + 1 ],
                                  quadVertices[ point3 + 2 ] );

        // Calculate the base indices of the three texture coordinates
        int uvcoord1 = 2 * quadElements[ i + 1 ]; // slots 0, 1
        int uvcoord2 = 2 * quadElements[ i + 4 ]; // slots 2, 3
        int uvcoord3 = 2 * quadElements[ i + 7 ]; // slots 4, 5

        // UVcoord is really Vertex, so we need a 'z' component
        glm::vec3 uv1 = glm::vec3( quadUV[ uvcoord1 + 0 ],
                                   quadUV[ uvcoord1 + 1 ], 0.0f );
        glm::vec3 uv2 = glm::vec3( quadUV[ uvcoord2 + 0 ],
                                   quadUV[ uvcoord2 + 1 ], 0.0f );
        glm::vec3 uv3 = glm::vec3( quadUV[ uvcoord3 + 0 ],
                                   quadUV[ uvcoord3 + 1 ], 0.0f );

        // Calculate the base indices of the three normals
        int normal1 = 3 * quadElements[ i + 2 ]; // slots 0, 1, 2
        int normal2 = 3 * quadElements[ i + 5 ]; // slots 3, 4, 5
        int normal3 = 3 * quadElements[ i + 8 ]; // slots 6, 7, 8

        glm::vec3 n1 = glm::vec3( quadNormals[ normal1 + 0 ],
                                  quadNormals[ normal1 + 1 ],
                                  quadNormals[ normal1 + 2 ] );

        glm::vec3 n2 = glm::vec3( quadNormals[ normal2 + 0 ],
                                  quadNormals[ normal2 + 1 ],
                                  quadNormals[ normal2 + 2 ] );

        glm::vec3 n3 = glm::vec3( quadNormals[ normal3 + 0 ],
                                  quadNormals[ normal3 + 1 ],
                                  quadNormals[ normal3 + 2 ] );

        // Add triangle and texture coordinates
        C.addTriangleWithNormsUV( p1, n1, uv1, p2, n2, uv2, p3, n3, uv3 );
    }
}

///
// Make the desired shape
//
// @param choice - which shape to make
// @param C      - the Canvas we'll use
///
void makeShape( int choice, Canvas &C ) {
    switch( choice ) {
        case OBJ_APPLE:
            readShape( "model/Apple.obj", C );
            break;

        case OBJ_COOKIES1:
            readShape( "model/Cookies1.obj", C );
            break;

        case OBJ_COOKIES2:
            readShape( "model/Cookies2.obj", C );
            break;

        case OBJ_CUP:
            readShape( "model/Cup.obj", C );
            // apply cylindrical texture mapping on the cup
            cylindricalUV( C );
            break;

        case OBJ_DOUGHNUT:
            readShape( "model/Doughnut.obj", C );
            break;

        case OBJ_FOLIAGE:
            readShape( "model/Foliage.obj", C );
            break;

        case OBJ_PLATE:
            readShape( "model/Plate.obj", C );
            break;

        case OBJ_POT:
            readShape( "model/Pot.obj", C );
            break;

        case OBJ_QUAD:
            makeQuad( C );
            break;

        case OBJ_SPOON:
            readShape( "model/Spoon.obj", C );
            break;

        case OBJ_TABLE:
            readShape( "model/Table.obj", C );
            break;

        case OBJ_TEAPOT:
            readShape( "model/Teapot.obj", C );
            break;

        default:
            cerr << "drawShape: unknown object " << choice << " - ignoring"
                 << endl;
    }
}

///
// Read the shape from an obj file.
//
// @param filename - the name of the model file
// @param C        - the Canvas to use
///
void readShape( const char *filename, Canvas &C ) {
    ifstream in( filename, ios::in );

    if( !in ) {
        cerr << "Cannot open " << filename << endl;
        exit( 1 );
    }

    // vertices of the shape
    vector< glm::vec3 > vertices;
    // normals of the shape
    vector< glm::vec3 > normals;
    // texture coordinate of the shape
    vector< glm::vec3 > uvCoords;

    // each group represent a triangle
    vector< int > elements;
    vector< int > normalIndices;
    vector< int > uvIndices;

    // the obj file contains normal information of the shape
    bool hasNormal = false;
    // the obj file contains texture coordinate of the shape
    bool hasUV = false;

    // a line of the file
    string line;
    while( getline( in, line ) ) {
        if( line.substr( 0, 2 ) == "v " ) {
            // vertex line
            istringstream s( line.substr( 2 ) );
            glm::vec3 v;
            s >> v.x;
            s >> v.y;
            s >> v.z;
            vertices.push_back( v );
        } else if( line.substr( 0, 3 ) == "vn " ) {
            // normal line
            hasNormal = true;

            istringstream s( line.substr( 3 ) );
            glm::vec3 n;
            s >> n.x;
            s >> n.y;
            s >> n.z;
            normals.push_back( n );
        } else if( line.substr( 0, 3 ) == "vt " ) {
            // texture coordinate line
            hasUV = true;

            istringstream s( line.substr( 3 ) );
            glm::vec3 uv;
            s >> uv.x;
            s >> uv.y;
            s >> uv.z;
            uvCoords.push_back( uv );
        } else if( line.substr( 0, 2 ) == "f " ) {
            // face line
            istringstream s( line.substr( 2 ) );

            for( int i = 0; i < 3; i++ ) {
                string str;
                s >> str;

                // locate the separators
                u_int first = str.find_first_of( '/' );
                u_int last = str.find_last_of( '/' );

                // the index of vertex
                int v = atoi( str.substr( 0, first ).c_str() );
                elements.push_back( v - 1 );

                if( hasNormal ) {
                    // the index of normal
                    int n = atoi( str.substr( last + 1 ).c_str() );
                    normalIndices.push_back( n - 1 );
                }

                if( hasUV ) {
                    // the index of texture coordinate
                    int uv = atoi(
                            str.substr( first + 1, last - first - 1 ).c_str() );
                    uvIndices.push_back( uv - 1 );
                }
            }
        }
    }

    for( int i = 0; i < elements.size() / 3; i++ ) {
        // the vertices of the triangle
        glm::vec3 p1 = vertices[ elements[ i * 3 ] ];
        glm::vec3 p2 = vertices[ elements[ i * 3 + 1 ] ];
        glm::vec3 p3 = vertices[ elements[ i * 3 + 2 ] ];

        // the normal of the vertices
        glm::vec3 n1, n2, n3;
        // the texture coordinate of the vertices
        glm::vec3 uv1, uv2, uv3;

        if( hasNormal ) {
            n1 = normals[ normalIndices[ i * 3 ] ];
            n2 = normals[ normalIndices[ i * 3 + 1 ] ];
            n3 = normals[ normalIndices[ i * 3 + 2 ] ];
        }

        if( hasUV ) {
            uv1 = uvCoords[ uvIndices[ i * 3 ] ];
            uv2 = uvCoords[ uvIndices[ i * 3 + 1 ] ];
            uv3 = uvCoords[ uvIndices[ i * 3 + 2 ] ];
        }

        if( hasNormal && !hasUV ) {
            // Add triangle and normal
            C.addTriangleWithNorms( p1, n1, p2, n2, p3, n3 );
        } else if( !hasNormal && hasUV ) {
            // Add triangle and texture coordinates
            C.addTriangleWithUV( p1, uv1, p2, uv2, p3, uv3 );
        } else if( hasNormal && hasUV ) {
            // Add triangle, normal and texture coordinates
            C.addTriangleWithNormsUV( p1, n1, uv1, p2, n2, uv2, p3, n3, uv3 );
        }
    }
}

///
// Apply cylindrical texture mapping on the shape.
//
// @param C - the Canvas to use
///
void cylindricalUV( Canvas &C ) {
    for( int i = 0; i < C.points.size() / 4; i++ ) {
        // the texture coordinate of the vertex
        float u, v;

        // the index of x value of the vertex
        int x = i * 4;
        // the index of y value of the vertex
        int y = i * 4 + 1;
        // the index of z value of the vertex
        int z = i * 4 + 2;

        if( C.points[ z ] == 0 ) {
            u = C.points[ x ] < 0 ? 0.5f : 1.0f;

        } else if( C.points[ x ] == 0 ) {
            u = C.points[ z ] < 0 ? 0.25f : 0.75f;

        } else {
            // the tangent of phi
            double tanPhi = C.points[ x ] / C.points[ z ];
            double phi = atan( tanPhi );

            u = float( phi / ( 2 * M_PI ) ) + 0.25f;

            // the front hemisphere
            if( C.points[ z ] > 0 ) {
                u += 0.5f;
            }
        }

        // the texture coordinate value of v-axis
        v = C.points[ y ];

        // add the texture coordinate
        C.uv.push_back( u );
        C.uv.push_back( v );
    }

    // clean up the uv coordinate, change the u-axis value to 0 for the vertex
    // position on positive x axis and it is the a vertex of the face in first
    // half of the shape
    for( int f = 0; f < C.uv.size() / 6; f++ ) {
        // the face contains a vertex on positive x axis
        bool hasEndpoint = false;
        // the face is in first half of the shape
        bool isFront = false;

        for( int i = 0; i < 3; i++ ) {
            // the index of u value of the vertex
            int u = f * 6 + i * 2;

            if( C.uv[u] < 0.5f ) {
                isFront = true;
            }

            if( C.uv[u] == 1.0f ) {
                hasEndpoint = true;
            }
        }

        if( hasEndpoint && isFront ) {
            for( int i = 0; i < 3; i++ ) {
                // the index of u value of the vertex
                int u = f * 6 + i * 2;

                if( C.uv[ u ] == 1.0f ) {
                    // change the u-axis value to 0
                    C.uv[ u ] = 0.0f;
                }
            }
        }
    }
}
