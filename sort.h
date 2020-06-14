#pragma once
#include <iostream>

/*ð������*/
void bubble_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	//���ѭ������������������n-1��
	for (int i = 0; i < size - 1; ++i) {
		bool swap = false;
		//�ڲ�ѭ������ÿһ���������
		//��ĩβ��i���Ѿ����ź���,����j�ķ�Χ��0��size-1-i
		for (int j = 0; j < size - 1 - i; ++j) {
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				swap = true;
			}
		}
		if (!swap) break;
	}
}

/*ѡ������*/
void selection_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	for (int i = 0; i < size - 1; ++i) {
		int min = i;
		//����������0��i��δ��������i��size-1
		//�ҵ�δ�������е���СԪ��arr[min]
		for (int j = i + 1; j < size; ++j) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		//���ҵ�����СԪ�طŵ����������е�ĩβ
		std::swap(arr[min], arr[i]);
	}
}

/*��������*/
void insertion_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	//һ��ʼ������������0��δ��������1��n-1
	for (int i = 1; i < size; ++i) {
		//��ǰδ�������е�һ��Ԫ��
		int key = arr[i];
		//���������е�ĩβλ��
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			--j;//��ǰ�ƶ�
		}
		//���뵽��Ӧλ��
		arr[j + 1] = key;
	}
}

/*ϣ������*/
void shell_sort(int* arr, const  int size) {
	if (arr == NULL || size < 2) return;
	int gap = 1;
	//����������
	while (gap < size / 2) {
		gap = 2 * gap;
	}
	while (gap >= 1) {
		//�����Ǽ���Ĳ�������
		for (int i = gap; i < size; ++i) {
			for (int j = i; j >= gap && (arr[j] < arr[j - gap]); j -= gap) {
				std::swap(arr[j], arr[j - gap]);
			}
		}
		gap /= 2;	//���¼����
	}
}

/*�鲢���򡪡��ݹ�汾*/
void merge_sort_recursive_helper(int* arr, int* help, const  int start, const  int end) {
	if (start >= end) return;

	/*����������ָ�*/
	int mid = ((end - start) >> 1) + start;		//�ҵ��м��
	//��ԭ�����ֳ�����
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	merge_sort_recursive_helper(arr, help, start1, end1);
	merge_sort_recursive_helper(arr, help, start2, end2);

	/*����������ϲ�*/
	int k = start;
	//�����κϲ���ֱ��һ������
	while (start1 <= end1 && start2 <= end2) {
		help[k++] = (arr[start1] < arr[start2]) ? arr[start1++] : arr[start2++];
	}
	//��û�����һ��ֱ�ӽ���ĩβ
	while (start1 <= end1) help[k++] = arr[start1++];
	while (start2 <= end2) help[k++] = arr[start2++];

	/*�����������ֵ�Ԫ�ظ��Ƶ�ԭ��������*/
	for (k = start; k <= end; ++k) {
		arr[k] = help[k];
	}
}
void merge_sort_recursive(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	//�������飬�����������Ľ��
	int* help = new int[size];
	merge_sort_recursive_helper(arr, help, 0, size - 1);
	delete[] help;
}
/*�鲢���򡪡������汾*/
void merge_sort_iterative(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	int* help = new int[size]();
	int* a = arr;
	//Ƭ�γ���block = 1,2,4,8....
	for (int block = 1; block < size; block *= 2) {
		//��������Ƭ��
		for (int start = 0; start < size; start += (block * 2)) {
			int low = start;
			//ȡstart+block��size�ֵĽ�С�ߣ���ֹԽ��,highͬ��
			int mid = (start + block) > size ? size : (start + block);
			int high = (start + block * 2) > size ? size : (start + block * 2);
			//�ֳ����Σ����ε���ʼ�ͽ����±�
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			int k = low;
			//�����κϲ���ֱ��һ������
			while (start1 < end1 && start2 < end2) {
				help[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
			}
			//��û�����һ��ֱ�ӽ���ĩβ
			while (start1 < end1) help[k++] = a[start1++];
			while (start2 < end2) help[k++] = a[start2++];
		}
		//����a��helpָ��
		int* temp = a;
		a = help;
		help = a;
	}
	/*
		��size��ż����ʱ��help��a�����ָ�򲻱�
		��size��������ʱ��help��a���ָ���෴
		����help�д洢�����źõ����У�Ҫ��help�е����и��Ƶ�ԭ����arr��
	*/
	if (a != arr) {
		for (int i = 0; i < size; ++i) {
			help[i] = a[i];
		}
		help = a;
	}
	delete[] help;
}

/*�����͵ݹ��ʹ��*/
int quick_sort_partition(int* arr, int low, int high) {
	int pivot = arr[low];	//��׼Ԫ��ȡ�����еĵ�һ��Ԫ��
	while (low < high) {
		//�ҵ�һ���Ȼ�׼Ԫ�ش��Ԫ�أ��ͻ�׼Ԫ�ؽ��н���
		while (low < high && arr[high] >= pivot) --high;
		arr[low] = arr[high];
		//�ҵ�һ���Ȼ�׼Ԫ��С��Ԫ�أ��ͻ�׼Ԫ�ؽ��н���
		while (low < high && arr[low] <= pivot) ++low;
		arr[high] = arr[low];
	}
	//ɨ��������ָ���׼Ԫ�ص�λ��
	arr[low] = pivot;
	//���ػ�׼Ԫ�ص�λ��
	return low;
}
/*�������򡪡��ݹ�汾*/
void quick_sort_recursive_helper(int* arr, const int low, const int high) {
	if (low >= high) return;
	//������ֳ�������
	int pivot = quick_sort_partition(arr, low, high);
	//�ݹ���������������
	quick_sort_recursive_helper(arr, low, pivot - 1);
	quick_sort_recursive_helper(arr, pivot + 1, high);
}
void quick_sort_recursive(int* arr, const int size) {
	if (arr == NULL || size < 2) return;
	quick_sort_recursive_helper(arr, 0, size - 1);
}
/*�������򡪡������汾*/
void quick_sort_iterative(int* arr, const int size) {
	//ջ����
	int min = 0, max = size - 1;
	int* stack = new int[size - 1];
	int top = -1;
	//�������Сֵѹ��ջ
	stack[++top] = min;
	stack[++top] = max;
	//��ʼ����
	while (top > -1) {
		max = stack[top--];
		min = stack[top--];
		//������ֳ�������
		int pivot = quick_sort_partition(arr, min, max);
		//����׼Ԫ����߻�������Ԫ��
		if (pivot - 1 > min) {
			stack[++top] = min;
			stack[++top] = pivot - 1;
		}
		//����׼Ԫ���ұ߻�������Ԫ��
		if (pivot + 1 < max) {
			stack[++top] = pivot + 1;
			stack[++top] = max;
		}
	}
}


/*������*/
void adjust_heap(int* arr, int cur, int size) {
	//����Ϊ����,curΪ���������
	//cur������
	int child = 2 * cur + 1;
	while (child < size) {
		//child + 1�ǵ�ǰ���cur���Һ���
		//������Һ��Ӷ��Ҵ������ӣ������Һ�������cur�Ƚϣ�����������
		if ((child + 1) < size && arr[child] < arr[child + 1]) child++;

		//���ϴ�ĺ��ӱȵ�ǰ���cur��
		if (arr[cur] < arr[child]) {
			//�������ӽ��͸��ڵ�
			std::swap(arr[cur], arr[child]);
			//��ʱchildָ�����ԭ���ĸ����
			//�����ж�ԭ���ĸ�����Ƿ���Ҫ��������
			cur = child;
			child = 2 * child + 1;
		}
		//���������С�������Һ��ӣ����õ�����ֱ�ӽ���
		else {
			break;
		}
	}
}
void heap_sort(int* arr, int size) {
	if (arr == NULL || size < 2) return;

	//����: ���һ����Ҷ�ӽ���λ����i = (size - 1) / 2��������ʼ�������ϵ���
	for (int i = (size - 1) / 2; i >= 0; --i) {
		adjust_heap(arr, i, size);
	}
	//������ѷ������
	for (int i = size - 1; i > 0; --i) {
		std::swap(arr[i], arr[0]);
		adjust_heap(arr, 0, i);
	}
}

/*��������*/
void count_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;

	int min = arr[0], max = arr[0];
	//Ѱ�����ֵmax����Сֵmin
	for (int i = 1; i < size; ++i) {
		if (min > arr[i]) min = arr[i];
		if (max < arr[i]) max = arr[i];
	}
	//count_num = 1��˵�������е�Ԫ��ȫ��һ��
	int count_num = max - min + 1;
	if (count_num < 2) return;
	//���ڼ���������,��ʼԪ�ض���0
	int* help = new int[count_num]();
	//����������ÿ��Ԫ��i���ֵĴ������洢��help��i����
	for (int i = 0; i < size; ++i) {
		help[arr[i] - min]++;
	}
	//����������С�ڵ���ÿ��Ԫ�صĸ���
	for (int i = min + 1; i <= max; ++i) {
		int index = i - min;
		help[i - min] += help[index - 1];;
	}
	//�������������result��
	int* res = new int[size];
	for (int i = size - 1; i >= 0; --i) {
		res[help[arr[i] - min] - 1] = arr[i];
		--help[arr[i] - min];
	}
	//��res�������Ԫ�ظ��Ƶ�arr������
	for (int i = 0; i < size; ++i) {
		arr[i] = res[i];
	}
	delete[] res;
	delete[] help;
}

/*Ͱ����*/
void bucket_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;

	int min = arr[0], max = arr[0];
	//Ѱ�����ֵmax����Сֵmin
	for (int i = 1; i < size; ++i) {
		if (min > arr[i]) min = arr[i];
		if (max < arr[i]) max = arr[i];
	}
	//Ͱ������
	int bucket_num = (max - min) / size + 1;	
	//ͳ��ÿ��Ͱ���ж��ٸ�Ԫ��
	int* sizeof_each_bucket = new int[bucket_num]();
	for (int i = 0; i < size; ++i) {
		int index_bucket = (arr[i] - min) / size;
		sizeof_each_bucket[index_bucket]++;
	}
	//����Ͱ�ռ�
	int** bucket_arr = new int* [bucket_num];
	for (int i = 0; i < bucket_num; ++i) {
		bucket_arr[i] = new int[(std::size_t)sizeof_each_bucket[i] + 1]();
		//��һλ��Ÿ�Ͱ��size-1
		bucket_arr[i][0] = 1;
	}
	//��ÿ��Ԫ�ط���Ͱ��
	for (int i = 0; i < size; ++i) {
		int index_bucket = (arr[i] - min) / size;
		int cur_bucket_size = bucket_arr[index_bucket][0]++;
		bucket_arr[index_bucket][cur_bucket_size] = arr[i];
	}
	//��ÿ��Ͱ��������
	for (int i = 0; i < bucket_num; ++i) {
		if (bucket_arr[i][0] == 1 || bucket_arr[i][0] == 2) continue;
		insertion_sort(bucket_arr[i] + 1, bucket_arr[i][0] - 1);
	}
	//��bucket_arr�е�Ԫ�ظ��Ƶ�arr��
	int index = 0;
	for (int i = 0; i < bucket_num; ++i) {
		for (int j = 1; j < bucket_arr[i][0]; ++j) {
			arr[index++] = bucket_arr[i][j];
		}
	}
	//�ͷ��ڴ�
	delete[] sizeof_each_bucket;
	for (int i = 0; i < bucket_num; ++i) {
		delete[] bucket_arr[i];
	}
	delete[] bucket_arr;
}

/*��������*/
int get_max_radix(int* arr, const int size) {
	/*��ȡ�����е������λ*/
	int max = arr[0];
	//���ҵ��������
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
	/*��ȡ����num��posλ����*/
	int temp = 1;
	for (int i = 0; i < pos - 1; ++i) {
		temp *= 10;
	}
	return (num / temp) % 10;
}
void radix_sort(int* arr, const int size) {
	if (arr == NULL || size < 2) return;

	//0-9��10��Ͱ
	int** help = new int* [10]();
	for (int i = 0; i < 10; ++i) {
		help[i] = new int[(std::size_t)size + 1]();
		help[i][0] = 1;
	}

	int max_radix = get_max_radix(arr, size);
	//��iλ������
	for (int radix = 1; radix <= max_radix; ++radix) {
		//�������е�Ԫ�أ�����λ���䵽����Ͱ��
		for (int i = 0; i < size; ++i) {
			int row = get_num(arr[i], radix);
			int col = help[row][0]++;
			help[row][col] = arr[i];
		}
		//�Ӹ���Ͱ���ռ�Ԫ��
		int index = 0;
		for (int row = 0; row < 10; ++row) {
			for (int col = 1; col < help[row][0]; ++col) {
				arr[index++] = help[row][col];
			}
			//��λ����һ����λ������
			help[row][0] = 1;
		}
	}
	
	for (int i = 0; i < 10; ++i) {
		delete[] help[i];
	}
	delete[] help;
}