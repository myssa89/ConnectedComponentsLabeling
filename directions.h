/* 
 * File: directions.h
 * Author: Sammy EL GHAZZAL
 * Date: Started 05/07/2013
 * Purpose: Implements the inline functions to get neighbors in an image vector. 
 */


// This file contains inline function to access elements in the
// neighborhood of a particular element. Returns ERROR_CODE
// if the neighboor requested is not reachable (the element is 
// on the boundary).

#include <climits>

typedef unsigned int uint;

static const uint ERROR_CODE = UINT_MAX - 1;

inline uint GetN(uint curr, uint width) {
    if (curr / width == 0) {
        return ERROR_CODE;
    }   
    return curr - width;
}

inline uint GetW(uint curr, uint width) {
    if (curr % width == 0) {
        return ERROR_CODE;
    }
    return curr - 1;
}

inline uint GetNW(uint curr, uint width) {
    if (curr / width == 0 || curr % width == 0) {
        return ERROR_CODE;
    }
    return curr - width - 1;
}

inline uint GetNE(uint curr, uint width) {
    if (curr / width == 0 || (curr + 1) % width == 0) {
        return ERROR_CODE;
    }
    return curr - width + 1;
}
