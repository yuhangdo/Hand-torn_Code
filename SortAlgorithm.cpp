//20230827 实现经典的排序算法
/*
 *排序算法	平均时间复杂度		最好情况	最坏情况	空间复杂度	排序方式	稳定性
 *冒泡排序	o(n^2)			o(n)		o(n^2)		o(1)		In-place	稳定
 *选择排序	o(n^2)			o(n^2)		o(n^2)		o(1)		In-place	不稳定
 *插入排序	o(n^2)			o(n)		o(n^2)		o(1)		In-place	稳定
 *归并排序	o(nlogn)		o(nlogn)	o(nlogn)	o(n)		Out-place	稳定
 *快速排序	o(nlogn)		o(nlogn)	o(n^2)		o(logn)		In-place	不稳定
 *堆排序	o(nlogn)		o(nlogn)	o(nlogn)	o(1)		In-place	不稳定
 *
 */

//tips
//内部排序：内部排序就是整个排序过程在内存储器中进行。
//外部排序：简单来说，就是数据量太大。内存储器容量装不下，需要借助外部设备，这类排序就是外部排序。

//以下各个排序算法各自独立，只是函数实现！

//1、	BubbleSort
//每次交换相邻的元素，每次把大的元素放到后面
//代码中的优化：代码中的flag，如果数组整个已经有序，数组有序就退出

vector<int> BubbleSort(vector<int>& nums) 
{
    for (int i = 0; i < nums.size(); ++i) {
        bool flag = false;
        for (int j = 0; j < n - i -1; ++j) {
            if (nums[j] > nums[j+1]) {
                swap(nums[j], nums[j+1]);
                flag = true;
            }             
        }
        if (flag == false) break;
    }
    return nums;
}


//2、 SelectSort
//选一个最小的和前面的交换 

vector<int> SelectSort(vector<int> nums) 
{
    if(nums.size() == 0) return nums;

    for (int i = 0; i < nums.size(); i++){
        int min = i;
        for (int j = i + 1; j < nums.size(); j++) {
            if(nums[j] < nums[min]) 
		min = j;
        }
        swap(nums[i], nums[min]);
    }
    return nums;
}


//3、 InsertSort
// 每次新加一个元素，放到截止到自己的位置的区间中合适的位置（该元素前面的已经排好序，所以i从1开始）

vector<int> InsertSort(vector<int> nums)
{
    if (nums.size() == 0) return nums;
    
    for (int i = 1; i < nums.size(); i++) {
        int cur = nums[i];
	int prev = nums[i - 1];
	while (prev >= 0 && nums[prev] > cur) {
	    nums[prev + 1] = nums[prev];
	    prev--;
	}
	
	nums[prev + 1] = cur;
    }

    return nums;

}


//4、 MergeSort
//分治

 
void merge_sort(vector<int>& q, int l, int r) //用到分治的思想。
{      
    if(l >= r) return;
    int mid = l + r >> 1;
    vector<int> tmp(r - l + 1, 0);
    merge_sort(q, l, mid);
    merge_sort(q, mid+1, r);
    int i = l, j = mid + 1, k=0;
    while (i <= mid && j <= r) {
        if (q[i]<=q[j]) tmp[k++] = q[i++];
        else  tmp[k++] = q[j++];
    }
    while (i <= mid)  tmp[k++] = q[i++];
    while (j <= r)  tmp[k++] = q[j++];  
    for (int i = l, j = 0; i <= r; i++,j++)
    {
        q[i] = tmp[j];
    }
}


//5、 QuickSort
//选>=pivot和<=pivot的元素进行交换


void quick_sort(vector<int>& q, int l, int r)  //stl源码剖析中快速排序差不多就是用的这种双指针
{
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j) {
        do i++; while (q[i] < x);
        do j--; while (q[j] > x);
        if (i < j) {
            swap(q[i], q[j]);
        }
    }
    quick_sort(q, l, j);
    quick_sort(q, j+1, r);
}


//6、 HeapSort
/*
*
*从非叶子节点到节点1,进行down操作，构造小根堆，这是o(n)的时间复杂度
*首先up（上溯）和down（下溯）的时间复杂度都是与树的高度成正比，所以是log(n)的。求最小值是o（1），插入和删除都是o(log(n))
*如何把一个数组建立堆，首先可以用插入的方式，就是一个一个进行插入，这个时间复杂度是log(n)，还有一个是从非叶子节点到节点1，时间复杂度是o(n)。
*因为从最后一个非叶子节点，即n/2，因为最后一层节点数量是n/2,倒数第二层的节点数量是n/4,再用错位相减法可以证明时间复杂度是o(n)的
*
*/

//输入一个长度为 n 的整数数列，从小到大输出前 m 小的数。
 
#include <iostream>
#include <algorithm>
 
using namespace std;
 
const int N = 1e5 + 10;
int n, m;
int h[N], cnt;
 
void up(int u)
{
    while (u / 2 && h[u / 2] > h[u]) {
        swap(h[u], h[u / 2]);
        u >>= 1;
    }
}
 
void down(int u)
{
    int t = u;
    while (u * 2 <= cnt && h[u * 2] < h[t]) 
        t = u * 2;
    while (u * 2 + 1 <= cnt && h[u * 2 + 1] < h[t]) 
        t = u * 2 + 1;
    
    if (u != t) {
        swap(h[t], h[u]);
        down(t);
    }
}
 
int main() {
    cin >> n >> m;
    cnt = n;
    
    for (int i = 1; i <= n; i++) cin >> h[i];
    
    //可以用插入的方法构造堆,时间复杂度o(nlg(n))
    //for (int i = 1; i <= n; i++) up(i);
    
    //用这种方法构造可以达到o(n)的时间复杂度
    for (int i = n / 2; i; i--) down(i);
    
    while (m--) {
        cout << h[1] << ' ';  //输出小根堆堆顶元素
        h[1] = h[cnt--]; // 删除小根堆对顶元素
        down(1);
    }
    
    return 0;
}

