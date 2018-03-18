//
// Created by starsapphire on 18-3-18.
//

#include "CWordCount.h"
#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>
using namespace std;
using namespace WordCount;
#define GENERATE_ARG(NAME,ARG) char* NAME = (char*)malloc(strlen(ARG)+1);\
                               memcpy(NAME,ARG,strlen(ARG));\
                               NAME[strlen(ARG)]=0;
#define CLEAR_ARGS for(int i=0;i<argc;++i) free(argv[i]);\
                   free(argv);
TEST(TestMethod1,UnitTest1){
    char** argv=(char**)malloc(sizeof(char*));
    GENERATE_ARG(arg,"test.exe");
    argv[0]=arg;
    int argc=1;
    CWordCount test;
    EXPECT_EQ(test.entrance(argc,argv),-1);
    CLEAR_ARGS;
}
TEST(TestMethod2,UnitTest1){
    char** argv=(char**)malloc(sizeof(char*)*3);
    GENERATE_ARG(arg0,"test.exe");
    argv[0]=arg0;
    GENERATE_ARG(arg1,"-q");
    argv[1]=arg1;
    GENERATE_ARG(arg2,"input.exe");
    argv[2]=arg2;
    int argc=3;
    CWordCount test;
    EXPECT_EQ(test.entrance(argc,argv),2);
    CLEAR_ARGS;
}
TEST(TestMethod3,UnitTest1){
    char** argv=(char**)malloc(sizeof(char*)*4);
    GENERATE_ARG(arg0,"test.exe");
    argv[0]=arg0;
    GENERATE_ARG(arg1,"-c");
    argv[1]=arg1;
    GENERATE_ARG(arg2,"-c");
    argv[2]=arg2;
    GENERATE_ARG(arg3,"input.txt");
    argv[3]=arg3;
    int argc=4;
    CWordCount test;
    EXPECT_EQ(test.entrance(argc,argv),1);
    CLEAR_ARGS;
}
TEST(TestMethod4,UnitTest1){
    char** argv=(char**)malloc(sizeof(char*)*4);
    GENERATE_ARG(arg0,"test.exe");
    argv[0]=arg0;
    GENERATE_ARG(arg1,"-c");
    argv[1]=arg1;
    GENERATE_ARG(arg2,"input.txt");
    argv[2]=arg2;
    GENERATE_ARG(arg3,"-r");
    argv[3]=arg3;
    int argc=4;
    CWordCount test;
    EXPECT_EQ(test.entrance(argc,argv),3);
    CLEAR_ARGS;
}
TEST(TestMethod5,UnitTest1){
    char** argv=(char**)malloc(sizeof(char*)*6);
    GENERATE_ARG(arg0,"test.exe");
    argv[0]=arg0;
    GENERATE_ARG(arg1,"-c");
    argv[1]=arg1;
    GENERATE_ARG(arg2,"input.txt");
    argv[2]=arg2;
    GENERATE_ARG(arg3,"-o");
    argv[3]=arg3;
    GENERATE_ARG(arg4,"output.txt");
    argv[4]=arg4;
    GENERATE_ARG(arg5,"-c");
    argv[5]=arg5;
    int argc=6;
    CWordCount test;
    EXPECT_EQ(test.entrance(argc,argv),4);
    CLEAR_ARGS;
}
TEST(TestMethod6,UnitTest1){
    char** argv=(char**)malloc(sizeof(char*)*4);
    GENERATE_ARG(arg0,"test.exe");
    argv[0]=arg0;
    GENERATE_ARG(arg1,"-c");
    argv[1]=arg1;
    GENERATE_ARG(arg2,"input.txt");
    argv[2]=arg2;
    GENERATE_ARG(arg3,"-o");
    argv[3]=arg3;
    int argc=4;
    CWordCount test;
    EXPECT_EQ(test.entrance(argc,argv),5);
    CLEAR_ARGS;
}
TEST(TestMethod7,UnitTest1){
    char** argv=(char**)malloc(sizeof(char*)*5);
    GENERATE_ARG(arg0,"test.exe");
    argv[0]=arg0;
    GENERATE_ARG(arg1,"-c");
    argv[1]=arg1;
    GENERATE_ARG(arg2,"-w");
    argv[2]=arg2;
    GENERATE_ARG(arg3,"-l");
    argv[3]=arg3;
    GENERATE_ARG(arg4,"example.txt");
    argv[4]=arg4;
    int argc=5;
    CWordCount test;
    EXPECT_EQ(test.entrance(argc,argv),6);
    CLEAR_ARGS;
}
TEST(TestMethod8,UnitTest1){
    char** argv=(char**)malloc(sizeof(char*)*5);
    GENERATE_ARG(arg0,"test.exe");
    argv[0]=arg0;
    GENERATE_ARG(arg1,"-c");
    argv[1]=arg1;
    GENERATE_ARG(arg2,"-w");
    argv[2]=arg2;
    GENERATE_ARG(arg3,"-l");
    argv[3]=arg3;
    GENERATE_ARG(arg4,"input.txt");
    argv[4]=arg4;
    int argc=5;
    CWordCount test;
    EXPECT_EQ(test.entrance(argc,argv),0);
    CLEAR_ARGS;
}
TEST(TestMethod9,UnitTest1){
    char** argv=(char**)malloc(sizeof(char*)*7);
    GENERATE_ARG(arg0,"test.exe");
    argv[0]=arg0;
    GENERATE_ARG(arg1,"-c");
    argv[1]=arg1;
    GENERATE_ARG(arg2,"-w");
    argv[2]=arg2;
    GENERATE_ARG(arg3,"-l");
    argv[3]=arg3;
    GENERATE_ARG(arg4,"input.txt");
    argv[4]=arg4;
    GENERATE_ARG(arg5,"-o");
    argv[5]=arg5;
    GENERATE_ARG(arg6,"output.txt");
    argv[6]=arg6;
    int argc=7;
    CWordCount test;
    EXPECT_EQ(test.entrance(argc,argv),0);
    CLEAR_ARGS;
}
TEST(TestMethod10,UnitTest1){
    char** argv=(char**)malloc(sizeof(char*)*2);
    GENERATE_ARG(arg0,"test.exe");
    argv[0]=arg0;
    GENERATE_ARG(arg1,"-x");
    argv[1]=arg1;
    int argc=2;
    CWordCount test;
    EXPECT_EQ(test.entrance(argc,argv),0);
    CLEAR_ARGS;
}
int main(int argc,char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return(RUN_ALL_TESTS());
}