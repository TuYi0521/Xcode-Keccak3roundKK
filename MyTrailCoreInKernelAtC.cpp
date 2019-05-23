//
//  MyTrailCoreInKernelAtC.cpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 23/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#include "translationsymmetry.h"
#include "time.h"
#include "MyTrailCoreInKernelAtC.hpp"
MyTrailCoreInKernelAtC::MyTrailCoreInKernelAtC(unsigned int aMaxWeight, KeccakFDCLC& aParent, KeccakFPropagation::DCorLC aDCorLC): InKernelAtCFilter(aMaxWeight, aParent,aDCorLC){

}

void MyTrailCoreInKernelAtC::XPeers2Slices(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);

        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
        }
    }
}

void MyTrailCoreInKernelAtC::Case422(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);

        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            //bit position
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            do {
                //!!!
                nextStructureOfStaringKnot();
                                knotsAtB.clear();
                                if (filterOnPeerRhoOffset_422()) {
                                    if (checkKnotsAtBInKernelAtC()) {
                                        if (updateSetOfMinimalStatesUpToNow()) {
                                            prepareOutputTrailCore();
                                            //Deal with all such trail cores.
                                            if (workCore.back().partialWeight <= maxWeight) {
                                                outputTrailCore(fileName);
                                            }
                                        }
                                    }
                                }
            } while (!isLastStructureOfStartingKnot);
        }
    }
}



void MyTrailCoreInKernelAtC::Case532(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);

        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            do {
                nextStructureOfStaringKnot();
                                knotsAtB.clear();
                                if (filterOnPeerRhoOffset_532()) {
                                    if (checkKnotsAtBInKernelAtC()) {
                                        if (updateSetOfMinimalStatesUpToNow()) {
                                            prepareOutputTrailCore();
                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                outputTrailCore(fileName);
                                            }
                                        }
                                    }

                                }
            } while (!isLastStructureOfStartingKnot);
        }
    }
}

void MyTrailCoreInKernelAtC::Case332(){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = valuePatternSet3.begin(); itOneValuePattern != valuePatternSet3.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);


        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot()) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if ((yOffset.size()==1)) {
                            isLastStructureOfOtherKnot = false;
                            isInitialStructureOfOtherKnot = false;
                            do {
                                if ((peersAtA.size() == 3) && (peerParameterOnRho.size()==3)) {
                                    if (nextStructureOfOtherKnot()) {
                                        knotsAtB.clear();
                                        if (filterOnPeerRhoOffset_332()) {
                                            if (checkKnotsAtBInKernelAtC()) {
                                                if (updateSetOfMinimalStatesUpToNow()) {
                                                    prepareOutputTrailCore();
                                                    if (workCore.back().partialWeight <= maxWeight) {
                                                        outputTrailCore(fileName);
                                                    }
                                                }
                                            }
                                        }
                                        peersAtA.pop_back();
                                        peerParameterOnRho.pop_back();
                                    }
                                }
                                else {
                                    cout << "Error in size of peersAtA!" << endl;
                                }
                            } while (!isLastStructureOfOtherKnot);
                            yOffset.pop_back();
                        }
                        else {
                            cout << "Error in size of yoffset!" << endl;
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}

void MyTrailCoreInKernelAtC::Case442(){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = valuePatternSet4.begin(); itOneValuePattern != valuePatternSet4.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);


        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot()) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        isLastStructureOfOtherKnot = false;
                        isInitialStructureOfOtherKnot = false;
                        if ((yOffset.size()==1) && (peersAtA.size()==4) && (peerParameterOnRho.size()==4)) {
                            do {
                                if (nextStructureOfOtherKnot()) {
                                    if ((yOffset.size()==2) && (peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                        knotsAtB.clear();
                                        if (filterOnPeerRhoOffset_442()) {
                                            if (checkKnotsAtBInKernelAtC()) {
                                                if (updateSetOfMinimalStatesUpToNow()) {
                                                    prepareOutputTrailCore();
                                                    if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                        outputTrailCore(fileName);
                                                    }
                                                }
                                            }
                                        }
                                        peersAtA.pop_back();
                                        peerParameterOnRho.pop_back();
                                    }
                                    else {
                                        cout << "Error in size of the other knot stage!" << endl;
                                    }
                                }
                            } while (!isLastStructureOfOtherKnot);
                            yOffset.pop_back();
                        }
                        else {
                            cout << "Error in size of peers or yOffsets at starting knot stage!" << endl;
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}



void MyTrailCoreInKernelAtC::Case3322C(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if ((yOffset.size()==1) && (peersAtA.size()==3)) {
                            if (checkMappedToSameOrbitalCase3322C()){
                                isInitialStructureOfOtherKnot = false;
                                isLastStructureOfOtherKnot = false;
                                isQ4Found = false;
                                BitPosition Q1B = getBitAtBFromBitAtA(peersAtA[0].back());
                                BitPosition Q4B(0, 0, Q1B.z);
                                do {
                                    if ((yOffset.size()<=2) && (peersAtA.size()==3) && (peerParameterOnRho.size()==3)) {
                                        if (nextStructureOfOtherKnot3322C(Q4B, Q1B)) {
                                            if ((peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                                if (filterOnPeerRhoOffset_3322C()) {
                                                    if (checkMappedToSameSlice3322C()) {
                                                        knotsAtB.clear();
                                                        if (checkKnotsAtBInKernelAtC()) {
                                                            if (knotsAtB.size()==4) {
                                                                if (updateSetOfMinimalStatesUpToNow()) {
                                                                    prepareOutputTrailCore();
                                                                    if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                        outputTrailCore(fileName);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }

                                                peersAtA.pop_back();//peer4
                                                peerParameterOnRho.pop_back();
                                                peersAtA.pop_back();//peer5
                                                peerParameterOnRho.pop_back();
                                            }
                                            else {
                                                cout << "Error of size on other knot stage!" << endl;
                                            }
                                        }
                                    }
                                    else {
                                        cout << "Size error in yOffset, peersAtA or peerParameterOnRho!" << endl;
                                    }
                                } while (!isLastStructureOfOtherKnot);
                            }
                        }
                        else {
                            cout << "Error in the size of yOffset and peersAtA!" << endl;
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}

void MyTrailCoreInKernelAtC::Case3322B(const multisetSet aValuePatternSet){

    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if ((yOffset.size() == 1) && (peersAtA.size() == 3)) {
                            isInitialStructureOfOtherKnot = false;
                            isLastStructureOfOtherKnot = false;
                            do {
                                if ((peersAtA.size() == 3) && (peerParameterOnRho.size() == 3)) {
                                    if (nextStructureOfOtherKnot3322B()) {
                                        if ((peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                            if (filterOnPeerRhoOffset_3322B()) {
                                                knotsAtB.clear();
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (knotsAtB.size()==4) {
                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                            prepareOutputTrailCore();
                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                outputTrailCore(fileName);
                                                            }
                                                        }
                                                    }
                                                }
                                            }

                                            peersAtA.pop_back();
                                            peersAtA.pop_back();
                                            peerParameterOnRho.pop_back();
                                            peerParameterOnRho.pop_back();
                                        }
                                        else {
                                            cout << "Error in size of other knot stage!" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << "Error in size on peersAtA!" << endl;
                                }
                            } while (!isLastStructureOfOtherKnot);
                            yOffset.pop_back();
                        }
                        else {
                            cout << "Error in yoffset or peersAtA!" << endl;

                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}

void MyTrailCoreInKernelAtC::Case3322A(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if (checkMappedToSameKnotCase3322A()){
                            if ((yOffset.size() == 1) && (peersAtA.size() == 3)) {
                                isInitialStructureOfOtherKnot = false;
                                isLastStructureOfOtherKnot = false;
                                do {
                                    if ((peersAtA.size() == 3) && (peerParameterOnRho.size() == 3)) {
                                        if (nextStructureOfOtherKnot3322A()) {
                                            if ((yOffset.size()==2) && (peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                                if (filterOnPeerRhoOffset_3322A()) {
                                                    knotsAtB.clear();
                                                    if (checkKnotsAtBInKernelAtC()) {
                                                        if (knotsAtB.size()==4) {
                                                            if (updateSetOfMinimalStatesUpToNow()) {
                                                                prepareOutputTrailCore();
                                                                if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                    outputTrailCore(fileName);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                peersAtA.pop_back();
                                                peersAtA.pop_back();
                                                peerParameterOnRho.pop_back();
                                                peerParameterOnRho.pop_back();
                                            }
                                            else {
                                                cout << "Error in size of other knot stage!" << endl;
                                            }
                                        }
                                    }
                                    else {
                                        cout << "Error in size on peersAtA!" << endl;
                                    }
                                } while (!isLastStructureOfOtherKnot);
                                yOffset.pop_back();
                            }
                            else {
                                cout << "Error in yoffset or peersAtA!" << endl;

                            }
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}


void MyTrailCoreInKernelAtC::Case4222(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);


        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot(4222)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if (checkMappedToSameOrbitalCase4222()){
                            
                            if ((yOffset.size() == 1) && (peersAtA.size() == 4)) {
                                isInitialStructureOfOtherKnot = false;
                                isLastStructureOfOtherKnot = false;
                                do {

                                    if (nextStructureOfOtherKnot4222()) {
                                        if ((yOffset.size()==2) && (peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                            if (filterOnPeerRhoOffset_4222()) {
                                                knotsAtB.clear();
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (knotsAtB.size()==4) {
                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                            prepareOutputTrailCore();
                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                outputTrailCore(fileName);
                                                            }
                                                        }

                                                    }
                                                }
                                            }
                                            peersAtA.pop_back();
                                            peerParameterOnRho.pop_back();
                                        }
                                        else {
                                            cout << "Error of size in other knot stage!" << endl;
                                        }
                                    }
                                } while (!isLastStructureOfOtherKnot);
                                yOffset.pop_back();
                            }
                            else {
                                cout << "Error in yoffset or peersAtA!" << endl;

                            }
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}


void MyTrailCoreInKernelAtC::Case433(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);


        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            while (updateStartingKnot(433)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        knotAtB433.clear();
                        if (checkMappedToSameKnotAtBCase433(knotAtB433)){
                            if ((yOffset.size() == 1) && (peersAtA.size() == 4)) {
                                isInitialStructureOfOtherKnot = false;
                                isLastStructureOfOtherKnot = false;
                                isP5Found = false;
                                BitPosition p5B(0,0,knotAtB433.back().back().z);
                                do {

                                    if (nextStructureOfOtherKnot433(p5B)) {
                                        if ((yOffset.size()==2) && (peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                            knotsAtB.clear();
                                            if (filterOnPeerRhoOffset_433()) {
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (updateSetOfMinimalStatesUpToNow()) {
                                                        prepareOutputTrailCore();
                                                        if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                            outputTrailCore(fileName);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        else {
                                            cout << "Error in size on other knot stage!" << endl;
                                        }
                                    }
                                } while (!isLastStructureOfOtherKnot);
                            }
                            else {
                                cout << "Error in yoffset or peersAtA!" << endl;
//                                return false;
                            }
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}



void MyTrailCoreInKernelAtC::Case6x(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        valuepatterncount++;
        cout<<"value pattern count:"<<valuepatterncount<<" = 2^"<<log(valuepatterncount)/log(2) <<endl;
        
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            //bit position
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            count = 0;
            do {
                //!!!
                count++;
                
                nextStructureOfStaringKnot();
                knotsAtB.clear();
                if (filterOnPeerRhoOffset_6x()) {
                     if (checkKnotsAtBInKernelAtC()) {
                        if (updateSetOfMinimalStatesUpToNow()) {
                            prepareOutputTrailCore();
                            //Deal with all such trail cores.
                            if (workCore.back().partialWeight <= maxWeight) {
                                outputTrailCore(fileName);
                            }
                        }
                    }
                }
            } while (!isLastStructureOfStartingKnot);
        }
        
        cout<<"structure for a value pattern count:"<<count<<"= 2^"<<log(count)/log(2)<<endl;
        counts.push_back(count);
    }
}

void MyTrailCoreInKernelAtC::XorbitalsPerslice2Bits(const multisetSet aValuePatternSet, unsigned int nrObitals){
    count = 0;
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
//            peersAtA.resize(nrObitals);
//            peerParameterOnRho.resize(nrObitals);
            //bit position
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            do {
                //!!!
                if(nextStructureOfStaringKnot22()){
                    
                    if (nrObitals>2) {
                        if ((peersAtA.size()==2) && (peerParameterOnRho.size()==2)) {
                            isInitialStructureOfOtherKnot = false;
                            isLastStructureOfOtherKnot = false;
                            do {
                                if (nextStructureOfChain22(nrObitals)) {
                                    if ((yOffset.size()==2) && (peersAtA.size()==nrObitals) && (peerParameterOnRho.size()==nrObitals)) {
                                        BitPosition qB(peersAtA.back()[1]);//q[nrObitals-1] at A
                                        qB.directRhoPi();//q at B
                                        BitPosition pB(peersAtA[0][0]);//p[0] at A
                                        pB.directRhoPi();//p at B
                                        //check q_nrObitals p1 same orbital
                                        if (checkMappedToSameOrbital(qB, pB)) {
                                            //filter v1 v2
                                            if (filterOnPeerRhoOffset_XorbitalsPerslice2Bits(nrObitals)){
                                                knotsAtB.clear();
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (knotsAtB.size()==nrObitals) {
                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                            prepareOutputTrailCore();
                                                            //Deal with all such trail cores.
                                                            if (workCore.back().partialWeight <=80) {
                                                                count++;
                                                                cout<<"weight:"<<workCore.back().partialWeight<<endl;
                                                                outputTrailCore(fileName);
                                                                if (workCore.back().partialWeight <=maxWeight) {
                                                                    weights.push_back(workCore.back().partialWeight);
                                                                    outputTrailCore(fileName2);
                                                                }
                                                                
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        
                                        
                                    }
                                    else {
                                        cout << "Error in peersAtA.size = nrorbitals!" << endl;
                                        
                                    }
                                    
                                    for (int i =2; i<nrObitals; i++) {
                                        peersAtA.pop_back();
                                        peerParameterOnRho.pop_back();
                                    }
                                    
                                }
                            } while (!isLastStructureOfOtherKnot);
                            yOffset.pop_back();
                        }
                        else {
                            cout << "Error in peersAtA.size = 2!" << endl;
                        }
                    }
                    else if (nrObitals ==2){
                        
                        BitPosition q1B(peersAtA[0].back());//q1 at A
                        q1B.directRhoPi();//q1 at B
                        BitPosition q2B(peersAtA[1].back());//q2 at A
                        q2B.directRhoPi();//q2 at B
                        
                        
                        if (checkMappedToSameOrbital(q1B, q2B)) {
                            //filter v1 v2
                            if ((peerParameterOnRho[0] + peerParameterOnRho[1])%64== 0){
                                if (checkKnotsAtBInKernelAtC()) {
                                    if (updateSetOfMinimalStatesUpToNow()) {
                                        prepareOutputTrailCore();
                                        //Deal with all such trail cores.
                                        if (workCore.back().partialWeight <= 80) {
                                            outputTrailCore(fileName);
                                        }
                                    }
                                }
                            }
                        }
                        
                    }
                    else{
                        cout << "One Orbital cannot satisfy" << endl;
                    }
                }
            }while (!isLastStructureOfStartingKnot);
        }
    }
    cout<<"total number of trails:"<<count<<endl;
    cout<<"total <=60 trails:"<<weights.size()<<endl;
}


void MyTrailCoreInKernelAtC::Case42222A(const multisetSet aValuePatternSet1,const multisetSet aValuePatternSet2){
    multisetSet :: iterator itOneValuePattern,itOneValuePattern2;
    for (itOneValuePattern = aValuePatternSet1.begin(); itOneValuePattern != aValuePatternSet1.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        
        valuepatterncount++;
        cout<<"value pattern count:"<<valuepatterncount<<" = 2^"<<log(valuepatterncount)/log(2) <<endl;
        
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            //bit position
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            do {
                //!!!
                nextStructureOfStaringKnot();
                if (filterOnPeerRhoOffset_422()) {
                    
                    for (itOneValuePattern2 = aValuePatternSet2.begin(); itOneValuePattern2 != aValuePatternSet2.end(); itOneValuePattern2 ++) {
                        set<SliceValue> allSlicePatternsForOneValuePattern2;
                        getAllSlicePatternsFromAValuePattern((*itOneValuePattern2), allSlicePatternsForOneValuePattern2);
                        
                        set<SliceValue> :: iterator itOneSlicePattern2;
                        for (itOneSlicePattern2 = allSlicePatternsForOneValuePattern2.begin(); itOneSlicePattern2 != allSlicePatternsForOneValuePattern2.end(); itOneSlicePattern2 ++) {
                            startingKnotPoints2.clear();
                            //bit position
                            getKnotPointsFromSlice((*itOneSlicePattern2), startingKnotPoints2);
                            isInitialStructure2 = false;
                            isLastStructureOfStartingKnot2 = false;
                            do {
                                //!!!
                                constructingStaringKnotfor2Orbitals();
                                if ((peersAtA.size()==6) && (peerParameterOnRho.size()==6)) {
                                    if (checkQ5Q6MappedToSameOrbital()) {
                                        if (filterOnPeerRhoOffset_22()) {
                                            //translate p5q6 p6q6
                                            for (int j = 1; j<64; j++) {
                                                peersAtA[4][0].z = (peersAtA[4][0].z +j)%64;
                                                peersAtA[4][1].z = (peersAtA[4][1].z +j)%64;
                                                peersAtA[5][0].z = (peersAtA[5][0].z +j)%64;
                                                peersAtA[5][1].z = (peersAtA[5][1].z +j)%64;
                                            
                                                knotsAtB.clear();
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (knotsAtB.size()==5) {
                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                            prepareOutputTrailCore();
                                                            //Deal with all such trail cores.
                                                            if (workCore.back().partialWeight <= maxWeight) {
                                                                outputTrailCore(fileName);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    peersAtA.pop_back();
                                    peersAtA.pop_back();
                                    peerParameterOnRho.pop_back();
                                    peerParameterOnRho.pop_back();
                                }
                            } while (!isLastStructureOfStartingKnot2);
                            yOffset.pop_back();
                        }
                    }
                }
            } while (!isLastStructureOfStartingKnot);
        }
    }
}

//void MyTrailCoreInKernelAtC::Case22(const multisetSet aValuePatternSet){
//    multisetSet :: iterator itOneValuePattern;
//    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
//        set<SliceValue> allSlicePatternsForOneValuePattern;
//        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
//
//        set<SliceValue> :: iterator itOneSlicePattern;
//        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
//            startingKnotPoints.clear();
//            yOffset.clear();
//            //bit position
//            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
//            isInitialStructure = false;
//            isLastStructureOfStartingKnot = false;
//            do {
//                //!!!
//                nextStructureOfStaringKnot();
//                knotsAtB.clear();
//                if ((peersAtA.size()==2) && (peerParameterOnRho.size()==2)) {
//
//                    if ((peerParameterOnRho[0] + peerParameterOnRho[1])%64== 0){
//                            if (checkKnotsAtBInKernelAtC()) {
//                                if (updateSetOfMinimalStatesUpToNow()) {
//                                    prepareOutputTrailCore();
//                                    //Deal with all such trail cores.
//                                    if (workCore.back().partialWeight <= maxWeight) {
//                                        outputTrailCore(fileName);
//                                    }
//                                }
//                            }
//                    }
//                }
//            }while (!isLastStructureOfStartingKnot);
//        }
//    }
//}


void MyTrailCoreInKernelAtC::Case22(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);

        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            //bit position
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            do {
                //!!!
                nextStructureOfStaringKnot();
                knotsAtB.clear();
                if ((peersAtA.size()==2) && (peerParameterOnRho.size()==2)) {

                    BitPosition q1B(peersAtA[0].back());//q1 at A
                    q1B.directRhoPi();//q1 at B
                    BitPosition q2B(peersAtA[1].back());//q2 at A
                    q2B.directRhoPi();//q2 at B
                   

                    if (checkMappedToSameOrbital(q1B, q2B)) {
                        //filter v1 v2
                        if ((peerParameterOnRho[0] + peerParameterOnRho[1])%64== 0){
                            if (checkKnotsAtBInKernelAtC()) {
                                if (updateSetOfMinimalStatesUpToNow()) {
                                    prepareOutputTrailCore();
                                    //Deal with all such trail cores.
                                    if (workCore.back().partialWeight <= maxWeight) {
                                        outputTrailCore(fileName);
                                    }
                                }
                            }
                        }
                    }
                }
            }while (!isLastStructureOfStartingKnot);
        }
    }
}

void MyTrailCoreInKernelAtC::Case222(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            //bit position
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            do {
                //!!!
                if(nextStructureOfStaringKnot()){
                    knotsAtB.clear();
                    if ((peersAtA.size()==2) && (peerParameterOnRho.size()==2)) {
                        isInitialStructureOfOtherKnot = false;
                        isLastStructureOfOtherKnot = false;
                        do {
                            if (nextP3Q3OfOtherKnot222()) {
                                if ((yOffset.size()==2) && (peersAtA.size()==3) && (peerParameterOnRho.size()==3)) {
                                    BitPosition q2B(peersAtA[1].back());//q2 at A
                                    q2B.directRhoPi();//q2 at B
                                    BitPosition q3B(peersAtA[2].back());//q3 at A
                                    q3B.directRhoPi();//q3 at B
                                    if (checkMappedToSameOrbital(q2B, q3B)) {
                                        //filter v1 v2
                                        if ((peerParameterOnRho[0] + peerParameterOnRho[2])%64== peerParameterOnRho[1]){
                                            if (checkKnotsAtBInKernelAtC()) {
                                                if (updateSetOfMinimalStatesUpToNow()) {
                                                    prepareOutputTrailCore();
                                                    //Deal with all such trail cores.
                                                    if (workCore.back().partialWeight <= maxWeight) {
                                                        outputTrailCore(fileName);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    
            
                                }
                                else {
                                    cout << "Error in peersAtA.size = 3!" << endl;
                                    
                                }
                                peersAtA.pop_back();
                                peerParameterOnRho.pop_back();
                            }
                        } while (!isLastStructureOfOtherKnot);
                        yOffset.pop_back();
                    }
                    else {
                        cout << "Error in peersAtA.size = 2!" << endl;
                        
                    }
                }
            }while (!isLastStructureOfStartingKnot);
        }
    }
}


//void MyTrailCoreInKernelAtC::Case22(const multisetSet aValuePatternSet){
//    multisetSet :: iterator itOneValuePattern;
//    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
//        set<SliceValue> allSlicePatternsForOneValuePattern;
//        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
//
//        set<SliceValue> :: iterator itOneSlicePattern;
//        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
//            startingKnotPoints.clear();
//            yOffset.clear();
//            //bit position
//            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
//            isInitialStructure = false;
//            isLastStructureOfStartingKnot = false;
//            do {
//                //!!!
//                nextStructureOfStaringKnot22();
//                knotsAtB.clear();
//                if ((peersAtA.size()==2) && (peerParameterOnRho.size()==2)) {
//                    bool find1;
//
//                    BitPosition q1B(peersAtA[0].back());//q1 at A
//                    q1B.directRhoPi();//q1 at B
//                    BitPosition q2B(peersAtA[1].back());//q2 at A
//                    q2B.directRhoPi();//q2 at B
//                    if ((q1B.z == q2B.z)&&(q1B.x == q2B.x)) {
//                        //                    if (q1B.x == q2B.x){
//                        if((q1B.y != q2B.y)){
//                            find1 = true;
//                        }
//                        else{
//                            find1 = false;
//                        }
//                    }
//                    else {
//                        find1 = false;
//                    }
//
//                    if (find1) {
//                        if ((peerParameterOnRho[0] + peerParameterOnRho[1])%64== 0){
//                            if (checkKnotsAtBInKernelAtC()) {
//                                if (updateSetOfMinimalStatesUpToNow()) {
//                                    prepareOutputTrailCore();
//                                    //Deal with all such trail cores.
//                                    if (workCore.back().partialWeight <= maxWeight) {
//                                        outputTrailCore(fileName);
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }while (!isLastStructureOfStartingKnot);
//            yOffset.pop_back();
//        }
//    }
//}





void MyTrailCoreInKernelAtC::Case42222B(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        
        valuepatterncount++;
        cout<<"value pattern count:"<<valuepatterncount<<" = 2^"<<log(valuepatterncount)/log(2) <<endl;
        
        set<SliceValue> :: iterator itOneSlicePattern;
        slicepatternForAvaluepattern=0;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            //updateStartingKnot里面额结构是怎么运作的
            count=0;
            slicepatternForAvaluepattern++;
            while (updateStartingKnot(4222)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    //改变yoffset[0]来构造starting knot 里的p点对应的q点
                    if (nextStructureOfStaringKnot()) {
                        count++;
                        //check q3''  q4'' same column
                        if (checkMappedToSameOrbitalCase4222()){
                            if ((yOffset.size() == 1) && (peersAtA.size() == 4)) {
                                isInitialStructureOfOtherKnot = false;
                                isLastStructureOfOtherKnot = false;
                                
                                do {
                                    if ((peersAtA.size() == 4) && (peerParameterOnRho.size() == 4)) {
                                        if (nextP56OfOtherKnot42222C()) {
                                            if ((peersAtA.size()==6) && (peerParameterOnRho.size()==6)) {
                                                if (checkQ5Q6MappedToSameOrbital()){
                                                    if (filterOnPeerRhoOffset_42222B()) {
                                                        knotsAtB.clear();
                                                        if (checkKnotsAtBInKernelAtC()) {
                                                            if (knotsAtB.size()==5) {
                                                                
                                                                if (updateSetOfMinimalStatesUpToNow()) {
                                                                    prepareOutputTrailCore();
                                                                    //                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                    if (workCore.back().partialWeight > 52) {
                                                                        outputTrailCore(fileName);
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                peersAtA.pop_back();
                                                peersAtA.pop_back();
                                                peerParameterOnRho.pop_back();
                                                peerParameterOnRho.pop_back();
                                            }
                                            else {
                                                cout << "Error in size of other knot stage!" << endl;
                                            }
                                        }
                                    }
                                    else {
                                        cout << "Error in size on peersAtA!" << endl;
                                    }
                                } while (!isLastStructureOfOtherKnot);
                                yOffset.pop_back();
                            }
                            else {
                                cout << "Error in yoffset or peersAtA!" << endl;
                                
                            }
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
            cout<<"structure for a value pattern count:"<<count<<"= 2^"<<log(count)/log(2)<<endl;
            counts.push_back(count);
        }
        cout<<"slice pattern counts for a value pattern:"<<slicepatternForAvaluepattern<<"= 2^"<<log(slicepatternForAvaluepattern)/log(2)<<endl;
    }
}


void MyTrailCoreInKernelAtC::Case42222C(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        valuepatterncount++;
        cout<<"value pattern count:"<<valuepatterncount<<" = 2^"<<log(valuepatterncount)/log(2) <<endl;
        
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            //bit position
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            count = 0;
            do {
                if (nextStructureOfStaringKnot()) {
                    count++;
                    if ((yOffset.size() == 1) && (peersAtA.size() == 4)) {
                        isInitialStructureOfOtherKnot = false;
                        isLastStructureOfOtherKnot = false;
                        do {
                            if ((peersAtA.size() == 4) && (peerParameterOnRho.size() == 4)) {
                                if (nextP56OfOtherKnot42222C()) {
                                    if ((peersAtA.size()==6) && (peerParameterOnRho.size()==6)) {
                                        if (checkQ3P5Q4P6MappedToSameOrbital()){
                                            if (filterOnPeerRhoOffset_42222C()) {
                                                knotsAtB.clear();
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (knotsAtB.size()==5) {
                                                        
                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                            prepareOutputTrailCore();
                                                            //                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                            if (workCore.back().partialWeight > 52) {
                                                                outputTrailCore(fileName);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        peersAtA.pop_back();
                                        peersAtA.pop_back();
                                        peerParameterOnRho.pop_back();
                                        peerParameterOnRho.pop_back();
                                    }
                                    else {
                                        cout << "Error in size of other knot stage!" << endl;
                                    }
                                }
                            }
                            else {
                                cout << "Error in size on peersAtA!" << endl;
                            }
                        } while (!isLastStructureOfOtherKnot);
                        yOffset.pop_back();
                    }
                    else {
                        cout << "Error in yoffset or peersAtA!" << endl;
                        
                    }
                }
            } while (!isLastStructureOfStartingKnot);
        }
        
        cout<<"structure for a value pattern count:"<<count<<"= 2^"<<log(count)/log(2)<<endl;
        counts.push_back(count);
    }
}


void MyTrailCoreInKernelAtC::Case33222A(const multisetSet aValuePatternSet, const multisetSet aValuePatternSet2){
    
    multisetSet :: iterator itOneValuePattern,itOneValuePattern2;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        valuepatterncount++;
        cout<<"value pattern count:"<<valuepatterncount<<" = 2^"<<log(valuepatterncount)/log(2) <<endl;
        
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        count=0;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            //轮流做p3
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if ((yOffset.size() == 1) && (peersAtA.size() == 3)) {
                            if ((peersAtA.size() == 3) && (peerParameterOnRho.size() == 3)) {
                                //filter 33
                                if ((peerParameterOnRho[0] == peerParameterOnRho[1])&&(peerParameterOnRho[2]== peerParameterOnRho[1])) {
                                
                                    //2 orbitals, validpatternset2
                                    for (itOneValuePattern2 = aValuePatternSet2.begin(); itOneValuePattern2 != aValuePatternSet2.end(); itOneValuePattern2 ++) {
                                        set<SliceValue> allSlicePatternsForOneValuePattern2;
                                        getAllSlicePatternsFromAValuePattern((*itOneValuePattern2), allSlicePatternsForOneValuePattern2);
                                        
                                        set<SliceValue> :: iterator itOneSlicePattern2;
                                        for (itOneSlicePattern2 = allSlicePatternsForOneValuePattern2.begin(); itOneSlicePattern2 != allSlicePatternsForOneValuePattern2.end(); itOneSlicePattern2 ++) {
                                            startingKnotPoints2.clear();
                                            //bit position
                                            getKnotPointsFromSlice((*itOneSlicePattern2), startingKnotPoints2);
                                            isInitialStructure2 = false;
                                            isLastStructureOfStartingKnot2 = false;
                                            count++;
                                            cout<<"structure for a value pattern count:"<<count<<"= 2^"<<log(count)/log(2)<<endl;
                                            counts.push_back(count);
                                            do {
                                                //!!!
                                                if(constructingStaringKnotfor2Orbitals()){
                                    
                                                    if ((peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
                                                        isInitialStructureOfOtherKnot = false;
                                                        isLastStructureOfOtherKnot = false;
                                                        do {
                                                            if (nextP6Q6OfOtherKnot33222A()) {
                                                                if ((yOffset.size()==3) && (peersAtA.size()==6) && (peerParameterOnRho.size()==6)) {
                                                                    BitPosition q5B(peersAtA[4].back());//q5 at A
                                                                    q5B.directRhoPi();//q5 at B
                                                                    BitPosition q6B(peersAtA[5].back());//q6 at A
                                                                    q6B.directRhoPi();//q6 at B
                                                                    if (checkMappedToSameOrbital(q5B, q6B)) {
                                                                        //filter v1 v2
                                                                        if ((peerParameterOnRho[3] + peerParameterOnRho[5])%64== peerParameterOnRho[4]){
                                                                            for (int j = 1; j<64; j++) {
                                                                                peersAtA[3][0].z = (peersAtA[3][0].z +j)%64;
                                                                                peersAtA[3][1].z = (peersAtA[3][1].z +j)%64;
                                                                                peersAtA[4][0].z = (peersAtA[4][0].z +j)%64;
                                                                                peersAtA[4][1].z = (peersAtA[4][1].z +j)%64;
                                                                                peersAtA[5][0].z = (peersAtA[5][0].z +j)%64;
                                                                                peersAtA[5][1].z = (peersAtA[5][1].z +j)%64;
                                                                                
                                                                                knotsAtB.clear();
                                                                                
                                                                                if (checkKnotsAtBInKernelAtC()) {
                                                                                    if (knotsAtB.size()==5) {
                                                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                                                            prepareOutputTrailCore();
                                                                                            //Deal with all such trail cores.
                                                                                            if (workCore.back().partialWeight <= maxWeight) {
                                                                                                outputTrailCore(fileName);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                    
                                                                    
                                                                }
                                                                else {
                                                                    cout << "Error in peersAtA.size = 6!" << endl;
                                                                    
                                                                }
                                                                peersAtA.pop_back();
                                                                peerParameterOnRho.pop_back();
                                                            }
                                                        } while (!isLastStructureOfOtherKnot);
                                                        yOffset.pop_back();
                                                    }
                                                    else {
                                                        cout << "Error in peersAtA.size = 5!" << endl;
                                                        
                                                    }
                                                    peersAtA.pop_back();
                                                    peerParameterOnRho.pop_back();
                                                    
                                                    peersAtA.pop_back();
                                                    peerParameterOnRho.pop_back();
                                                    
                                                }
                                            }while (!isLastStructureOfStartingKnot2);
                                            yOffset.pop_back();
                                        }
                                    }
                                }
                            }
                            else {
                                cout << "Error in peersAtA.size =3!" << endl;
                                
                            }
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
            
        }
        cout<<"structure for a value pattern count"<<endl;
        counts.push_back(count);
    }
}



void MyTrailCoreInKernelAtC::Case33222B(const multisetSet aValuePatternSet){
    
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            //轮流做p3
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        if ((yOffset.size() == 1) && (peersAtA.size() == 3)) {
                            isInitialStructureOfOtherKnot = false;
                            isLastStructureOfOtherKnot = false;
                            do {
                                if ((peersAtA.size() == 3) && (peerParameterOnRho.size() == 3)) {
                                    if (nextP456OfOtherKnot33222B()) {
                                        if ((peersAtA.size()==6) && (peerParameterOnRho.size()==6)) {
                                            if (filterOnPeerRhoOffset_33222B()) {
                                                knotsAtB.clear();
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (knotsAtB.size()==5) {
                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                            prepareOutputTrailCore();
//                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                            if (workCore.back().partialWeight > 52) {
                                                                outputTrailCore(fileName);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            
                                            peersAtA.pop_back();
                                            peersAtA.pop_back();
                                            peersAtA.pop_back();
                                            peerParameterOnRho.pop_back();
                                            peerParameterOnRho.pop_back();
                                            peerParameterOnRho.pop_back();
                                        }
                                        else {
                                            cout << "Error in size of other knot stage!" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << "Error in size on peersAtA!" << endl;
                                }
                            } while (!isLastStructureOfOtherKnot);
                            yOffset.pop_back();
                        }
                        else {
                            cout << "Error in yoffset or peersAtA!" << endl;
                            
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
        }
    }
}


void MyTrailCoreInKernelAtC::Case33222C1(const multisetSet aValuePatternSet, const multisetSet aValuePatternSet2){
    
    multisetSet :: iterator itOneValuePattern,itOneValuePattern2;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        valuepatterncount++;
        cout<<"value pattern count:"<<valuepatterncount<<" = 2^"<<log(valuepatterncount)/log(2) <<endl;
        
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        count=0;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            //轮流做p3
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        
                        if ((yOffset.size() == 1) && (peersAtA.size() == 3)) {
                            isInitialStructureOfOtherKnot = false;
                            isLastStructureOfOtherKnot = false;
                            do {
                                if ((peersAtA.size() == 3) && (peerParameterOnRho.size() == 3)) {
                                    if (nextP4Q4OfOtherKnot33222C1()) {
                                        if ((peersAtA.size()==4) && (peerParameterOnRho.size()==4)) {
                                            BitPosition q3B(peersAtA[2].back());//q1 at A
                                            q3B.directRhoPi();//q1 at B
                                            BitPosition q4B(peersAtA[3].back());//q2 at A
                                            q4B.directRhoPi();//q2 at B
                                            
                                            
                                            if (checkMappedToSameOrbital(q3B, q4B)) {
                                                
                                                //2 orbitals, validpatternset2
                                                for (itOneValuePattern2 = aValuePatternSet2.begin(); itOneValuePattern2 != aValuePatternSet2.end(); itOneValuePattern2 ++) {
                                                    set<SliceValue> allSlicePatternsForOneValuePattern2;
                                                    getAllSlicePatternsFromAValuePattern((*itOneValuePattern2), allSlicePatternsForOneValuePattern2);
                                                    
                                                    set<SliceValue> :: iterator itOneSlicePattern2;
                                                    for (itOneSlicePattern2 = allSlicePatternsForOneValuePattern2.begin(); itOneSlicePattern2 != allSlicePatternsForOneValuePattern2.end(); itOneSlicePattern2 ++) {
                                                        startingKnotPoints2.clear();
                                                        //bit position
                                                        getKnotPointsFromSlice((*itOneSlicePattern2), startingKnotPoints2);
                                                        isInitialStructure2 = false;
                                                        isLastStructureOfStartingKnot2 = false;
                                                        do {
                                                            //把p5p6弄进去
                                                            count++;
                                                            
                                                            
                                                            cout<<"structure for a value pattern count:"<<count<<"= 2^"<<log(count)/log(2)<<endl;
                                                            counts.push_back(count);
                                                            
                                                            if (constructingStaringKnotfor2Orbitals()){
                                                                for (int j = 1; j<64; j++) {
                                                                    peersAtA[4][0].z = (peersAtA[4][0].z +j)%64;
                                                                    peersAtA[4][1].z = (peersAtA[4][1].z +j)%64;
                                                                    peersAtA[5][0].z = (peersAtA[5][0].z +j)%64;
                                                                    peersAtA[5][1].z = (peersAtA[5][1].z +j)%64;
                                                                    
                                                                    
                                                                    
                                                                    if (checkMappedToSameSliceAfterRhoPi(peersAtA[0].back(), peersAtA[4].back(), peersAtA[5].back())) {
                                                                        
                                                                        if ((peersAtA.size()==6) && (peerParameterOnRho.size()==6)) {
                                                                            
                                                                            if (filterOnPeerRhoOffset_33222C1()) {
                                                                                knotsAtB.clear();
                                                                                if (checkKnotsAtBInKernelAtC()) {
                                                                                    if (knotsAtB.size()==5) {
                                                                                        
                                                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                                                            prepareOutputTrailCore();
                                                                                            //                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                                            if (workCore.back().partialWeight > 52) {
                                                                                                outputTrailCore(fileName);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                        else {
                                                                            cout << "Error in size of other knot stage!" << endl;
                                                                        }
                                                                        
                                                                    }
                                                                }
                                                                
                                                                peersAtA.pop_back();
                                                                peerParameterOnRho.pop_back();
                                                                
                                                                peersAtA.pop_back();
                                                                peerParameterOnRho.pop_back();
                                                            }
                                                        } while (!isLastStructureOfStartingKnot2);
                                                        yOffset.pop_back();
                                                    }
                                                }
                                                
                                            }
                                            // 删掉这一轮的p4q4
                                            peersAtA.pop_back();
                                            peerParameterOnRho.pop_back();
                                        }
                                        else {
                                            cout << "Error in P4Q4 on peersAtA!" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << "Error in peersAtA.size() == 3!" << endl;
                                }
                            } while (!isLastStructureOfOtherKnot);
                            yOffset.pop_back();
                        }
                        else {
                            cout << "Error in yoffset or peersAtA!" << endl;
                            
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
            
        }
        cout<<"structure for a value pattern count"<<endl;
        counts.push_back(count);
    }
}


void MyTrailCoreInKernelAtC::Case33222C2(const multisetSet aValuePatternSet){
    
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        valuepatterncount++;
        cout<<"value pattern count:"<<valuepatterncount<<" = 2^"<<log(valuepatterncount)/log(2) <<endl;
        
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        count=0;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            //轮流做p3
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        count++;
                        if ((yOffset.size() == 1) && (peersAtA.size() == 3)) {
                            isInitialStructureOfOtherKnot = false;
                            isLastStructureOfOtherKnot = false;
                            do {
                                if ((peersAtA.size() == 3) && (peerParameterOnRho.size() == 3)) {
                                    if (nextP456OfOtherKnot33222C()) {
                                        if ((peersAtA.size()==6) && (peerParameterOnRho.size()==6)) {
                                            if (filterOnPeerRhoOffset_33222C2()) {
                                                knotsAtB.clear();
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (knotsAtB.size()==5) {
                                                
                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                            prepareOutputTrailCore();
//                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                            if (workCore.back().partialWeight > 52) {
                                                                outputTrailCore(fileName);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            
                                            peersAtA.pop_back();
                                            peersAtA.pop_back();
                                            peersAtA.pop_back();
                                            peerParameterOnRho.pop_back();
                                            peerParameterOnRho.pop_back();
                                            peerParameterOnRho.pop_back();
                                        }
                                        else {
                                            cout << "Error in size of other knot stage!" << endl;
                                        }
                                    }
                                }
                                else {
                                    cout << "Error in size on peersAtA!" << endl;
                                }
                            } while (!isLastStructureOfOtherKnot);
                            yOffset.pop_back();
                        }
                        else {
                            cout << "Error in yoffset or peersAtA!" << endl;
                            
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
            
        }
        cout<<"structure for a value pattern count:"<<count<<"= 2^"<<log(count)/log(2)<<endl;
        counts.push_back(count);
    }
}

void MyTrailCoreInKernelAtC::Case33222D1(const multisetSet aValuePatternSet, const multisetSet aValuePatternSet2){
    
    multisetSet :: iterator itOneValuePattern,itOneValuePattern2;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        valuepatterncount++;
        cout<<"value pattern count:"<<valuepatterncount<<" = 2^"<<log(valuepatterncount)/log(2) <<endl;
        
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        set<SliceValue> :: iterator itOneSlicePattern;
        count=0;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            startingKnotUpdateCounter = 0;
            //轮流做p3
            while (updateStartingKnot(33221)) {
                isInitialStructure = false;
                isLastStructureOfStartingKnot = false;
                do {
                    if (nextStructureOfStaringKnot()) {
                        
                        if ((yOffset.size() == 1) && (peersAtA.size() == 3)) {
                            isInitialStructureOfOtherKnot = false;
                            isLastStructureOfOtherKnot = false;
                            
                            BitPosition q1B(peersAtA[0].back());//q1 at A
                            q1B.directRhoPi();//q1 at B
                            BitPosition q3B(peersAtA[2].back());//q3 at A
                            q3B.directRhoPi();//q1 at B
                           
                            if (checkMappedToSameOrbital(q1B, q3B)) {
                
                                do {
                                    if ((peersAtA.size() == 3) && (peerParameterOnRho.size() == 3)) {
                                        if (nextP4Q4OfOtherKnot33222C1()) {
                                            if ((peersAtA.size()==4) && (peerParameterOnRho.size()==4)) {
                                                //2 orbitals, validpatternset2
                                                for (itOneValuePattern2 = aValuePatternSet2.begin(); itOneValuePattern2 != aValuePatternSet2.end(); itOneValuePattern2 ++) {
                                                    set<SliceValue> allSlicePatternsForOneValuePattern2;
                                                    getAllSlicePatternsFromAValuePattern((*itOneValuePattern2), allSlicePatternsForOneValuePattern2);
                                                    
                                                    set<SliceValue> :: iterator itOneSlicePattern2;
                                                    for (itOneSlicePattern2 = allSlicePatternsForOneValuePattern2.begin(); itOneSlicePattern2 != allSlicePatternsForOneValuePattern2.end(); itOneSlicePattern2 ++) {
                                                        startingKnotPoints2.clear();
                                                        //bit position
                                                        getKnotPointsFromSlice((*itOneSlicePattern2), startingKnotPoints2);
                                                        isInitialStructure2 = false;
                                                        isLastStructureOfStartingKnot2 = false;
                                                        do {
                                                           //把p5p6弄进去
                                                            count++;
                                                            
                                                            
                                                            cout<<"structure for a value pattern count:"<<count<<"= 2^"<<log(count)/log(2)<<endl;
                                                            counts.push_back(count);
                                                            //same with 33222C1 to construct p5 p6 q5 q6
                                                            if (constructingStaringKnotfor2Orbitals()){
                                                                for (int j = 1; j<64; j++) {
                                                                    peersAtA[4][0].z = (peersAtA[4][0].z +j)%64;
                                                                    peersAtA[4][1].z = (peersAtA[4][1].z +j)%64;
                                                                    peersAtA[5][0].z = (peersAtA[5][0].z +j)%64;
                                                                    peersAtA[5][1].z = (peersAtA[5][1].z +j)%64;
                                                                
                                                                
                                                                    //check q4 q5 q6 at B same slice
                                                                    if (checkMappedToSameSliceAfterRhoPi(peersAtA[3].back(), peersAtA[4].back(), peersAtA[5].back())) {
                                                                        
                                                                        if ((peersAtA.size()==6) && (peerParameterOnRho.size()==6)) {
                                                                            
                                                                            if (filterOnPeerRhoOffset_33222D1()) {
                                                                                knotsAtB.clear();
                                                                                if (checkKnotsAtBInKernelAtC()) {
                                                                                    if (knotsAtB.size()==5) {
                                                                                        
                                                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                                                            prepareOutputTrailCore();
                                                                                            //                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                                                            if (workCore.back().partialWeight > 52) {
                                                                                                outputTrailCore(fileName);
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                        else {
                                                                            cout << "Error in size of other knot stage!" << endl;
                                                                        }
                                                                        
                                                                    }
                                                                }
                                                            
                                                                peersAtA.pop_back();
                                                                peerParameterOnRho.pop_back();
                                                            
                                                                peersAtA.pop_back();
                                                                peerParameterOnRho.pop_back();
                                                            }
                                                        } while (!isLastStructureOfStartingKnot2);
                                                        yOffset.pop_back();
                                                    }
                                                }
                                                
                                                
                                                // 删掉这一轮的p4q4
                                                peersAtA.pop_back();
                                                peerParameterOnRho.pop_back();
                                            }
                                            else {
                                                cout << "Error in P4Q4 on peersAtA!" << endl;
                                            }
                                        }
                                    }
                                    else {
                                        cout << "Error in peersAtA.size() == 3!" << endl;
                                    }
                                } while (!isLastStructureOfOtherKnot);
                                yOffset.pop_back();
                            }
                        }
                        else {
                            cout << "Error in yoffset or peersAtA!" << endl;
                            
                        }
                    }
                } while (!isLastStructureOfStartingKnot);
                yOffset.pop_back();
            }
            
        }
        cout<<"structure for a value pattern count"<<endl;
        counts.push_back(count);
    }
}


void MyTrailCoreInKernelAtC::Case33222D2(const multisetSet aValuePatternSet){
    multisetSet :: iterator itOneValuePattern;
    for (itOneValuePattern = aValuePatternSet.begin(); itOneValuePattern != aValuePatternSet.end(); itOneValuePattern ++) {
        valuepatterncount++;
        cout<<"value pattern count:"<<valuepatterncount<<" = 2^"<<log(valuepatterncount)/log(2) <<endl;
        
        set<SliceValue> allSlicePatternsForOneValuePattern;
        getAllSlicePatternsFromAValuePattern((*itOneValuePattern), allSlicePatternsForOneValuePattern);
        
        set<SliceValue> :: iterator itOneSlicePattern;
        for (itOneSlicePattern = allSlicePatternsForOneValuePattern.begin(); itOneSlicePattern != allSlicePatternsForOneValuePattern.end(); itOneSlicePattern ++) {
            startingKnotPoints.clear();
            yOffset.clear();
            //bit position
            getKnotPointsFromSlice((*itOneSlicePattern), startingKnotPoints);
            isInitialStructure = false;
            isLastStructureOfStartingKnot = false;
            count = 0;
            do {
                if (nextStructureOfStaringKnot()) {
                    count++;
                    if ((yOffset.size() == 1) && (peersAtA.size() == 3)) {
                        isInitialStructureOfOtherKnot = false;
                        isLastStructureOfOtherKnot = false;
                        do {
                            if ((peersAtA.size() == 3) && (peerParameterOnRho.size() == 3)) {
                                if (nextP456OfOtherKnot33222D2()) {
                                    if ((peersAtA.size()==6) && (peerParameterOnRho.size()==6)) {
                                        if (checkQ5Q6MappedToSameOrbital()){
                                            if (filterOnPeerRhoOffset_33222D2()) {
                                                knotsAtB.clear();
                                                if (checkKnotsAtBInKernelAtC()) {
                                                    if (knotsAtB.size()==5) {
                                                        
                                                        if (updateSetOfMinimalStatesUpToNow()) {
                                                            prepareOutputTrailCore();
                                                            //                                                            if ((workCore.back().partialWeight <= maxWeight) && (workCore.back().partialWeight > 52)) {
                                                            if (workCore.back().partialWeight > 52) {
                                                                outputTrailCore(fileName);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        peersAtA.pop_back();
                                        peersAtA.pop_back();
                                        peersAtA.pop_back();
                                        peerParameterOnRho.pop_back();
                                        peerParameterOnRho.pop_back();
                                        peerParameterOnRho.pop_back();
                                    }
                                    else {
                                        cout << "Error in size of other knot stage!" << endl;
                                    }
                                }
                            }
                            else {
                                cout << "Error in size on peersAtA!" << endl;
                            }
                        } while (!isLastStructureOfOtherKnot);
                        yOffset.pop_back();
                    }
                    else {
                        cout << "Error in yoffset or peersAtA!" << endl;
                        
                    }
                }
            } while (!isLastStructureOfStartingKnot);
        }
        
        cout<<"structure for a value pattern count:"<<count<<"= 2^"<<log(count)/log(2)<<endl;
        counts.push_back(count);
    }
}



void MyTrailCoreInKernelAtC::test(){
    //    XPeers2Slices(valuePatternSet3);//Checked
    //
    //    XPeers2Slices(valuePatternSet4);//Searched but not Checked
    //    Case422(valuePatternSet4);//Checked, Correct
    //    Case332();//Checked, Correct
    //    XPeers2Slices(valuePatternSet5);//Searched but not Checked//no such combination
    //    Case532(valuePatternSet5);
    //    Case442();
    //    Case433(valuePatternSet4);
    //    Case4222(valuePatternSet4);
    //    Case3322A(valuePatternSet3);
    //    Case3322B(valuePatternSet3);
    //    Case3322C(valuePatternSet3);
    clock_t start, finish;
    double duration;
    start = clock();
    
//    Case633(valuePatternSet6);//checked
    XorbitalsPerslice2Bits(valuePatternSet2, 7);
//    Case4222(valuePatternSet4);
//    Case42222B(valuePatternSet4);//checked
//    Case33222A(valuePatternSet3,valuePatternSet2);
//    Case33222B(valuePatternSet3);//checked
//    Case33222C1(valuePatternSet3,valuePatternSet2);//checked
//    Case33222C2(valuePatternSet3);//checked
//    Case33222D1(valuePatternSet3,valuePatternSet2);
//    Case33222D2(valuePatternSet3);//checked
//    Case42222C(valuePatternSet4);//checked
//    Case42222A(valuePatternSet4,valuePatternSet2);

//    Case22(valuePatternSet2);//checked

//    Case222(valuePatternSet2);
    finish = clock();
    duration = (double)(finish-start)/CLOCKS_PER_SEC;
    printf("%f seconds\n", duration);
    //    XPeers2Slices(valuePatternSet6);
    cout << "Hi!" << endl;
}
