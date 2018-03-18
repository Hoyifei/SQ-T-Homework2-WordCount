//
// Created by starsapphire on 18-3-17.
//

#ifndef WORDCOUNT_CWORDCOUNT_H
#define WORDCOUNT_CWORDCOUNT_H
#include <string>
#include <vector>
namespace WordCount {
    enum ArgsStatus{
        Uninitialized = 0,
        NormalOption = 1,
        SourceFile = 2,
        OutputOption = 3,
        OutputFile = 4,
        ExceptOption=5,
        ExceptFile=6,
        Finish = 7
    };
    class CWordCount {
    protected:
        struct TAdvancedResult{
            int code;
            int empty;
            int note;
        };
        char* str;
        long long num_line,num_word,num_char;
        size_t count_line();
        size_t count_char();
        size_t count_word();
        CWordCount::TAdvancedResult count_advanced();
        void log_arg_error(int err);
        char* getstr(const char* target_str);
        std::vector < char* > options;
        std::vector < char* > excepts;
        std::vector < char* > sourceFiles;
        char* sourceFile;
        char* outputFile;
        char* exceptFile;
        void reset();
        void deal_with_recursive();
        int deal_with_except();
    public:
        int entrance(int argc, char** argv);
        int read(const char* fileName);
        char* getinputfile(void);
        CWordCount();
        ~CWordCount();
    };
}


#endif //WORDCOUNT_CWORDCOUNT_H
