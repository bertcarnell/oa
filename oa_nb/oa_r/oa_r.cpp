/**
 * @file oa_r.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * @license <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License (GPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "oa_r.h"

RcppExport SEXP test(SEXP n)
{
    Rcpp::IntegerVector ivn(n);
    Rcpp::IntegerVector output(1);
    output[0] = 0;
    for (int i = 0; i < ivn.size(); i++)
    {
        output[0] += ivn[i];
    }
    return output;
}

#include <sstream>
RcppExport SEXP test2(SEXP one, SEXP two, SEXP three, SEXP four)
{
    Rprintf("\nstarting test2\n");
    Rcpp::IntegerVector itwo(two);
    Rcpp::IntegerVector ithree(three);
    Rcpp::IntegerVector ifour(four);
    Rcpp::CharacterVector ione(one);
    
    Rcpp::IntegerVector output(1);
    output[0] = 0;
    for (int i = 0; i < itwo.size(); i++)
    {
        output[0] += itwo[i] + ithree[i] + ifour[i];
    }
    std::ostringstream s;
    s << (char *) ione[0] << output[0];
    ione[0] = s.str().c_str();
    return ione;
}

#include <algorithm>
RcppExport SEXP /*int matrix*/ oa_type1(SEXP /*char*/ type, SEXP /*int*/ q, 
        SEXP /*int*/ ncol, SEXP /*int*/ n, SEXP /*bool*/ bRandom)
{
    SEXP output = R_NilValue;
    Rcpp::IntegerMatrix rcppA;
    oacpp::COrthogonalArray oa;
    try
    {
        int qlocal = Rcpp::as<int>(q);
        int ncollocal = Rcpp::as<int>(ncol);
        int nlocal = Rcpp::as<int>(n);
        std::string stype = Rcpp::as<std::string>(type);
        bool bRandomLocal = Rcpp::as<bool>(bRandom);
        
        if (stype == "bose")
        {
            oa.bose(qlocal, ncollocal, &nlocal);
        }
        else if (stype == "bosebush")
        {
            oa.bosebush(qlocal, ncollocal, &nlocal);
        }
        else if (stype == "bush")
        {
            oa.bush(qlocal, ncollocal, &nlocal);
        }
        else if (stype == "addelkemp3")
        {
            oa.addelkemp3(qlocal, ncollocal, &nlocal);
        }
        else if (stype == "addelkemp")
        {
            oa.addelkemp(qlocal, ncollocal, &nlocal);
        }
        else
        {
            throw std::runtime_error("Unrecognized orthogonal array algorithm in function oa_type1");
        }
        
        oarutils::convertToIntegerMatrix<int>(oa.getoa(), rcppA);
        if (bRandomLocal)
        {
            oarutils::randomizeOA(rcppA, qlocal);
        }
        output = rcppA;
    }
    catch (std::exception & e)
    {
        throw Rcpp::exception(e.what());
    }
    catch (...)
    {
        throw Rcpp::exception("Unknown Exception in oa_type1");
    }
    return output;
}

RcppExport SEXP /*int matrix*/ oa_type2(SEXP /*char*/ type, SEXP /*int*/ int1, SEXP /*int*/ q, SEXP /*int*/ ncol, SEXP /*int*/ n)
{
    Rcpp::IntegerMatrix rcppA;
    oacpp::COrthogonalArray oa;
    try
    { 
        int qlocal = Rcpp::as<int>(q);
        int ncollocal = Rcpp::as<int>(ncol);
        int nlocal = Rcpp::as<int>(n);
        int int1local = Rcpp::as<int>(int1);
        std::string stype = Rcpp::as<std::string>(type);
        if (stype == "bosebushl")
        {
            // int1 is lambda
            oa.bosebushl(int1local, qlocal, ncollocal, &nlocal);
        }
        else if (stype == "busht")
        {
            // int1 is str
            oa.busht(int1local, qlocal, ncollocal, &nlocal);
        }
        else if (stype == "addelkempn")
        {
            // int1 is akn
            oa.addelkempn(int1local, qlocal, ncollocal, &nlocal);
        }
        else
        {
            throw std::runtime_error("Unrecognized orthogonal array algorithm in oa_type2");
        }
        oarutils::convertToIntegerMatrix<int>(oa.getoa(), rcppA);
    }
    catch (std::exception & e)
    {
        throw Rcpp::exception(e.what());
    }
    catch (...)
    {
        throw Rcpp::exception("Unknown Message");
    }
    return rcppA;
}

