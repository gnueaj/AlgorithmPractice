#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <map>
#include <algorithm>
#include <utility>
#include <cstring>
#include <map>
#include <set>
#include <iostream>

#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_REMOVE 300
#define CMD_QUERY 400

using namespace std;

extern void init();
// 등록된 성적이 없는 상태가 됨

extern int add(int mId, int mGrade, char mGenderString[7], int mScore); 
/* mId: 학생의 ID ( 1 ≤ mId ≤ 1,000,000,000 )
    mGrade: 학생의 학년 ( 1 ≤ mGrade ≤ 3 )
    mGender: 학생의 성별 ( ‘＼0’ 문자로 끝나는 “male” 또는 “female” 문자열 )
    mScore: 학생의 점수 ( 0 ≤ mScore ≤ 300,000 )
    mGrade학년 mGender인 학생 중에서 점수가 가장 높은 학생의 ID를 반환 */

extern int remove(int mId); 
/* 학생id가 mId인 학생의 기록을 삭제함
    삭제 후 mId 학생의 학년과 성별이 동일한 학생 중에서 점수가 가장 낮은 학생의 ID를 반환함
    id가 mId인 학생의 점수가 기록되어 있지 않다면 0을 반환 */

extern int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGenderString[][7], int mScore);
/* 학년(mGrade)과 성별(mGender)을 만족하면서
    특정 점수( 0 ≤ mScore ≤ 300,000 )이상의 학생 중 점수가 가장 낮은 학생의 id를 반환 
    점수가 가장 낮은 학생이 여러 명이면 ID가 가장 작은 값을 반환 
    ( 1 ≤ mGradeCnt ≤ 3 )개의 학년이 ( 1 ≤ mGrade[i] ≤ 3 ) 배열로 주어지며 ex) {1, 3}
    ( 1 ≤ mGenderCnt ≤ 2 )개의 성별이 ( mGender[i] = ‘＼0’ 문자로 끝나는 “male” 또는 “female” 문자열 ) 
    배열로 주어짐 ex) {"male"}, {"male","female"} 
    점수가 mScore 이상인 학생이 없다면 0을 반환*/
    
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

static bool run() {
	int q;
	scanf("%d", &q);

	int id, grade, score;
	char gender[7];
	int cmd, ans, ret;
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
			case CMD_INIT:
				init();
				okay = true;
				break;
			case CMD_ADD:
				scanf("%d %d %s %d %d", &id, &grade, gender, &score, &ans);
				ret = add(id, grade, gender, score);
				if (ans != ret)
					okay = false;
				break;
			case CMD_REMOVE:
				scanf("%d %d", &id, &ans);
				ret = remove(id);
				if (ans != ret)
					okay = false;
				break;
			case CMD_QUERY: {
				int gradeCnt, genderCnt;
				int gradeArr[3];
				char genderArr[2][7];
				scanf("%d", &gradeCnt);
				if (gradeCnt == 1) {
					scanf("%d %d", &gradeArr[0], &genderCnt);
				} else if (gradeCnt == 2) {
					scanf("%d %d %d", &gradeArr[0], &gradeArr[1], &genderCnt);
				} else {
					scanf("%d %d %d %d", &gradeArr[0], &gradeArr[1], &gradeArr[2], &genderCnt);
				}
				if (genderCnt == 1) {
					scanf("%s %d %d", genderArr[0], &score, &ans);
				} else {
					scanf("%s %s %d %d", genderArr[0], genderArr[1], &score, &ans);
				}
				ret = query(gradeCnt, gradeArr, genderCnt, genderArr, score);
				if (ans != ret)
					okay = false;
				break;
			}
			default:
				okay = false;
				break;
		}
	}
	return okay;
}

int genderToInt(char mGender[7]){
    return strlen(mGender) != 4;
}/* male -> 0, female -> 1 */

void init() {
    studentDB.clear();
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            mScoreDB[i][j].clear();
        }
    }
	return;
}

int add(int mId, int mGrade, char mGenderString[7], int mScore) {
    int mGender = genderToInt(mGenderString);

    studentDB.insert({mId, student(mGrade, mGender, mScore)});
    if(mScoreDB[mGrade][mGender].find(mScore) == mScoreDB[mGrade][mGender].end()){
        set<int> mIdSet; 
        mIdSet.insert(mId);
        
        mScoreDB[mGrade][mGender].insert({mScore, mIdSet});
        /* mScore점수를 가진 학생이 존재하지 않을 경우 */
    }else{
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
    else{  //mId학생이 있는 경우
        student st = studentDB.find(mId)->second;
        //mId 학생 정보 저장
        studentDB.erase(mId);

        if(mScoreDB[st.mGrade][st.mGender].find(st.mScore)->second.size() == 1){ //mScore인 학생이 한 명일 때
            mScoreDB[st.mGrade][st.mGender].erase(st.mScore);
        }else{
            mScoreDB[st.mGrade][st.mGender].find(st.mScore)->second.erase(mId); //mScore인 학생이 여러 명일 때
        }
        
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

    for(int i = 0; i < mGradeCnt; i++){
        for(int j = 0; j < mGenderCnt; j++){
            if(!mScoreDB[mGrade[i]][mGender[j]].empty() && 
                mScoreDB[mGrade[i]][mGender[j]].lower_bound(mScore) != mScoreDB[mGrade[i]][mGender[j]].end())
            {// 조건에 맞는 ID가 존재
                int score = mScoreDB[mGrade[i]][mGender[j]].lower_bound(mScore)->first;
                if(lowestScore == score){// 조건에 맞는 ID의 가장 낮은 점수가 이전까지의 가장 낮은 점수와 같을 때
                    returnId = min(returnId, *mScoreDB[mGrade[i]][mGender[j]].find(score)->second.begin());
                }else if(lowestScore >= score){
                    lowestScore = score;
                    returnId = *mScoreDB[mGrade[i]][mGender[j]].find(score)->second.begin();
                }
            }
        }
    }
	return returnId == 1000000001 ? 0 : returnId ;
}

int main() {
	setbuf(stdout, NULL);
	freopen("test.txt", "r", stdin);

	int T, MARK; //test case, 
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}