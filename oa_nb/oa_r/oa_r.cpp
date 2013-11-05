/**
 * @file oa_r.cpp
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */

#include "oa_r.h"

// Notes:  if q, ncol, n is a vector, Rcpp::as<int> should throw
// NA's are not caught
// infinites are not caught
// should do tests in C for all of these to determine what must be checked in R
RcppExport SEXP /*int matrix*/ oa_type1(SEXP /*char*/ type, SEXP /*int*/ q, SEXP /*int*/ ncol, SEXP /*int*/ n)
{
    Rcpp::IntegerMatrix rcppA = R_NilValue;
    oacpp::COrthogonalArray oa;
    try
    {
        int qlocal = Rcpp::as<int>(q);
        int ncollocal = Rcpp::as<int>(ncol);
        int nlocal = Rcpp::as<int>(n);
        std::string stype = Rcpp::as<std::string>(type);
        if (stype == "bose")
        {
            oa.bose(qlocal, ncollocal, &nlocal);
        }
        else if (stype == "bosebush")
        {
            oa.bosebush(qlocal, ncollocal,&nlocal);
        }
        else if (stype == "bush")
        {
            oa.bush(qlocal, ncollocal, &nlocal);
        }
        else if (stype == "addelkemp3")
        {
            oa.addelkemp3(qlocal, ncollocal, &nlocal);
        }
        else if (stype == "addelkemp_c")
        {
            oa.addelkemp(qlocal, ncollocal, &nlocal);
        }
        else
        {
            throw new std::runtime_error("Unrecognized orthogonal array algorithm in oa_type1");
        }
        rcppA = oarutils::convertToIntegerMatrix<int>(oa.getoa());
    }
    catch (std::exception & e)
    {
        throw new Rcpp::exception(e.what());
    }
    catch (...)
    {
        throw new Rcpp::exception("Unknown Message");
    }
    return rcppA;
}

RcppExport SEXP /*int matrix*/ oa_type2(SEXP /*char*/ type, SEXP /*int*/ int1, SEXP /*int*/ q, SEXP /*int*/ ncol, SEXP /*int*/ n)
{
    Rcpp::IntegerMatrix rcppA = R_NilValue;
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
            throw new std::runtime_error("Unrecognized orthogonal array algorithm in oa_type2");
        }
        rcppA = oarutils::convertToIntegerMatrix<int>(oa.getoa());
    }
    catch (std::exception & e)
    {
        throw new Rcpp::exception(e.what());
    }
    catch (...)
    {
        throw new Rcpp::exception("Unknown Message");
    }
    return rcppA;
}

