#include <map>
#include <set>
#include <utility>

using namespace std;

map<int, int> allocated; // {Start, Size} 
map<int, int> emptySpaceIdx; //{Start, Size}
set<pair<int, int>> emptySpaceSize; // {Size, Start}  

void init(int N) {
    allocated.clear();
    emptySpaceIdx.clear();
    emptySpaceSize.clear();

    emptySpaceSize.insert({N, 0}); // 0 ~ N-1 할당
    emptySpaceIdx.insert({0, N}); // 
	return;
}

int allocate(int mSize) {
    if(emptySpaceSize.lower_bound({mSize, -1}) == emptySpaceSize.end())
        return -1;
    // 공간이 없는 경우
    pair<int, int> emptySpace = *emptySpaceSize.lower_bound({mSize, -1});

    int prevSize = emptySpace.first;
    int start = emptySpace.second;
    
    allocated.insert({start, mSize});

    emptySpaceSize.erase({prevSize, start});
    emptySpaceIdx.erase(start);

    if(prevSize - mSize > 0)
    {
        emptySpaceSize.insert({prevSize - mSize, start + mSize});
        emptySpaceIdx.insert({start + mSize, prevSize - mSize});
    }

	return start;
}

int release(int mAddr) {
    if(allocated.find(mAddr) == allocated.end())
        return -1;
    
    int size = allocated.find(mAddr)->second; //시작주소가 mAddr인 메모리의 size
    allocated.erase(mAddr); //메모리 해제
   
    map<int, int>::iterator it = emptySpaceIdx.lower_bound(mAddr);
    if(it != emptySpaceIdx.end() && it->first == mAddr + size) 
    {
        int backStart = it->first;
        int backSize = it->second;
        if(it != emptySpaceIdx.begin() && emptySpaceIdx.size() >= 2 &&
            (--it)->first + it->second == mAddr)
        {
            int frontStart = it->first;
            int frontSize = it->second;
            int totalSize = frontSize + size + backSize;
            emptySpaceIdx.erase(backStart);
            emptySpaceSize.erase({backSize, backStart});
            emptySpaceIdx.erase(frontStart);
            emptySpaceSize.erase({frontSize, frontStart});

            emptySpaceIdx.insert({frontStart, totalSize});
            emptySpaceSize.insert({totalSize, frontStart});
        }//해제된 공간 앞/뒤에 빈 공간 존재
        else
        {
            int totalSize = backSize + size;
            emptySpaceIdx.erase(backStart);
            emptySpaceSize.erase({backSize, backStart});

            emptySpaceIdx.insert({mAddr, totalSize});
            emptySpaceSize.insert({totalSize, mAddr});
        }//해제된 공간 뒤에 빈 공간 존재
    }
    else if(((it == emptySpaceIdx.end() && emptySpaceIdx.size() >= 1) || 
        (it != emptySpaceIdx.end() && it != emptySpaceIdx.begin() && emptySpaceIdx.size() >= 2)) && 
        (--it)->first + it->second == mAddr)
    {
        int frontStart = it->first;
        int frontSize = it->second;
        int totalSize = frontSize + size;
        emptySpaceIdx.erase(frontStart);
        emptySpaceSize.erase({frontSize, frontStart});

        emptySpaceIdx.insert({frontStart, totalSize});
        emptySpaceSize.insert({totalSize, frontStart});
        //해제된 공간 앞에 빈 공간 존재 
    }
    else
    {   
        emptySpaceSize.insert({size, mAddr});
        emptySpaceIdx.insert({mAddr, size});
    } //빈 공간이 존재하지 않음
	return size;
}