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
	Global_Info(int start, int end, static int& alphabet_Name, static int& alphabet_num, static int& id) {
		if (alphabet_Name > end) {
			alphabet_Name = start;
			alphabet_num++;
		}
		letter = alphabet_Name++;
		this->id = id++;
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
	Point() :Global_Info(65, 90, alphabet_Point, alphabet_num, general_id) {}

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
int Point::general_id = 0;

//клас вектора
class Vector : public Global_Info {
private:
	float x, y, z;
	static int general_id, alphabet_Vector, alphabet_num;
public:
	//стартове заповнення
	Vector() :Global_Info(97, 122, alphabet_Vector, alphabet_num, general_id) {}
	//перегрузка конструктора
	Vector(Point& other_1, Point& other_2) :Global_Info(97, 122, alphabet_Vector, alphabet_num, general_id) {
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
		Vector temp;
		temp.x = this->x + other.x;
		temp.y = this->x + other.y;
		temp.z = this->z + other.z;
		alphabet_Vector--;
		return temp;
	}
	//метод віднімання двох векторів
	Vector operator -(const Vector& other) {
		Vector temp;
		temp.x = this->x - other.x;
		temp.y = this->x - other.y;
		temp.z = this->z - other.z;
		alphabet_Vector--;
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
int Vector::general_id = 0;

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

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << endl << setw(5) << "" << "Трохвимірний простір" << endl;
	int j, index, k = 1, i = 0, num = 0, num_new = 0, size_point = 0, size_vector = 0;
	bool check_menu, chec_finaly;

	Print_Info print;
	vector<Vector> object;
	vector<Point> point;
	cout << endl << setw(5) << "" << "Введіть скільки векторів ви хочете побудувати: ";
	cin >> num_new;
	do {
		num += num_new;
		while (size_vector < num) {
			for (j = 0; j < 2; j++) {
				//занесення об'єкта в масив об'єктів
				point.emplace_back(print.Point_Data());
				cout << endl << setw(7) << "" << "Координати точки " << point[size_point].Get_Name() << ": ";
				print.Point_Info_Coordinates(point[size_point++]);
				cout << endl << endl;
			}
			//занесення об'єкта в масив об'єктів
			Vector vect(point[size_point - 2], point[size_point - 1]);
			object.emplace_back(vect);
			size_vector++;
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
				chec_finaly = false;
				cout << endl << setw(5) << "" << "Введіть скільки іще векторів ви хочете створити: ";
				cin >> num;
				break;
			}
			case 2: check_menu = chec_finaly = true; break;
			default: check_menu = false;  cout << endl << setw(12) << "-> " << "Такого варіанту немає в списку!!! Спробуйте іще раз" << endl;
			}
		} while (!check_menu);

	} while (!chec_finaly);

	//виведення інформації (таблиця)
	print.Table();
	for (j = 0; j < num; j++) {
		print.Print(object[j], point[i], point[k]);
		i += 2; k += 2;
	}
	return 0;
}