#ifndef __PWN_LIB__
#define __PWN_LIB__

#define MAX_SIZE 1000
#define MAX_PIPE_TIME 1000
#define NODE_MAX_NUM 10
#include "node.h"
#include "print.h"
#include "Mstring.h"

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <stack>
#include <map>
#include <cstring>
#include <ctime>

using namespace std;


enum FORMAT
{
    ELF = 0,
    PE
}; //executable file Format
enum ARCH
{
    x86 = 0,
    x86_64,
    mips
}; //architecture of executtable file
enum FD
{
    INPUT = 0,
    OUTPUT
}; //define filedis

/* template class PWN */
//Class PWN struction in order to analyse the Executable file and generate.
//This class also provide several funciton to interact with child process(loaded with our Executive file),
//A bit like pwntools.While user need provide a Parse_Mod for this class to analyse
//the programm or use the initial version.
//Example:
//PWN<Auto_Mod> *p = new PWN<Auto_Mod>(string("../bin/test"));
template <class Parse_Mod>
class PWN
{
public:
    PWN(string Path, FORMAT Form = ELF, ARCH Arch = x86_64) : path(Path), form(Form), arch(Arch) {}
    string get_path_() const { return path; }
    const char *get_path_c_char() { return path.c_str(); }
    FORMAT get_form_() const { return form; }
    ARCH get_arch_() const { return arch; }
    ///////////////////////////////////////
    /*       the tools of PWNlib         */
    inline bool load_();
    inline char *recv_();
    inline char *recv_line_();
    inline bool send_(string str);
    inline bool send_line_(string str);
    inline void analyze_();
    inline void analyze_manual_();
    inline void show_node_list_();
    inline void gengerate_();

protected:
    Node<string> node_list[NODE_MAX_NUM]; // store the node list
    int round{0};                         // analyse round

private:
    string path; //path to executable file
    FORMAT form; //executable file Format
    ARCH arch;   // architecture of executable file
    pid_t pid;   //pid for child process
    int fd[2], fd2[2];
};



template <class Parse_Mod>
inline bool PWN<Parse_Mod>::load_()
{
#ifdef __DEBUG__
    //cout << "[*] Loading Executable file" << endl;
    Print out("[*] Loading Executable file");
    out.color_(F_BLUE);
    out.out_();
#endif
    pipe(this->fd);
    pipe(this->fd2);
    //int flags = fcntl(this->fd[0],F_GETFL);
    //flags |= O_NONBLOCK;
    int flags;
    fcntl(this->fd[0], F_SETFL, flags | O_NONBLOCK); //  NO BLOCK
    if ((this->pid = fork()) == -1)
    {
        cout << "[^] Error in fork!" << endl;
        return false;
    }
    if (this->pid == 0)
    { // child process
        //cout << "[+] child process " << endl;
        close(this->fd[INPUT]);
        close(this->fd2[OUTPUT]);
        dup2(this->fd[OUTPUT], STDOUT_FILENO);
        dup2(this->fd2[INPUT], STDIN_FILENO);
        char *argv[] = {"", "", "", (char *)0};
        char *envp[] = {"", 0};
        execve(this->get_path_c_char(), argv, envp);

        //execv(this->get_path().c_str(),ARG);
        //execve("/bin/ls",ARG,ARG);
        //cout << "[^] ERROR in execv" <<endl;
        //write(fd[OUTPUT],"hello data",11); //test pipe
        //cout << "child test"; // test if dup stdout to fd[1]
        //exit(0);
    }
    else
    { // father process
        //cout << "[+] father process " << endl;
        //char pipebuf[200];
        //char outbuf[200];
        close(this->fd[OUTPUT]);
        //read(fd[INPUT],pipebuf,50);
        //strcpy(outbuf,pipebuf);
        //cout << "recv: (" << outbuf  << ")"<< endl;
        //exit(0);
    }
    return true;
}
/* Function Recv*/
//Read all the data from pipe,and store in the pipe,
//Return this buffer.
//Example:
//pwn.recv_();  Attation: use after load_()
template <class Parse_Mod>
inline char *PWN<Parse_Mod>::recv_()
{
    if (!this->pid)
    {
        cout << "[^] Error in recv , the Executable file load_() error." << endl;
        exit(0);
    }
    sleep(1);
    char pipebuf[MAX_SIZE];
    static char outbuf[MAX_SIZE];
    memset(pipebuf, '\0', sizeof(pipebuf));
    memset(outbuf, '\0', sizeof(outbuf));
    clock_t start{clock()};
    int i = 0;
    do
    {
        read(this->fd[INPUT], pipebuf + i, 1);
        i++;
    } while (this->fd[INPUT] && clock() - start <= 300 && *(pipebuf + i - 1) != '\x00' && i < MAX_SIZE);

    *(pipebuf + i) = '\x00';
    strcpy(outbuf, pipebuf);
    //cout << "recv: (" << outbuf  << ")"<< endl;
#ifdef __DEBUG__
    //cout << "=====string====\n"
    //     << str << "===============\n";
    Print out(outbuf);
    out.color_(F_GREEN);
    out.out_format_(BLOCK);
#endif
    return outbuf;
}
template <class Parse_Mod>
inline char *PWN<Parse_Mod>::recv_line_()
{
    if (!this->pid)
    {
        cout << "[^] Error in recv , you need to use load_() first." << endl;
        exit(0);
    }
    sleep(1);
    char pipebuf[MAX_SIZE];
    static char outbuf[MAX_SIZE];
    memset(pipebuf, '\0', sizeof(pipebuf));
    memset(outbuf, '\0', sizeof(outbuf));
    clock_t start = clock();
    int i = 0;
    do
    {
        read(this->fd[INPUT], pipebuf + i, 1);
        i++;
    } while (this->fd[INPUT] && clock() - start <= 300 && *(pipebuf + i - 1) != '\n' && i < MAX_SIZE);

    *(pipebuf + i) = '\x00';
    strcpy(outbuf, pipebuf);
    //cout << "recv: (" << outbuf  << ")"<< endl;
#ifdef __DEBUG__
    //cout << "=====string====\n"
    //     << str << "===============\n";
    Print out(outbuf);
    out.color_(F_GREEN);
    out.out_format_(BLOCK);
#endif

    return outbuf;
}
template <class Parse_Mod>
inline bool PWN<Parse_Mod>::send_(string str)
{
    if (!this->pid)
    {
        cout << "[^] Error in recv , you need to use load_() first." << endl;
        exit(0);
    }

    if (write(this->fd2[OUTPUT], str.c_str(), str.length()))
    {
#ifdef __DEBUG__
        //cout << "[+] sending : " << str.substr(0, str.length() - 1) << endl;
        Print out("[+] sending : " + str.substr(0, str.length() - 1));
        out.color_(F_RED);
        out.out_();
#endif
    }
    else
    {
#ifdef __DEBUG__
        cout << "[^] Error in write." << endl;
        Print out("[^] Error in write.");
        out.color_(B_RED);
        out.out_();
#endif
    }
}
template <class Parse_Mod>
inline bool PWN<Parse_Mod>::send_line_(string str)
{
    if (!this->pid)
    {
        cout << "[^] Error in recv , you need to use load_() first." << endl;
        exit(0);
    }
    if (write(this->fd2[OUTPUT], (str + '\n').c_str(), str.length()))
    {
#ifdef __DEBUG__
        //cout << "[+] sending : " << str << "\\n"
        //     << endl;
        Print out("[+] sending : " + str + "\\n");
        out.color_(F_RED);
        out.out_();
#endif
    }
    else
    {
#ifdef __DEBUG__
        //cout << "[^] Error in write." << endl;
        Print out("[^] Error in write.");
        out.color_(B_RED);
        out.out_();
#endif
    }
}

//Analyse the Executable file and Store the infomation to Node,
//this rule will follow the class "Parse_Mod",you can override
//the functions in "Parse_Mod" ,so that you can improve the performance
//of analyze_() funciton.
//简单来说我是将anlyse的一些功能做了抽象，然后封装成了Parse_Mod。所有修改都可以通过重载Parse_mod来实现，
//这样不仅能够方便代码共享，也能方便使用者重构分析逻辑。
template <class Parse_Mod>
inline void PWN<Parse_Mod>::analyze_()
{
    Parse_Mod mod;
    char *tmp_buf, *out_buf;
    //cout << "[*] Analysing ... " << endl;
    Print out1("[*] Analysing ... ");
    out1.color_(F_YELLOW);
    out1.out_();
    do
    {
        static int i{-1};
        static int j{0};
        if (!mod.if_loaded_())
        {
            i++;
            j = 0;
            mod.load_(this->load_());
            mod.menu_buf_() = string(mod.recv_(this->recv_()));
            this->send_line_(mod.send_(i));
        }
        else
        {
            j++;
            mod.recv_(this->recv_());
            this->send_line_(mod.send_(i));
            //cout << "j = " << j << endl;
            if (j >= 5)
                mod.abort_();
        }
    } while (!mod.if_abort_());

    //cout << "[*] Analysing finished!" << endl;
    Print out2("[*] Analysing finished!");
    out2.color_(F_YELLOW);
    out2.out_();
}

template <class Parse_Mod>
inline void PWN<Parse_Mod>::analyze_manual_()
{
    Parse_Mod mod;
    char *tmp_buf, *out_buf;
    mod.load_node_list_(this->node_list); //load the contants for analysing result

    Print out1("[*] Analysing ... ");
    out1.color_(F_YELLOW);
    out1.out_();

    do
    {
        static int i{-1};
        static int j{0};
        if (!mod.if_loaded_())
        {
            i++;
            j = 0;
            mod.load_(this->load_());
            mod.menu_buf_() = string(mod.recv_(this->recv_()));
            this->send_line_(mod.send_(i));
        }
        else
        {
            j++;
            mod.recv_(this->recv_());
            this->send_line_(mod.send_(i));
            //cout << "j = " << j << endl;
            if (j >= 5)
                mod.abort_();
        }
    } while (!mod.if_abort_());

    //cout << "[*] Analysing finished!" << endl;
    Print out2("[*] Analysing finished!");
    out2.color_(F_YELLOW);
    out2.out_();

    //mod.show_node_list_();
    this->round=mod.get_round_();
    show_node_list_();
}

template <class Parse_Mod>
inline void PWN<Parse_Mod>::show_node_list_()
{
    int i{0};
    Print out;
    out.str_("Results after analysis");
    out.out_();
    while (i <= this->round)
    {
        out.out_("Round " + to_string(i + 1) + " : ");
        for (auto iter : node_list[i].node_map_())
        {
            //cout << iter.first << iter.second << endl;
            out.str_(iter.first);
            out.out_format_(BLOCK);
            out.str_(string("\t|\n\t-->") + iter.second);
            out.out_();
        }
        i++;
    }
}



template <class Parse_Mod>
inline void PWN<Parse_Mod>::gengerate_()
{
    Print out;
    out.color_(F_YELLOW);
    out.out_("[*] generating Python Script");
    sleep(1);
    int i{0};
    ofstream outfile;
    outfile.open("exploit.py");
    outfile << "#!/usr/bin/python\n";
    outfile << "#======PWNlib Script=======\n";
    outfile << "from pwn import *\n";
    outfile << "p=process([\"" << this->path << "\"] , env = {\"LD_PRELOAD\":\"/glibc/2.29/64/lib/libc.so.6\"})" <<endl;
    outfile << "debug=1\nif debug:\n\tcontext.log_level='Debug'\n\tcontext.terminal=context.terminal = ['tmux','splitw','-h' ]\n\tgdb.attach(p)" << endl;
    outfile << "else:\n\tp=remote(\"ip_address\",ip_port)"<<endl;
    outfile << "r  = lambda data	:p.recv(data)\nru = lambda data 	:p.recvuntil(data)\ns  = lambda data	:p.send(data)\nsl = lambda data	:p.sendline(data)"<<endl;
    outfile << endl;
    while(i <= round)
    {
        int j{0};
        for (auto iter : node_list[i].node_map_())
            j++;

        //func1(arg1,arg2):
        outfile << "def func"+to_string(i+1)+"(";
        for(int x{0} ; x < j-1 ; x++)
        {
            outfile << "arg"+to_string(x+1);
            if(x!=j-2) outfile << ",";
        }
        outfile << "):\n";
        //  recvuntil
        stack<string> stack1,stack2;
        for(auto iter : node_list[i].node_map_())
        {
            stack1.push(mstr::select_line(iter.first,1));
            stack2.push(iter.second);
            //outfile << "\tru(\"" << mstr::select_line(iter.first,1) << "\")" << endl;
            //outfile << "\tsl(\'" << iter.second << "\')" << endl;
        }
        bool first {false};
        int t {0};
        while(!stack1.empty() && !stack2.empty())
        {
            outfile << "\tru(\"" << stack1.top() << "\")" << endl;
            if(first == false)
            {
                outfile << "\tsl(\'" << stack2.top() << "\')" << endl;
                first = true;
            }
            else
            {
                outfile << "\tsl(" << "arg" << to_string(t) << ")" << endl; 
            }
            t++;
            stack1.pop();
            stack2.pop();
        }
        i++;
    }

    outfile << "p.interactive()";
    out.out_("[+] generate finish");
}
/*
inline string select_line(string str,int x)
{
    int pos1{0}, pos2{0}, i{1};
    string split = "\n";
    string tmp_str;
    while ((pos2 = str.find(split, pos1)) >= 0 && i <= x)
    {
        tmp_str = str.substr(pos1, pos2 - pos1);
        pos1 = pos2 + 1;
        i++;
    }
    return tmp_str;
}
*/


#endif