/**
 * @file galdef.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * License:  This file may be freely used and shared according to the original license.
 * 
 * Reference:
 * <ul><li><a href="http://lib.stat.cmu.edu/designs/">Statlib Designs</a></li>
 * <li><a href="http://lib.stat.cmu.edu/designs/oa.c">Owen's Orthogonal Array Algorithms</a></li></ul>
 * 
 * Original Header:
 * <blockquote>
 * These programs construct and manipulate orthogonal arrays.  They were prepared by
 * 
 * - Art Owen
 * - Department of Statistics
 * - Sequoia Hall
 * - Stanford CA 94305
 * 
 * They may be freely used and shared.  This code comes 
 * with no warranty of any kind.  Use it at your own
 * risk.
 * 
 * I thank the Semiconductor Research Corporation and
 * the National Science Foundation for supporting this
 * work.
 * </blockquote>
 */

#ifndef GALDEF_H
#define GALDEF_H

#include "CommonDefines.h"
#include "matrix.h"

/* Definitions for Galois Field code */
namespace oacpp {
    struct GF 
    {
        int n,p,q;
        //int *xton;
        std::vector<int> xton, inv, neg, root;
        //int **plus;
        matrix<int> plus, times, poly;
        //int **times;
        //int *inv;
        //int *neg;
        //int *root;
        //int **poly;
    };
} // end namespace

#endif
