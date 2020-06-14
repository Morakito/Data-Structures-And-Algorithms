#pragma once
#include <iostream>

/*冒泡排序*/
void bubble_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	//外层循环控制排序趟数，共n-1趟
	for (int i = 0; i < size - 1; ++i) {
		bool swap = false;
		//内层循环控制每一趟排序次数
		//最末尾的i个已经被排好了,所以j的范围是0到size-1-i
		for (int j = 0; j < size - 1 - i; ++j) {
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				swap = true;
			}
		}
		if (!swap) break;
	}
}

/*选择排序*/
void selection_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	for (int i = 0; i < size - 1; ++i) {
		int min = i;
		//已排序序列0到i，未排序序列i到size-1
		//找到未排序序列的最小元素arr[min]
		for (int j = i + 1; j < size; ++j) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		//将找到的最小元素放到已排序序列的末尾
		std::swap(arr[min], arr[i]);
	}
}

/*插入排序*/
void insertion_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	//一开始的已排序序列0，未排序序列1到n-1
	for (int i = 1; i < size; ++i) {
		//当前未排序序列的一个元素
		int key = arr[i];
		//已排序序列的末尾位置
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			--j;//向前移动
		}
		//插入到相应位置
		arr[j + 1] = key;
	}
}

/*希尔排序*/
void shell_sort(int* arr, const  int size) {
	if (arr == NULL || size < 2) return;
	int gap = 1;
	//定义间隔序列
	while (gap < size / 2) {
		gap = 2 * gap;
	}
	while (gap >= 1) {
		//这里是间隔的插入排序
		for (int i = gap; i < size; ++i) {
			for (int j = i; j >= gap && (arr[j] < arr[j - gap]); j -= gap) {
				std::swap(arr[j], arr[j - gap]);
			}
		}
		gap /= 2;	//更新间隔数
	}
}

/*归并排序——递归版本*/
void merge_sort_recursive_helper(int* arr, int* help, const  int start, const  int end) {
	if (start >= end) return;

	/*以下是数组分割*/
	int mid = ((end - start) >> 1) + start;		//找到中间点
	//将原数组拆分成两段
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	merge_sort_recursive_helper(arr, help, start1, end1);
	merge_sort_recursive_helper(arr, help, start2, end2);

	/*以下是排序合并*/
	int k = start;
	//将两段合并，直到一段用完
	while (start1 <= end1 && start2 <= end2) {
		help[k++] = (arr[start1] < arr[start2]) ? arr[start1++] : arr[start2++];
	}
	//将没用完的一段直接接在末尾
	while (start1 <= end1) help[k++] = arr[start1++];
	while (start2 <= end2) help[k++] = arr[start2++];

	/*将辅助数组种的元素复制到原来的数组*/
	for (k = start; k <= end; ++k) {
		arr[k] = help[k];
	}
}
void merge_sort_recursive(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	//辅助数组，用来存放排序的结果
	int* help = new int[size];
	merge_sort_recursive_helper(arr, help, 0, size - 1);
	delete[] help;
}
/*归并排序——迭代版本*/
void merge_sort_iterative(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	int* help = new int[size]();
	int* a = arr;
	//片段长度block = 1,2,4,8....
	for (int block = 1; block < size; block *= 2) {
		//两两遍历片段
		for (int start = 0; start < size; start += (block * 2)) {
			int low = start;
			//取start+block和size种的较小者，防止越界,high同理
			int mid = (start + block) > size ? size : (start + block);
			int high = (start + block * 2) > size ? size : (start + block * 2);
			//分成两段，两段的起始和结束下标
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			int k = low;
			//将两段合并，直到一段用完
			while (start1 < end1 && start2 < end2) {
				help[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
			}
			//将没用完的一段直接接在末尾
			while (start1 < end1) help[k++] = a[start1++];
			while (start2 < end2) help[k++] = a[start2++];
		}
		//交换a和help指针
		int* temp = a;
		a = help;
		help = a;
	}
	/*
		当size是偶数的时候，help和a最后结果指向不变
		当size是奇数的时候，help和a最后指向相反
		最终help中存储的是排好的序列，要将help中的序列复制到原来的arr中
	*/
	if (a != arr) {
		for (int i = 0; i < size; ++i) {
			help[i] = a[i];
		}
		help = a;
	}
	delete[] help;
}

/*迭代和递归均使用*/
int quick_sort_partition(int* arr, int low, int high) {
	int index = (rand() & (high - low)) + low;
	int pivot = arr[index];	//基准元素取子序列的第一个元素
	while (low < high) {
		//找到一个比基准元素大的元素，和基准元素进行交换
		while (low < high && arr[high] >= pivot) --high;
		arr[low] = arr[high];
		//找到一个比基准元素小的元素，和基准元素进行交换
		while (low < high && arr[low] <= pivot) ++low;
		arr[high] = arr[low];
	}
	//扫描结束，恢复基准元素的位置
	arr[low] = pivot;
	//返回基准元素的位置
	return low;
}
/*快速排序——递归版本*/
void quick_sort_recursive_helper(int* arr, const int low, const int high) {
	if (low >= high) return;
	//将数组分成两部分
	int pivot = quick_sort_partition(arr, low, high);
	//递归排序左右子数组
	quick_sort_recursive_helper(arr, low, pivot - 1);
	quick_sort_recursive_helper(arr, pivot + 1, high);
}
void quick_sort_recursive(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	quick_sort_recursive_helper(arr, 0, size - 1);
}
/*快速排序——迭代版本*/
void quick_sort_iterative(int* arr, const int size) {
	//栈数组
	int min = 0, max = size - 1;
	int* stack = new int[size - 1];
	int top = -1;
	//将最大最小值压入栈
	stack[++top] = min;
	stack[++top] = max;
	//开始迭代
	while (top > -1) {
		max = stack[top--];
		min = stack[top--];
		//将数组分成两部分
		int pivot = quick_sort_partition(arr, min, max);
		//若基准元素左边还有数据元素
		if (pivot - 1 > min) {
			stack[++top] = min;
			stack[++top] = pivot - 1;
		}
		//若基准元素右边还有数据元素
		if (pivot + 1 < max) {
			stack[++top] = pivot + 1;
			stack[++top] = max;
		}
	}
}


/*堆排序*/
void adjust_heap(int* arr, int cur, int size) {
	//调整为最大堆,cur为待调整结点
	//cur的左孩子
	int child = 2 * cur + 1;
	while (child < size) {
		//child + 1是当前结点cur的右孩子
		//如果有右孩子而且大于左孩子，则用右孩子来与cur比较，否则用左孩子
		if ((child + 1) < size && arr[child] < arr[child + 1]) child++;

		//若较大的孩子比当前结点cur大
		if (arr[cur] < arr[child]) {
			//交换孩子结点和父节点
			std::swap(arr[cur], arr[child]);
			//此时child指向的是原来的父结点
			//继续判断原来的父结点是否需要继续调整
			cur = child;
			child = 2 * child + 1;
		}
		//待调整结点小于其左右孩子，不用调整，直接结束
		else {
			break;
		}
	}
}
void heap_sort(int* arr, int size) {
	if (arr == NULL || size < 2) return;

	//建堆: 最后一个非叶子结点的位置是i = (size - 1) / 2，从它开始依次向上调整
	for (int i = (size - 1) / 2; i >= 0; --i) {
		adjust_heap(arr, i, size);
	}
	//将大根堆反向输出
	for (int i = size - 1; i > 0; --i) {
		std::swap(arr[i], arr[0]);
		adjust_heap(arr, 0, i);
	}
}

/*计数排序*/
void count_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;

	int min = arr[0], max = arr[0];
	//寻找最大值max和最小值min
	for (int i = 1; i < size; ++i) {
		if (min > arr[i]) min = arr[i];
		if (max < arr[i]) max = arr[i];
	}
	//count_num = 1，说明数组中的元素全部一样
	int count_num = max - min + 1;
	if (count_num < 2) return;
	//用于计数的数组,初始元素都是0
	int* help = new int[count_num]();
	//计算数组中每个元素i出现的次数，存储到help【i】中
	for (int i = 0; i < size; ++i) {
		help[arr[i] - min]++;
	}
	//计算数组中小于等于每个元素的个数
	for (int i = min + 1; i <= max; ++i) {
		int index = i - min;
		help[i - min] += help[index - 1];;
	}
	//将排序结果存放在result中
	int* res = new int[size];
	for (int i = size - 1; i >= 0; --i) {
		res[help[arr[i] - min] - 1] = arr[i];
		--help[arr[i] - min];
	}
	//将res数组里的元素复制到arr数组中
	for (int i = 0; i < size; ++i) {
		arr[i] = res[i];
	}
	delete[] res;
	delete[] help;
}

/*桶排序*/
void bucket_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;

	int min = arr[0], max = arr[0];
	//寻找最大值max和最小值min
	for (int i = 1; i < size; ++i) {
		if (min > arr[i]) min = arr[i];
		if (max < arr[i]) max = arr[i];
	}
	//桶的数量
	int bucket_num = (max - min) / size + 1;	
	//统计每个桶里有多少个元素
	int* sizeof_each_bucket = new int[bucket_num]();
	for (int i = 0; i < size; ++i) {
		int index_bucket = (arr[i] - min) / size;
		sizeof_each_bucket[index_bucket]++;
	}
	//开辟桶空间
	int** bucket_arr = new int* [bucket_num];
	for (int i = 0; i < bucket_num; ++i) {
		bucket_arr[i] = new int[(std::size_t)sizeof_each_bucket[i] + 1]();
		//第一位存放该桶的size-1
		bucket_arr[i][0] = 1;
	}
	//将每个元素放入桶中
	for (int i = 0; i < size; ++i) {
		int index_bucket = (arr[i] - min) / size;
		int cur_bucket_size = bucket_arr[index_bucket][0]++;
		bucket_arr[index_bucket][cur_bucket_size] = arr[i];
	}
	//对每个桶进行排序
	for (int i = 0; i < bucket_num; ++i) {
		if (bucket_arr[i][0] == 1 || bucket_arr[i][0] == 2) continue;
		insertion_sort(bucket_arr[i] + 1, bucket_arr[i][0] - 1);
	}
	//将bucket_arr中的元素复制到arr中
	int index = 0;
	for (int i = 0; i < bucket_num; ++i) {
		for (int j = 1; j < bucket_arr[i][0]; ++j) {
			arr[index++] = bucket_arr[i][j];
		}
	}
	//释放内存
	delete[] sizeof_each_bucket;
	for (int i = 0; i < bucket_num; ++i) {
		delete[] bucket_arr[i];
	}
	delete[] bucket_arr;
}

/*基数排序*/
int get_max_radix(int* arr, const int size) {
	/*获取数组中的最大数位*/
	int max = arr[0];
	//先找到最大数字
	for (int i = 1; i < size; ++i) {
		if (arr[i] > max) max = arr[i];
	}
	int radix = 1, temp = 1;
	while (true) {
		temp *= 10;
		if (max / temp != 0) {
			radix++;
		}
		else {
			break;
		}
	}
	return radix;
}
int get_num(const int num, const int pos) {
	/*获取数字num第pos位数字*/
	int temp = 1;
	for (int i = 0; i < pos - 1; ++i) {
		temp *= 10;
	}
	return (num / temp) % 10;
}
void radix_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;

	//0-9共10个桶
	int** help = new int* [10]();
	for (int i = 0; i < 10; ++i) {
		help[i] = new int[(std::size_t)size + 1]();
		help[i][0] = 1;
	}

	int max_radix = get_max_radix(arr, size);
	//第i位数排序
	for (int radix = 1; radix <= max_radix; ++radix) {
		//将数组中的元素，按数位分配到各个桶中
		for (int i = 0; i < size; ++i) {
			int row = get_num(arr[i], radix);
			int col = help[row][0]++;
			help[row][col] = arr[i];
		}
		//从各个桶中收集元素
		int index = 0;
		for (int row = 0; row < 10; ++row) {
			for (int col = 1; col < help[row][0]; ++col) {
				arr[index++] = help[row][col];
			}
			//复位，下一个数位继续用
			help[row][0] = 1;
		}
	}
	
	for (int i = 0; i < 10; ++i) {
		delete[] help[i];
	}
	delete[] help;
}
