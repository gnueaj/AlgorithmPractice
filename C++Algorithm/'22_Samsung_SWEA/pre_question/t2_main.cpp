#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

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

#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_REMOVE 300
#define CMD_QUERY 400

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