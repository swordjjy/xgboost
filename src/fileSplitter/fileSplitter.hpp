//
//  fileSplitter.hpp
//  fileSplitter
//
//  Created by Haifeng Zhao on 11/28/15.
//  Copyright © 2015 Haifeng Zhao. All rights reserved.
//

#ifndef fileSplitter_hpp
#define fileSplitter_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <exception>
#include <iostream>
#include <map>
#include <string.h>
#include <vector>
using namespace std;

#endif /* fileSplitter_hpp */

class fileSplitter
{
    char * buffer = NULL;
    int bufferSize;
    //int splits;
    size_t * splitSizes = NULL;
    char inputFile[256];
    int splitDigitLen;
    int splitCount;
    size_t memSize;
    map<char,bool> & delimiters;
    vector<string> partitionNames;
public:
    fileSplitter(const char* inputFile, int bufferSize, size_t memSize, map<char,bool> & delimiters);
    ~fileSplitter();
    bool splitfile();
    void createPartition(ifstream & is, int index);
    bool prepareSplit(size_t inputFileSize);
    int getSplitDigitLen() const;
    const vector<string> & getpartitionNames() const;
};



