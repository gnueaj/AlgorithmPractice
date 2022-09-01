#include<deque>
#include<iostream>
using namespace std;
class Deque
{
    int  arr[500001];
    int  front;
    int  rear;
public :
    Deque(){
        front=250000;
        rear=250000;
    }
 
    // Operations on Deque:
    void  insertfront(int key);
    void  insertrear(int key);
    void clear();
    int size();
    int operator[](int i);
};
 
int Deque::size(){
    return rear-front;
}
 
// Inserts an element at front
void Deque::insertfront(int key)
{
    arr[--front]=key;
   
}
 
// function to inset element at rear end
// of Deque.
void Deque ::insertrear(int key)
{
    arr[rear++]=key;

}


int Deque::operator[](int i){
    return arr[front+i];
}

void Deque::clear(){
    this->front=250000;
    this->rear=250000;
}

constexpr int mod=20;
Deque d;
Deque sum[31];//jocker가 index일때 합을 저장해놓는다
int jocker;

int change(int value,int to){
    if(value==-1){
        return to;
    }else{
        return value;
    }
}

void init(int mJoker, int mNumbers[5])
{
    d.clear();
    for(int i=0;i<31;i++){
        sum[i].clear();
    }
    jocker = mJoker;
    for(int i=0;i<5;i++){
        d.insertrear(mNumbers[i]);
    }
    for(int i=1;i<31;i++){
        sum[i].insertrear((change(d[0],i)+change(d[1],i)+change(d[2],i)+change(d[3],i))%mod);
        sum[i].insertrear((change(d[1],i)+change(d[2],i)+change(d[3],i)+change(d[4],i))%mod);
    }


}
void putCards(int mDir, int mNumbers[5])
{
    if(mDir==1){
        for(int i=0;i<5;i++){
            d.insertrear(mNumbers[i]);
        }
        int size=d.size();
        for(int i=1;i<31;i++){
            for(int j=0;j<5;j++){
                sum[i].insertrear((change(d[size-8+j],i)+change(d[size-7+j],i)+change(d[size-6+j],i)+change(d[size-5+j],i))%mod);
            }
        }

    }else if(mDir==0){
        for(int i=4;i>=0;i—){
            d.insertfront(mNumbers[i]);
        }
        for(int i=1;i<31;i++){
            for(int j=0;j<5;j++){
                sum[i].insertfront((change(d[4-j],i)+change(d[5-j],i)+change(d[6-j],i)+change(d[7-j],i))%mod);
            }
        }
    }else{
        //wrong mDir
    }
 
}


int findNumber(int mNum, int mNth, int ret[4])
{
    int success=0;
    int size=sum[jocker].size();
    for(int i=0;i<size;i++){
        if(sum[jocker][i]==mNum){
            mNth—;
        }
        if(mNth==0){
            for(int j=0;j<4;j++){
                ret[j]=d[i+j];
            }
            success=1;
            break;
        }
    }
    return success;
}

void changeJoker(int mValue)
{
    jocker=mValue;
}

// [멋쩍은 튜브] [오후 6:43] 아마 3초 가까이 쓰시고 통과될 것 같은데
// [멋쩍은 튜브] [오후 6:43] 그 조커가
// [멋쩍은 튜브] [오후 6:43] 굳이 30까지 필요가 없어요
// [멋쩍은 튜브] [오후 6:44] 간단한 예를 들어 드리면
// [멋쩍은 튜브] [오후 6:44] % 20말고
// [멋쩍은 튜브] [오후 6:44] % 2라고 치면
// [멋쩍은 튜브] [오후 6:44] 각 카드의 합이 홀수인가 짝수인가?
// [멋쩍은 튜브] [오후 6:44] 가 되겠죠
// [멋쩍은 튜브] [오후 6:45] 각 카드에 % 2 한 값의 합과
// [멋쩍은 튜브] [오후 6:45] 모든 카드에 합에 % 2 한 값은
// [멋쩍은 튜브] [오후 6:45] 다르지 않아요
// [멋쩍은 튜브] [오후 6:46] 저기에 마지막에도 % 2 한다 치면
// [멋쩍은 튜브] [오후 6:46] 값은 같아요
// [멋쩍은 튜브] [오후 6:46] 제 말의 요지는
// [멋쩍은 튜브] [오후 6:46] 조커를 굳이 30까지 고려 안하고
// [멋쩍은 튜브] [오후 6:46] % 20해서
// [멋쩍은 튜브] [오후 6:47] 0~19로 압축하면
// [멋쩍은 튜브] [오후 6:47] 결과는 같은데 반복문을 많이 줄일 수 있죠
