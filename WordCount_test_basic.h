//
// Created by starsapphire on 18-3-19.
//

#ifndef WORDCOUNT_WORDCOUNT_TEST_BASIC_H
#define WORDCOUNT_WORDCOUNT_TEST_BASIC_H
#include <cstdlib>
#include "CWordCount.h"

class WordCount_test :public WordCount::CWordCount{
public:
    struct TAdvancedResult_test{
        int code;
        int empty;
        int note;
    };
    long long num_line,num_word,num_char;
    size_t count_line_test();
    size_t count_char_test();
    size_t count_word_test();
    TAdvancedResult_test count_advanced_test();
    void reset_test();
    void deal_with_recursive_test();
    int deal_with_except_test();
    void set_str(char* s);
    void set_source(char* s);
    void set_output(char* s);
    void set_except(char* s);
    std::vector < char* >* get_excepts();
    std::vector < char* >* get_sources();
    char* getstr_test(const char* str);
    ~WordCount_test();
    ;
};


#endif //WORDCOUNT_WORDCOUNT_TEST_BASIC_H
