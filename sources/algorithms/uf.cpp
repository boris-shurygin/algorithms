/**
* @file: uf.cpp
* Implementation of Union-Find family of algorithms
*/
/*
* Copyright (C) 2015  Boris Shurygin
*/
#include "alg_iface.h"

namespace Alg
{
    PlainUF::PlainUF(UInt32 size) : data(size) 
    {
        UInt32 i = 0;
        for (UInt32 &elem : data)
        {
            elem = i++;
        }
    }
    
    /** Connect the given nodes */
    void PlainUF::unite(UInt32 i, UInt32 j)
    {
        // Trivial case
        if ( areConnected(i, j) )
            return;

        // Mark all 
        UInt32 new_group = data[i];
        UInt32 old_group = data[j];
        for ( UInt32 &elem : data )
        {
            if (elem == old_group) elem = new_group;
        }
    }
    
    /** Check if the given nodes are connected */        
    bool PlainUF::areConnected(UInt32 i, UInt32 j)
    {
        return data[i] == data[j];
    }
    
}