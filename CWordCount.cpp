//
// Created by starsapphire on 18-3-17.
//

#include "CWordCount.h"
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <regex>
#include <sstream>

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
    string word;
    char lastChar = ' ';
    auto len=strlen(str);
    char c;
    word.clear();
    for(auto i=0;i<len;++i){
        c=str[i];
        if ((c != ',' && c != ' ' && c != '\0' && c != '\r' && c != '\n' && c != '\t')) {
            if(lastChar == ','|| lastChar == ' '|| lastChar == '\n' || lastChar=='\t') {
                if (!word.empty()){
                    bool matched=false;
                    for(auto it=excepts.begin();it!=excepts.end();++it){
                        char* except_word=*it;
                        if(strcasecmp(except_word,word.c_str())==0){
                            matched=true;
                            break;
                        }
                    }
                    //cerr<<word<<endl;
                    if(!matched) count++;
                }
                word.clear();
            }
            word.push_back(c);
        }
        lastChar = c;
    }
    if (!word.empty()){
        bool matched=false;
        for(auto it=excepts.begin();it!=excepts.end();++it){
            char* except_word=*it;
            if(strcasecmp(except_word,word.c_str())==0){
                matched=true;
                break;
            }
        }
        //cerr<<word<<endl;
        if(!matched) count++;
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
    bool recursive_search=false;
    bool operation_specified=false;
    bool source_specified=false;
    bool except_specified= false;
    ArgsStatus status = Uninitialized;
    for (int i=1;i<argc;++i){
        if(status==Uninitialized || status==NormalOption) {
            if (status == Uninitialized && strcasecmp(argv[i], "-x")==0) {
                status = Finish;
                options.push_back(getstr("-c"));
                options.push_back(getstr("-w"));
                options.push_back(getstr("-l"));
                options.push_back(getstr("-a"));
                output_to_file = false;
                is_select_file = true;
                operation_specified=true;
                source_specified=true;
            }else if(strcasecmp(argv[i],"-c")==0||
                     strcasecmp(argv[i],"-l")==0||
                     strcasecmp(argv[i],"-w")==0||
                     strcasecmp(argv[i],"-a")==0) {
                bool operation_appeared=false;
                for (int k = 0; k < options.size(); ++k) {
                    if (strcasecmp(argv[i], options[k]) == 0) {
                        operation_appeared=true;
                    }
                }
                operation_specified=true;
                if(!operation_appeared)
                    options.push_back(getstr(argv[i]));
                status = NormalOption;
            }else if(strcasecmp(argv[i],"-s")==0){
                if(recursive_search){
                    log_arg_error(0x1);
                    return (0x1);
                }
                recursive_search=true;
            }else if(strcasecmp("-o",argv[i])==0){
                if(outputFile!= nullptr){
                    log_arg_error(0x4);
                    return(0x4);
                }
                status=OutputFile;
            }else if(strcasecmp("-e",argv[i])==0){
                if(exceptFile!= nullptr){
                    log_arg_error(0x4);
                    return(0x4);
                }
                status=ExceptFile;
            }else if(status==NormalOption){
                if(sourceFile){
                    sourceFiles.push_back(sourceFile);
                }
                sourceFile=getstr(argv[i]);
                source_specified=true;
            }else{
                log_arg_error(0x2);
                return(0x2);
            }
        }else if(status==OutputFile){
            outputFile=getstr(argv[i]);
            status=NormalOption;
        }else if(status==ExceptFile){
            exceptFile=getstr(argv[i]);
            except_specified=true;
            status=NormalOption;
        }else if(status==Finish){
            log_arg_error(0x4);
            return(0x4);
        }
    }
    if(status==OutputFile||status==ExceptFile){
        log_arg_error(0x5);
        return(0x5);
    }
    if(!operation_specified||!source_specified){
        log_arg_error(0x5);
        return(0x5);
    }
    if(outputFile==nullptr){
        outputFile=getstr("result.txt");
    }
    if(except_specified){
        if(deal_with_except()!=0){
            return (0x6);
        }
    }
    if (is_select_file) {
        sourceFiles.push_back(getinputfile());
        sourceFile= nullptr;
    }else if(recursive_search){
        deal_with_recursive();
    }else{
        sourceFiles.push_back(sourceFile);
        sourceFile= nullptr;
    }
//    cout<<output_to_file<<" "<<outputFile<<endl;
    stringstream output_content;
    for(auto it=sourceFiles.begin();it!=sourceFiles.end();++it) {
        char* current_source_file=*it;
        //cerr<<current_source_file<<endl;
        if (read(current_source_file) != 0) {
            cerr << "Error while opening input file" << current_source_file << endl;
            return (0x6);
        }
        int c_result = -1;
        int w_result = -1;
        int l_result = -1;
        CWordCount::TAdvancedResult a_result;
        a_result.note=-1;

        for (int i = 0; i < options.size(); ++i) {
            if (strcasecmp("-c", options[i]) == 0)
                c_result = (int) count_char();
            else if (strcasecmp("-w", options[i]) == 0)
                w_result = (int) count_word();
            else if (strcasecmp("-l", options[i]) == 0)
                l_result = (int) count_line();
            else if (strcasecmp("-a", options[i]) == 0)
                a_result = count_advanced();
            else {
                cerr << "Invalid argument accepted!!!" << endl;
                return (-1);
            }
        }

        if (c_result != -1)
            cout << current_source_file << " has " << c_result << " character(s)" << endl;
        if (w_result != -1)
            cout << current_source_file << " has " << w_result << " word(s)" << endl;
        if (l_result != -1)
            cout << current_source_file << " has " << l_result << " line(s)" << endl;
        if (a_result.note!=-1)
            cout << current_source_file << " has " <<
                    a_result.code<<"/"<<a_result.empty<<"/"<<a_result.note<<
                    " code/empty/note lines"<<endl;

        if (output_to_file) {
            if (c_result != -1)
                output_content << current_source_file << " has " << c_result << " character(s)" << endl;
            if (w_result != -1)
                output_content << current_source_file << " has " << w_result << " word(s)" << endl;
            if (l_result != -1)
                output_content << current_source_file << " has " << l_result << " line(s)" << endl;
            if (a_result.note!=-1)
                output_content << current_source_file << " has " <<
                                  a_result.code<<"/"<<a_result.empty<<"/"<<a_result.note<<
                                  " code/empty/note lines"<<endl;
            //Console.WriteLine("输出到文件" + outputFile + "成功");
        }
        free(str);
        str= nullptr;
    }
    ofstream outfile;
    if (output_to_file) {
        outfile.open(outputFile);
        if (!outfile.good()) {
            cerr << "Error while opening output file" << (outputFile == nullptr ? "NULL" : sourceFile) << endl;
            return (0x6);
        }
        outfile<<output_content.str();
        outfile.close();
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
    str=(char*)malloc((size_t)size+(size_t)9);
    memset(str,0,sizeof(str));
    buffer->sgetn(str,size);
    filestr.close();
    //cerr<<str<<endl;
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
    for(int i=0;i<excepts.size();++i){
        free(excepts[i]);
    }
    for(int i=0;i<sourceFiles.size();++i){
        free(sourceFiles[i]);
    }
    options.clear();
    excepts.clear();
    sourceFiles.clear();
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
    outputFile = nullptr;
    exceptFile = nullptr;
}

char *WordCount::CWordCount::getinputfile(void) {
    string filename;
    cout<<"Please input SourceFile:";
    cin>>filename;
    if(read(filename.c_str())!=0){
        cerr<<"Error while opening input file"<<filename.c_str()<<endl;
        return(nullptr);
    }
    return(getstr(filename.c_str()));
}

void CWordCount::deal_with_recursive() {
    char *regex_path=(char*)malloc((strlen(sourceFile)+1)<<1);
    int cur_position=0;
    //cerr<<sourceFile<<endl;
    for(int i=0;i<strlen(sourceFile);++i){
        switch(sourceFile[i]){
            case '.':
            case '\\':
            case '$':
            case '(':
            case ')':
            case '+':
            case '[':
            case ']':
            case '^':
            case '{':
            case '}':
            case '|':{//they are not wildcard,keep them unchanged
                regex_path[cur_position] = '\\';
                ++cur_position;
                break;
            }
            case '*':
            case '?':{//*->.* ?->.
                regex_path[cur_position] = '.';
                ++cur_position;
                break;
            }
            default:break;
        }
        if(sourceFile[i]!='?'){
            regex_path[cur_position] = sourceFile[i];
            ++cur_position;
        }
    }
    regex_path[cur_position]=0;
    //cerr<<regex_path<<endl;
    regex wildcard_path_reg(regex_path,regex_constants::ECMAScript);
    boost::filesystem::path dir_path(".");
    boost::filesystem::recursive_directory_iterator dir_iter(dir_path),end;
    while(dir_iter!=end){
        if(!boost::filesystem::is_directory(dir_iter->path())) {
            //cerr<<dir_iter->path().filename().string()<<endl;
            if(regex_match(dir_iter->path().filename().string(),wildcard_path_reg)){
                sourceFiles.push_back(getstr(dir_iter->path().c_str()));
            }
        }
        ++dir_iter;
    }
}

int CWordCount::deal_with_except() {
    if(read(exceptFile)!=0){
        cerr<<"Error while opening except list file"<<exceptFile<<endl;
        return(-1);
    }
    string word;
    char lastChar = ' ';
    auto len=strlen(str);
    char c;
    word.clear();
    for(auto i=0;i<len;++i){
        c=str[i];
        if ((c != ',' && c != ' ' && c != '\0' && c != '\r' && c != '\n')) {
            if(lastChar == ','|| lastChar == ' '|| lastChar == '\n') {
                if (!word.empty())
                    excepts.push_back(getstr(word.c_str()));
                word.clear();
            }
            word.push_back(c);
        }
        lastChar = c;
    }
    if (!word.empty())
        excepts.push_back(getstr(word.c_str()));
    free(str);
    return 0;
}

CWordCount::TAdvancedResult CWordCount::count_advanced() {
    TAdvancedResult ans;
    ans.empty=0;
    ans.code=0;
    ans.note=0;
    auto len=strlen(str);
    char c;
    int cur_line_code_chars=0,cur_line_visible_chars=0;
    bool line_note=false,block_note=false,line_include_note=false;
    char last_char=0;
    for(auto i=0;i<len;++i){
        c=str[i];
        switch(c){
            case ' ':case '\t':case '\r':case '\0':{
                last_char=c;
                break;
            }
            case '\n':{
                if(cur_line_visible_chars<=1) ++ans.empty;
                if(cur_line_code_chars>1) ++ans.code;
                if(cur_line_code_chars<=1&&line_include_note) ++ans.note;
                cur_line_visible_chars=0;
                cur_line_code_chars=0;
                line_note=false;
                line_include_note=false;
                if(block_note) line_include_note=true;
                last_char=c;
                break;
            }
            case '/':{
                ++cur_line_visible_chars;
                if(!line_note&&!block_note) {
                    if (last_char == '/') {
                        --cur_line_code_chars;
                        line_note = true;
                        line_include_note=true;
                        last_char=0;
                    }else {
                        ++cur_line_code_chars;
                        last_char=c;
                    }
                }else if(block_note){
                    if(last_char=='*'){
                        block_note=false;
                        last_char=0;
                    }else{
                        last_char=c;
                    }
                }
                break;
            }
            case '*':{
                ++cur_line_visible_chars;
                if(!line_note&&!block_note) {
                    if (last_char == '/') {
                        --cur_line_code_chars;
                        block_note = true;
                        line_include_note=true;
                        last_char=0;
                    }else {
                        ++cur_line_code_chars;
                        last_char=c;
                    }
                }else{
                    last_char=c;
                }
                break;
            }
            default: {
                if(!line_note&&!block_note) ++cur_line_code_chars;
                ++cur_line_visible_chars;
                break;
            }
        }
    }
    if(last_char!='\n') {
        if (cur_line_visible_chars <= 1) ++ans.empty;
        if (cur_line_code_chars > 1) ++ans.code;
        if (cur_line_code_chars <= 1 && line_include_note) ++ans.note;
    }
    //cerr<<ans.note<<" "<<ans.empty<<" "<<ans.code<<endl;
    return ans;
}

