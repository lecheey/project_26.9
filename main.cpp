#include <iostream>
#include <vector>
#include <iterator>
#include <thread>
#include <algorithm>

class MyArr{
public:
	std::vector<int> arr{};

	void fillArr(std::vector<int> &_arr, int _l, int _r){
		for(int _i = _l; _i < _r; _i++){
			arr.push_back(_arr[_i]);
		}
	}
};

int main(){
	// вводные данные
	while(true){
	int n, m;
	std::cout << "количество элементов: ";
	std::cin >> n;
	
	std::cout << "количество потоков: ";
	std::cin >> m;

	// int n = 20; // размер массива
	//int m = 4; // кол-во частей
	std::vector<int> arr{}; // массив
	
	// генерация значений массива
	srand(time(0));
	for(int i = 0; i < n; i++){
		arr.push_back(1 + rand() % 100);
	}
/*
	// вывод оригинального массива
	for(int j = 0; j < n; j++){
		std::cout << arr[j] << " ";
	}
	std::cout << std::endl;
*/
    std::vector<std::thread> threads{}; // массив потоков

	// разделение массива
    std::vector<int> final_arr{}; // сюда сохраняются результаты вычислений
	int l = 0; // начало части массива
	int r = 0; // конец части

    for (int i = 0; i < m; i++){
		if((l+(n/m)) < n){
			r = l+(n/m);
		}
		else{
			r = n;
		}
		
		MyArr arr_part;	// объект - элемент массива
		arr_part.fillArr(arr, l, r); // наполнение данныеми

		// вызов потока для суммирования значений части массива
        threads.push_back(std::thread([arr_part, &final_arr]() { std::cout << "поток" << std::endl; int x = 0;
				for(int j = 0; j < arr_part.arr.size(); j++){
								x += arr_part.arr[j];}
								final_arr.push_back(x);}
				));
		l = r; // переход к следующей части массива
	}

    std::for_each(threads.begin(), threads.end(), [] (std::thread &t)
         { t.join(); });

	// суммирование полученных результатов
	int result = 0;
	for(int k = 0; k < m; k++){
//		std::cout << final_arr[k] << " ";
		result += final_arr[k];
	}

	std::cout << std::endl;
	std::cout << result << std::endl;

	char choice;
	std::cout << "continue? y / n" << std::endl;
	std::cin >> choice;
	if(choice == 'n'){ break; }

	}
	return 0;
}
