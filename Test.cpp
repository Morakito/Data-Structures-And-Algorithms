#include <fstream>
#include "sort.h"
#include <ctime>
using namespace std;

/*生成乱序序列*/
int* rand_arry(const int size, const int min, const int max) {
	//开辟数组空间
	int* arr = new int[(std::size_t)size + 1];
	arr[0] = size;
	//采用当前系统时钟作为种子
	srand((unsigned)time(NULL));
	for (int i = 1; i < size + 1; ++i) {
		arr[i] = (rand() & (max - min)) + min;
	}
	return arr;
}
/*将生成的乱序序列写入文件*/
void write_rand(const char* filename, const int size, const int min, const int max) {
	int* arr = rand_arry(size, min, max);
	ofstream outfile;
	outfile.open(filename);
	if (!outfile.is_open()) {
		cerr << "打开文件失败！" << endl;
		exit(1);
	}
	for (int i = 0; i <= arr[0]; ++i) {
		outfile << arr[i];
		outfile << endl;
	}
}
/*模拟最差情况：元素反序*/
void write_reserve(const char* filename, const int size, const int min, const int max) {
	int* arr = rand_arry(size, min, max);
	ofstream outfile;
	outfile.open(filename);
	if (!outfile.is_open()) {
		cerr << "打开文件失败！" << endl;
		exit(1);
	}
	//将数组排序:数组长度小于47使用插入排序，大于47使用快速排序
	if (arr[0] < 47) {
		insertion_sort(arr + 1, arr[0]);
	}
	else {
		quick_sort_recursive(arr + 1, arr[0]);
	}
	//将数组元素反向写入文件
	outfile << arr[0] << endl;
	for (int i = arr[0]; i > 0; --i) {
		outfile << arr[i];
		outfile << endl;
	}
	delete[] arr;
}
/*从文件中读取乱序序列*/
int* read_rand(const char* filename) {
	ifstream infile;
	infile.open(filename);
	if (!infile.is_open()) {
		cerr << "打开文件失败！" << endl;
		exit(1);
	}
	int size;
	infile >> size;
	int* arr = new int[(std::size_t)size + 1];
	arr[0] = size;
	for (int i = 1; i <= size; ++i) {
		infile >> arr[i];
	}
	return arr;
}

/*测试不同数据规模下各排序算法的效率*/
void Test_sort(int size, const int min, const int max) {
	write_reserve("Arrays.txt", size, min, max);
	//write_rand("Arrays.txt", size, min, max);
	cout << "-------------数据规模：" << size << "----------" << endl;
	clock_t start, end;

	//冒泡排序
	int* a1 = read_rand("Arrays.txt");
	start = clock();
	bubble_sort(a1 + 1, a1[0]);
	end = clock();
	cout << "冒泡排序：" << end - start << "ms" << endl;
	delete[] a1;

	//选择排序
	int* a2 = read_rand("Arrays.txt");
	start = clock();
	selection_sort(a2 + 1, a2[0]);
	end = clock();;
	cout << "选择排序：" << end - start << "ms" << endl;
	delete[] a2;

	//插入排序
	int* a3 = read_rand("Arrays.txt");
	start = clock();
	insertion_sort(a3 + 1, a3[0]);
	end = clock();;
	cout << "插入排序：" << end - start << "ms" << endl;
	delete[] a3;

	//希尔排序
	int* a4 = read_rand("Arrays.txt");
	start = clock();
	shell_sort(a4 + 1, a4[0]);
	end = clock();
	cout << "希尔排序：" << end - start << "ms" << endl;
	delete[] a4;

	//归并排序——递归
	int* a5 = read_rand("Arrays.txt");
	start = clock();
	merge_sort_recursive(a5 + 1, a5[0]);
	end = clock();
	cout << "归并排序(递归)：" << end - start << "ms" << endl;
	delete[] a5;

	//归并排序——迭代
	int* a6 = read_rand("Arrays.txt");
	start = clock();
	merge_sort_iterative(a6 + 1, a6[0]);
	end = clock();
	cout << "归并排序(迭代)：" << end - start << "ms" << endl;
	delete[] a6;

	//快速排序——递归
	int* a7 = read_rand("Arrays.txt");
	start = clock();
	quick_sort_recursive(a7 + 1, a7[0]);
	end = clock();
	cout << "快速排序(递归)：" << end - start << "ms" << endl;
	delete[] a7;

	//快速排序——递归
	int* a8 = read_rand("Arrays.txt");
	start = clock();
	quick_sort_iterative(a8 + 1, a8[0]);
	end = clock();
	cout << "快速排序(迭代)：" << end - start << "ms" << endl;
	delete[] a8;


	//堆排序
	int* a9 = read_rand("Arrays.txt");
	start = clock();
	heap_sort(a9 + 1, a9[0]);
	end = clock();
	cout << "堆排序：" << end - start << "ms" << endl;
	delete[] a9;
	
	//计数排序
	int* a10 = read_rand("Arrays.txt");
	start = clock();
	count_sort(a10 + 1, a10[0]);
	end = clock();
	cout << "计数排序：" << end - start << "ms" << endl;
	delete[] a10;

	//桶排序
	int* a11 = read_rand("Arrays.txt");
	start = clock();
	bucket_sort(a11 + 1, a11[0]);
	end = clock();
	cout << "桶排序：" << end - start << "ms" << endl;
	delete[] a11;
	
	//基数排序
	int* a12 = read_rand("Arrays.txt");
	start = clock();
	radix_sort(a12 + 1, a12[0]);
	end = clock();
	cout << "基数排序：" << end - start << "ms" << endl;
	delete[] a12;
}

void Test_base() {
	int a[] = { 10,9,20,7,6,48,0,3,11,1 };
	//bubble_sort(a, 10);
	//selection_sort(a, 10);
	//insertion_sort(a, 10);
	//shell_sort(a, 10);

	//merge_sort_recursive(a, 10);
	//merge_sort_iteration(a, 10);

	//quick_sort_recursive(a, 10);
	//quick_sort_iterative(a, 10);

	//heap_sort(a, 10);
	//count_sort(a, 10);
	//bucket_sort(a, 10);
	//radix_sort(a, 10);
	for (int i = 0; i < 10; ++i) {
		cout << a[i] << " ";
	}
}

void Test_advance() {
	write_rand("Arrays.txt", 50000, 0, 500);
	int* a = read_rand("Arrays.txt");
	//bubble_sort(a + 1, a[0]);
	//selection_sort(a + 1, a[0]);
	//insertion_sort(a + 1, a[0]);
	//shell_sort(a + 1, a[0]);
	//merge_sort_recursive(a + 1, a[0]);
	//merge_sort_iteration(a + 1, a[0]);
	//quick_sort_recursive(a + 1, a[0]);
	//heap_sort(a + 1, a[0]);
	count_sort(a + 1, a[0]);
	//bucket_sort(a + 1, a[0]);
	//radix_sort(a + 1, a[0]);
	for (int i = 1; i <= a[0]; ++i) {
		cout << a[i] << " ";
	}
}

int main() {
	Test_sort(5000, 0, 500);

	//Test_base();
	//Test_advance();
	
	return 0;
}