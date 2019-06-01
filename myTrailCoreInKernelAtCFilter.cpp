//
//  myTrailCoreInKernelAtCFilter.cpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 23/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#include "translationsymmetry.h"
#include "myTrailCoreInKernelAtCFilter.hpp"

InKernelAtCFilter::InKernelAtCFilter(unsigned int aMaxWeight, KeccakFDCLC& aParent, KeccakFPropagation::DCorLC aDCorLC):InKernelAtCStructureConstruct(aMaxWeight, aParent, aDCorLC){
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_XPeers2Slices(){
    if (peerParameterOnRho.size() > 0) {
        unsigned int lastPeerParameter = peerParameterOnRho.back();
        for (int i = 0; i < peerParameterOnRho.size(); i++) {
            if (lastPeerParameter != peerParameterOnRho[i]) {
                return false;
            }
        }
        return true;
    }
    else {
        cout << "Error! Less than 1 peer parameter!" << endl;
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_22(){
    if (peerParameterOnRho[4] == peerParameterOnRho[6]) {
        return true;
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_422(){
    if (peerParameterOnRho.size() == 4) {
        unsigned int value1 = peerParameterOnRho[0];
        bool find1 = false, find2 = false;
        vector<unsigned int> aParameterSet;
        for (int i=1; i<peerParameterOnRho.size(); i++) {
            if (peerParameterOnRho[i] == value1) {
                find1 = true;
            }
            else {
                aParameterSet.push_back(peerParameterOnRho[i]);
            }
        }
        if (aParameterSet.size() == 2) {
            if (aParameterSet[0] == aParameterSet[1]) {
                find2 = true;
            }
            if (find1 && find2) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        if (!isLastStructureOfStartingKnot) {
            cout << "Error! Less than 1 peer parameter!" << endl;
        }
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_6x(){
    if (peerParameterOnRho.size() == 6) {
        //        cout<<"attempt"<<endl;
        unsigned int value1 = peerParameterOnRho[0];
        //        cout<<"v1:"<<value1<<endl;
        bool find1 = false, find2 = false, find3 = false;
        vector<unsigned int> aParameterSet1,aParameterSet2,aParameterSet3,aParameterSet22;
        for (int i=0; i<peerParameterOnRho.size(); i++) {
            //            cout<<"v:"<<peerParameterOnRho[i]<<endl;
            if (peerParameterOnRho[i] == value1) {
                aParameterSet1.push_back(peerParameterOnRho[i]);
            }
            else {
                aParameterSet2.push_back(peerParameterOnRho[i]);
            }
        }
        
        unsigned int value2 = aParameterSet2[0];
        for (int i=0; i<aParameterSet2.size(); i++) {
            //            cout<<"v:"<<peerParameterOnRho[i]<<endl;
            if (aParameterSet2[i] == value2) {
                
                aParameterSet22.push_back(aParameterSet2[i]);
            }
            else{
                aParameterSet3.push_back(aParameterSet2[i]);
            }
        }
        
        
        
        if (aParameterSet1.size() == 3) {
            
            if ((aParameterSet1[0] == aParameterSet1[1]) && (aParameterSet1[0]== aParameterSet1[2])) {
                
                find1 = true;
            }
            //            cout<<"find1:"<<find1<<endl;
            
            
            // below need to be corrected
            if (aParameterSet2.size() == 3) {
                if ((aParameterSet2[0] == aParameterSet2[1]) && ( aParameterSet2[0]== aParameterSet2[2])) {
                    
                    find2 = true;
                }
                if (find1 && find2) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        //642
        else if (aParameterSet1.size() == 4) {
            
            if ((aParameterSet1[0] == aParameterSet1[1]) && (aParameterSet1[0]== aParameterSet1[2])&& (aParameterSet1[0]== aParameterSet1[3])) {
                
                find1 = true;
            }
            //            cout<<"find1:"<<find1<<endl;
            
            
            // below need to be corrected
            if (aParameterSet2.size() == 2) {
                if (aParameterSet2[0] == aParameterSet2[1]) {
                    
                    find2 = true;
                }
                if (find1 && find2) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        //6222
        else if (aParameterSet1.size() == 2) {
            
            if (aParameterSet1[0] == aParameterSet1[1]) {
                
                find1 = true;
            }
            //            cout<<"find1:"<<find1<<endl;
            
            
            // below need to be corrected
            if (aParameterSet22.size() == 2) {
                if (aParameterSet22[0] == aParameterSet22[1]) {
                    
                    find2 = true;
                }
                if (aParameterSet3.size() == 2) {
                    if (aParameterSet3[0] == aParameterSet3[1]) {
                        
                        find3 = true;
                    }
                    
                    
                    if (find1 && find2 && find3) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }
            else{
                return false;
            }
            
            
        }
        else{
            return false;
        }
    }
    else {
        if (!isLastStructureOfStartingKnot) {
            cout << "Error! Less than 1 peer parameter!" << endl;
        }
        return false;
    }
}



bool InKernelAtCFilter::filterOnPeerRhoOffset_332(){
    if ((peersAtA.size()==4) && (peerParameterOnRho.size()==4)) {
        if (peerParameterOnRho[0] == peerParameterOnRho[1]) {
            if (peerParameterOnRho[2] == ((peerParameterOnRho[0] + 64 -  peerParameterOnRho[3])%64)) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        if (!isLastStructureOfStartingKnot) {
            cout << "Error! Less than 1 peer parameter!" << endl;
        }
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_532(){
    if ((peersAtA.size()==5) && (peerParameterOnRho.size()==5)) {
        vector<vector<int>> index{{0,1,2,3,4}, {0,1,3,2,4}, {0,2,3,1,4}, {1,2,3,0,4}, {0,1,4,2,3}, {0,2,4,1,3}, {1,2,4,0,3}, {0,3,4,1,2}, {1,3,4,0,2}, {2,3,4,0,1}};
        for (int i=0; i<10; i++) {
            vector<unsigned int> v(5,0);
            for (int j=0; j<5; j++) {
                v[j] = peerParameterOnRho[index[i][j]];
            }
            if (((v[0]==v[1]) && (v[1]==v[2])) && (v[3]==v[4]) && (v[0]!=v[4])) {
                return true;
            }
        }
        return false;
    }
    else {
        if (!isLastStructureOfStartingKnot) {
            cout << "Error! Less than 5 peer parameter!" << endl;
        }
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_442(){
    if ((peerParameterOnRho[0]) == (peerParameterOnRho[1])) {
        if ((peerParameterOnRho[1]) == (peerParameterOnRho[2])) {
            if ((peerParameterOnRho[0]) == ((peerParameterOnRho[3]+peerParameterOnRho[4])%64)) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_433(){
    if ((peerParameterOnRho[0]) == (peerParameterOnRho[1])) {
        if ((peerParameterOnRho[2]) == (peerParameterOnRho[3])) {
            if ((peerParameterOnRho[2]) == ((peerParameterOnRho[0]+64-peerParameterOnRho[4])%64)) {
                return true;
            }
            else {
                return false;
            }
//            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_4222(){
    if ((peerParameterOnRho[2]) == (peerParameterOnRho[3])) {
        if ((peerParameterOnRho[1]) == ((peerParameterOnRho[0]+peerParameterOnRho[4])%64)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_42222B(){
    if ((peerParameterOnRho[2]) == (peerParameterOnRho[3])) {
        if (((peerParameterOnRho[0]+peerParameterOnRho[5])%64) == ((peerParameterOnRho[1]+peerParameterOnRho[4])%64)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_42222C(){
    if (peerParameterOnRho[3] == ((peerParameterOnRho[1]+peerParameterOnRho[5])%64)) {
        if (((peerParameterOnRho[0]+peerParameterOnRho[4])%64) == peerParameterOnRho[2]) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_33222A(){
    if ((peerParameterOnRho[0] == peerParameterOnRho[1]) && (peerParameterOnRho[0] == peerParameterOnRho[2])) {
        if (peerParameterOnRho[3] == (peerParameterOnRho[5]+peerParameterOnRho[4])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_33222B(){
    if (peerParameterOnRho[0] == peerParameterOnRho[1]) {
        if (peerParameterOnRho[0] == (peerParameterOnRho[2]+peerParameterOnRho[3]+peerParameterOnRho[4]+peerParameterOnRho[5])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}


bool InKernelAtCFilter::filterOnPeerRhoOffset_33222C1(){
    if (peerParameterOnRho[4] == peerParameterOnRho[5]) {
        if (((peerParameterOnRho[1]+peerParameterOnRho[3])%64) == peerParameterOnRho[2]) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_33222C2(){
    if (peerParameterOnRho[0] == (peerParameterOnRho[1]+peerParameterOnRho[3])%64) {
        if (peerParameterOnRho[0] == (peerParameterOnRho[2]+peerParameterOnRho[4]+peerParameterOnRho[5])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}





bool InKernelAtCFilter::filterOnPeerRhoOffset_33222D1(){
    if ((peerParameterOnRho[0]) == (peerParameterOnRho[2])) {
        if (peerParameterOnRho[4] == peerParameterOnRho[5]) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_33222D2(){
if (((peerParameterOnRho[0]+peerParameterOnRho[3])%64) == ((peerParameterOnRho[1]+peerParameterOnRho[4])%64)) {
        if (((peerParameterOnRho[2]+peerParameterOnRho[5])%64) == ((peerParameterOnRho[1]+peerParameterOnRho[4])%64)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}



bool InKernelAtCFilter::filterOnPeerRhoOffset_5322A(){
    if ((peerParameterOnRho[0] == peerParameterOnRho[1]) && (peerParameterOnRho[0] == peerParameterOnRho[2])) {
        if (peerParameterOnRho[4] == (peerParameterOnRho[5]+peerParameterOnRho[3])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}


bool InKernelAtCFilter::filterOnPeerRhoOffset_5322B(){
    if ((peerParameterOnRho[0] == peerParameterOnRho[1]) && (peerParameterOnRho[3] == peerParameterOnRho[4])) {
        if (peerParameterOnRho[0] == (peerParameterOnRho[5]+peerParameterOnRho[2])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_4422A(){
  if ((peerParameterOnRho[0] == peerParameterOnRho[1]) && (peerParameterOnRho[0] == peerParameterOnRho[2])) {
        if (peerParameterOnRho[0] == (peerParameterOnRho[3]+peerParameterOnRho[4]+peerParameterOnRho[6])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_4422B(){
    if (peerParameterOnRho[0] == peerParameterOnRho[1]) {
        if ((peerParameterOnRho[2]+peerParameterOnRho[4])%64 == (peerParameterOnRho[5]+peerParameterOnRho[3])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_4332A(){
  if ((peerParameterOnRho[0] == peerParameterOnRho[1]) && (peerParameterOnRho[0] == peerParameterOnRho[2])) {
        if (peerParameterOnRho[4] == peerParameterOnRho[5]) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_4332B(){
    if ((peerParameterOnRho[0]) == (peerParameterOnRho[1]) && (peerParameterOnRho[2] == peerParameterOnRho[3])) {
      if ((peerParameterOnRho[2]+peerParameterOnRho[4])%64 == (peerParameterOnRho[5]+peerParameterOnRho[0])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_4332C(){
    if ((peerParameterOnRho[2]) == (peerParameterOnRho[3]) && (peerParameterOnRho[4] == peerParameterOnRho[5])) {
        if (peerParameterOnRho[0] == (peerParameterOnRho[1]+peerParameterOnRho[4])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}


bool InKernelAtCFilter::filterOnPeerRhoOffset_3333A(){
    if ((peerParameterOnRho[0]) == (peerParameterOnRho[2]) && (peerParameterOnRho[0] == peerParameterOnRho[1])) {
        if ((peerParameterOnRho[3]) == (peerParameterOnRho[4]) && (peerParameterOnRho[3] == peerParameterOnRho[5])) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}


bool InKernelAtCFilter::filterOnPeerRhoOffset_3333B(){
    if ((peerParameterOnRho[0] == peerParameterOnRho[1]) && (peerParameterOnRho[4] == peerParameterOnRho[5])) {
      if ((peerParameterOnRho[2]+peerParameterOnRho[3])%64 == (peerParameterOnRho[0]+peerParameterOnRho[4])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_3333C(){
    if ((peerParameterOnRho[1]) == (peerParameterOnRho[2]) && (peerParameterOnRho[4] == peerParameterOnRho[5])) {
      if ((peerParameterOnRho[0]+peerParameterOnRho[3])%64 == (peerParameterOnRho[1]+peerParameterOnRho[4])%64) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}


bool InKernelAtCFilter::filterOnPeerRhoOffset_3322A(){
    if ((peerParameterOnRho[0]) == (peerParameterOnRho[1])) {
        if ((peerParameterOnRho[2]) == ((peerParameterOnRho[0]+128-peerParameterOnRho[3]-peerParameterOnRho[4])%64)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::filterOnPeerRhoOffset_3322B(){
    if ((peerParameterOnRho[1]) == ((peerParameterOnRho[0]+64-peerParameterOnRho[3])%64)) {
        if ((peerParameterOnRho[2]) == ((peerParameterOnRho[0]+64-peerParameterOnRho[4])%64)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}


bool InKernelAtCFilter::filterOnPeerRhoOffset_3322C(){
    if ((peerParameterOnRho[1]) == (peerParameterOnRho[2])) {
        if ((peerParameterOnRho[3]) == ((64-peerParameterOnRho[4])%64)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::checkMappedToSameSlice3322C(){
    BitPosition q5B(peersAtA.back().back());//q5 at A
    q5B.directRhoPi();
    BitPosition q1B(peersAtA[0].back());//q1 at A
    q1B.directRhoPi();
    if ((q1B.z) == (q5B.z)) {
        return true;
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::checkMappedToSameSliceAfterRhoPi(BitPosition p1, BitPosition p2){
   
    p1.directRhoPi();
    p2.directRhoPi();
    if ((p1.z) == (p2.z)) {
        return true;
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::checkMappedToSameSliceAfterRhoPi(BitPosition p1, BitPosition p2, BitPosition p3, BitPosition p4){
    
    p1.directRhoPi();
    p2.directRhoPi();
    p3.directRhoPi();
    p4.directRhoPi();
    if ((p1.z) == (p2.z) && (p1.z) == (p3.z) && (p1.z) == (p4.z)) {
        return true;
    }
    else {
        return false;
    }
}



bool InKernelAtCFilter::filterOnPeerRhoOffset_XorbitalsPerslice2Bits(unsigned int nrorbitals){
    unsigned int sum = 0;
    for (int i=0; i<nrorbitals; i++) {
        sum += peerParameterOnRho[i];
    }
    
    
    if ((sum % 64) == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool InKernelAtCFilter::checkMappedToSameSliceAfterRhoPi(BitPosition p1, BitPosition p2, BitPosition p3){
    
    p1.directRhoPi();
    p2.directRhoPi();
    p3.directRhoPi();
    if ( (p1.z == p2.z) && (p1.z == p3.z) ) {
        return true;
    }
    else {
        return false;
    }
}


bool InKernelAtCFilter::checkMappedToSameOrbital(BitPosition point1, BitPosition point2){
   
    if ((point1.z == point2.z)&&(point1.x == point2.x)) {
        if((point1.y != point2.y)){
            return true;
        }
        else{
            return false;
        }
    }
    else {
        return false;
    }
}




bool InKernelAtCFilter::populateKnotsAtBStep1(){
    //pq to p'' q'' to check
    bitSetForMinimalStateB.clear();
    for (unsigned int nrPeers = 0; nrPeers < peersAtA.size(); nrPeers ++) {
        if (peersAtA[nrPeers].size() != 2) {
            cout << "Error! There aren't 2 bits at one peer!" << endl;
            return false;
        }
        else {
            for (unsigned int nrBits = 0; nrBits < peersAtA[nrPeers].size(); nrBits ++) {
                BitPosition pB(peersAtA[nrPeers][nrBits]);//p
                pB.directRhoPi();//p"
                knotsAtB[pB.z].bitsChain.push_back(pB);
                knotsAtB[pB.z].nrBits++;
                
                bitSetForMinimalStateB.insert(pB);
            }
        }
    }
    return true;
}

bool InKernelAtCFilter::populateKnotsAtBStep2(){
    map<unsigned int, KnotAtBInfo>::iterator itKnot;
    for (itKnot = knotsAtB.begin(); itKnot != knotsAtB.end(); itKnot++) {
        if ((itKnot->second).nrBits >= 2) {
            itKnot->second.sliceValue = getSliceValueFromBitChain(itKnot->second.bitsChain);
            itKnot->second.valuePattern = getValuePatternFromSlice(itKnot->second.sliceValue);
            itKnot->second.isInKernelAtC = valuePatternInKernelAtCCheck(itKnot->second.nrBits, itKnot->second.valuePattern);
        }
        else {
            cout << "Error! Less than 2 bits in one knot!" << endl;
            return false;
        }
    }
    return true;
}

bool InKernelAtCFilter::checkKnotsAtBInKernelAtC(){
    if (populateKnotsAtBStep1() && populateKnotsAtBStep2()) {
        map<unsigned int, KnotAtBInfo>::iterator itKnot;
        for (itKnot = knotsAtB.begin(); itKnot != knotsAtB.end(); itKnot++) {
            if (!itKnot->second.isInKernelAtC) {
//                cout << "This knot can't lead to at least one inkernel slice after chi!" << endl;
                return false;
            }
        }
        return true;
    }
    else{
        cout << "Error at the populating knots at B stage!" << endl;
        return false;
    }
}

bool InKernelAtCFilter::updateSetOfMinimalStatesUpToNow(){
    //hua jian
    set<BitPosition> abitSetForMinimalStateB = bitSetForMinimalStateB;
    for (int dz = 0; dz < 64; dz ++) {
        set<BitPosition> aMin;
        set<BitPosition>::iterator itBitSet;
        for (itBitSet = abitSetForMinimalStateB.begin(); itBitSet != abitSetForMinimalStateB.end(); itBitSet++) {
            BitPosition aBit((*itBitSet));
            aBit.zTranslate(dz, 64);
            aMin.insert(aBit);
        }
        if (aMin < bitSetForMinimalStateB) {
            bitSetForMinimalStateB = aMin;
        }
    }
    if (setOfBitSetForMinimalStateBUpToNow.insert(bitSetForMinimalStateB).second == false) {
//        cout << "Minimal state of this state AtB has already existed!" << endl;
        return false;
    }
    else {
        return true;
    }
}


void InKernelAtCFilter::prepareOutputTrailCore(){
    workCore.clear();
    stateAtA.clear();
    stateAtB.clear();
    partialStateAtD.clear();
    for (int i = 0; i < 64; i ++) {
        stateAtA.push_back(0);
        stateAtB.push_back(0);
        partialStateAtD.push_back(0);
    }

    for (int nrPeer = 0; nrPeer < peersAtA.size(); nrPeer++) {
        if (peersAtA[nrPeer].size() == 2) {
            for (int nrBit = 0; nrBit < peersAtA[nrPeer].size(); nrBit++) {
                setBitToOne(stateAtA, peersAtA[nrPeer][nrBit]);
            }
        }
        else {
            cout << "Error! There aren't 2 bits in oen peer!" << endl;
        }
    }

    vector<SliceValue> partialStateAtC(64);
    map<unsigned int, KnotAtBInfo>::iterator itKnot;
    for (itKnot = knotsAtB.begin(); itKnot != knotsAtB.end(); itKnot ++) {
        stateAtB[itKnot->first] = itKnot->second.sliceValue;
        partialStateAtC[itKnot->first] = getMinimumInKernelSliceAfterChi(itKnot->second.sliceValue);
//        partialStateAtC[itKnot->first] = myGetMinimumInKernelSliceAfterChi(itKnot->second.sliceValue);
    }
    weightAtB = getWeight(stateAtB);
    directLambdaAfterTheta(partialStateAtC, partialStateAtD);
    unsigned int reverseWeightA = getMinReverseWeight(stateAtA);
    unsigned int partialWeightD = getWeight(partialStateAtD);
    partialWeight = getMinReverseWeight(stateAtA) + weightAtB + getWeight(partialStateAtD);

    minWeightBAndC = weightAtB + partialWeightD;

    CoreInfo currentCore;
    currentCore.stateAtB = stateAtB;
    currentCore.partialStateAtC = partialStateAtC;
    currentCore.partialWeight = partialWeight;
    currentCore. weightAtB = weightAtB;
    getSymmetricMinimum(stateAtB, currentCore.minimalStateAtB);
    workCore.push_back(currentCore);

    return;
}

SliceValue InKernelAtCFilter::myGetMinimumInKernelSliceAfterChi(const SliceValue sliceBeforeChi){
    SliceValue minimalsliceAfterChi = maxSliceValue;
    vector<RowValue> rowsBefore;
    vector<vector<RowValue>> outputDiffs;
    vector<unsigned int> index;
    for (unsigned int y = 0; y < 5; y++) {
        RowValue rowBefore = getRowFromSlice(sliceBeforeChi, y);
        if (rowBefore) {
            rowsBefore.push_back(rowBefore);
            vector<RowValue> aValue = directRowOutputListPerInput[rowBefore].values;
            outputDiffs.push_back(aValue);
            index.push_back(0);
        }
    }
    do {
        RowValue parity = 0;
        for (unsigned int i = 0; i < rowsBefore.size(); i++) {
            parity ^= outputDiffs[i][index[i]];
        }
        if (parity == 0) {
            SliceValue sliceAfterChi = 0;
            int nrRows = 0;
            for (unsigned int y = 0; y < 5; y++) {
                RowValue rowBefore = getRowFromSlice(sliceBeforeChi, y);
                if (rowBefore) {
                    sliceAfterChi ^= getSliceFromRow(outputDiffs[nrRows][index[nrRows]], y);
                    nrRows++ ;
                }
            }
            if (getHammingWeightSlice(sliceAfterChi) < getHammingWeightSlice(minimalsliceAfterChi)) {
                minimalsliceAfterChi = sliceAfterChi;
            }
        }
    } while (updateIndex(index, outputDiffs));
    return minimalsliceAfterChi;
}

bool InKernelAtCFilter::updateIndex(vector<unsigned int> & index, const vector<vector<RowValue> > rowsDiff){
    if (index.size() == rowsDiff.size()) {
        if (index.back() < (rowsDiff.back().size() - 1)) {
            index.back()++;
            return true;
        }
        else {
            index.pop_back();
            if (updateIndex(index, rowsDiff)) {
                index.push_back(0);
                return true;
            }
            return false;
        }
    }
    else if((index.size() < rowsDiff.size()) && (index.size() > 1)) {
        if (index.back() < (rowsDiff[index.size()-1].size()-1)) {
            index.back()++;
            return true;
        }
        else {
            index.pop_back();
            if (updateIndex(index, rowsDiff)) {
                index.push_back(0);
                return true;
            }
            return false;
        }
    }
    else if (index.size() == 1){
        if (index.back() < (rowsDiff[0].size()-1)) {
            index.back()++;
            return true;
        }
        else {
            index.pop_back();
            return false;
        }
    }
    else {
        cout << "Unexpected situation!" << endl;
        return false;
    }
}

void InKernelAtCFilter::outputTrailCore(const string& fileName){
    ofstream fout(fileName.c_str(), ios::app);
    Trail trail;
    trail.setFirstStateReverseMinimumWeight(getMinReverseWeight(stateAtA));
    trail.append(workCore.back().stateAtB, workCore.back().weightAtB);
//    trail.append(workCore.back().minimalStateAtB, workCore.back().weightAtB);
    trail.save(fout);
}
























