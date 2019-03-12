//
// Shapes.h
//
// Prototypes for shape-drawing functions.
//
// Contributor:  Jietong Chen
//

#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "Canvas.h"
#include "Buffers.h"

///
// Make the desired shape
//
// @param choice - which shape to make
// @param C      - the Canvas we'll use
///
void makeShape( int choice, Canvas &C );

///
// Read the shape from an obj file.
//
// @param filename - the name of the model file
// @param C        - the Canvas to use
///
void readShape( const char *filename, Canvas &C );

///
// Apply cylindrical texture mapping on the shape.
//
// @param C - the Canvas to use
///
void cylindricalUV( Canvas &C );

#endif
