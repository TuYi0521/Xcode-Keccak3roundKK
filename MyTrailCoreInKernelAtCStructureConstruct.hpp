//
//  MyTrailCoreInKernelAtCStructureConstruct.hpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 23/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#ifndef MyTrailCoreInKernelAtCStructureConstruct_hpp
#define MyTrailCoreInKernelAtCStructureConstruct_hpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <iterator>

#include "Keccak-f.h"
#include "Keccak-fDCLC.h"
#include "Keccak-fPropagation.h"
#include "Keccak-fPositions.h"
#include "types.h"

#include "Keccak-fState.h"
#include "translationsymmetry.h"
using namespace std;

//typedef unsigned char RowValue;
//typedef UINT32 SliceValue;
typedef std::vector<std::vector<RowValue>> DualVector;
typedef std::vector<std::vector<std::vector<RowValue>>> TriVector;
typedef multiset <RowValue, greater <RowValue>> ValuePatternmultiset;
typedef set <ValuePatternmultiset> multisetSet;

struct StartingKnotInfo{
    //    bool isStartingKnot;
    vector<BitPosition> knotPoints;
    unsigned int orbitalMark;
//    vector<unsigned int> yOffset;
};

class InKernelAtCStructureConstruct: public KeccakFPropagation{
public:
    InKernelAtCStructureConstruct(unsigned int aMaxWeight, const KeccakFDCLC & aParent, KeccakFPropagation::DCorLC aDCorLC);
    void genInputforAllActiveSbox(DualVector slicePatternCase,TriVector& activeSboxAllCase);
    void printValueSlicePattern(multisetSet valuePattern);
    void twoSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern2);
    void threeSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern3);
    void fourSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern4);
    void fiveSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern5);
    //
    
    
    void generateValidSliceValuePattern(unsigned int nBit, multisetSet& patternSet);
    void initializeValuePatterns(void);
    void printSingleValuePattern_ForTest(const vector<RowValue> aRowChainOfValuePattern);
    unsigned int Sbox(unsigned int a);
    void differential_distribution_table_dir(int DDT[32][32]);

    void getAllSlicePatternsFromAValuePattern(const ValuePatternmultiset aValuePattern, set<SliceValue> & aAllSlicePatternSet);
    void getKnotPointsFromSlice(const SliceValue aSlice, vector<BitPosition>& aStartingKnotPoints);
    void getKnotPointsFromSlice(const SliceValue aSlice, const unsigned int nrSlice, vector<BitPosition>& knotPoints);
    void addPeerParameterOnRho(vector<BitPosition> aPeerAtA);
    bool recursiveYOffsetOfStartingKnot(vector<unsigned int>& yOffset);
    bool updateStartingKnot();
    bool updateStartingKnot(const unsigned int chooseCode);
    
    bool nextStructureOfStaringKnot();
    void completeStructureOfStartingKnot();
    
    
    bool nextStructureOfStaringKnot22();
    void completeStructureOfStartingKnot22();
    
    bool nextStructureOfChain22(unsigned int nrObitals);
    void completeStructureOfChain22(unsigned int nrObitals);
    
    bool constructingStaringKnotfor2Orbitals();
    void completeConstructingOfStartingKnotfor2Orbitals();
    
    void completeStructureOfOtherKnot();
    bool nextStructureOfOtherKnot();

    bool nextStructureOfOtherKnot433(BitPosition& aP5B);
    bool nextStructureOfOtherKnot4222();
    void completeStructureOfOtherKnot4222();
    
    
    bool constructingStaringKnot42222A();
    void completeConstructingOfStartingKnot42222A();
    
    

    bool nextP56OfOtherKnot42222B();
    void completeP56OfOtherKnot42222B();
    
    bool nextP56OfOtherKnot42222C();
    void completeP56OfOtherKnot42222C();
    
    
    bool nextStructureOfOtherKnot3322A();
    void completeStructureOfOtherKnot3322A();
    bool nextStructureOfOtherKnot3322B();
    void completeStructureOfOtherKnot3322B();
    
    bool nextStructureOfOtherKnot33222B();
    void completeStructureOfOtherKnot33222B();
    
    bool nextP456OfOtherKnot33222B();
    void completeP456OfOtherKnot33222B();
    
    bool nextP456OfOtherKnot33222C();
    void completeP456OfOtherKnot33222C();
    
    bool nextP4Q4OfOtherKnot33222C1();
    void completeP4Q4OfOtherKnot33222C1();
    
    bool nextP3Q3OfOtherKnot222();
    void completeP3Q3OfOtherKnot222();
    
    bool nextP6Q6OfOtherKnot33222A();
    void completeP6Q6OfOtherKnot33222A();
    
    bool nextP456OfOtherKnot33222D2();
    void completeP456OfOtherKnot33222D2();
    
    
    bool nextStructureOfOtherKnot3322C(BitPosition & Q4B, const BitPosition Q1B);
    void completeStructureOfOtherKnot3322C(const BitPosition Q4B);
    bool checkMappedToSameOrbitalCase3322C();
    bool checkMappedToSameKnotAtBCase433(vector<vector<BitPosition>>& aKnotAtB);
    bool checkMappedToSameOrbitalCase4222();
    bool checkQ5Q6MappedToSameOrbital();
    bool checkQ3P5Q4P6MappedToSameOrbital();
    bool checkP4P5P6MappedToSameKnot();
    
    bool checkMappedToSameKnotCase3322A();
    
    BitPosition getBitAtBFromBitAtA(BitPosition pA);
    BitPosition getBitAtAFromBitAtB(BitPosition pA);
    
    bool checkKnotInKernelAtC(vector<BitPosition> aKnot);
    bool valuePatternInKernelAtCCheck(const unsigned nrBits, const ValuePatternmultiset aValuePattern);
    ValuePatternmultiset  getValuePatternFromSlice(const SliceValue aSliceValue);
    SliceValue getSliceValueFromBitChain(vector<BitPosition> aBitPointsChain);

protected:
    /** Store all the valid value patterns of 2, 3, 4, 5 bits.
     */
    multisetSet valuePatternSet2;
    multisetSet valuePatternSet3;
    multisetSet valuePatternSet4;
    multisetSet valuePatternSet5;
    multisetSet valuePatternSet6;

//    BitPosition aP1, aQ1, aP2, aQ2, aP3, aQ3, aP4, aQ4, aP5, aQ5, aP6, aQ6, tempp;
//    BitPosition bP1, bQ1, bP2, bQ2, bP3, bQ3, bP4, bQ4, bP5, bQ5, bP6, bQ6;
    
    
    unsigned int maxWeight;
    unsigned long count = 0;
    vector<unsigned long> counts;
    unsigned long valuepatterncount=0;
    unsigned int startingKnotUpdateCounter;
    vector<unsigned int> peerParameterOnRho;

    vector<vector<BitPosition>> peersAtA;
//    StartingKnotInfo startingKnot;
    vector<vector<unsigned int>> yOffset;
    vector<BitPosition> startingKnotPoints;
    vector<BitPosition> startingKnotPoints2;
    vector<vector<BitPosition>> knotAtB433;



    bool isLastStructureOfStartingKnot;
    bool isLastStructureOfOtherKnot;
    bool isInitialStructure;
    bool isInitialStructureOfOtherKnot;
    
    bool isLastStructureOfStartingKnot2;
    bool isLastStructureOfOtherKnot2;
    bool isInitialStructure2;
    bool isInitialStructureOfOtherKnot2;
    
    
    bool isP5Found;
    bool isQ4Found;

    const DualVector sbox2YPosition {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 0}, {1, 2}, {1,3}, {1, 4}, {2, 0}, {2, 1},
        {2, 3}, {2, 4}, {3, 0}, {3, 1}, {3, 2}, {3, 4}, {4, 0}, {4, 1}, {4, 2}, {4, 3}
    };
    const DualVector sbox3YPosition {
        {0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 2, 1}, {0, 2, 3}, {0, 2, 4}, {0, 3, 1}, {0, 3, 2}, {0, 3, 4}, {0, 4, 1},
        {0, 4, 2}, {0, 4, 3}, {1, 0, 2}, {1, 0, 3}, {1, 0, 4}, {1, 2, 0}, {1, 2, 3}, {1, 2, 4}, {1, 3, 0}, {1, 3, 2},
        {1, 3, 4}, {1, 4, 0}, {1, 4, 2}, {1, 4, 3}, {2, 0, 1}, {2, 0, 3}, {2, 0, 4}, {2, 1, 0}, {2, 1, 3}, {2, 1, 4},
        {2, 3, 0}, {2, 3, 1}, {2, 3, 4}, {2, 4, 0}, {2, 4, 1}, {2, 4, 3}, {3, 0, 1}, {3, 0, 2}, {3, 0, 4}, {3, 1, 0},
        {3, 1, 2}, {3, 1, 4}, {3, 2, 0}, {3, 2, 1}, {3, 2, 4}, {3, 4, 0}, {3, 4, 1}, {3, 4, 2}, {4, 0, 1}, {4, 0, 2},
        {4, 0, 3}, {4, 1, 0}, {4, 1, 2}, {4, 1, 3}, {4, 2, 0}, {4, 2, 1}, {4, 2, 3}, {4, 3, 0}, {4, 3, 1}, {4, 3, 2}
    };
    const DualVector sbox4YPosition {
        {0, 1, 2, 3}, {0, 1, 2, 4}, {0, 1, 3, 2}, {0, 1, 3, 4}, {0, 1, 4, 2}, {0, 1, 4, 3},
        {0, 2, 1, 3}, {0, 2, 1, 4}, {0, 2, 3, 1}, {0, 2, 3, 4}, {0, 2, 4, 1}, {0, 2, 4, 3},
        {0, 3, 1, 2}, {0, 3, 1, 4}, {0, 3, 2, 1}, {0, 3, 2, 4}, {0, 3, 4, 1}, {0, 3, 4, 2},
        {0, 4, 1, 2}, {0, 4, 1, 3}, {0, 4, 2, 1}, {0, 4, 2, 3}, {0, 4, 3, 1}, {0, 4, 3, 2},
        {1, 0, 2, 3}, {1, 0, 2, 4}, {1, 0, 3, 2}, {1, 0, 3, 4}, {1, 0, 4, 2}, {1, 0, 4, 3},
        {1, 2, 0, 3}, {1, 2, 0, 4}, {1, 2, 3, 0}, {1, 2, 3, 4}, {1, 2, 4, 0}, {1, 2, 4, 3},
        {1, 3, 0, 2}, {1, 3, 0, 4}, {1, 3, 2, 0}, {1, 3, 2, 4}, {1, 3, 4, 0}, {1, 3, 4, 2},
        {1, 4, 0, 2}, {1, 4, 0, 3}, {1, 4, 2, 0}, {1, 4, 2, 3}, {1, 4, 3, 0}, {1, 4, 3, 2},
        {2, 0, 1, 3}, {2, 0, 1, 4}, {2, 0, 3, 1}, {2, 0, 3, 4}, {2, 0, 4, 1}, {2, 0, 4, 3},
        {2, 1, 0, 3}, {2, 1, 0, 4}, {2, 1, 3, 0}, {2, 1, 3, 4}, {2, 1, 4, 0}, {2, 1, 4, 3},
        {2, 3, 0, 1}, {2, 3, 0, 4}, {2, 3, 1, 0}, {2, 3, 1, 4}, {2, 3, 4, 0}, {2, 3, 4, 1},
        {2, 4, 0, 1}, {2, 4, 0, 3}, {2, 4, 1, 0}, {2, 4, 1, 3}, {2, 4, 3, 0}, {2, 4, 3, 1},
        {3, 0, 1, 2}, {3, 0, 1, 4}, {3, 0, 2, 1}, {3, 0, 2, 4}, {3, 0, 4, 1}, {3, 0, 4, 2},
        {3, 1, 0, 2}, {3, 1, 0, 4}, {3, 1, 2, 0}, {3, 1, 2, 4}, {3, 1, 4, 0}, {3, 1, 4, 2},
        {3, 2, 0, 1}, {3, 2, 0, 4}, {3, 2, 1, 0}, {3, 2, 1, 4}, {3, 2, 4, 0}, {3, 2, 4, 1},
        {3, 4, 0, 1}, {3, 4, 0, 2}, {3, 4, 1, 0}, {3, 4, 1, 2}, {3, 4, 2, 0}, {3, 4, 2, 1},
        {4, 0, 1, 2}, {4, 0, 1, 3}, {4, 0, 2, 1}, {4, 0, 2, 3}, {4, 0, 3, 1}, {4, 0, 3, 2},
        {4, 1, 0, 2}, {4, 1, 0, 3}, {4, 1, 2, 0}, {4, 1, 2, 3}, {4, 1, 3, 0}, {4, 1, 3, 2},
        {4, 2, 0, 1}, {4, 2, 0, 3}, {4, 2, 1, 0}, {4, 2, 1, 3}, {4, 2, 3, 0}, {4, 2, 3, 1},
        {4, 3, 0, 1}, {4, 3, 0, 2}, {4, 3, 1, 0}, {4, 3, 1, 2}, {4, 3, 2, 0}, {4, 3, 2, 1}
    };
    const DualVector sbox5YPosition {
        {0, 1, 2, 3, 4}, {0, 1, 2, 4, 3}, {0, 1, 3, 2, 4}, {0, 1, 3, 4, 2}, {0, 1, 4, 2, 3}, {0, 1, 4, 3, 2},
        {0, 2, 1, 3, 4}, {0, 2, 1, 4, 3}, {0, 2, 3, 1, 4}, {0, 2, 3, 4, 1}, {0, 2, 4, 1, 3}, {0, 2, 4, 3, 1},
        {0, 3, 1, 2, 4}, {0, 3, 1, 4, 2}, {0, 3, 2, 1, 4}, {0, 3, 2, 4, 1}, {0, 3, 4, 1, 2}, {0, 3, 4, 2, 1},
        {0, 4, 1, 2, 3}, {0, 4, 1, 3, 2}, {0, 4, 2, 1, 3}, {0, 4, 2, 3, 1}, {0, 4, 3, 1, 2}, {0, 4, 3, 2, 1},
        {1, 0, 2, 3, 4}, {1, 0, 2, 4, 3}, {1, 0, 3, 2, 4}, {1, 0, 3, 4, 2}, {1, 0, 4, 2, 3}, {1, 0, 4, 3, 2},
        {1, 2, 0, 3, 4}, {1, 2, 0, 4, 3}, {1, 2, 3, 0, 4}, {1, 2, 3, 4, 0}, {1, 2, 4, 0, 3}, {1, 2, 4, 3, 0},
        {1, 3, 0, 2, 4}, {1, 3, 0, 4, 2}, {1, 3, 2, 0, 4}, {1, 3, 2, 4, 0}, {1, 3, 4, 0, 2}, {1, 3, 4, 2, 0},
        {1, 4, 0, 2, 3}, {1, 4, 0, 3, 2}, {1, 4, 2, 0, 3}, {1, 4, 2, 3, 0}, {1, 4, 3, 0, 2}, {1, 4, 3, 2, 0},
        {2, 0, 1, 3, 4}, {2, 0, 1, 4, 3}, {2, 0, 3, 1, 4}, {2, 0, 3, 4, 1}, {2, 0, 4, 1, 3}, {2, 0, 4, 3, 1},
        {2, 1, 0, 3, 4}, {2, 1, 0, 4, 3}, {2, 1, 3, 0, 4}, {2, 1, 3, 4, 0}, {2, 1, 4, 0, 3}, {2, 1, 4, 3, 0},
        {2, 3, 0, 1, 4}, {2, 3, 0, 4, 1}, {2, 3, 1, 0, 4}, {2, 3, 1, 4, 0}, {2, 3, 4, 0, 1}, {2, 3, 4, 1, 0},
        {2, 4, 0, 1, 3}, {2, 4, 0, 3, 1}, {2, 4, 1, 0, 3}, {2, 4, 1, 3, 0}, {2, 4, 3, 0, 1}, {2, 4, 3, 1, 0},
        {3, 0, 1, 2, 4}, {3, 0, 1, 4, 2}, {3, 0, 2, 1, 4}, {3, 0, 2, 4, 1}, {3, 0, 4, 1, 2}, {3, 0, 4, 2, 1},
        {3, 1, 0, 2, 4}, {3, 1, 0, 4, 2}, {3, 1, 2, 0, 4}, {3, 1, 2, 4, 0}, {3, 1, 4, 0, 2}, {3, 1, 4, 2, 0},
        {3, 2, 0, 1, 4}, {3, 2, 0, 4, 1}, {3, 2, 1, 0, 4}, {3, 2, 1, 4, 0}, {3, 2, 4, 0, 1}, {3, 2, 4, 1, 0},
        {3, 4, 0, 1, 2}, {3, 4, 0, 2, 1}, {3, 4, 1, 0, 2}, {3, 4, 1, 2, 0}, {3, 4, 2, 0, 1}, {3, 4, 2, 1, 0},
        {4, 0, 1, 2, 3}, {4, 0, 1, 3, 2}, {4, 0, 2, 1, 3}, {4, 0, 2, 3, 1}, {4, 0, 3, 1, 2}, {4, 0, 3, 2, 1},
        {4, 1, 0, 2, 3}, {4, 1, 0, 3, 2}, {4, 1, 2, 0, 3}, {4, 1, 2, 3, 0}, {4, 1, 3, 0, 2}, {4, 1, 3, 2, 0},
        {4, 2, 0, 1, 3}, {4, 2, 0, 3, 1}, {4, 2, 1, 0, 3}, {4, 2, 1, 3, 0}, {4, 2, 3, 0, 1}, {4, 2, 3, 1, 0},
        {4, 3, 0, 1, 2}, {4, 3, 0, 2, 1}, {4, 3, 1, 0, 2}, {4, 3, 1, 2, 0}, {4, 3, 2, 0, 1}, {4, 3, 2, 1, 0}
    };
};

#endif /* MyTrailCoreInKernelAtCStructureConstruct_hpp */
