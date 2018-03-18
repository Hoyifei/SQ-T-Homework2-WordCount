//
// Created by starsapphire on 18-3-17.
//

#include "CWordCount.h"
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;
using namespace WordCount;

size_t WordCount::CWordCount::count_line() {
    int count = 0;
    auto len=strlen(str);
    char c;
    for(auto i=0;i<len;++i){
        c=str[i];
        if (count == 0) {
            count++;
            continue;
        }
        if (c == '\n') {
            count++;
        }
    }
    return count;
}

size_t WordCount::CWordCount::count_char() {
    return strlen(str);
}

size_t WordCount::CWordCount::count_word() {
    size_t count = 0;
    char lastChar = ' ';
    auto len=strlen(str);
    char c;
    for(auto i=0;i<len;++i){
        c=str[i];
        if ((c != ',' && c != ' ' && c != '\0' && c != '\r' && c != '\n') && (lastChar == ','|| lastChar == ' '|| lastChar == '\n')) {
            count++;
        }
        lastChar = c;
    }
    return count;
}

int WordCount::CWordCount::entrance(int argc, char **argv) {
    if(argc<2||argv==nullptr){
        return(-1);
    }

    reset();
    bool output_to_file=true;
    bool is_select_file = false;
    ArgsStatus status = Uninitialized;
    for (int i=1;i<argc;++i){
        //cerr<<"ZXCV"<<" "<<status<<" "<<argv[i]<<" "<<strcasecmp(argv[i],"-c")<<endl;
        if(status==Uninitialized || status==NormalOption) {
            if (status == Uninitialized && strcasecmp(argv[i], "-x")==0) {
                status = Finish;
                options.push_back(getstr("-c"));
                options.push_back(getstr("-w"));
                options.push_back(getstr("-l"));
                output_to_file = false;
                is_select_file = true;
            }else if(strcasecmp(argv[i],"-c")==0||strcasecmp(argv[i],"-l")==0||strcasecmp(argv[i],"-w")==0){
                for(int k=0;k<options.size();++k){
                    //cerr<<"ASDF"<<" "<<argv[i]<<" "<<options[k]<<endl;
                    if(strcasecmp(argv[i],options[k])==0){
                        log_arg_error(0x1);
                        return(0x1);
                    }
                }
                options.push_back(getstr(argv[i]));
                status=NormalOption;
            }else if(status==NormalOption){
                sourceFile=getstr(argv[i]);
                status=OutputOption;
            }else{
                log_arg_error(0x2);
                return(0x2);
            }
        }else if(status==OutputOption){
            if(strcasecmp("-o",argv[i])==0){
                status=OutputFile;
            }else{
                log_arg_error(0x3);
                return(0x3);
            }
        }else if(status==OutputFile){
            outputFile=getstr(argv[i]);
            status=Finish;
        }else if(status==Finish){
            log_arg_error(0x4);
            return(0x4);
        }
    }
    if(status!=Finish&&status!=OutputOption){
        log_arg_error(0x5);
        return(0x5);
    }
    if(outputFile==nullptr){
        outputFile=getstr("result.txt");
    }
    if (is_select_file) {
        sourceFile=read();
        if(sourceFile== nullptr){
            return(0x6);
        }
    } else {
        if(read(sourceFile)!=0){
            cerr<<"Error while opening input file"<<sourceFile<<endl;
            return(0x6);
        }
    }
    int c_result = -1;
    int w_result = -1;
    int l_result = -1;

    for(int i=0;i<options.size();++i) {
        if (strcasecmp("-c",options[i])==0)
            c_result = (int)count_char();
        else if (strcasecmp("-w",options[i])==0)
            w_result = (int)count_word();
        else if (strcasecmp("-l",options[i])==0)
            l_result = (int)count_line();
        else {
            cerr<<"Invalid argument accepted!!!"<<endl;
            return(-1);
        }
    }

    if (c_result != -1)
        cout<<sourceFile<<" has "<<c_result<<" character(s) in total"<<endl;
    if (w_result != -1)
        cout<<sourceFile<<" has "<<w_result<<" word(s) in total"<<endl;
    if (l_result != -1)
        cout<<sourceFile<<" has "<<l_result<<" line(s) in total"<<endl;

    if (output_to_file) {
        ofstream outfile;
        outfile.open(outputFile);
        if(outfile.good()) {
            if (c_result != -1)
                outfile<<sourceFile<<" has "<<c_result<<" character(s) in total"<<endl;
            if (w_result != -1)
                outfile<<sourceFile<<" has "<<w_result<<" word(s) in total"<<endl;
            if (l_result != -1)
                outfile<<sourceFile<<" has "<<l_result<<" line(s) in total"<<endl;
            outfile.close();
        } else {
            cerr<<"Error while opening output file"<<(outputFile==nullptr?"NULL":sourceFile)<<endl;
            return(0x6);
        }
            //Console.WriteLine("输出到文件" + outputFile + "成功");
    }
    return 0;
}

int WordCount::CWordCount::read(const char *fileName) {
    filebuf *buffer;
    ifstream filestr;
    filestr.open(fileName,ios::binary);
    if(!filestr.good()){
        return(-1);
    }
    buffer=filestr.rdbuf();
    auto size=buffer->pubseekoff(0,ios::end,ios::in);
    buffer->pubseekpos(0,ios::in);
    str=(char*)malloc(size);
    buffer->sgetn(str,size);
    filestr.close();
    return(0);
}

WordCount::CWordCount::CWordCount() {
    num_line=-1;num_word=-1;num_char=-1;
    str=nullptr;
    sourceFile = nullptr;
    outputFile = nullptr;
}

void WordCount::CWordCount::log_arg_error(int err) {
    cerr<<"Invalid argment.Code="<<err<<endl;
}

char *WordCount::CWordCount::getstr(const char *target_str) {
    char* ans_str = (char*)malloc(strlen(target_str)+1);
    memcpy(ans_str,target_str,strlen(target_str));
    ans_str[strlen(target_str)]=0;
    return ans_str;
}

WordCount::CWordCount::~CWordCount() {
    reset();
}

void WordCount::CWordCount::reset() {
    for(int i=0;i<options.size();++i){
        free(options[i]);
    }
    if(sourceFile!=nullptr){
        free(sourceFile);
    }
    if(outputFile!= nullptr){
        free(outputFile);
    }
    if(str!= nullptr){
        free(str);
    }
    num_line=-1;num_word=-1;num_char=-1;
    str=nullptr;
    sourceFile = nullptr;
    outputFile = nullptr;
}

char *WordCount::CWordCount::read(void) {
    string filename;
    cout<<"Please input SourceFile:";
    cin>>filename;
    if(read(filename.c_str())!=0){
        cerr<<"Error while opening input file"<<filename.c_str()<<endl;
        return(nullptr);
    }
    return(getstr(filename.c_str()));
}

