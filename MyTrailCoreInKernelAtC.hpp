//
//  MyTrailCoreInKernelAtC.hpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 23/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#ifndef MyTrailCoreInKernelAtC_hpp
#define MyTrailCoreInKernelAtC_hpp

#include <iostream>
#include "myParts.hpp"
#include "myTrailCoreInKernelAtCFilter.hpp"

using namespace std;

class MyTrailCoreInKernelAtC : public InKernelAtCFilter{
public:
    MyTrailCoreInKernelAtC(unsigned int aMaxWeight, KeccakFDCLC& aParent, KeccakFPropagation::DCorLC aDCorLC);

    void XPeers2Slices(const multisetSet aValuePatternForStartingKnot);

    void Case422(const multisetSet aValuePatternSetForStartingKnot);
    void Case532(const multisetSet aValuePatternSetForStaringKnot);


//    void test4Peers3Slices();
    
    void Case22(const multisetSet aValuePatternSetForStartingKnot);
    void Case222(const multisetSet aValuePatternSetForStartingKnot);
    
    void Case332();
    void Case442();

    void Case433(const multisetSet aValuePatternSetForStartingKnot);
    void Case4222(const multisetSet aValuePatternSetForStartingknot);
    void Case3322A(const multisetSet aValuePatternSetForStartingknot);
    void Case3322B(const multisetSet aValuePatternSetForStartingknot);
    void Case3322C(const multisetSet aValuePatternSetForStartingknot);
    
    void Case42222A(const multisetSet aValuePatternSetForStartingknot1,const multisetSet aValuePatternSetForStartingknot2);
    void Case42222B(const multisetSet aValuePatternSetForStartingknot);
    void Case42222C(const multisetSet aValuePatternSetForStartingknot);
    
    void Case33222A(const multisetSet aValuePatternSetForStartingknot, const multisetSet aValuePatternSetForStartingknot2);
    void Case33222B(const multisetSet aValuePatternSetForStartingknot);
    void Case33222C1(const multisetSet aValuePatternSetForStartingknot1,const multisetSet aValuePatternSetForStartingknot2);
    void Case33222C2(const multisetSet aValuePatternSetForStartingknot);
   
    void Case33222D1(const multisetSet aValuePatternSetForStartingknot,const multisetSet aValuePatternSetForStartingknot2);
    void Case33222D2(const multisetSet aValuePatternSetForStartingknot);
    
    //for 6 orbitals
    void Case6x(const multisetSet aValuePatternSetForStartingKnot);
    void XorbitalsPerslice2Bits(const multisetSet aValuePatternSetForStartingKnot, unsigned int nrOrbitals);
    
    void test();

protected:
    string fileName = "/Users/niklaus/Desktop/InKernelAtCTrailCoreSearch/Core-60.txt";
    string fileName2 = "/Users/niklaus/Desktop/InKernelAtCTrailCoreSearch/Core.txt";
};

#endif /* MyTrailCoreInKernelAtC_hpp */
