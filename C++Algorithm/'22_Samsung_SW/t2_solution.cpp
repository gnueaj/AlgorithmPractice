#include <map>
#include <algorithm>
#include <utility>
#include <vector>
#include <cstring>
#include <map>
#include <set>
#include <iostream>

using namespace std;

class student{
public:
    int mGrade;
    int mGender;
    int mScore;
    student(){}
    student(int grade, int gender, int score) : mGrade(grade), mGender(gender), mScore(score){}
};

map<int, student> studentDB; // key: mId, value: student info
map<int, set<int>> mScoreDB[4][2]; // key: mScore, value: mId, array[mGrade][mGender]

int genderToInt(char mGender[7]){
    return strlen(mGender) != 4;
}/* male -> 0, female -> 1 */

void init() {
    studentDB.clear();
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            mScoreDB[i][j].clear();
        }
    }
	return;
}

int add(int mId, int mGrade, char mGenderString[7], int mScore) {
    int mGender = genderToInt(mGenderString);

    studentDB.insert({mId, student(mGrade, mGender, mScore)});
    if(mScoreDB[mGrade][mGender].find(mScore) == mScoreDB[mGrade][mGender].end())
    {
        set<int> mIdSet; mIdSet.insert(mId);
        mScoreDB[mGrade][mGender].insert({mScore, mIdSet});
        /* mScore점수를 가진 학생이 존재하지 않을 경우 */
    }
    else
    {
        mScoreDB[mGrade][mGender].find(mScore)->second.insert(mId);
        /* mScore점수를 가진 학생이 이미 존재할 경우 */
    }
    /* DB insert */

    int highestScore = mScoreDB[mGrade][mGender].rbegin()->first; 
    /*mGrade학년 mGender인 학생 중 가장 높은 점수*/
    
    return *mScoreDB[mGrade][mGender].find(highestScore)->second.rbegin();

    /* mGrade학년 mGender인 학생 중에서 점수가 가장 높은 학생의 ID를 반환
    점수가 가장 높은 학생이 여러 명이라면, 그 중에서 ID가 가장 큰 값을 반환*/
}

int remove(int mId) {
    if(studentDB.find(mId) == studentDB.end()) // mId학생이 없는 경우
        return 0;
    else //mId학생이 있는 경우
    {
        student st = studentDB.find(mId)->second;
        //mId 학생 정보 저장
        studentDB.erase(mId);
        mScoreDB[st.mGrade][st.mGender].erase(st.mScore);
        //삭제
        if(mScoreDB[st.mGrade][st.mGender].empty()) //학년과 성별이 동일한 학생이 없는 경우
            return 0;
        else
            return *mScoreDB[st.mGrade][st.mGender].begin()->second.begin();
        //점수가 가장 낮은 학생 중 ID가 가장 작은 값 반환
    }
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGenderString[][7], int mScore) {
    int mGender[2];
    for(int i = 0; i < mGenderCnt; i++)
        mGender[i] = genderToInt(mGenderString[i]);

    int lowestScore = 300001;
    int returnId = 1000000001;

    for(int i = 0; i < mGradeCnt; i++)
    {
        for(int j = 0; j < mGenderCnt; j++)
        {
            if(!mScoreDB[mGrade[i]][mGender[j]].empty() && 
                mScoreDB[mGrade[i]][mGender[j]].lower_bound(mScore) != mScoreDB[mGrade[i]][mGender[j]].end())
            {// 조건에 맞는 ID가 존재
                int score = mScoreDB[mGrade[i]][mGender[j]].lower_bound(mScore)->first;
                if(lowestScore == score)
                    returnId = min(returnId, *mScoreDB[mGrade[i]][mGender[j]].find(score)->second.begin());
                else if(lowestScore >= score)
                {
                    lowestScore = score;
                    returnId = *mScoreDB[mGrade[i]][mGender[j]].find(score)->second.begin();
                }
            }
        }
    }
	return returnId == 1000000001 ? 0 : returnId ;
}