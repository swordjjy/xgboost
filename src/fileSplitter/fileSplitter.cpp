//
//  fileSplitter.cpp
//  fileSplitter
//
//  Created by Haifeng Zhao on 11/28/15.
//  Copyright © 2015 Haifeng Zhao. All rights reserved.
//

#include "fileSplitter.hpp"
#include <stdlib.h>
fileSplitter::fileSplitter(const char * inputFileName, int bufferSize, size_t memSize,
                           map<char,bool> & delimiters): bufferSize(bufferSize), memSize(memSize), delimiters(delimiters), buffer(NULL), splitSizes(NULL)
{
    strcpy(inputFile, inputFileName);
    
}

fileSplitter::~fileSplitter(){
    if(buffer != NULL)
        delete [] buffer;
    if(splitSizes != NULL)
        delete [] splitSizes;
    
}

bool fileSplitter::prepareSplit(size_t inputFileSize){
    splitCount = (int)inputFileSize/memSize + ((int)(inputFileSize)%memSize==0?0:1);
    splitDigitLen = 1;
    int i = splitCount;
    while(i/10!=0){
        splitDigitLen++;
        i = i/10;
    }
    
    
    splitSizes = new size_t[splitCount];
    for (i = 0; i <splitCount ; i++) {
        splitSizes[i] = memSize;
    }
    splitSizes[splitCount-1] = splitSizes[splitCount-2] = (splitSizes[splitCount-1] + splitSizes[splitCount-2]+1)/2;
    try {
        buffer = new char[bufferSize];
        return true;
    } catch (exception&e) {
        cout << e.what() << '\n';
        return false;
    }
    
    
}

bool fileSplitter::splitfile(){
    int i = 0;
    try
    {
        ifstream is(inputFile);
        if(!is){
            cout<<"fail open"<<endl;
        }
        is.seekg (0, is.end);
        size_t length = is.tellg();
        is.seekg (0, is.beg);
	cout << "file len:" << length << endl;        
        if(!prepareSplit(length)){
            cout << "fileSplitter::splitfile : buffer allocation returns error" << endl;
            return false;
        }
        for (i = 0; i < splitCount; i++){
            createPartition(is, i);
        }
        is.close();
        return true;
        
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
        cout << "at" << i << "th partition" << endl ;
        
    }
    return false;
}

void fileSplitter::createPartition(ifstream & is, int index){
    
    string partitionFileName = "partition";
    //string partitionFileName = "output";
    
    //determine output file name
    int indexDigitLen = 1;
    unsigned int i = index;
    while(i/10!=0){
        indexDigitLen++;
        i = i/10;
    }
    while(indexDigitLen < splitDigitLen){
        partitionFileName += '0';
        indexDigitLen++;
    } 
    //cout << partitionFileName << index <<  endl;
    ////partitionFileName += to_string(index);
    partitionFileName += to_string((_Longlong)index);
    cout << partitionFileName << endl;
    ofstream os(partitionFileName);
    if(!os){
        cout<<"outfilt open file"<<endl;
    }
    
    size_t partitionSize = splitSizes[index];
    int totalReads = (int)partitionSize/bufferSize + ((int)(partitionSize)%bufferSize==0?0:1);
    
    //process first buffer read
    size_t extracted = is.read(buffer, bufferSize).gcount();
    int readIndex = 1;
    map<char,bool>::iterator it;
    size_t firstBlockStart = 0;
    for(i = 0; i < extracted; i++){
        //it = delimiters.begin();
        //it = delimiters.find(buffer[i]);
        if (delimiters.find(buffer[i]) != delimiters.end()){
            firstBlockStart = i+1; //os.write(buffer+i,bufferSize-i);
            break;
        }
    }
    if(i == extracted)
    {
        cout << "no delimiter found in the entire first buffer read to the partition " << index << "! Too small buffer?" << endl;
	return;
    }
    
    while(is && readIndex < totalReads){
        if(readIndex == 1){
            os.write(buffer+firstBlockStart,bufferSize-firstBlockStart);
            firstBlockStart = 0;
        }
        else {
            os.write(buffer,bufferSize);
        }
        extracted = is.read(buffer, bufferSize).gcount();
        readIndex++;
    }
    
    //    int i = 0;
    //    if(extracted == bufferSize && i < totalReads - 1){
    //        os.write(buffer+firstBlockStart,bufferSize-firstBlockStart);
    //        firstBlockStart = 0;
    //    }
    //
    //    while(is && i < totalReads-1){  //the last read should be forced to stripping outside the loop
    //        os.write(buffer,bufferSize);
    //        extracted = is.read(buffer, bufferSize).gcount();
    //        i++;
    //    }
    
    //strip the last line from the partition
    
    //    int delimiterCount = 0;
    size_t lastDelimiterPos = -1;
    for(i = extracted - 1; i >= 0; i--){
        //it = delimiters.begin();
        //it = delimiters.find(buffer[i]);
        if (delimiters.find(buffer[i]) != delimiters.end()){
            lastDelimiterPos = i;
            break;
            //            if (delimiterCount == 0){
            //                delimiterCount ++;
            //            }
            //            else if(delimiterCount == 1)
            //            {
            //                break;
            //            }
        }
    }
    if(lastDelimiterPos <= 0){
        cout << "no delimiter found in the entire last buffer read to partition " << index << "! Too small buffer?" << endl;
        return;
    }
    
    os.write(buffer+firstBlockStart,lastDelimiterPos-firstBlockStart+1);
    os.close();
    partitionNames.push_back(partitionFileName);
    
}

int fileSplitter::getSplitDigitLen() const {
    return splitDigitLen;
}

const vector<string> & fileSplitter::getpartitionNames() const {
    return partitionNames;
}

