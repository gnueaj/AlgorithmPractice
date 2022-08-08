
#define size_t int
void swap(int& a, int& b)
{
    int c = a;
    a = b;
    b = c; 
}

class MaxHeap {
#define parent  (i >> 1)
#define left	(i << 1)
#define right   (i << 1 | 1)

	static constexpr size_t MAX_N = 100001;

	int data[MAX_N + 1];
    int ID[MAX_N + 1];
	size_t size;

public:
	MaxHeap() = default;

	void init() {
		size = 0;
        for(int i = 0; i <= MAX_N; i++)
        {
            data[i] = ID[i] = 0;
        }
	}

	// x 삽입
	void push(int uID, int income) {
		data[++size] = income;
        ID[size] = uID;
		for (int i = size; parent != 0 && data[parent] <= data[i]; i >>= 1) {
            if(data[parent] == data[i] && ID[parent] < ID[i]) break;
			swap(data[parent], data[i]);
            swap(ID[parent], ID[i]);
		}
	}

	// 최대값 리턴
	int top() const {

		return ID[1];
	}
    int getdata(){return data[1];}
    int getsize() const{
        return size;
    }
	// 최대값 삭제
	void pop() {

		data[1] = data[size];
        ID[1] = ID[size--];
		for (size_t i = 1; left <= size;) {
			const size_t max_child = ((left == size) || (data[left] > data[right]) 
                        || (data[left] == data[right] && ID[left] < ID[right])) ? left : right;
			if (data[max_child] > data[i] || 
                (data[max_child] == data[i] && ID[max_child] < ID[i])) {
				swap(data[max_child], data[i]);
                swap(ID[max_child], ID[i]);
				i = max_child;
			} else {
				break;
			}
		}
	}

#undef parent
#undef left
#undef right
};

MaxHeap DB;

void init()
{
    DB.init();
}

void addUser(int uID, int income) 
{
    DB.push(uID, income);
}

int getTop10(int result[10]) 
{
    int size = DB.getsize();

    int d[10];
    if(DB.getsize() < 10)
    {
        for(int i = 0; i < size; i++)
        {
            result[i] = DB.top(); 
            d[i] = DB.getdata();
            DB.pop();
        }
    }
    else
    {
        for(int i = 0; i < 10; i++)
        {
            result[i] = DB.top(); 
            d[i] = DB.getdata();
            DB.pop();
        }
    }
    for(int i = 0; i < (size >= 10 ? 10 : size); i++)
    {
        DB.push(result[i],d[i]);
    }
    return size >= 10 ? 10 : size;
}
