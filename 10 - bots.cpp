#include "stdafx.h"
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <assert.h>

using namespace std;

class Bot{
public:
	Bot(){
		id = lower = higher = INVALID_VAL;
	}

	Bot(int id){
		this->id = id;
		lower = higher = INVALID_VAL;
	}
	static const int INVALID_VAL = -1;

	void Set(int val){
		if(val == INVALID_VAL){
			return;
		}
		if(higher == INVALID_VAL){
			higher = val;
		}
		else if(lower == INVALID_VAL){
			lower = val;
		}
		else{
			assert(false);
		}
		if(lower > higher){
			std::swap(lower, higher);
		}
	}

	void ReadVals(int & l, int & h){
		l = lower;
		h = higher;
	}

	int id;
	int lower;
	int higher;
};

struct BotOperation{
	enum Type{
		VALUE,
		GIVE
	};
	Type type;
	int val;
	int bot1;
	int botLower;
	int botHigher;
};


int _tmain(int argc, _TCHAR* argv[]){
	
	FILE* fd = fopen("C:\\Users\\Tom\\Desktop\\input.txt", "r");
	if(!fd){
		printf("cannot read file");
	}
	std::string buffer;
	buffer.resize(1000);
	
	std::map<int, Bot> bots;
	std::map<int, int> outputs;
	std::vector<BotOperation> operations;
	std::map<int, Bot>::iterator it;

	while(fgets(&buffer[0], buffer.size(), fd)){
		buffer.erase(buffer.find("\n"));

		BotOperation op;

		//value 61 goes to bot 205
		if(buffer.find("value") == 0){
			op.type = BotOperation::VALUE;
			op.val = atoi(&buffer[buffer.find(" ") + 1]);
			op.bot1 = atoi(&buffer[buffer.rfind(" ") + 1]);
			
			if(bots.find(op.bot1) == bots.end()){
				bots[op.bot1] = Bot(op.bot1);
			}
		}
		//bot 103 gives low to bot 166 and high to bot 127
		else if(buffer.find("bot") == 0){
			op.type = BotOperation::GIVE;
			op.bot1 = atoi(&buffer[buffer.find(" ") + 1]);
			
			int pos;
			if((pos = buffer.find("low to output")) != std::string::npos){
				op.botLower = atoi(&buffer[pos + 14]);
				op.botLower |= 0xF0000000;
			}
			else{
				op.botLower = atoi(&buffer[buffer.find("to bot") + 7]);
			}
			op.botHigher = atoi(&buffer[buffer.rfind(" ") + 1]);
			if(buffer.find("high to output") != std::string::npos){
				op.botHigher |= 0xF0000000;
			}

			if(bots.find(op.bot1) == bots.end()){
				bots[op.bot1] = Bot(op.bot1);
			}
			if(bots.find(op.botLower) == bots.end()){
				bots[op.botLower] = Bot(op.botLower);
			}
			if(bots.find(op.botHigher) == bots.end()){
				bots[op.botHigher] = Bot(op.botHigher);
			}
		}
		else{
			assert(false);
		}
		operations.push_back(op);
		buffer.resize(1000);

	}
	
	int i = 0;
	while(!operations.empty() && i < operations.size()){
		if(operations[i].type == BotOperation::VALUE){
			bots[operations[i].bot1].Set(operations[i].val);
			operations.erase(operations.begin() + i);
			i = 0;
			continue;
		}
		else{
			//bot 103 gives low to bot 166 and high to bot 127
			if((bots[operations[i].bot1].lower != Bot::INVALID_VAL) &&
				(bots[operations[i].bot1].higher != Bot::INVALID_VAL))
			{
				int botLower = operations[i].botLower;
				if(botLower < 0){
					int outputIndex = botLower & 0x0FFFFFFF;
					outputs[outputIndex] = bots[operations[i].bot1].lower;
				}
				else{
					bots[botLower].Set(bots[operations[i].bot1].lower);
				}
				int botHigher = operations[i].botHigher;
				if(botHigher < 0){
					int outputIndex = botHigher & 0x0FFFFFFF;
					outputs[outputIndex] = bots[operations[i].bot1].higher;
				}
				else{
					bots[botHigher].Set(bots[operations[i].bot1].higher);
				}
				operations.erase(operations.begin() + i);
				i = 0;
				continue;
			}

		}
		i++;
	}

	int lower, higher;
	for(it = bots.begin(); it != bots.end(); it++){
		it->second.ReadVals(lower, higher);
		if(lower == 17 && higher == 61){
			printf("bot %d\n", it->first);
			break;
		}
	}
	printf("output multiplication: %d", outputs[0] * outputs[1] * outputs[2]);
	getchar();
	return 0;
}

