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
        Finish = 5
    };
    class CWordCount {
    protected:
        char* str;
        long long num_line,num_word,num_char;
        size_t count_line();
        size_t count_char();
        size_t count_word();
        void log_arg_error(int err);
        char* getstr(const char* target_str);
        std::vector < char* > options;
        char* sourceFile;
        char* outputFile;
        void reset();
    public:
        int entrance(int argc, char** argv);
        int read(const char* fileName);
        char* read(void);
        CWordCount();
        ~CWordCount();
    };
}


#endif //WORDCOUNT_CWORDCOUNT_H
