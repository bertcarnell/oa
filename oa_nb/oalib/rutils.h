/**
 * @file rutils.h
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
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

#pragma once

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "runif.h"

namespace oacpp
{
	/*
	 Utilities based on runif
	*/
	class RUtils
	{
	public:
		static void unifperm( std::vector<int> & pi, int q );
		//static int rankcomp( double** a, double** b );
		//static int rankcomp(const void* a, const void* b);
		//static int findranks_orig(int n, std::vector<double> & v, std::vector<int> & r );
		//static int doubcomp( double a, double b );
	};

    template <class T>
    void findranks_slow(const std::vector<T> & v, std::vector<int> & indx)
    {
        if (indx.size() != v.size())
        {
            indx.resize(v.size());
        }
        for (size_t i = 0; i < v.size(); i++)
        {
            indx[i] = i;
        }
        std::vector<T> vsort(v);
        std::sort<typename std::vector<T>::iterator>(vsort.begin(), vsort.end());
        
        for (size_t i = 0; i < v.size(); i++)
        {
            indx[i] = std::find(vsort.begin(), vsort.end(), v[i]) - vsort.begin() + 1;
        }
    }
    
    template <class T>
    bool findranksCompare(const std::pair<T, int> first, const std::pair<T, int> second)
    {
        return (first.first < second.first);
    }
    
    template <class T>
    void findranks(const std::vector<T> & v, std::vector<int> & rank)
    {
        std::vector<std::pair<T, int> > p(v.size());
        std::vector<int> temp(p.size());
        for (size_t i = 0; i < v.size(); i++)
        {
            p[i] = std::pair<T, int>(v[i], static_cast<int>(i));
        }
        
        if (rank.size() != v.size())
        {
            rank.resize(v.size());
        }

        std::sort(p.begin(), p.end(), findranksCompare<double>);
        
        for (size_t i = 0; i < v.size(); i++)
        {
            rank[p[i].second] = i + 1;
        }
    }
} // end namespace
