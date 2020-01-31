#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <assert.h>
using namespace std;

#if 0
void Bubble(int *arr, int size) {
	for (int i = 0; i < size-1; ++i) {
		for (int j = 1; j < size - i; ++j) {
			// 降序
			if (arr[j] > arr[j - 1]) {
				swap(arr[j], arr[j - 1]);
			}
		}
	}
}

void BubbleSort(int* arr, int size) {
	int bound = 0;
	for (; bound < size - 1; ++bound) {
		for (int cur = size - 1; cur > bound; --cur) {
			//升序
			if (arr[cur - 1] > arr[cur]){
				swap(arr[cur - 1], arr[cur]);
			}
		}
	}
}

void AdjustDown(int *array, int size, int last) {
	int child = last * 2 + 1;
	while (child < size) {
		if (child + 1 < size && \
			array[child] > array[child + 1]) {
			++child;
		}
		if (array[child] < array[last]) {
			swap(array[child], array[last]);
			last = child;
			child = 2 * last + 1;
		}
		else { return; }
	}
}
//堆排序
void HeapSort(int* array, int size) {
	int last = (size-2)/2;
	for (; last >= 0; --last) {
		AdjustDown(array, size, last);
	}
	//堆删除
	int end = size - 1;
	while (end) {
		swap(array[end], array[0]);
		AdjustDown(array, end, 0);
		end--;
	}
}


int Partion2(int *array, int left, int right) {
	int key = array[right - 1];
	int begin = left;
	int end = right - 1;
	while (begin < end) {
		while (begin < end && array[begin] <= key) {
			begin++;
		}
		if (begin < end) {
			array[end] = array[begin];
			end--;
		}
		while (begin < end && array[end] >= key) {
			--end;
		}
		if (begin < end) {
			array[begin] = array[end];
			begin++;
		}
	}
	array[begin] = key;
	return begin;
}

int	Partion3(int *array, int left, int right) {
	int key = array[right - 1];
	int pre = left - 1;
	for (int cur = left; cur < right; ++cur) {
		if (array[cur] < key && ++pre != cur) {
			swap(array[cur], array[pre]);
		}
	}
	swap(array[++pre], array[right - 1]);
	return pre;
}

void QuickSort(int* array, int left, int right) {
	if (right - left <= 1) {
		return;
	}
	int div = Partion3(array, left, right);
	// 然后分别对 [left,div] 和 [div+1,right] 中的元素排序
	QuickSort(array, left, div);
	QuickSort(array, div + 1, right);
}

void MergeData(int *array, int left, int mid, int right, int *temp) {
	int begin1 = left, end1 = mid;
	int begin2 = mid, end2 = right;
	int index = left;
	while (begin1 < end1 && begin2 < end2) {
		if (array[begin1] < array[begin2]) {
			temp[index++] = array[begin1++];
		}
		else {
			temp[index++] = array[begin2++];
		}
	}
	while (begin1 < end1) {
		temp[index++] = array[begin1++];
	}
	while (begin2 < end2) {
		temp[index++] = array[begin2++];
	}
}

void _MergeSort(int* array, int left, int right, int* temp) {
	if (right - left <= 1) {
		return;
	}
	int mid = (left + right) / 2;
	_MergeSort(array, left, mid, temp);
	_MergeSort(array, mid, right, temp);
	MergeData(array, left, mid, right, temp);
	memcpy(array + left, temp + left, sizeof(array[left]) * (right - left));
}

void MergeSort(int* array, int size) {
	int* temp = (int*)malloc(size * sizeof(array[0]));
	if (temp == NULL) {
		assert(0);
		return;
	}
	_MergeSort(array, 0, size, temp);
	free(temp);
}
#endif

void CountSort(int *array, int size) {
	//选择最小的和最大的数字·O（N）	N代表的是数据个数
	int MaxValue = array[0];
	int MinValue = array[0];

	for (int i = 1; i < size; ++i) {
		if (array[i] > MaxValue) {
			MaxValue = array[i];
		}

		if (array[i] < MinValue) {
			MinValue = array[i];
		}
	}

	//申请空间·O（M）[辅助空间]·M代表是数据范围
	int Range = MaxValue - MinValue + 1;
	int* array2 = (int*)malloc(sizeof(int)*Range);
	if (array2 == NULL) {
		assert(0);
		return;
	}

	//将每一个位置置空
	memset(array2, 0, sizeof(int)*Range);

	//统计元素出现次数·O(N)
	for (int i = 0; i < size; ++i) {
		array2[array[i] - MinValue]++;
	}

	//往出搬移元素·O（N）
	int index = 0;
	for (int i = 0; i < Range; ++i) {
		while (array2[i]--) {
			array[index++] = i + MinValue;
		}
	}
	free(array2);
}

int main() {
	int arr[] = { 1,3,4,6,2,7,9,0,8,5 };
	CountSort(arr,10);
	for (int i = 0; i < 10; ++i) {
		cout << arr[i] << ' ';
	}
	cout << endl;

	system("pause");
	return 0;
}