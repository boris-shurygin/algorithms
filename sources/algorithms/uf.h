/**
* @file: uf.h
* Interface of union-find algorithms library
* @ingroup Algorithms
* @brief Implementation of Union-Find algorithms after lectures by Robert Segewick
*/
/*
* Algorithms library
* Copyright (C) 2015  Boris Shurygin
*/
#include <vector>

namespace Alg
{
    /**
     * Union-find data structure
     */
    template < class UFImplementation> class UF:
        protected UFImplementation
    {
    public:
        UF(UInt32 size) : UFImplementation(size){};   /**< Constructs UF data structure of given size */
        inline void unite(UInt32 i, UInt32 j);        /**< Connect the given nodes                    */
        inline bool areConnected(UInt32 i, UInt32 j); /**< Check if the given nodes are connected     */
    };

    template < class UFImplementation> 
    void UF<UFImplementation>::unite(UInt32 i, UInt32 j)
    {
        UFImplementation::unite(i, j);
    }

    template < class UFImplementation>
    bool UF<UFImplementation>::areConnected(UInt32 i, UInt32 j)
    {
        return UFImplementation::areConnected(i, j);
    }

    /** Naive implementation of union-find with plain array of component ids */
    class PlainUF
    {
    public:
        PlainUF(UInt32 size);
        void unite(UInt32 i, UInt32 j);        /**< Connect the given nodes */
        bool areConnected(UInt32 i, UInt32 j); /**< Check if the given nodes are connected */
    private:
        std::vector<UInt32> data;
    };

    /* TreeUF implementaiton options */
    enum TreeUFWeighted { NotWeighted, Weighted };
    enum TreeUFCompress { NoCompression, PathCompression};

    template <TreeUFWeighted Weighted> struct WeightsImpl;
    template <> struct WeightsImpl< NotWeighted > // Empty implementation
    {
        WeightsImpl(UInt32 size){}
        inline void include(UInt32 parent, UInt32 child){}; /**< Update the weights */
        /** Select parent and child items */
        inline void selectParent(UInt32 i, UInt32 j, UInt32 *parent, UInt32 *child) {};
    };
    template <> struct WeightsImpl< Weighted >
    {
        std::vector<UInt32> sizes;
        WeightsImpl(UInt32 size):sizes(size, 1){}
        
        /** Update the weights */
        inline void include(UInt32 parent, UInt32 child)
        {
            sizes[parent] += sizes[child];
        }

        /** Select parent and child items */
        inline void selectParent(UInt32 i, UInt32 j, UInt32 *parent, UInt32 *child)
        {
            if (sizes[i] > sizes[j])
            {
                *parent = i; *child = j;
            } else
            {
                *parent = j; *child = i;
            }
        }
    };

    template <TreeUFCompress compress> struct PathCompImpl;
    template <> struct PathCompImpl < NoCompression > 
    {
        static inline void pathCompression(std::vector<UInt32> &root, UInt32 i) {};
    };
    template <> struct PathCompImpl < PathCompression >
    {
        static inline void pathCompression(std::vector<UInt32> &root, UInt32 i) 
        {
            root[i] = root[root[i]];
        };
    };


    /** Tree based implementation of union-find */
    template <TreeUFWeighted is_weighted = Weighted,
              TreeUFCompress compress = PathCompression> class TreeUF
    {
    public:
        TreeUF(UInt32 size);
        void unite(UInt32 i, UInt32 j);        /**< Connect the given nodes */
        bool areConnected(UInt32 i, UInt32 j); /**< Check if the given nodes are connected */
    private:
        UInt32 findRoot(UInt32 i);
        std::vector<UInt32> root;
        WeightsImpl < is_weighted > weights;
    };
    
    /* Constructor implementation */
    template <TreeUFWeighted is_weighted, TreeUFCompress compress>
    TreeUF<is_weighted, compress>::TreeUF(UInt32 size):
        root(size), weights(size)
    {
        UInt32 i = 0;
        for (UInt32 &elem : root)
        {
            elem = i++;
        }
    }

    /* Connection check is universal for all option variations */
    template <TreeUFWeighted is_weighted, TreeUFCompress compress> 
    bool TreeUF<is_weighted, compress>::areConnected(UInt32 i, UInt32 j)
    {
        return findRoot(i) == findRoot(j);
    }

    /* Tree traversal may be used to compress the path */
    template <TreeUFWeighted is_weighted, TreeUFCompress compress>
    UInt32 TreeUF<is_weighted, compress>::findRoot(UInt32 i)
    {
        while (root[i] != i)
        {
            PathCompImpl<compress>::pathCompression(root, i);
            i = root[i];
        }
        return i;
    }

    /* Unite rotine depends on weighted-non weighted option */
    template <TreeUFWeighted is_weighted, TreeUFCompress compress>
    void TreeUF<is_weighted, compress>::unite(UInt32 i, UInt32 j)
    {
        if (i == j) return;
        
        UInt32 root_i = findRoot(i);
        UInt32 root_j = findRoot(j);

        weights.selectParent(root_i, root_j, &root_i, &root_j);

        root[root_j] = root_i;
        weights.include(root_i, root_j);
    }

    // Test template for all implementations of uf
    template <class UFImpl> bool uTestUF(UnitTest *utest_p)
    {
        UF< UFImpl> uf(200);
        UTEST_CHECK(utest_p, !uf.areConnected(1, 2));
        UTEST_CHECK(utest_p, !uf.areConnected(1, 4));

        // Group A: 1-2-3-4
        uf.unite(1, 2);
        uf.unite(2, 3);
        uf.unite(3, 4);

        // Group B: 5-6-7
        uf.unite(5, 6);
        uf.unite(6, 7);

        // Group C: 8-9-10
        uf.unite(8, 9);
        uf.unite(9, 10);

        UTEST_CHECK(utest_p, uf.areConnected(1, 2));
        UTEST_CHECK(utest_p, uf.areConnected(1, 4));
        UTEST_CHECK(utest_p, uf.areConnected(5, 6));
        UTEST_CHECK(utest_p, !uf.areConnected(4, 5));
        UTEST_CHECK(utest_p, !uf.areConnected(7, 8));
        UTEST_CHECK(utest_p, !uf.areConnected(5, 10));

        // unite groups B and C
        uf.unite(5, 9);

        UTEST_CHECK(utest_p, uf.areConnected(7, 8));
        UTEST_CHECK(utest_p, uf.areConnected(5, 10));

        return true;
    }
}