//
//  InKernelAtCStructureConstructStructureConstruct.cpp
//  InKernelAtCTrailCoreSearch
//
//  Created by 刘国珍 on 23/05/2018.
//  Copyright © 2018 Liu Guozhen. All rights reserved.
//

#include "MyTrailCoreInKernelAtCStructureConstruct.hpp"

void InKernelAtCStructureConstruct::genInputforAllActiveSbox(DualVector slicePatternCase,TriVector& activeSboxAllCase) {
    std::vector<RowValue> set1{1, 2, 4, 8, 16};
    std::vector<RowValue> set2{3, 5, 6, 9, 10, 12, 17, 18, 20, 24};//10
    std::vector<RowValue> set3{7, 11, 13, 14, 19, 21, 22, 25, 26, 28};//10
    std::vector<RowValue> set4{15, 23, 27, 29, 30};
    std::vector<RowValue> set5{31};// 5 bits 1

    int Case, nSbox;
    //each case indicates 1)number of active sboxes 2)number of bits within each Sbox
    //e.g., "slicePatternCase" stores {{1,3},{2,2},{1,1,2},{1,1,1,1}}, 4 possible cases
    for (Case = 0; Case < slicePatternCase.size(); Case++) {
        DualVector activeSbox;
        for (nSbox = 0; nSbox < slicePatternCase[Case].size(); nSbox++) {
            std::vector<RowValue> Sbox;
            switch (slicePatternCase[Case][nSbox]) {
                    //active bits
                case 1:
                    for (int i = 0; i < set1.size(); i++) {
                        Sbox.push_back(set1[i]);
                    }
                    break;
                case 2:
                    for (int i = 0; i < set2.size(); i++) {
                        Sbox.push_back(set2[i]);
                    }
                    break;
                case 3:
                    for (int i = 0; i < set3.size(); i++) {
                        Sbox.push_back(set3[i]);
                    }
                    break;
                case 4:
                    for (int i = 0; i < set4.size(); i++) {
                        Sbox.push_back(set4[i]);
                    }
                    break;
                case 5:
                {
                    for (int i = 0; i < set5.size(); i++) {
                        Sbox.push_back(set5[i]);
                    }
                }
                    break;
                default:
                {
                    cout << "Error! More than 5 active bits in one ROW!" << endl;
                }
            }
            // a case {input difference, input diff}
            activeSbox.push_back(Sbox);
        }
        activeSboxAllCase.push_back(activeSbox);
    }
}

void InKernelAtCStructureConstruct::printValueSlicePattern(multisetSet valuePattern){
    cout << valuePattern.size() << " value patterns in total!" << endl;
    multisetSet :: iterator itSet;
    for ( itSet = valuePattern.begin(); itSet != valuePattern.end(); itSet++) {
        multiset <RowValue, greater <RowValue> > :: iterator it;
        for ( it = (*itSet).begin(); it != (*itSet).end(); it++) {
            bitset<5> input(*it);
            cout << " " << input;
        }
        cout << endl;
    }
}

void InKernelAtCStructureConstruct::twoSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern2){
    //see whether there is a p()=0, valid value pattern
    int i, j, ii, jj;
    int cases;
    for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
        for (i = 0; i < activeSboxAllCase[cases][0].size(); i++) {//the vector stores all possible input differences of the first active sbox
            for (j = 0; j < activeSboxAllCase[cases][1].size(); j++) {//the vector stores all possible input differences of the second active sbox
                bool flag = 0;
                for (ii = 1; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {//for each of the input difference, check all compatible output differences
                    for (jj = 1; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
                        unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                        unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                        if ((output1^output2)==0) {
                            multiset <RowValue, greater <RowValue> > validSlice;
                            validSlice.insert(activeSboxAllCase[cases][0][i]);
                            validSlice.insert(activeSboxAllCase[cases][1][j]);
                            valuePattern2.insert(validSlice);
                            flag = 1;
                            break;
                        }
                    }
                    if (flag) {
                        break;
                    }
                }
            }
        }
    }
//    printValueSlicePattern(valuePattern2);
}

void InKernelAtCStructureConstruct::threeSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern3){
    int i, j, k, ii, jj, kk;
    int cases;
    for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
        for (i = 0; i < activeSboxAllCase[cases][0].size(); i++) {
            for (j = 0; j < activeSboxAllCase[cases][1].size(); j++) {
                for ( k = 0; k < activeSboxAllCase[cases][2].size(); k++) {
                    bool flag = 0;
                    for ( ii = 1; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {
                        for ( jj = 1; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
                            for ( kk = 1; kk < DDTOutput[activeSboxAllCase[cases][2][k]][0]; kk++) {
                                unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                                unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                                unsigned int output3 = DDTOutput[activeSboxAllCase[cases][2][k]][kk];
                                unsigned int outputvalue = output1 ^ output2 ^ output3;
                                if (outputvalue == 0) {
                                    multiset <RowValue, greater <RowValue> > validSlice;
                                    validSlice.insert(activeSboxAllCase[cases][0][i]);
                                    validSlice.insert(activeSboxAllCase[cases][1][j]);
                                    validSlice.insert(activeSboxAllCase[cases][2][k]);
                                    valuePattern3.insert(validSlice);
                                    flag = 1;
                                    break;
                                }
                            }
                            if (flag) {
                                break;
                            }
                        }
                        if (flag) {
                            break;
                        }
                    }
                }
            }
        }
    }
//     printValueSlicePattern(valuePattern3);
}


void InKernelAtCStructureConstruct::fourSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern4){
    int i, j, k, m, ii, jj, kk, mm;
    int cases;
    for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
        for ( i = 0; i < activeSboxAllCase[cases][0].size(); i++) {
            for ( j = 0; j < activeSboxAllCase[cases][1].size(); j++) {
                for ( k = 0; k < activeSboxAllCase[cases][2].size(); k++) {
                    for ( m = 0; m < activeSboxAllCase[cases][3].size(); m++) {
                        bool flag = 0;
                        for ( ii = 1; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {
                            for ( jj = 1; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
                                for ( kk = 1; kk < DDTOutput[activeSboxAllCase[cases][2][k]][0]; kk++) {
                                    for ( mm = 1; mm < DDTOutput[activeSboxAllCase[cases][3][m]][0]; mm++) {
                                        unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                                        unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                                        unsigned int output3 = DDTOutput[activeSboxAllCase[cases][2][k]][kk];
                                        unsigned int output4 = DDTOutput[activeSboxAllCase[cases][3][m]][mm];
                                        unsigned int outputvalue = output1 ^ output2 ^ output3 ^ output4;
                                        if (outputvalue==0) {
                                            multiset <RowValue, greater<RowValue> > validSlice;
                                            validSlice.insert(activeSboxAllCase[cases][0][i]);
                                            validSlice.insert(activeSboxAllCase[cases][1][j]);
                                            validSlice.insert(activeSboxAllCase[cases][2][k]);
                                            validSlice.insert(activeSboxAllCase[cases][3][m]);
                                            valuePattern4.insert(validSlice);
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag) {
                                        break;
                                    }
                                }
                                if (flag) {
                                    break;
                                }
                            }
                            if (flag) {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
//     printValueSlicePattern(valuePattern4);
}

void InKernelAtCStructureConstruct::fiveSboxValuePatternSearch(TriVector activeSboxAllCase, int DDTOutput[32][32], multisetSet& valuePattern5){
    int i, j, k, m, n, ii, jj, kk, mm, nn;
    int cases;
    for ( cases = 0; cases < activeSboxAllCase.size(); cases++) {
        for ( i = 0; i < activeSboxAllCase[cases][0].size(); i++) {
            for ( j = 0; j < activeSboxAllCase[cases][1].size(); j++) {
                for ( k = 0; k < activeSboxAllCase[cases][2].size(); k++) {
                    for ( m = 0; m < activeSboxAllCase[cases][3].size(); m++) {
                        for ( n = 0; n < activeSboxAllCase[cases][4].size(); n++) {
                            bool flag = 0;
                            for ( ii = 1; ii < DDTOutput[activeSboxAllCase[cases][0][i]][0]; ii++) {
                                for ( jj = 1; jj < DDTOutput[activeSboxAllCase[cases][1][j]][0]; jj++) {
                                    for ( kk = 1; kk < DDTOutput[activeSboxAllCase[cases][2][k]][0]; kk++) {
                                        for ( mm = 1; mm < DDTOutput[activeSboxAllCase[cases][3][m]][0]; mm++) {
                                            for ( nn = 1; nn < DDTOutput[activeSboxAllCase[cases][4][n]][0]; nn++) {
                                                unsigned int output1 = DDTOutput[activeSboxAllCase[cases][0][i]][ii];
                                                unsigned int output2 = DDTOutput[activeSboxAllCase[cases][1][j]][jj];
                                                unsigned int output3 = DDTOutput[activeSboxAllCase[cases][2][k]][kk];
                                                unsigned int output4 = DDTOutput[activeSboxAllCase[cases][3][m]][mm];
                                                unsigned int output5 = DDTOutput[activeSboxAllCase[cases][4][n]][nn];
                                                unsigned int outputvalue = output1 ^ output2 ^ output3 ^ output4 ^ output5;
                                                if (outputvalue == 0) {
                                                    multiset <RowValue, greater <RowValue> > validSlice;
                                                    validSlice.insert(activeSboxAllCase[cases][0][i]);
                                                    validSlice.insert(activeSboxAllCase[cases][1][j]);
                                                    validSlice.insert(activeSboxAllCase[cases][2][k]);
                                                    validSlice.insert(activeSboxAllCase[cases][3][m]);
                                                    validSlice.insert(activeSboxAllCase[cases][4][n]);
                                                    valuePattern5.insert(validSlice);
                                                    flag = 1;
                                                    break;
                                                }
                                            }
                                            if (flag) {
                                                break;
                                            }
                                        }
                                        if (flag) {
                                            break;
                                        }
                                    }
                                    if (flag) {
                                        break;
                                    }
                                }
                                if (flag) {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
//     printValueSlicePattern(valuePattern5);
}



void InKernelAtCStructureConstruct::differential_distribution_table_dir(int DDT[32][32]){
    RowValue din, dout, x, k, index;
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            DDT[i][j] = 0;
        }
    }

    for (int i = 0; i < 32; i++) {
        DDT[i][0] = 1;
    }

    for (din = 0; din < 32; din++) {
        for (x = 0; x < 32; x++) {
            dout = Sbox(x) ^ Sbox(x^din);
            int flag = 0;
            for (k = 1; k < 32; k++) {
                if (DDT[din][k] == dout) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                index = DDT[din][0];
                DDT[din][index] = dout;
                DDT[din][0]++;
            }
        }
    }
    return;
}

unsigned int InKernelAtCStructureConstruct::Sbox(unsigned int a){
    unsigned int res = 0;
    for (int i = 0; i < 5; i++) {
        res = res^(((a>>i)&0x1)^(~((a>>(i+1)%5)&0x1))&((a>>(i+2)%5)&0x1))<<i;
    }
    return res;
}

void InKernelAtCStructureConstruct::generateValidSliceValuePattern(unsigned int nBit, multisetSet& patternSet) {
    int DDTOutput[32][32];
    differential_distribution_table_dir(DDTOutput);

    switch (nBit) {
        case 2:
        {
            DualVector twoBitSlice{{1,1}};
            TriVector activeSbox;
            genInputforAllActiveSbox(twoBitSlice,activeSbox);
            twoSboxValuePatternSearch(activeSbox, DDTOutput, patternSet);
        }
            break;

        case 3:
        {
            DualVector twoSboxSlice{{1,2}};
            TriVector activeSbox2;
            DualVector threeSboxSlice{{1,1,1}};
            TriVector activeSbox3;
            genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
            genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
            twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
            threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
        }
            break;

        case 4:
        {
            DualVector twoSboxSlice{{1,3},{2,2}};
            TriVector activeSbox2;
            DualVector threeSboxSlice{{1,1,2}};
            TriVector activeSbox3;
            DualVector fourSboxSlice{{1,1,1,1}};
            TriVector activeSbox4;
            genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
            genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
            genInputforAllActiveSbox(fourSboxSlice, activeSbox4);
            twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
            threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
            fourSboxValuePatternSearch(activeSbox4, DDTOutput, patternSet);
        }
            break;

        case 5:
        {
            DualVector twoSboxSlice{{1,4},{2,3}};
            TriVector activeSbox2;
            DualVector threeSboxSlice{{1,1,3},{1,2,2}};
            TriVector activeSbox3;
            DualVector fourSboxSlice{{1,1,1,2}};
            TriVector activeSbox4;
            DualVector fiveSboxSlice{{1,1,1,1,1}};
            TriVector activeSbox5;
//            genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
//            twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
//            genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
//            threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
//            genInputforAllActiveSbox(fourSboxSlice, activeSbox4);
//            fourSboxValuePatternSearch(activeSbox4, DDTOutput, patternSet);
//            genInputforAllActiveSbox(fiveSboxSlice, activeSbox5);
//            fiveSboxValuePatternSearch(activeSbox5, DDTOutput, patternSet);
            
            genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
            genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
            genInputforAllActiveSbox(fourSboxSlice, activeSbox4);
            genInputforAllActiveSbox(fiveSboxSlice, activeSbox5);
            twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
            threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
            fourSboxValuePatternSearch(activeSbox4, DDTOutput, patternSet);
            fiveSboxValuePatternSearch(activeSbox5, DDTOutput, patternSet);//until here, right
        }
            break;
            
        //case 6
            
        case 6:
        {
            DualVector twoSboxSlice{{1,5},{2,4},{3,3}};
            TriVector activeSbox2;
            DualVector threeSboxSlice{{1,1,4},{1,2,3},{2,2,2}};
            TriVector activeSbox3;
            DualVector fourSboxSlice{{1,1,1,3},{1,1,2,2}};
            TriVector activeSbox4;
            DualVector fiveSboxSlice{{1,1,1,1,2}};
            TriVector activeSbox5;
            genInputforAllActiveSbox(twoSboxSlice, activeSbox2);
            genInputforAllActiveSbox(threeSboxSlice, activeSbox3);
            genInputforAllActiveSbox(fourSboxSlice, activeSbox4);
            genInputforAllActiveSbox(fiveSboxSlice, activeSbox5);
            twoSboxValuePatternSearch(activeSbox2, DDTOutput, patternSet);
            threeSboxValuePatternSearch(activeSbox3, DDTOutput, patternSet);
            fourSboxValuePatternSearch(activeSbox4, DDTOutput, patternSet);
            fiveSboxValuePatternSearch(activeSbox5, DDTOutput, patternSet);
        }
            break;
        default:
            break;
    }
}

void InKernelAtCStructureConstruct:: initializeValuePatterns(void)
{   // active bits of a slice
    generateValidSliceValuePattern(2, valuePatternSet2);
    generateValidSliceValuePattern(3, valuePatternSet3);
    generateValidSliceValuePattern(4, valuePatternSet4);
    generateValidSliceValuePattern(5, valuePatternSet5);
    generateValidSliceValuePattern(6, valuePatternSet6);
    
//        printValueSlicePattern(valuePatternSet2);
//        printValueSlicePattern(valuePatternSet3);
//        printValueSlicePattern(valuePatternSet4);
//        printValueSlicePattern(valuePatternSet5);
//        printValueSlicePattern(valuePatternSet6);
    
    
}

void InKernelAtCStructureConstruct::printSingleValuePattern_ForTest(const vector<RowValue> aRowChainOfValuePattern){
    for (int i = 0; i < aRowChainOfValuePattern.size(); i++) {
        bitset<5> output(aRowChainOfValuePattern[i]);
        cout << " " << output;
    }
    cout << endl;
}

InKernelAtCStructureConstruct:: InKernelAtCStructureConstruct(unsigned int aMaxWeight, const KeccakFDCLC & aParent, KeccakFPropagation::DCorLC aDCorLC):
KeccakFPropagation(aParent, aDCorLC), maxWeight(aMaxWeight)
{
    initializeValuePatterns();
//    test4Peers3Slices();
}

void InKernelAtCStructureConstruct::getAllSlicePatternsFromAValuePattern(const ValuePatternmultiset aValuePattern, set<SliceValue> & aAllSlicePatternSet){

    //Store the value pattern with a vector
    ValuePatternmultiset:: iterator itValuePattern;
    vector<RowValue> rowChainOfValuePattern;
    for (itValuePattern = aValuePattern.begin(); itValuePattern != aValuePattern.end(); itValuePattern ++) {
        rowChainOfValuePattern.push_back(*itValuePattern);
    }
    //    printSingleValuePattern_ForTest(rowChainOfValuePattern);

    unsigned int nrActiveRows = aValuePattern.size();
    SliceValue oneSlice;
    unsigned int nrSlicePatterns, nrRows;
    switch (nrActiveRows) {
        case 2:
        {
            for (nrSlicePatterns = 0; nrSlicePatterns < sbox2YPosition.size(); nrSlicePatterns ++) {
                oneSlice = 0;
                for (nrRows = 0; nrRows < nrActiveRows; nrRows++) {
                    oneSlice ^= getSliceFromRow(rowChainOfValuePattern[nrRows], sbox2YPosition[nrSlicePatterns][nrRows]);
                }
                //                printSliceRowByRow(oneSlice);
                aAllSlicePatternSet.insert(oneSlice);
            }
        }
            break;

        case 3:
        {
            for (nrSlicePatterns = 0; nrSlicePatterns < sbox3YPosition.size(); nrSlicePatterns ++) {
                oneSlice = 0;
                for (nrRows = 0; nrRows < nrActiveRows; nrRows++) {
                    oneSlice ^= getSliceFromRow(rowChainOfValuePattern[nrRows], sbox3YPosition[nrSlicePatterns][nrRows]);
                }
                //                printSliceRowByRow(oneSlice);
                aAllSlicePatternSet.insert(oneSlice);
            }
        }
            break;

        case 4:
        {
            for (nrSlicePatterns = 0; nrSlicePatterns < sbox4YPosition.size(); nrSlicePatterns ++) {
                oneSlice = 0;
                for (nrRows = 0; nrRows < nrActiveRows; nrRows++) {
                    oneSlice ^= getSliceFromRow(rowChainOfValuePattern[nrRows], sbox4YPosition[nrSlicePatterns][nrRows]);
                }
                //                printSliceRowByRow(oneSlice);
                aAllSlicePatternSet.insert(oneSlice);
            }
        }
            break;

        case 5:
        {
            for (nrSlicePatterns = 0; nrSlicePatterns < sbox5YPosition.size(); nrSlicePatterns ++) {
                oneSlice = 0;
                for (nrRows = 0; nrRows < nrActiveRows; nrRows++) {
                    oneSlice ^= getSliceFromRow(rowChainOfValuePattern[nrRows], sbox5YPosition[nrSlicePatterns][nrRows]);
                }
                //                printSliceRowByRow(oneSlice);
                aAllSlicePatternSet.insert(oneSlice);
            }
        }
            break;

        default:
            cout << "Error! You should Expand the value pattern set for more bits!" << endl;
            break;
    }
}

void InKernelAtCStructureConstruct::getKnotPointsFromSlice(const SliceValue aSlice, vector<BitPosition>& aStartingKnotPoints){
//    vector<unsigned int> aYOffset;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if ((aSlice >> (x+5*y))&0x1) {
                BitPosition onePoit(x,y,0);
                aStartingKnotPoints.push_back(onePoit);
//                aYOffset.push_back(0);
            }
        }
    }
//    yOffset.push_back(aYOffset);
    return;
}

void InKernelAtCStructureConstruct::getKnotPointsFromSlice(const SliceValue aSlice, const unsigned int nrSlice, vector<BitPosition>& knotPoints){
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if ((aSlice >> (x+5*y))&0x1) {
                BitPosition onePoit(x,y,nrSlice);
                knotPoints.push_back(onePoit);
            }
        }
    }
    //    yOffset.push_back(aYOffset);
    return;
}

void InKernelAtCStructureConstruct::addPeerParameterOnRho(vector<BitPosition> aPeerAtA){
    unsigned int offset[5][5] = {//[x][y] fashion, my state is [y][x]fashion
        {0, 36, 3, 41, 18},
        {1, 44, 10, 45, 2},
        {62, 6, 43, 15, 61},
        {28, 55, 25, 21, 56},
        {27, 20, 39, 8, 14}
    };
    unsigned int valueParameter;
    //v1 v2 v3 v4 !!!
    if (aPeerAtA.size() == 2) {
        valueParameter = (64 + offset[aPeerAtA[0].x][aPeerAtA[0].y] - offset[aPeerAtA[1].x][aPeerAtA[1].y])%64;
        peerParameterOnRho.push_back(valueParameter);
    }
    else
        cout<< "Error! The peer doesn't contain 2 bits!" << endl;
    return;
}

bool InKernelAtCStructureConstruct:: recursiveYOffsetOfStartingKnot(vector<unsigned int>& yOffset){
    if (yOffset.size() == 0) {
        return false;
    } else if((yOffset.size() >= 1) && (yOffset.back() == 4)){
        yOffset.pop_back();
        if(recursiveYOffsetOfStartingKnot(yOffset)){
            yOffset.push_back(1);
            return true;
        }
        else
            return false;
    } else if ((yOffset.size() >= 1) && (yOffset.back() < 4)){
        yOffset.back()++;
        return true;
    }
    else
        cout << "Error! Unexpected situation in yOffset recursion!" << endl;
    return true;
}

bool InKernelAtCStructureConstruct::checkMappedToSameKnotAtBCase433(vector<vector<BitPosition>>& aKnotAtB){
    vector<BitPosition> knot1, knot2;
    if (peersAtA.size() == 4) {
        BitPosition q1B(peersAtA[0].back());
        q1B.directRhoPi();
        BitPosition q2B(peersAtA[1].back());
        q2B.directRhoPi();
        BitPosition q3B(peersAtA[2].back());//q3 at A
        q3B.directRhoPi();//q3 at B
        BitPosition q4B(peersAtA[3].back());//q4 at A
        q4B.directRhoPi();//q4 at B
        if ((q3B.z == q4B.z) && (q1B.z == q2B.z)) {
            knot1.push_back(q1B);
            knot1.push_back(q2B);
            knot2.push_back(q3B);
            knot2.push_back(q4B);
            aKnotAtB.push_back(knot1);
            aKnotAtB.push_back(knot2);
            return true;
        }
        else {
            return false;
        }
    }
    else {
        cout << "Error in the number of peers at A!" << endl;
        return false;
    }
}

bool InKernelAtCStructureConstruct::checkMappedToSameOrbitalCase4222(){
    if (peersAtA.size() == 4) {
        BitPosition q3B(peersAtA[2].back());//q3 at A
        q3B.directRhoPi();//q3 at B
        BitPosition q4B(peersAtA[3].back());//q4 at A
        q4B.directRhoPi();//q4 at B
        if (q3B.z == q4B.z) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        cout << "Error in the number of peers at A!" << endl;
        return false;
    }
}

bool InKernelAtCStructureConstruct::checkQ5Q6MappedToSameOrbital(){
    if (peersAtA.size() == 6) {
        BitPosition q5B(peersAtA[4].back());//q5 at A
        q5B.directRhoPi();//q5 at B
        BitPosition q6B(peersAtA[5].back());//q6 at A
        q6B.directRhoPi();//q6 at B
        if ((q5B.z == q6B.z)&&(q5B.x == q6B.x)) {
            if((q5B.y != q6B.y)){
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
    else {
        cout << "Error in the number of peers at A!" << endl;
        return false;
    }
}



bool InKernelAtCStructureConstruct::checkQ3P5Q4P6MappedToSameOrbital(){
    if (peersAtA.size() == 6) {
        bool find1, find2;
        BitPosition q3B(peersAtA[2].back());//q3 at A
        q3B.directRhoPi();//q3 at B
        BitPosition q4B(peersAtA[3].back());//q4 at A
        q4B.directRhoPi();//q4 at B
        
        BitPosition q5B(peersAtA[4].back());//p5 at A
        q5B.directRhoPi();//p5 at B
        BitPosition q6B(peersAtA[5].back());//p6 at A
        q6B.directRhoPi();//p6 at B
        
        if ((q5B.z == q3B.z)&&(q5B.x == q3B.x)) {
            if((q5B.y != q3B.y)){
                find1 = true;
            }
            else{
                find1 = false;
            }
        }
        else {
            find1 = false;
        }
        
        if ((q4B.z == q6B.z)&&(q4B.x == q6B.x)) {
            if((q4B.y != q6B.y)){
                find2 = true;
            }
            else{
                find2 = false;
            }
        }
        else {
            find2 = false;
        }
        
        if (find1 && find2) {
            return true;
        }
        else{
            return false;
        }
        
    }
    else {
        cout << "Error in the number of peers at A!" << endl;
        return false;
    }
}

bool InKernelAtCStructureConstruct::checkP4P5P6MappedToSameKnot(){
    if (peersAtA.size() == 6) {
        BitPosition q4B(peersAtA[3].back());//q4 at A
        q4B.directRhoPi();//q4 at B
        
        BitPosition q5B(peersAtA[4].back());//q5 at A
        q5B.directRhoPi();//q5 at B
        
        BitPosition q6B(peersAtA[5].back());//q6 at A
        q6B.directRhoPi();//q6 at B
        if ((q4B.z == q5B.z)&&(q5B.z == q6B.z)) {
            if((q5B.y != q6B.y)){
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
    else {
        cout << "Error in the number of peers at A!" << endl;
        return false;
    }
}


bool InKernelAtCStructureConstruct::checkMappedToSameKnotCase3322A(){
    if (peersAtA.size() == 3) {
        BitPosition q1B(peersAtA[0].back());//q1 at A
        q1B.directRhoPi();//q1"
        BitPosition q2B(peersAtA[1].back());//q2 at A
        q2B.directRhoPi();//q2"
        if (q1B.z == q2B.z) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        cout << "Error in the number of peers at A!" << endl;
        return false;
    }
}

bool InKernelAtCStructureConstruct::checkMappedToSameOrbitalCase3322C(){
    BitPosition q2B(peersAtA[1].back());//q2 at A
    q2B.directRhoPi();//q2"
    BitPosition q3B(peersAtA[2].back());//q3 at A
    q3B.directRhoPi();//q3"
    if ((q2B.z == q3B.z) && (q2B.x == q3B.x)) {//Previous BUg:q2B.y==q3B.y
        return true;
    }
    else {
        return false;
    }
}

bool InKernelAtCStructureConstruct::valuePatternInKernelAtCCheck(const unsigned nrBits, const ValuePatternmultiset aValuePattern){
    switch (nrBits) {
        case 2:
        {
            if ((valuePatternSet2.find(aValuePattern)) != (valuePatternSet2.end())) {
                return true;
            }
            else{
                return false;
            }
        }
            break;

        case 3:
        {
            if ((valuePatternSet3.find(aValuePattern)) != (valuePatternSet3.end())) {
                return true;
            }
            else{
                return false;
            }
        }
            break;

        case 4:
        {
            if ((valuePatternSet4.find(aValuePattern)) != (valuePatternSet4.end())) {
                return true;
            }
            else{
                return false;
            }
        }
            break;

        case 5:
        {
            if ((valuePatternSet5.find(aValuePattern)) != (valuePatternSet5.end())) {
                return true;
            }
            else{
                return false;
            }
        }
            break;
            
        case 6:
        {
            if ((valuePatternSet6.find(aValuePattern)) != (valuePatternSet6.end())) {
                return true;
            }
            else{
                return false;
            }
        }
            break;
            
        default:
        {
            cout << "In this case, there are more than 6 active bits in a slice!" << endl;
            return false;
        }
            break;
    }
}

ValuePatternmultiset InKernelAtCStructureConstruct:: getValuePatternFromSlice(const SliceValue aSliceValue){
    RowValue aRow;
    ValuePatternmultiset aValuePattern;
    for (int nrRow = 0; nrRow < 5; nrRow++) {
        aRow = getRowFromSlice(aSliceValue, nrRow);
        if (aRow) {
            aValuePattern.insert(aRow);
        }
    }
    if (aValuePattern.size() >= 2) {
        return aValuePattern;
    }
    else {
//        cout << "Error! There are less than 2 active rows in the knot at B!" << endl;//Note at the checking slice stage(for 433) this error alerts so I comment this line.
        return aValuePattern;
    }
}

SliceValue InKernelAtCStructureConstruct::getSliceValueFromBitChain(vector<BitPosition> aBitPointsChain){
    SliceValue aSliceValue = 0;
    for (int i =0; i< aBitPointsChain.size(); i++) {
        aSliceValue |= (SliceValue)1 << (aBitPointsChain[i].x + 5*aBitPointsChain[i].y);
    }
    return aSliceValue;
}

bool InKernelAtCStructureConstruct::checkKnotInKernelAtC(vector<BitPosition> aKnot){
    if (aKnot.size() == 3) {
        SliceValue knot = getSliceValueFromBitChain(aKnot);
        ValuePatternmultiset valuePattern = getValuePatternFromSlice(knot);
        if (valuePatternInKernelAtCCheck(3, valuePattern)) {
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

BitPosition InKernelAtCStructureConstruct::getBitAtBFromBitAtA(const BitPosition pA){
    BitPosition pB(pA);//at A
    pB.directRhoPi();//at B
    return pB;
}

BitPosition InKernelAtCStructureConstruct::getBitAtAFromBitAtB(const BitPosition pA){
    BitPosition pB(pA);//at A
    pB.inverseRhoPi();//at B
    return pB;
}


bool InKernelAtCStructureConstruct::nextStructureOfOtherKnot3322C(BitPosition & Q4B, const BitPosition Q1B){
    if ((!isInitialStructureOfOtherKnot) || (!isQ4Found)) {
        if (!isInitialStructureOfOtherKnot) {
            if (Q4B == Q1B) {
                Q4B.nextXY();
            }
        }
        if ((!isQ4Found) && (isInitialStructureOfOtherKnot)) {
            if (yOffset.size()==2) {
                yOffset.pop_back();//For each new q4, a new yOffset[1] should be added
                if (Q4B.nextXY()) {
                    if (Q4B == Q1B) {
                        if(Q4B.nextXY());
                        else {
                            isLastStructureOfOtherKnot = true;
                            return false;
                        }
                    }
                }
                else {
                    isLastStructureOfOtherKnot = true;
                    return false;
                }
            }
            else {
                cout << "Error in size of yOffset!" << endl;
                return false;
            }
        }
        vector<unsigned int> aYOffset;
        vector<BitPosition> aPeer4;//(q4,p4)
        vector<BitPosition> aPeer5;//(p5,q5)
        BitPosition q4(Q4B);//q4" at B
        q4.inverseRhoPi();//q4 at A
        aPeer4.push_back(q4);
        aYOffset.push_back(1);
        q4.yTranslate(aYOffset.back());//p4 at A
        aPeer4.push_back(q4);
        q4.directRhoPi();//p4" at B
        BitPosition p5(q4);//p4"
        aYOffset.push_back(1);
        p5.yTranslate(aYOffset.back());//p5" at B
        p5.inverseRhoPi();//p5 at A
        aPeer5.push_back(p5);
        aYOffset.push_back(1);
        p5.yTranslate(aYOffset.back());//q5 at A
        aPeer5.push_back(p5);

        peersAtA.push_back(aPeer4);
        addPeerParameterOnRho(aPeer4);//Note the order of peer 4
        peersAtA.push_back(aPeer5);
        addPeerParameterOnRho(aPeer5);
        yOffset.push_back(aYOffset);

        isInitialStructureOfOtherKnot = true;
        isQ4Found = true;

        return true;
    }
    else {
        if ((yOffset.size() == 2) && (isQ4Found)) {
            if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
                completeStructureOfOtherKnot3322C(Q4B);
                return true;
            }
            else {
                isQ4Found = false;
                return false;
            }
        }
        else {
            cout << "Size error of yOffset!" << endl;
            return false;
        }
    }
}

void InKernelAtCStructureConstruct::completeStructureOfOtherKnot3322C(const BitPosition Q4B){
    if (yOffset.back().size() == 3) {
        vector<BitPosition> aPeer4;//(q4,p4)
        vector<BitPosition> aPeer5;//(p5,q5)
        BitPosition q4(Q4B);//q4" at B
        q4.inverseRhoPi();//q4 at A
        aPeer4.push_back(q4);
        q4.yTranslate(yOffset.back()[0]);//p4 at A
        aPeer4.push_back(q4);
        q4.directRhoPi();//p4" at B
        BitPosition p5(q4);//p4"
        p5.yTranslate(yOffset.back()[1]);//p5" at B
        p5.inverseRhoPi();//p5 at A
        aPeer5.push_back(p5);
        p5.yTranslate(yOffset.back()[2]);//q5 at A
        aPeer5.push_back(p5);

        peersAtA.push_back(aPeer4);
        addPeerParameterOnRho(aPeer4);//Note the order of peer 4
        peersAtA.push_back(aPeer5);
        addPeerParameterOnRho(aPeer5);
    }
    else {
        cout << "Size error of yOffset[1]!" << endl;
    }
    return;
}

//Note I didn't update the parameter of last peer as I forgot it.
bool InKernelAtCStructureConstruct::nextStructureOfOtherKnot433(BitPosition& aP5B){
    vector<BitPosition> aKnot = knotAtB433.back();
    if (!isInitialStructureOfOtherKnot) {
        while (!isP5Found) {
            aKnot.push_back(aP5B);
            if (checkKnotInKernelAtC(aKnot)) {
                vector<BitPosition> aPeer;
                vector<unsigned int> aYOffset;
                BitPosition Q5(aP5B);
                Q5.inverseRhoPi();
                aPeer.push_back(Q5);
                aYOffset.push_back(1);
                Q5.yTranslate(aYOffset.back());
                aPeer.push_back(Q5);
                peersAtA.push_back(aPeer);
                addPeerParameterOnRho(aPeer);
                yOffset.push_back(aYOffset);

                isP5Found = true;
                isInitialStructureOfOtherKnot = true;

                return true;
            }
            else {
                aKnot.pop_back();
                if (aP5B.nextXY()) {
                    ;
                }
                else {
                    isLastStructureOfOtherKnot = true;
                    return false;
                }
            }
        }
        cout << "Error!" << endl;
        return false;
    }
    else {
        yOffset.back().back()++;
        if (yOffset.back().back() <= 4) {
            peerParameterOnRho.pop_back();
            peersAtA.back().pop_back();
            BitPosition q5(peersAtA.back().back());
            q5.yTranslate(yOffset.back().back());
            peersAtA.back().push_back(q5);
            addPeerParameterOnRho(peersAtA.back());

            return true;
        }
        else {
            peersAtA.pop_back();
            peerParameterOnRho.pop_back();
            yOffset.pop_back();
            isP5Found = false;
            while ((!isP5Found)) {
                if (aP5B.nextXY()) {
                    aKnot.push_back(aP5B);
                    if (checkKnotInKernelAtC(aKnot)) {
                        vector<BitPosition> aPeer;
                        vector<unsigned int> aYOffset;
                        BitPosition Q5(aP5B);
                        Q5.inverseRhoPi();
                        aPeer.push_back(Q5);
                        aYOffset.push_back(1);
                        Q5.yTranslate(aYOffset.back());
                        aPeer.push_back(Q5);
                        peersAtA.push_back(aPeer);
                        addPeerParameterOnRho(aPeer);
                        yOffset.push_back(aYOffset);

                        isP5Found = true;
                        return true;
                    }
                    else {
                        aKnot.pop_back();
                    }
                }
                else {
                    isLastStructureOfOtherKnot = true;
                    return false;
                }
            }
            cout << "Error!" << endl;
            return false;
        }
    }
}

bool InKernelAtCStructureConstruct::nextStructureOfOtherKnot4222(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeer;
        vector<unsigned int> aYOffset;
        BitPosition p5B(peersAtA[0].back());//q1 at A
        p5B.directRhoPi();//q1'' at B
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//p5''
        p5B.inverseRhoPi();//p5 at A
        aPeer.push_back(p5B);
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//q5 at A
        aPeer.push_back(p5B);
        peersAtA.push_back(aPeer);
        yOffset.push_back(aYOffset);
        addPeerParameterOnRho(aPeer);
        
        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeStructureOfOtherKnot4222();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}

void InKernelAtCStructureConstruct::completeStructureOfOtherKnot4222(){
    vector<BitPosition> aPeer;
    BitPosition p5B(peersAtA[0].back());//q1 at A
    p5B.directRhoPi();//q1'' at B
    p5B.yTranslate(yOffset.back()[0]);//p5''
    p5B.inverseRhoPi();//p5 at A
    aPeer.push_back(p5B);
    p5B.yTranslate(yOffset.back().back());//q5 at A
    aPeer.push_back(p5B);
    peersAtA.push_back(aPeer);
    addPeerParameterOnRho(aPeer);
    return;
}





bool InKernelAtCStructureConstruct::nextStructureOfOtherKnot3322A(){
    count++;
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeerA, aPeerB;
        vector<unsigned int> aYOffset;
        BitPosition p5B(peersAtA.back().back());//q3 at A
        p5B.directRhoPi();//q3"
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//p5"
        p5B.inverseRhoPi();//p5
        aPeerA.push_back(p5B);
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//q5
        aPeerA.push_back(p5B);
        p5B.directRhoPi();//q5"
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//p4"
        p5B.inverseRhoPi();//p4
        aPeerB.push_back(p5B);
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//q4
        aPeerB.push_back(p5B);

        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
        yOffset.push_back(aYOffset);

        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeStructureOfOtherKnot3322A();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}

void InKernelAtCStructureConstruct::completeStructureOfOtherKnot3322A(){
    vector<BitPosition> aPeerA, aPeerB;
    if (yOffset.back().size() == 4) {
        BitPosition p5B(peersAtA.back().back());//q3 at A
        p5B.directRhoPi();//q3"
        p5B.yTranslate(yOffset.back()[0]);//p5"
        p5B.inverseRhoPi();//p5
        aPeerA.push_back(p5B);
        p5B.yTranslate(yOffset.back()[1]);//q5
        aPeerA.push_back(p5B);
        p5B.directRhoPi();//q5"
        p5B.yTranslate(yOffset.back()[2]);//p4"
        p5B.inverseRhoPi();//p4
        aPeerB.push_back(p5B);
        p5B.yTranslate(yOffset.back()[3]);//q4
        aPeerB.push_back(p5B);

        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
    }
    else {
        cout << "Error! There aren't 4 increments in last element of yOffset!" << endl;
    }
    return;
}

bool InKernelAtCStructureConstruct::nextStructureOfOtherKnot3322B(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeerA, aPeerB;
        vector<unsigned int> aYOffset;
        BitPosition p4B(peersAtA[1].back());//q2
        p4B.directRhoPi();//q2"
        aYOffset.push_back(1);
        p4B.yTranslate(aYOffset.back());//p4"
        p4B.inverseRhoPi();//p4
        aPeerA.push_back(p4B);
        aYOffset.push_back(1);
        p4B.yTranslate(aYOffset.back());//q4
        aPeerA.push_back(p4B);
        
        
        BitPosition p5B(peersAtA.back().back());//q3
        p5B.directRhoPi();//q3"
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//p5"
        p5B.inverseRhoPi();//p5
        aPeerB.push_back(p5B);
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//q5
        aPeerB.push_back(p5B);

        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
        yOffset.push_back(aYOffset);

        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeStructureOfOtherKnot3322B();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}
void InKernelAtCStructureConstruct::completeStructureOfOtherKnot3322B(){
    if (yOffset.back().size() == 4) {
        vector<BitPosition> aPeerA, aPeerB;
        BitPosition p4B(peersAtA[1].back());//q2
        p4B.directRhoPi();//q2"
        p4B.yTranslate(yOffset.back()[0]);//p4"
        p4B.inverseRhoPi();//p4
        aPeerA.push_back(p4B);
        p4B.yTranslate(yOffset.back()[1]);//q4
        aPeerA.push_back(p4B);
        BitPosition p5B(peersAtA.back().back());//q3
        p5B.directRhoPi();//q3"
        p5B.yTranslate(yOffset.back()[2]);//p5"
        p5B.inverseRhoPi();//p5
        aPeerB.push_back(p5B);
        p5B.yTranslate(yOffset.back().back());//q5
        aPeerB.push_back(p5B);

        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
    }
    else {
        cout << "Error in size of yOffset[1] in complete other knots! " << endl;
    }
}

bool InKernelAtCStructureConstruct::nextP56OfOtherKnot42222B(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeerB, aPeerC;
        vector<unsigned int> aYOffset;
        
        BitPosition p5B(peersAtA[0].back());//q1
        p5B.directRhoPi();//q1"
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//p5"
        p5B.inverseRhoPi();//p5
        aPeerB.push_back(p5B);
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//q5
        aPeerB.push_back(p5B);
        
        BitPosition p6B(peersAtA[2].back());//q2
        p6B.directRhoPi();//q2"
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//p6"
        p6B.inverseRhoPi();//p6
        aPeerC.push_back(p6B);
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//q6
        aPeerC.push_back(p6B);
        
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
        peersAtA.push_back(aPeerC);
        addPeerParameterOnRho(aPeerC);
        yOffset.push_back(aYOffset);
        
        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeP56OfOtherKnot42222B();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}
void InKernelAtCStructureConstruct::completeP56OfOtherKnot42222B(){
    if (yOffset.back().size() == 4) {
        vector<BitPosition> aPeerB, aPeerC;
        
        
        BitPosition p5B(peersAtA[0].back());//q1
        p5B.directRhoPi();//q1"
        p5B.yTranslate(yOffset.back()[4]);//p5"
        p5B.inverseRhoPi();//p5
        aPeerB.push_back(p5B);
        p5B.yTranslate(yOffset.back()[5]);//q5
        aPeerB.push_back(p5B);
        
        BitPosition p6B(peersAtA[1].back());//q2
        p6B.directRhoPi();//q2"
        p6B.yTranslate(yOffset.back()[2]);//p6"
        p6B.inverseRhoPi();//p6
        aPeerC.push_back(p6B);
        p6B.yTranslate(yOffset.back()[3]);//q6
        aPeerC.push_back(p6B);
        
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
        peersAtA.push_back(aPeerC);
        addPeerParameterOnRho(aPeerC);
    }
    else {
        cout << "Error in size of yOffset[1] in complete other knots! " << endl;
    }
}


bool InKernelAtCStructureConstruct::nextP56OfOtherKnot42222C(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeerB, aPeerC;
        vector<unsigned int> aYOffset;
        
        BitPosition p5B(peersAtA[0].back());//q1
        p5B.directRhoPi();//q1"
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//p5"
        p5B.inverseRhoPi();//p5
        aPeerB.push_back(p5B);
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//q5
        aPeerB.push_back(p5B);
        
        BitPosition p6B(peersAtA[2].back());//q2
        p6B.directRhoPi();//q2"
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//p6"
        p6B.inverseRhoPi();//p6
        aPeerC.push_back(p6B);
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//q6
        aPeerC.push_back(p6B);
        
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
        peersAtA.push_back(aPeerC);
        addPeerParameterOnRho(aPeerC);
        yOffset.push_back(aYOffset);
        
        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeP56OfOtherKnot42222C();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}
void InKernelAtCStructureConstruct::completeP56OfOtherKnot42222C(){
    if (yOffset.back().size() == 4) {
        vector<BitPosition> aPeerB, aPeerC;
        
        
        BitPosition p5B(peersAtA[0].back());//q1
        p5B.directRhoPi();//q1"
        p5B.yTranslate(yOffset.back()[4]);//p5"
        p5B.inverseRhoPi();//p5
        aPeerB.push_back(p5B);
        p5B.yTranslate(yOffset.back()[5]);//q5
        aPeerB.push_back(p5B);
        
        BitPosition p6B(peersAtA[1].back());//q2
        p6B.directRhoPi();//q2"
        p6B.yTranslate(yOffset.back()[2]);//p6"
        p6B.inverseRhoPi();//p6
        aPeerC.push_back(p6B);
        p6B.yTranslate(yOffset.back()[3]);//q6
        aPeerC.push_back(p6B);
        
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
        peersAtA.push_back(aPeerC);
        addPeerParameterOnRho(aPeerC);
    }
    else {
        cout << "Error in size of yOffset[1] in complete other knots! " << endl;
    }
}




bool InKernelAtCStructureConstruct::nextP456OfOtherKnot33222B(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeerA, aPeerB, aPeerC;
        vector<unsigned int> aYOffset;
        BitPosition p6B(peersAtA[2].back());//q3
        p6B.directRhoPi();//q3"
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//p6"
        p6B.inverseRhoPi();//p6
        aPeerA.push_back(p6B);
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//q6
        aPeerA.push_back(p6B);
        
        
        BitPosition p5B(aPeerA.back());//q6
        p5B.directRhoPi();//q6"
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//p5"
        p5B.inverseRhoPi();//p5
        aPeerC.push_back(p5B);
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//q5
        aPeerC.push_back(p5B);
        
        BitPosition p4B(aPeerC.back());//q5
        p4B.directRhoPi();//q5"
        aYOffset.push_back(1);
        p4B.yTranslate(aYOffset.back());//p4"
        p4B.inverseRhoPi();//p4
        aPeerB.push_back(p4B);
        aYOffset.push_back(1);
        p4B.yTranslate(aYOffset.back());//q4
        aPeerB.push_back(p4B);
        
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);//p4q4
        
        peersAtA.push_back(aPeerC);
        addPeerParameterOnRho(aPeerC);//p5q5
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);//p6q6
        
        yOffset.push_back(aYOffset);
        
        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeP456OfOtherKnot33222B();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}
void InKernelAtCStructureConstruct::completeP456OfOtherKnot33222B(){
    if (yOffset.back().size() == 6) {

        vector<BitPosition> aPeerA, aPeerB, aPeerC;
        vector<unsigned int> aYOffset;
        BitPosition p6B(peersAtA[2].back());//q3
        p6B.directRhoPi();//q3"
        
        p6B.yTranslate(yOffset.back()[0]);//p6"
        p6B.inverseRhoPi();//p6
        aPeerA.push_back(p6B);
        
        p6B.yTranslate(yOffset.back()[1]);//q6
        aPeerA.push_back(p6B);
        
        
        BitPosition p5B(aPeerA.back());//q6
        p5B.directRhoPi();//q6"
        p5B.yTranslate(yOffset.back()[2]);//p5"
        p5B.inverseRhoPi();//p5
        aPeerC.push_back(p5B);
        p5B.yTranslate(yOffset.back()[3]);//q5
        aPeerC.push_back(p5B);
        
        BitPosition p4B(aPeerC.back());//q5
        p4B.directRhoPi();//q5"
        p4B.yTranslate(yOffset.back()[4]);//p4"
        p4B.inverseRhoPi();//p4
        aPeerB.push_back(p4B);
        p4B.yTranslate(yOffset.back()[5]);//q4
        aPeerB.push_back(p4B);
        
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);//p4q4
        
        peersAtA.push_back(aPeerC);
        addPeerParameterOnRho(aPeerC);//p5q5
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);//p6q6
    }
    else {
        cout << "Error in size of yOffset[1] in complete other knots! " << endl;
    }
}




bool InKernelAtCStructureConstruct::nextP456OfOtherKnot33222C(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeerA, aPeerB, aPeerC;
        vector<unsigned int> aYOffset;
        BitPosition p4B(peersAtA[1].back());//q2
        p4B.directRhoPi();//q2"
        aYOffset.push_back(1);
        p4B.yTranslate(aYOffset.back());//p4"
        p4B.inverseRhoPi();//p4
        aPeerA.push_back(p4B);
        aYOffset.push_back(1);
        p4B.yTranslate(aYOffset.back());//q4
        aPeerA.push_back(p4B);
        
        
        BitPosition p6B(peersAtA.back().back());//q3
        p6B.directRhoPi();//q3"
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//p6"
        p6B.inverseRhoPi();//p6
        aPeerC.push_back(p6B);
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//q6
        aPeerC.push_back(p6B);
        
        BitPosition p5B(aPeerC.back());//q6
        p5B.directRhoPi();//q6"
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//p5"
        p5B.inverseRhoPi();//p5
        aPeerB.push_back(p5B);
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//q5
        aPeerB.push_back(p5B);
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
        peersAtA.push_back(aPeerC);
        addPeerParameterOnRho(aPeerC);
        yOffset.push_back(aYOffset);
        
        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeP456OfOtherKnot33222C();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}
void InKernelAtCStructureConstruct::completeP456OfOtherKnot33222C(){
    if (yOffset.back().size() == 6) {
        vector<BitPosition> aPeerA, aPeerB, aPeerC;
        BitPosition p4B(peersAtA[1].back());//q2
        p4B.directRhoPi();//q2"
        p4B.yTranslate(yOffset.back()[0]);//p4"
        p4B.inverseRhoPi();//p4
        aPeerA.push_back(p4B);
        p4B.yTranslate(yOffset.back()[1]);//q4
        aPeerA.push_back(p4B);
        
        BitPosition p6B(peersAtA.back().back());//q3
        p6B.directRhoPi();//q3"
        p6B.yTranslate(yOffset.back()[2]);//p6"
        p6B.inverseRhoPi();//p6
        aPeerC.push_back(p6B);
        p6B.yTranslate(yOffset.back()[3]);//q6
        aPeerC.push_back(p6B);
        
        BitPosition p5B(aPeerC.back());//q6
        p5B.directRhoPi();//q6"
        
        p5B.yTranslate(yOffset.back()[4]);//p5"
        p5B.inverseRhoPi();//p5
        aPeerB.push_back(p5B);
        
        p5B.yTranslate(yOffset.back()[5]);//q5
        aPeerB.push_back(p5B);
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
        peersAtA.push_back(aPeerC);
        addPeerParameterOnRho(aPeerC);
    }
    else {
        cout << "Error in size of yOffset[1] in complete other knots! " << endl;
    }
}

bool InKernelAtCStructureConstruct::nextP4Q4OfOtherKnot33222C1(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeerA;
        vector<unsigned int> aYOffset;
        BitPosition p4B(peersAtA[1].back());//q2
        p4B.directRhoPi();//q2"
        aYOffset.push_back(1);
        p4B.yTranslate(aYOffset.back());//p4"
        p4B.inverseRhoPi();//p4
        aPeerA.push_back(p4B);
        aYOffset.push_back(1);
        p4B.yTranslate(aYOffset.back());//q4
        aPeerA.push_back(p4B);
        
        
        
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);

        yOffset.push_back(aYOffset);
        
        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeP4Q4OfOtherKnot33222C1();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}
void InKernelAtCStructureConstruct::completeP4Q4OfOtherKnot33222C1(){
    if (yOffset.back().size() == 2) {
        vector<BitPosition> aPeerA;
        BitPosition p4B(peersAtA[1].back());//q2
        p4B.directRhoPi();//q2"
    
        p4B.yTranslate(yOffset.back()[0]);//p4"
        p4B.inverseRhoPi();//p4
        aPeerA.push_back(p4B);
        p4B.yTranslate(yOffset.back()[1]);//q4
        aPeerA.push_back(p4B);
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
    }
    else {
        cout << "Error in size of yOffset[1] in complete other knots! " << endl;
    }
}


bool InKernelAtCStructureConstruct::nextP6Q6OfOtherKnot33222A(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeerA;
        vector<unsigned int> aYOffset;
        BitPosition p6B(peersAtA[3].back());//q4
        p6B.directRhoPi();//q4"
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//p6"
        p6B.inverseRhoPi();//p6
        aPeerA.push_back(p6B);
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//q6
        aPeerA.push_back(p6B);
        
        
        
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
        
        yOffset.push_back(aYOffset);
        
        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeP6Q6OfOtherKnot33222A();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}
void InKernelAtCStructureConstruct::completeP6Q6OfOtherKnot33222A(){
    if (yOffset.back().size() == 2) {
        vector<BitPosition> aPeerA;
        
        
        BitPosition p6B(peersAtA[3].back());//q4
        p6B.directRhoPi();//q4"
        p6B.yTranslate(yOffset.back()[0]);//p6"
        p6B.inverseRhoPi();//p6
        aPeerA.push_back(p6B);
        p6B.yTranslate(yOffset.back()[1]);//q6
        aPeerA.push_back(p6B);
        
        
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
    }
    else {
        cout << "Error in size of yOffset[1] in complete other knots! " << endl;
    }
}




bool InKernelAtCStructureConstruct::nextP3Q3OfOtherKnot222(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeerA;
        vector<unsigned int> aYOffset;
        BitPosition p3B(peersAtA[0].back());//q1
        p3B.directRhoPi();//q1"
        aYOffset.push_back(1);
        p3B.yTranslate(aYOffset.back());//p3"
        p3B.inverseRhoPi();//p3
        aPeerA.push_back(p3B);
        aYOffset.push_back(1);
        p3B.yTranslate(aYOffset.back());//q3
        aPeerA.push_back(p3B);
        
        
        
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
        
        yOffset.push_back(aYOffset);
        
        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeP3Q3OfOtherKnot222();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}
void InKernelAtCStructureConstruct::completeP3Q3OfOtherKnot222(){
    if (yOffset.back().size() == 2) {
        vector<BitPosition> aPeerA;
        
        
        BitPosition p3B(peersAtA[0].back());//q1
        p3B.directRhoPi();//q1"
        p3B.yTranslate(yOffset.back()[0]);//p3"
        p3B.inverseRhoPi();//p3
        aPeerA.push_back(p3B);
        p3B.yTranslate(yOffset.back()[1]);//q3
        aPeerA.push_back(p3B);
        
        
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
    }
    else {
        cout << "Error in size of yOffset[1] in complete other knots! " << endl;
    }
}




bool InKernelAtCStructureConstruct::nextP456OfOtherKnot33222D2(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeerA, aPeerB, aPeerC;
        vector<unsigned int> aYOffset;
        BitPosition p4B(peersAtA[0].back());//q1
        p4B.directRhoPi();//q1"
        aYOffset.push_back(1);
        p4B.yTranslate(aYOffset.back());//p4"
        p4B.inverseRhoPi();//p4
        aPeerA.push_back(p4B);
        aYOffset.push_back(1);
        p4B.yTranslate(aYOffset.back());//q4
        aPeerA.push_back(p4B);
        
        BitPosition p5B(peersAtA[1].back());//q2
        p5B.directRhoPi();//q2"
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//p5"
        p5B.inverseRhoPi();//p5
        aPeerB.push_back(p5B);
        aYOffset.push_back(1);
        p5B.yTranslate(aYOffset.back());//q5
        aPeerB.push_back(p5B);
        
        BitPosition p6B(peersAtA.back().back());//q3
        p6B.directRhoPi();//q3"
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//p6"
        p6B.inverseRhoPi();//p6
        aPeerC.push_back(p6B);
        aYOffset.push_back(1);
        p6B.yTranslate(aYOffset.back());//q6
        aPeerC.push_back(p6B);
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
        peersAtA.push_back(aPeerC);
        addPeerParameterOnRho(aPeerC);
        yOffset.push_back(aYOffset);
        
        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeP456OfOtherKnot33222D2();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}
void InKernelAtCStructureConstruct::completeP456OfOtherKnot33222D2(){
    if (yOffset.back().size() == 6) {
        vector<BitPosition> aPeerA, aPeerB, aPeerC;
        BitPosition p4B(peersAtA[0].back());//q1
        p4B.directRhoPi();//q1"
        p4B.yTranslate(yOffset.back()[0]);//p4"
        p4B.inverseRhoPi();//p4
        aPeerA.push_back(p4B);
        p4B.yTranslate(yOffset.back()[1]);//q4
        aPeerA.push_back(p4B);
        
        BitPosition p5B(peersAtA[1].back());//q2
        p5B.directRhoPi();//q2"
        p5B.yTranslate(yOffset.back()[4]);//p5"
        p5B.inverseRhoPi();//p5
        aPeerB.push_back(p5B);
        p5B.yTranslate(yOffset.back()[5]);//q5
        aPeerB.push_back(p5B);
        
        BitPosition p6B(peersAtA[2].back());//q3
        p6B.directRhoPi();//q3"
        p6B.yTranslate(yOffset.back()[2]);//p6"
        p6B.inverseRhoPi();//p6
        aPeerC.push_back(p6B);
        p6B.yTranslate(yOffset.back()[3]);//q6
        aPeerC.push_back(p6B);
        
        peersAtA.push_back(aPeerA);
        addPeerParameterOnRho(aPeerA);
        peersAtA.push_back(aPeerB);
        addPeerParameterOnRho(aPeerB);
        peersAtA.push_back(aPeerC);
        addPeerParameterOnRho(aPeerC);
    }
    else {
        cout << "Error in size of yOffset[1] in complete other knots! " << endl;
    }
}




bool InKernelAtCStructureConstruct::nextStructureOfOtherKnot(){
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeer;
        vector<unsigned int> aYOffset;
        BitPosition pB(peersAtA.back().back());//at A
        pB.directRhoPi();// to B
        aYOffset.push_back(1);
        pB.yTranslate(aYOffset.back());//orbital
        pB.inverseRhoPi();//to A
        aPeer.push_back(pB);
        aYOffset.push_back(1);
        pB.yTranslate(aYOffset.back());//peer
        aPeer.push_back(pB);
        yOffset.push_back(aYOffset);
        peersAtA.push_back(aPeer);
        addPeerParameterOnRho(aPeer);
        isInitialStructureOfOtherKnot = true;
        return true;
    }
    else {
        if (recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeStructureOfOtherKnot();
            return true;
        }
        else {
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}

void InKernelAtCStructureConstruct::completeStructureOfOtherKnot(){
    vector<BitPosition> aPeer;
    BitPosition pB(peersAtA.back().back());//at A
    pB.directRhoPi();// to B
    pB.yTranslate(yOffset.back()[0]);//orbital
    pB.inverseRhoPi();//to A
    aPeer.push_back(pB);
    pB.yTranslate(yOffset.back().back());//peer
    aPeer.push_back(pB);
    peersAtA.push_back(aPeer);
    addPeerParameterOnRho(aPeer);
    return;
}

bool InKernelAtCStructureConstruct::updateStartingKnot(){
    unsigned int totalCounter = startingKnotPoints.size();
    startingKnotUpdateCounter++;
    if (startingKnotUpdateCounter <= totalCounter) {
        vector<BitPosition> aKnotPoints = startingKnotPoints;
        for (int i = 0; i < totalCounter; i++) {
            startingKnotPoints[i] = aKnotPoints[(i+1)%totalCounter];
        }
        return true;
    }
    else{
        return false;
    }
}

bool InKernelAtCStructureConstruct::updateStartingKnot(const unsigned int chooseCode){
    startingKnotUpdateCounter++;
    unsigned int totalCounter = 0;
    vector<BitPosition> aKnotPoints = startingKnotPoints;

    if ((chooseCode==442) || (chooseCode==332) || (chooseCode==33221)) {
        totalCounter = startingKnotPoints.size();
        if (startingKnotUpdateCounter <= totalCounter) {
            for (int i = 0; i < totalCounter; i++) {
                startingKnotPoints[i] = aKnotPoints[(i+1)%totalCounter];
            }
            return true;
        }
        else{
            return false;
        }
    }
    else if (chooseCode==433) {
//        totalCounter = startingKnotPoints.size()-1;

        
        if (startingKnotUpdateCounter <= 3) {
            for (int i = 0; i < 3; i++) {
                startingKnotPoints[i] = aKnotPoints[(i+1)%3];
            }
            return true;
        }
        else {
            return false;
        }
    }
    else if (chooseCode == 4222) {
        vector<vector<unsigned int>> combinationDeterminator = {
            {0, 1, 2, 3}, {2, 3, 0, 1},
            {2, 0, 3, 1}, {2, 3, 0, 1},
            {2, 1, 0, 3}, {2, 3, 0, 1}
        };
        totalCounter = startingKnotPoints.size();
   
        
        if ((startingKnotUpdateCounter <= 6) && (totalCounter == 4)) {
            for (int i = 0; i < totalCounter; i++) {
                startingKnotPoints[i] = aKnotPoints[combinationDeterminator[startingKnotUpdateCounter - 1][i]];
            }
            return true;
        }
        else {
            return false;
        }
    }
//    else if (<#condition#>) {
//
//    }
    else {
        cout << "Cannot update starting knot!" << endl;
        return false;
    }
}

bool InKernelAtCStructureConstruct::nextStructureOfStaringKnot(){
    peersAtA.clear();
    peerParameterOnRho.clear();
    if (!isInitialStructure) {
        vector<unsigned int> aYOffset;
        //initialization
        for (int i = 0; i < startingKnotPoints.size(); i++) {
            vector<BitPosition> aPeerAtA;
            BitPosition pA(startingKnotPoints[i]);//knot at B
            pA.inverseRhoPi();//to A
            aPeerAtA.push_back(pA);
            aYOffset.push_back(1);
            pA.yTranslate(aYOffset.back());// in a peer, get qi
            //orbital
            aPeerAtA.push_back(pA);
            //orbitals in slice
            peersAtA.push_back(aPeerAtA);
            addPeerParameterOnRho(aPeerAtA);
        }
        yOffset.push_back(aYOffset);
        isInitialStructure = true;
        return true;
    }
   else {
        if(recursiveYOffsetOfStartingKnot(yOffset[0])) {
            completeStructureOfStartingKnot();
            return true;
        }
        else{
            isLastStructureOfStartingKnot = true;
            return false;
        }
    }
}

void InKernelAtCStructureConstruct::completeStructureOfStartingKnot(){
    for (int i =0; i < startingKnotPoints.size(); i++) {
        vector<BitPosition> aPeerAtA;
        BitPosition pA(startingKnotPoints[i]);
        pA.inverseRhoPi();
        aPeerAtA.push_back(pA);
        pA.yTranslate(yOffset[0][i]);
        aPeerAtA.push_back(pA);
        
        //orbitals at A
        peersAtA.push_back(aPeerAtA);
        
        //compute v
        addPeerParameterOnRho(aPeerAtA);
    }
    return;
}




bool InKernelAtCStructureConstruct::nextStructureOfChain22(unsigned int nrObitals){
//    peersAtA.clear();
//    peerParameterOnRho.clear();
    if (!isInitialStructureOfOtherKnot) {
        vector<BitPosition> aPeer;
        vector<unsigned int> aYOffset;
        for (int i=1; i<(nrObitals-1); i++) {
            aPeer.clear();
            BitPosition q1A(peersAtA[i].back());//q(i+1)
            q1A.directRhoPi();//q(i+1)"
            aYOffset.push_back(1);
            
            q1A.yTranslate(aYOffset.back());//orbital p(i+2)"
            
            q1A.inverseRhoPi();//p(i+2)
            aPeer.push_back(q1A);
            aYOffset.push_back(1);
            q1A.yTranslate(aYOffset.back());//orbital q(i+2)
            
            aPeer.push_back(q1A);
            peersAtA.push_back(aPeer);
            addPeerParameterOnRho(aPeer);
        }
        
        yOffset.push_back(aYOffset);
        isInitialStructureOfOtherKnot = true;
        return true;

    }
    else {
        if(recursiveYOffsetOfStartingKnot(yOffset[1])) {
            completeStructureOfChain22(nrObitals);
            return true;
        }
        else{
            isLastStructureOfOtherKnot = true;
            return false;
        }
    }
}

void InKernelAtCStructureConstruct::completeStructureOfChain22(unsigned int nrObitals){
    vector<BitPosition> aPeer;

    for (int i=1; i<(nrObitals-1); i++) {
        aPeer.clear();
        BitPosition q1A(peersAtA[i].back());//q(i+1)
        q1A.directRhoPi();//q(i+1)"
       

        q1A.yTranslate(yOffset.back()[2*i-2]);//orbital p(i+2)"
        
        q1A.inverseRhoPi();//p(i+2)
        aPeer.push_back(q1A);

        q1A.yTranslate(yOffset.back()[2*i-1]);//orbital q(i+2)
        
        aPeer.push_back(q1A);
        peersAtA.push_back(aPeer);
        addPeerParameterOnRho(aPeer);
    }
 
    return;
}



bool InKernelAtCStructureConstruct::nextStructureOfStaringKnot22(){
    peersAtA.clear();
    peerParameterOnRho.clear();
    if (!isInitialStructure) {
        
        
        vector<BitPosition> aPeer;
        vector<unsigned int> aYOffset;
        BitPosition q1A(startingKnotPoints[0]);//q1"
        q1A.inverseRhoPi();// q1
        aYOffset.push_back(1);

        BitPosition p1A(q1A);
        p1A.yTranslate(aYOffset.back());//orbital p1
        aPeer.push_back(p1A);
        aPeer.push_back(q1A);
        peersAtA.push_back(aPeer);
        addPeerParameterOnRho(aPeer);
        
        aPeer.clear();
        BitPosition p2A(startingKnotPoints[1]);//p2"
        p2A.inverseRhoPi();// p2
        aYOffset.push_back(1);
        
        BitPosition q2A(p2A);
        q2A.yTranslate(aYOffset.back());//orbital p1
        aPeer.push_back(p2A);
        aPeer.push_back(q2A);
        
        peersAtA.push_back(aPeer);
        addPeerParameterOnRho(aPeer);
        
        yOffset.push_back(aYOffset);
        
        isInitialStructure = true;
        return true;
                           
                           
                           
    }
    else {
        if(recursiveYOffsetOfStartingKnot(yOffset[0])) {
            completeStructureOfStartingKnot22();
            return true;
        }
        else{
            isLastStructureOfStartingKnot = true;
            return false;
        }
    }
}

void InKernelAtCStructureConstruct::completeStructureOfStartingKnot22(){
    vector<BitPosition> aPeer;
    BitPosition q1A(startingKnotPoints[0]);//q1"
    q1A.inverseRhoPi();// q1
    
    BitPosition p1A(q1A);
    p1A.yTranslate(yOffset[0][0]);//orbital p1
    aPeer.push_back(p1A);
    aPeer.push_back(q1A);
    peersAtA.push_back(aPeer);
    addPeerParameterOnRho(aPeer);
    
    aPeer.clear();
    BitPosition p2A(startingKnotPoints[1]);//p2"
    p2A.inverseRhoPi();// p2
    
    BitPosition q2A(p2A);
    q2A.yTranslate(yOffset[0][1]);//orbital p1
    aPeer.push_back(p2A);
    aPeer.push_back(q2A);
    
    peersAtA.push_back(aPeer);
    addPeerParameterOnRho(aPeer);
    
    return;
}


//used for 33222C1
bool InKernelAtCStructureConstruct::constructingStaringKnotfor2Orbitals(){
    
//    peersAtA.pop_back();
//    peersAtA.pop_back();
//    peerParameterOnRho.pop_back();
//    peerParameterOnRho.pop_back();
    
    if (!isInitialStructure2) {
        vector<unsigned int> aYOffset;
        //initialization
        for (int i = 0; i < startingKnotPoints2.size(); i++) {
            vector<BitPosition> aPeerAtA;
            BitPosition pA(startingKnotPoints2[i]);//knot at B
            pA.inverseRhoPi();//to A
            aPeerAtA.push_back(pA);
            aYOffset.push_back(1);
            pA.yTranslate(aYOffset.back());// in a peer, get qi
            //orbital
            aPeerAtA.push_back(pA);
            //orbitals in slice
            peersAtA.push_back(aPeerAtA);
            addPeerParameterOnRho(aPeerAtA);
        }
        yOffset.push_back(aYOffset);
        isInitialStructure2 = true;
        return true;
    }
    else {
        if(recursiveYOffsetOfStartingKnot(yOffset.back())) {
            completeConstructingOfStartingKnotfor2Orbitals();
            return true;
        }
        else{
            isLastStructureOfStartingKnot2 = true;
            return false;
        }
    }
}


void InKernelAtCStructureConstruct::completeConstructingOfStartingKnotfor2Orbitals(){
    for (int i =0; i < startingKnotPoints2.size(); i++) {
        vector<BitPosition> aPeerAtA;
        BitPosition pA(startingKnotPoints2[i]);
        pA.inverseRhoPi();
        aPeerAtA.push_back(pA);
        pA.yTranslate(yOffset.back()[i]);
        aPeerAtA.push_back(pA);
        
        //orbitals at A
        peersAtA.push_back(aPeerAtA);
        
        //compute v
        addPeerParameterOnRho(aPeerAtA);
    }
    return;
}


//used for 42222A
bool InKernelAtCStructureConstruct::constructingStaringKnot42222A(){
    
    //    peersAtA.pop_back();
    //    peersAtA.pop_back();
    //    peerParameterOnRho.pop_back();
    //    peerParameterOnRho.pop_back();
    
    if (!isInitialStructure2) {
        vector<unsigned int> aYOffset;
        //initialization
        for (int i = 0; i < startingKnotPoints2.size(); i++) {
            vector<BitPosition> aPeerAtA;
            BitPosition pA(startingKnotPoints2[i]);//knot at B
            pA.inverseRhoPi();//to A
            aPeerAtA.push_back(pA);
            aYOffset.push_back(1);
            pA.yTranslate(aYOffset.back());// in a peer, get qi
            //orbital
            aPeerAtA.push_back(pA);
            //orbitals in slice
            peersAtA.push_back(aPeerAtA);
            addPeerParameterOnRho(aPeerAtA);
        }
        yOffset.push_back(aYOffset);
        isInitialStructure2 = true;
        return true;
    }
    else {
        if(recursiveYOffsetOfStartingKnot(yOffset[1])) {
            completeConstructingOfStartingKnotfor2Orbitals();
            return true;
        }
        else{
            isLastStructureOfStartingKnot2 = true;
            return false;
        }
    }
}


void InKernelAtCStructureConstruct::completeConstructingOfStartingKnot42222A(){
    for (int i =0; i < startingKnotPoints2.size(); i++) {
        vector<BitPosition> aPeerAtA;
        BitPosition pA(startingKnotPoints2[i]);
        pA.inverseRhoPi();
        aPeerAtA.push_back(pA);
        pA.yTranslate(yOffset[1][i]);
        aPeerAtA.push_back(pA);
        
        //orbitals at A
        peersAtA.push_back(aPeerAtA);
        
        //compute v
        addPeerParameterOnRho(aPeerAtA);
    }
    return;
}
































