//
//  main.cpp
//  fileSplitter
//
//  Created by Haifeng Zhao on 11/28/15.
//  Copyright © 2015 Haifeng Zhao. All rights reserved.
//


// print the content of a text file.
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include "fileSplitter.hpp"
#include <map>
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    //
    //        ifstream ifs("/Users/haifengzhao/programs/c++/fileSplitter/test");
    //        if(!ifs.is_open())
    //            cout<<"file does not exist"<<endl;
    //        else{
    //            char buffer[200];
    //            int extracted  = ifs.read(buffer, 200).gcount();
    //            if(ifs){
    //                cout<<"valid while eof"<<endl;
    //            }
    //            else
    //                cout<<"not valid while eof"<<endl;
    //            cout<<"file read returns "<<extracted<<" bytes"<<endl;
    //            cout<<"buffer content:"<<buffer<<endl;
    //        }
    //        ifs.close();
    
    // (char * inputFileName, int bufferSize, size_t memSize,
    //  map<char,bool> & delimiters)
    map<char,bool> delimiters;
    delimiters.insert (pair<char,bool>('\n',500));
    char fileName[256] = "train";
    
    cout << "file name:" << endl;
    cin >> fileName;
    int bufferSize = 0;
    int memSize = 0;
    cout << "provide bufferSize:";
    cin >> bufferSize;
    cout << "provide memSize:";
    cin >> memSize;
    cout << endl;
    fileSplitter splitter(fileName, bufferSize, memSize, delimiters);
    splitter.splitfile();
    const vector<string> partitionNames = splitter.getpartitionNames();
    for(vector<string>::const_iterator it = partitionNames.begin(); it != partitionNames.end(); ++it) {
        cout<<*it<<endl;
    }
        
    return 0;
}
