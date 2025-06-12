#include <iostream>
#include <algorithm> // sort 함수 사용을 위해 필요
using namespace std;

template <typename T>
class SimpleVector
{
private:
	T* data;               // 데이터를 저장하는 동적 배열 포인터
	int currentSize;       // 현재 저장된 요소의 개수
	int currentCapacity;   // 현재 배열의 용량

	// 배열 크기를 재할당하는 내부 함수
	void resize(int newCapacity)
	{
		if (newCapacity <= currentCapacity)
			return; // 현재 용량보다 작거나 같으면 아무 작업도 하지 않음

		// 새로운 배열 생성
		T* newData = new T[newCapacity];

		// 기존 데이터 복사
		for (int i = 0; i < currentSize; ++i)
		{
			newData[i] = data[i];
		}

		// 기존 배열 해제
		delete[] data;

		// 새 배열로 교체
		data = newData;
		currentCapacity = newCapacity;
	}

public:
	// 기본 생성자 (크기 10)
	SimpleVector()
	{
		currentCapacity = 10;
		currentSize = 0;
		data = new T[currentCapacity];
	}

	// capacity 지정 생성자
	SimpleVector(int capacity)
	{
		currentCapacity = capacity;
		currentSize = 0;
		data = new T[currentCapacity];
	}

	// 복사 생성자
	SimpleVector(const SimpleVector& other)
	{
		currentSize = other.currentSize;
		currentCapacity = other.currentCapacity;
		data = new T[currentCapacity];
		for (int i = 0; i < currentSize; ++i)
		{
			data[i] = other.data[i];
		}
	}

	// 소멸자
	~SimpleVector()
	{
		delete[] data;
	}

	// 원소 추가 (뒤에 추가)
	void push_back(const T& value)
	{
		if (currentSize >= currentCapacity)
		{
			// 용량이 부족할 경우 5칸 확장
			resize(currentCapacity + 5);
		}
		data[currentSize++] = value;
	}

	// 마지막 원소 제거
	void pop_back()
	{
		if (currentSize > 0)
			--currentSize;
	}

	// 현재 원소 개수 반환
	int size() const
	{
		return currentSize;
	}

	// 현재 용량 반환
	int capacity() const
	{
		return currentCapacity;
	}

	// 내부 데이터를 오름차순 정렬
	void sortData()
	{
		sort(data, data + currentSize); // STL sort 사용
	}
};

int main()
{
	SimpleVector<int> vec;

	vec.push_back(5);
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(9);
	vec.push_back(2);

	cout << "Size: " << vec.size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;

	vec.sortData();  // 정렬 수행

	// 확인 출력
	cout << "Sorted: ";
	for (int i = 0; i < vec.size(); ++i)
	{
		// 직접 접근은 안되므로 일시적 허용
		// data를 public으로 만들지 않는 설계가 더 좋음 → 여기에선 테스트 목적
		//cout << vec[i] << " "; ← 불가능
	}
	cout << endl;

	return 0;
}
