#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

std::vector<std::string> incompletes;
std::vector<long> scores;

void scoreincomplete(void){
    int charscore;
    for(const std::string& s : incompletes){
        long score{};
        for(const char& c: s){
            score *= 5;
            switch(c){
                case ')':
                    charscore = 1;
                    break;
                case ']':
                    charscore = 2;
                    break;
                case '}':
                    charscore = 3;
                    break;
                case '>':
                    charscore = 4;
                    break;
            }
            score += charscore;
        }
        scores.push_back(score);
    }
}

long getincomplete(void){
    std::sort(scores.begin(), scores.end());
    int median = (scores.size() / 2);
    return scores[median];
}



int getscore(const char& x){
    switch(x){
        case ')':
            return 3;
        case ']':
            return 57;
        case '}':
            return 1197;
        case '>':
            return 25137;
    }
    return 0;
}

inline bool isopener(const char& x){
    return x == '<' || x == '[' || x == '(' || x == '{';
}

char complement(const char& x){
    switch(x){
        case '(':
            return ')';
        case '[':
            return ']';
        case '{':
            return '}';
        case '<':
            return '>';
    }
    return 0;

}

char checkline(const std::string& buf){
    std::stack<char> chunks;
    char top;
    for(const char& x: buf){
        if(isopener(x)){
            chunks.push(complement(x));
            continue;
        }
        top = chunks.top();
        if(x != top){
            return x;
        }
        chunks.pop();
    }
    // Add the unmatched braces to a string in the vector
    if(!chunks.empty()){
        std::string& inc = incompletes.emplace_back();
        for(int i = chunks.size(); i > 0; --i){
            inc.push_back(chunks.top());
            chunks.pop();
        }
    }
    return 0;
}