#include <iostream>
#include "CWordCount.h"
using namespace WordCount;
int main(int argc,char** argv) {
    CWordCount wordcnt;
    return(wordcnt.entrance(argc,argv));
    //std::cout << "Hello, World!" << std::endl;
    return 0;
}