#include "stdafx.h"
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <assert.h>

using namespace std;

class Instruction{
public:
    enum Type{
        CPY,
        INC,
        DEC,
        JNZ
    };
   
    enum OperandType{
        VALUE,
        REGISTER
    };

    Instruction(Type type, OperandType op1Type, int op1, int op2 = 0):
        type(type),
        op1Type(op1Type),
        op1(op1),
        op2(op2)
    {}

    Type type;
    OperandType op1Type;
    int op1;
    int op2;
};

class BunnyComputer{
public:
    BunnyComputer(){
        registers[0] = registers[1] = registers[2] = registers[3] = 0;	
		registers[2] = 1;	//second part
    }
    void Execute(const std::vector<Instruction> & program);
    int GetRegister(int reg){ return registers[reg]; }
private:
    int registers[4];
};

void BunnyComputer::Execute(const std::vector<Instruction> & program){
    int i = 0;
    while(i < program.size()){
        int op1;
        switch(program[i].type){
            case Instruction::INC:
                registers[program[i++].op1]++;
                break;
            case Instruction::DEC:
                registers[program[i++].op1]--;
                break;
            case Instruction::CPY:
                op1 = (program[i].op1Type == Instruction::VALUE) ? program[i].op1 : registers[program[i].op1];
                registers[program[i++].op2] = op1;
                break;
            case Instruction::JNZ:
                op1 = (program[i].op1Type == Instruction::VALUE) ? program[i].op1 : registers[program[i].op1];
                if(op1){
                    i += program[i].op2;
                }
                else{
                    i++;
                }
                break;
        }
    }
}

int main()
{
    FILE* fd = fopen("C:\\Users\\Tom\\Desktop\\input.txt", "r");
    if(!fd){
        return 2;
    }
    char buffer[100];
    std::vector<Instruction> program;

    while(fgets(buffer, 100, fd)){
        std::string instStr(buffer);
        if(instStr.find("cpy") == 0){
            char op1FirstChar = instStr[instStr.find(" ") + 1];
            Instruction::OperandType op1Type;
            int op1, op2;
            if(op1FirstChar >= 'a' &&  op1FirstChar <= 'd'){
                op1Type = Instruction::REGISTER;
                op1 = op1FirstChar - 'a';
            }
            else{
                op1Type = Instruction::VALUE;
                op1 = atoi(&instStr[instStr.find(" ") + 1]);

            }
            op2 = instStr[instStr.rfind(" ") + 1] - 'a';
            program.push_back(Instruction(Instruction::CPY, op1Type, op1, op2));
        }
        else if(instStr.find("inc") == 0){
            int op1 = instStr[instStr.find(" ") + 1] - 'a';
            program.push_back(Instruction(Instruction::INC, Instruction::VALUE, op1));
        }
        else if(instStr.find("dec") == 0){
            int op1 = instStr[instStr.find(" ") + 1] - 'a';
            program.push_back(Instruction(Instruction::DEC, Instruction::VALUE, op1));
        }
        else if(instStr.find("jnz") == 0){
            char op1FirstChar = instStr[instStr.find(" ") + 1];
            Instruction::OperandType op1Type;
            int op1, op2;
            if(op1FirstChar >= 'a' &&  op1FirstChar <= 'd'){
                op1Type = Instruction::REGISTER;
                op1 = op1FirstChar - 'a';
            }
            else{
                op1Type = Instruction::VALUE;
                op1 = atoi(&instStr[instStr.find(" ") + 1]);

            }
            op2 = atoi(&instStr[instStr.rfind(" ") + 1]);
            program.push_back(Instruction(Instruction::JNZ, op1Type, op1, op2));
        }
        else{
            assert(false);
        }
    }

    BunnyComputer cpu;
    cpu.Execute(program);

    printf("%d\n", cpu.GetRegister(0));
    getchar();
    return 0;
}

