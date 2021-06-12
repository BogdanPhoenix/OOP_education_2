#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class Point;
class Vector;
class Global_Info;
class Print_Info;

//батьківський клас
class Global_Info {
protected:
	int id;
	string name;
	char letter;
public:
	//заповнення імені та id
	Global_Info(int end, static int& alphabet_Name, static int& alphabet_num, static int& id) {
		if (alphabet_Name > end) {
			alphabet_Name = end - 26;
			alphabet_num++;
		}
		letter = alphabet_Name++;
		this->id = ++id;
		this->name = letter + to_string(alphabet_num);
	}
	//виведення імені
	string Get_Name() { return this->name; }
	//виведення id поточного об'єкту
	int Get_Id() { return this->id; }
};

//клас точки
class Point : public Global_Info {
private:
	static int general_id, alphabet_Point, alphabet_num;
	float x, y, z;
public:
	//стартове заповнення
	Point() :Global_Info(90, alphabet_Point, alphabet_num, general_id) {}

	//заповнення координат точки за межами класу
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	void SetZ(float z) { this->z = z; }

	//виведення координат точки
	float GetX() { return this->x; }
	float GetY() { return this->y; }
	float GetZ() { return this->z; }
	static int Get_General_Id() { return general_id; }
};
//стартове значення імен точок
int Point::alphabet_Point = 65;
int Point::alphabet_num = 0;
int Point::general_id = -1;

//клас вектора
class Vector : public Global_Info {
private:
	float x, y, z;
	static int general_id, alphabet_Vector, alphabet_num;
public:
	//стартове заповнення
	Vector() :Global_Info(122, alphabet_Vector, alphabet_num, general_id) {}
	//перегрузка конструктора
	Vector(Point& other_1, Point& other_2) :Global_Info(122, alphabet_Vector, alphabet_num, general_id) {
		//заповнення координат вектора
		this->x = ceil((other_2.GetX() - other_1.GetX()) * 1000) / 1000;
		this->y = ceil((other_2.GetY() - other_1.GetY()) * 1000) / 1000;
		this->z = ceil((other_2.GetZ() - other_1.GetZ()) * 1000) / 1000;
	}
	//виведення косинусів
	float Get_Angle_A() { return this->x / Get_Length(); }
	float Get_Angle_B() { return this->y / Get_Length(); }
	float Get_Angle_C() { return this->z / Get_Length(); }
	//виведення координат вектора
	float GetX() { return this->x; }
	float GetY() { return this->y; }
	float GetZ() { return this->z; }
	//скалярний добутку вектора
	float Get_Scalar(const Vector& other) { return this->x * other.x + this->y * other.y + this->z * other.z; }
	//виведення довжини
	float Get_Length() { return ceil(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) * 1000) / 1000.; }
	//виведення загальної кількості елементів
	static int Get_General_Id() { return general_id; }
	//метод додавання двох векторів
	Vector operator +(const Vector& other) {
		alphabet_Vector--;
		general_id--;
		Vector temp;
		temp.x = this->x + other.x;
		temp.y = this->y + other.y;
		temp.z = this->z + other.z;
		return temp;
	}
	//метод віднімання двох векторів
	Vector operator -(const Vector& other) {
		alphabet_Vector--;
		general_id--;
		Vector temp;
		temp.x = this->x - other.x;
		temp.y = this->x - other.y;
		temp.z = this->z - other.z;
		return temp;
	}
	//метод присвоєння значень
	Vector& operator = (const Vector& other) {
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->name = other.name;
		return *this;
	}
};
//стартове значення імен точок
int Vector::alphabet_Vector = 97;
int Vector::alphabet_num = 0;
int Vector::general_id = -1;

//клас створення таблиці
class Print_Info {
private:
	const int Size_name = 20, Size_point = 20, Size_coordinates = 20, limit = Size_name + Size_point + Size_coordinates + 9;
	int i;

	//визначає позицію тексту по центру
	void Lenght(string text, const int& size, int& size_text_st, int& size_text_e) {
		size_text_st = (size + 2 - strlen(text.c_str())) / 2; //відступ перед 
		size_text_e = size + 2 - size_text_st - strlen(text.c_str()); // відступ після 
	}
public:
	//виведення інформації про точку
	void Point_Info_Coordinates(Point& other) { cout << "{" << other.GetX() << "; " << other.GetY() << "; " << other.GetZ() << "}"; }
	//виведення інформації про точку
	void Vector_Info_Coordinates(Vector& other) { cout << "{" << other.GetX() << "; " << other.GetY() << "; " << other.GetZ() << "}"; }
	//заповнення координат в межах класу
	Point Point_Data() {
		Point temp;
		float x, y, z;
		cout << endl << setw(5) << "" << "Введіть координату точки " << temp.Get_Name() << " по осі x: ";
		cin >> x;
		cout << endl << setw(5) << "" << "Введіть координату точки " << temp.Get_Name() << " по осі y: ";
		cin >> y;
		cout << endl << setw(5) << "" << "Введіть координату точки " << temp.Get_Name() << " по осі z: ";
		cin >> z;

		//занесення даних в об'єкт
		temp.SetX(x);
		temp.SetY(y);
		temp.SetZ(z);

		return temp;
	}
	//шапка таблиці
	void Table() {
		int name_st, name_e, point_st, point_e;
		string name, point, coordinates;
		name = "Назва вектора";
		point = "Назва точок вектора";
		coordinates = "Координати вектора";
		Lenght(name, Size_name, name_st, name_e);
		Lenght(point, Size_point, point_st, point_e);
		cout << endl << setw(name_st + 6) << "" << name << setw(name_e + point_st + 1) << "" << point << setw(6) << "" << coordinates << endl;
		cout << setw(5) << "";
		for (i = 0; i < limit; i++)cout << "-";
	}

	//виведення вмісту
	void Print(Vector& vector, Point& point_1, Point& point_2) {
		int name_st, name_e, point_st, point_e;
		string name, point;
		name = vector.Get_Name();
		point = point_1.Get_Name() + '_' + point_2.Get_Name();
		Lenght(name, Size_name, name_st, name_e);
		Lenght(point, Size_point, point_st, point_e);
		cout << endl << setw(6) << "|" << setw(name_st) << "" << name << setw(name_e + 1) << "|" << setw(point_st) << "" << point << setw(point_e + 1) << "|" << setw(5) << "";
		Vector_Info_Coordinates(vector);
		cout << setw(6) << "|" << endl;
		cout << setw(5) << "";
		for (i = 0; i < limit; i++)cout << "-";
	}
};
//виведення таблиці з даними про вектор
void Print_Object(vector<Vector> object, vector<Point> point) {
	int j, i = 0, k = 1;
	Print_Info print;
	print.Table();
	for (j = 0; j <= Vector::Get_General_Id(); j++) {
		print.Print(object[j], point[i], point[k]);
		i += 2; k += 2;
	}
}
//визначення першої точки вектора після додавання, або віднімання (чи потрібно виправити)
void First_Point(Point& other, vector<Point> &point, int j){
	other.SetX(point[j].GetX());
	other.SetY(point[j].GetY());
	other.SetZ(point[j].GetZ());
}
//додавання та віднімання вектора
void Addition_And_Subtraction(vector<Vector> &object, vector<Point> &point, const char* action) {
	int vector_a, vector_b, check;
	bool check_menu;
	Vector temp;
	Point other[2];
	Print_Info print;
	string text;
	cout << endl << setw(5) << "" << "Введіть номер першого вектора: ";
	cin >> vector_a;
	cout << endl << setw(5) << "" << "Введіть номер другого вектора: ";
	cin >> vector_b;
	if (!strcmp(action, "+")) {
		temp = object[vector_a - 1] + object[vector_b - 1];
		text = "додавання";
	}
	if (!strcmp(action, "-")) {
		temp = object[vector_a - 1] - object[vector_b - 1];
		text = "віднімання";
	}
	cout << endl << setw(7) << "" << "Результат " << text << " вектора " << object[vector_a - 1].Get_Name() << " та вектора " << object[vector_b - 1].Get_Name() << " становить: ";
	print.Vector_Info_Coordinates(temp);
	do {
		cout << endl << setw(5) << "" << "Чи хочете ви додати його в список до інших векторів?" << endl;
		cout << setw(10) << "-> " << "1. Так." << endl;
		cout << setw(10) << "-> " << "2. Ні." << endl;
		cout << setw(12) << "-> " << "Ваш варіант: ";
		cin >> check;
		switch (check) {
		case 1: {
			check_menu = true;
			object.emplace_back(temp);
			//визначення координат першої точки нового вектора
			vector_a - 1 == 0 ? First_Point(other[0], point, 0) : First_Point(other[0], point, pow(2, vector_a - 1));
			//визначення координат другої точки нового вектора
			other[1].SetX(temp.GetX() + other[0].GetX());
			other[1].SetY(temp.GetY() + other[0].GetY());
			other[1].SetZ(temp.GetZ() + other[0].GetZ());
			//занесення даних про точку в масив об'єктів
			for (int j = 0; j < 2; j++)
				point.emplace_back(other[j]);
			//виведення інформації
			Print_Object(object, point);
			break;
		}
		// вихід з циклу
		case 2: check_menu = true; break;
		default: check_menu = false;  cout << endl << setw(12) << "-> " << "Такого варіанту немає в списку!!! Спробуйте іще раз" << endl;
		}
	} while (!check_menu);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << endl << setw(5) << "" << "Трохвимірний простір" << endl;
	int j, index, k = 1, i = 0, num = 0, num_new = 0;
	bool check_menu, check_finaly;

	Print_Info print;
	vector<Vector> object;
	vector<Point> point;
	cout << endl << setw(5) << "" << "Введіть скільки векторів ви хочете побудувати: ";
	cin >> num_new;
	do {
		num += num_new;
		while (Vector::Get_General_Id() < num - 1) {
			for (j = 0; j < 2; j++) {
				//занесення об'єкта в масив об'єктів
				point.emplace_back(print.Point_Data());
				cout << endl << setw(7) << "" << "Координати точки " << point[Point::Get_General_Id()].Get_Name() << ": ";
				print.Point_Info_Coordinates(point[Point::Get_General_Id()]);
				cout << endl << endl;
			}
			//занесення об'єкта в масив об'єктів
			Vector vect(point[Point::Get_General_Id() - 1], point[Point::Get_General_Id()]);
			object.emplace_back(vect);
			if (num > 1) {
				for (j = 0; j < 100; j++)cout << "-";
				cout << endl << endl;
			}
		}

		do {
			cout << endl << setw(5) << "Ви хочете додати іще векторів." << endl;
			cout << setw(10) << "-> " << "1. Так." << endl;
			cout << setw(10) << "-> " << "2. Ні." << endl;
			cout << setw(12) << "-> " << "Ваш варіант: ";
			cin >> index;
			switch (index) {
			case 1: {
				check_menu = true;
				check_finaly = false;
				cout << endl << setw(5) << "" << "Введіть скільки іще векторів ви хочете створити: ";
				cin >> num;
				break;
			}
			case 2: check_menu = check_finaly = true; break;
			default: check_menu = false;  cout << endl << setw(12) << "-> " << "Такого варіанту немає в списку!!! Спробуйте іще раз" << endl;
			}
		} while (!check_menu);

	} while (!check_finaly);

	//виведення інформації (таблиця)
	Print_Object(object, point);

	//переробити
	check_finaly = false;
	do {
		cout << endl << setw(5) << "" << "Меню" << endl;
		cout << setw(5) << "" << "0. Вихід." << endl;
		cout << setw(5) << "" << "1. Додавання двох любих векторів." << endl;
		cout << setw(5) << "" << "2. Віднімання двох любих векторів." << endl;
		cout << setw(5) << "" << "3. Скалярний добуток будь-яких векторів." << endl;
		cout << setw(5) << "" << "4. Напрямні косинуси вектора." << endl;
		cout << setw(5) << "" << "Ваш варіант: ";
		cin >> index;
		switch (index) {
		case 0: check_finaly = true; break;
		//додавання
		case 1: { Addition_And_Subtraction(object, point, "+"); break;	}
		//віднімання
		case 2: { Addition_And_Subtraction(object, point, "-"); break;	}
		case 3: {
			int id_vector_1, id_vector_2;
			cout << endl << setw(5) << "" << "Введіть номер першого вектора: ";
			cin >> id_vector_1;
			cout << endl << setw(5) << "" << "Введіть номер першого вектора: ";
			cin >> id_vector_2;
			cout << endl << setw(7) << "" << "Скалярний добуток вектора " << object[id_vector_1 - 1].Get_Name() << " та вектора " << object[id_vector_2 - 1].Get_Name() << ", становить: " << object[id_vector_1 - 1].Get_Scalar(object[id_vector_2 - 1]) << endl;
			break;
		}
		case 4: {
			int id_vector;
			cout << endl << setw(5) << "" << "Введіть номер вектора: ";
			cin >> id_vector;
			cout << endl << setw(7) << "" << "Координати вектора " << object[id_vector - 1].Get_Name() << " ";
			print.Vector_Info_Coordinates(object[id_vector - 1]);
			cout << ", довжина вектора " << object[id_vector - 1].Get_Length() << endl << endl;
			cout << setw(7) << "" << "Напрямний вектор по осі x " << object[id_vector - 1].Get_Angle_A() << endl;
			cout << setw(7) << "" << "Напрямний вектор по осі y " << object[id_vector - 1].Get_Angle_B() << endl;
			cout << setw(7) << "" << "Напрямний вектор по осі z " << object[id_vector - 1].Get_Angle_C() << endl;
			break;
		}
		default: cout << endl << setw(12) << "-> " << "Такого варіанту немає в списку!!! Спробуйте іще раз" << endl;
		}
	} while (!check_finaly);
	
	return 0;
}
