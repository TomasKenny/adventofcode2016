// adventofcode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

std::string AbATobAb(const std::string & str){
	std::string bab(str);
	std::swap(bab[0], bab[1]);
	bab[2] = bab[0];
	return bab;
}

std::vector<std::string> GetAbA(const std::string & str){
	std::vector<std::string> vec;
	for(int i = 0; i < str.size() - 2; i++){
		if((str[i] == str[i + 2]) &&
			(str[i] != str[i + 1]))
		{
			vec.push_back(std::string(str.begin() + i, str.begin() + i + 3));
		}
	}
	return vec;
}

int _tmain(int argc, _TCHAR* argv[]){
	
	FILE* fd = fopen("C:\\Users\\Tom\\Desktop\\input.txt", "r");
	if(!fd){
		printf("cannot read file");
	}
	char buffer[1000];
	
	int counter = 0;

	while(fgets(buffer, 1000, fd)){
		bool likeAbba = true;
		char* ptr = strtok(buffer, "[]");
		std::vector<std::string> aba, bab;

		do{
			std::vector<std::string> res = GetAbA(ptr);
			if(likeAbba){
				aba.insert(aba.end(), res.begin(), res.end());
			}
			else{
				bab.insert(bab.end(), res.begin(), res.end());
			}
			likeAbba = !likeAbba;
		}while(ptr = strtok(NULL, "[]"));
		
		for(int i = 0; i < aba.size(); i++){
			std::string babStr = AbATobAb(aba[i]);
			for(int j = 0; j < bab.size(); j++){
				if(babStr == bab[j]){
					counter++;
					goto end;
				}
			}
		}
end:	
		;
	}
	
	printf("%d", counter);
	getchar();
	return 0;
}

