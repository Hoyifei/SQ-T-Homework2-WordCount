//
// Created by starsapphire on 18-3-19.
//
#include "WordCount_test_basic.h"
#include <gtest/gtest.h>
//#include <cstdlib>
class WordCount_UnitTest2:public ::testing::Test{
public:
    WordCount_test counter1;
    WordCount_test counter2;
    WordCount_test counter3;
    WordCount_test counter4;
    WordCount_test::TAdvancedResult_test aresult1;
    WordCount_test::TAdvancedResult_test aresult2;
    WordCount_UnitTest2(){
        counter1.read("unittest2_testinputs/test1.txt");
        counter2.read("unittest2_testinputs/test2.txt");
        counter3.read("unittest2_testinputs/test3.txt");
        aresult1=counter3.count_advanced_test();
        counter4.read("unittest2_testinputs/test4.txt");
        aresult2=counter4.count_advanced_test();
    }
} ;
TEST_F(WordCount_UnitTest2,UnitTest2_case1) {
    EXPECT_EQ(counter1.count_char_test(), 51);
}
TEST_F(WordCount_UnitTest2,UnitTest2_case2){
    EXPECT_EQ(counter1.count_line_test(),5);
}
TEST_F(WordCount_UnitTest2,UnitTest2_case3){
    EXPECT_EQ(counter1.count_word_test(),18);
}
TEST_F(WordCount_UnitTest2,UnitTest2_case4){
    counter1.set_except(counter1.getstr_test("unittest2_testinputs/except.txt"));
    counter1.deal_with_except_test();
    counter1.read("unittest2_testinputs/test1.txt");
    EXPECT_EQ(counter1.count_word_test(),10);
}
TEST_F(WordCount_UnitTest2,UnitTest2_case5){
    EXPECT_EQ(counter2.count_line_test(),1);
}
TEST_F(WordCount_UnitTest2,UnitTest2_case6){
    EXPECT_EQ(aresult1.code,10);
}
TEST_F(WordCount_UnitTest2,UnitTest2_case7){
    EXPECT_EQ(aresult1.empty,3);
}
TEST_F(WordCount_UnitTest2,UnitTest2_case8){
    EXPECT_EQ(aresult1.note,9);
}
TEST_F(WordCount_UnitTest2,UnitTest2_case9){
    EXPECT_EQ(aresult2.code,5);
}
TEST_F(WordCount_UnitTest2,UnitTest2_case10){
    EXPECT_EQ(aresult2.empty,13);
}
TEST_F(WordCount_UnitTest2,UnitTest2_case11){
    EXPECT_EQ(aresult2.note,8);
}
int main(int argc,char** argv){
    //system("pwd");
    ::testing::InitGoogleTest(&argc, argv);
    return(RUN_ALL_TESTS());
}
