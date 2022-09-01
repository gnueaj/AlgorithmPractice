#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_DESTROY 200
#define CMD_UPDATE 300
#define CMD_PARTICIPATE 400
#define CMD_CANCEL 500
#define CMD_CALCPROFIT 600

extern void init(int N, int K, int M, int mResPrice[]);
extern void destroy();
extern void update(int mBlockR, int mBlockC, int mCost, int mResInfo[][100]);
extern int participate(char mCompany[], int mR1, int mC1, int mR2, int mC2);
extern void cancel(char mCompany[]);
extern int calcProfit(int mTop);
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static unsigned int mSeed;
static unsigned int pseudo_rand(void)
{
	mSeed = mSeed * 214013 + 2531011;
	return (mSeed >> 16) & 0x7FFF;
}

static int run()
{
	int isOK = 0;

	int N, S;

	int cmd;
	int result;
	int check;

	int mN, mK, mM;
	int mResPrice[10];
	int ResMod;
	int mBlockR, mBlockC, mCost;
	static int mResInfo[100][100];
	int mR1, mC1, mR2, mC2;
	char mCompany[11];
	int mTop;

	int inputOrder = 0;

	scanf("%d %d", &N, &S);

	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			mSeed = S;
			scanf("%d %d %d", &mN, &mK, &mM);
			ResMod = 1 << mM;
			for (int m = 0; m < mM; m++) {
				scanf("%d", &mResPrice[m]);
			}
			init(mN, mK, mM, mResPrice);
			inputOrder = 0;
			isOK = 1;
			break;

		case CMD_UPDATE:
			scanf("%d %d %d", &mBlockR, &mBlockC, &mCost);
			if (S != -1) {
				if (inputOrder % 6 == 0) {
					for (int r = 0; r < mK; r++) {
						for (int c = 0; c < mK; c++) {
							scanf("%d", &mResInfo[r][c]);
						}
					}
				} else {
					for (int r = 0; r < mK; r++) {
						for (int c = 0; c < mK; c++) {
							mResInfo[r][c] = pseudo_rand() % ResMod;
						}
					}
				}
			}
			else {
				scanf("%d %d %d %d", &mResInfo[0][0], &mResInfo[0][1], &mResInfo[1][0], &mResInfo[1][1]);
			}
			update(mBlockR, mBlockC, mCost, mResInfo);
			inputOrder++;
			break;

		case CMD_PARTICIPATE:
			scanf("%s %d %d %d %d", mCompany, &mR1, &mC1, &mR2, &mC2);
			result = participate(mCompany, mR1, mC1, mR2, mC2);
			scanf("%d", &check);
			if (result != check)
				isOK = 0;
			break;

		case CMD_CANCEL:
			scanf("%s", mCompany);
			cancel(mCompany);
			break;

		case CMD_CALCPROFIT:
			scanf("%d", &mTop);
			result = calcProfit(mTop);
			scanf("%d", &check);
			if (result != check)
				isOK = 0;
			break;
		default:
			break;
		}
	}
	destroy();
	return isOK;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input7.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		if (run()) printf("#%d %d\n", tc, MARK);
		else printf("#%d %d\n", tc, 0);
	}
	return 0;
}