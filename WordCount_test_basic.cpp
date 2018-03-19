//
// Created by starsapphire on 18-3-19.
//

#include "WordCount_test_basic.h"

size_t WordCount_test::count_line_test() {
    return count_line();
}

size_t WordCount_test::count_char_test() {
    return count_char();
}

size_t WordCount_test::count_word_test() {
    return count_word();
}

WordCount_test::TAdvancedResult_test WordCount_test::count_advanced_test() {
    TAdvancedResult_test test_ans;
    TAdvancedResult ans=count_advanced();
    test_ans.note=ans.note;
    test_ans.empty=ans.empty;
    test_ans.code=ans.code;
    return test_ans;
}

void WordCount_test::reset_test() {
    reset();
}

void WordCount_test::deal_with_recursive_test() {
    deal_with_recursive();
}

int WordCount_test::deal_with_except_test() {
    return(deal_with_except());
}

void WordCount_test::set_str(char *s) {
    str=s;
}

void WordCount_test::set_source(char *s) {
    sourceFile=s;
}

void WordCount_test::set_output(char *s) {
    outputFile=s;
}

void WordCount_test::set_except(char *s) {
    exceptFile=s;
}

std::vector<char *> *WordCount_test::get_excepts() {
    return &excepts;
}

std::vector<char *> *WordCount_test::get_sources() {
    return &sourceFiles;
}

char *WordCount_test::getstr_test(const char *str) {
    return getstr(str);
}

WordCount_test::~WordCount_test() {
    reset();
}
