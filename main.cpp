#include <iostream>

using namespace std;

/*1. Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram (параллелограмм) и Circle (круг).
 * Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат), Rhombus (ромб).
 * Для всех классов создать конструкторы. Для класса Figure добавить чисто виртуальную функцию area() (площадь).
 * Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.*/
class Figure {
public:
    virtual double area() = 0;
};

class Parallelogram : public Figure {
private:
    double height;
    double length;
public:
    Parallelogram(double h, double a) : height(h), length(a) {}

    double area() override {
        return height * length;
    }
};

class Circle : public Figure {
private:
    double radius;
    const double PI = 3.14;
public:
    Circle(double r) : radius(r) {}

    double area() override {
        return 2 * PI * radius;
    }
};

class Rectangle : public Parallelogram {
public:
    Rectangle(double a, double b) : Parallelogram(a, b) {}
};

class Square : public Parallelogram {
public:
    Square(double a) : Parallelogram(a, a) {}
};

class Rhombus : public Parallelogram {
public:
    Rhombus(double h, double a) : Parallelogram(h, a) {}
};

/*2. Создать класс Car (автомобиль) с полями company (компания) и model (модель). Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус).
 * От этих классов наследует класс Minivan (минивэн). Создать конструкторы для каждого из классов, чтобы они выводили данные о классах.
 * Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы. Обратить внимание на проблему «алмаз смерти».*/
class Car {
private:
    string company;
    string model;
public:
    Car(string com, string mod) {
        cout << "Car: " << com << " " << mod << endl;
    }
};

class PassengerCar : virtual public Car {
public:
    PassengerCar(string com, string mod) : Car(com, mod) {
        cout << "Passenger car: " << com << " " << mod << endl;
    }
};

class Bus : virtual public Car {
public:
    Bus(string com, string mod) : Car(com, mod) {
        cout << "Bus: " << com << " " << mod << endl;
    }
};

class Minivan : public PassengerCar, public Bus {
public:
    Minivan(string com, string mod) : Car(com, mod), Bus(com, mod), PassengerCar(com, mod) {
        cout << "Minivan: " << com << " " << mod << endl;
    }
};

/*3. Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2).
 * Предусмотреть, чтобы знаменатель не был равен 0. Перегрузить:
математические бинарные операторы (+, -, , /) для выполнения действий с дробями
унарный оператор (-)
логические операторы сравнения двух дробей (==, !=, <, >, <=, >=).*/

class Fraction {
private:
    int divisible;
    int divider;
public:
//    Fraction() {}
    Fraction(int dvsbl, int dvdr = 0) : divisible(dvsbl), divider(dvdr) {
        while (dvdr == 0) {
            cout << "Enter divider:";
            cin >> dvdr;
            divider = dvdr;
        }
    }

    void printFraction() {
        if (divisible == 0)
            cout << 0 << endl;
        else if (abs(divisible) == abs(divider))
            if (divisible != divider)
                cout << -1 << endl;
            else
                cout << 1 << endl;
        else
            cout << divisible << "/" << divider << endl;
    }

    friend Fraction operator+(const Fraction &f1, const Fraction &f2);

    friend Fraction operator-(const Fraction &f1, const Fraction &f2);

    friend Fraction operator*(const Fraction &f1, const Fraction &f2);

    friend Fraction operator/(const Fraction &f1, const Fraction &f2);

    Fraction operator-() const {
        return Fraction(-divisible, divider);
    }

    friend bool operator==(const Fraction &f1, const Fraction &f2);

    friend bool operator!=(const Fraction &f1, const Fraction &f2);

    friend bool operator<(const Fraction &f1, const Fraction &f2);

    friend bool operator>(const Fraction &f1, const Fraction &f2);

    friend bool operator<=(const Fraction &f1, const Fraction &f2);

    friend bool operator>=(const Fraction &f1, const Fraction &f2);
};

Fraction operator+(const Fraction &f1, const Fraction &f2) {
    int newDivisible, newDivider;
    if (f1.divider == f2.divider) {
        newDivisible = f1.divisible + f2.divisible;
        newDivider = f1.divider;
    } else {
        newDivisible = f1.divisible * f2.divider + f2.divisible * f1.divider;
        newDivider = f1.divider * f2.divider;
    }
    return Fraction(newDivisible, newDivider);
}

Fraction operator-(const Fraction &f1, const Fraction &f2) {
    int newDivisible, newDivider;
    if (f1.divider == f2.divider) {
        newDivisible = f1.divisible - f2.divisible;
        newDivider = f1.divider;
    } else {
        newDivisible = f1.divisible * f2.divider - f2.divisible * f1.divider;
        newDivider = f1.divider * f2.divider;
    }
    return Fraction(newDivisible, newDivider);
}

Fraction operator*(const Fraction &f1, const Fraction &f2) {
    int newDivisible, newDivider;
    newDivisible = f1.divisible * f2.divisible;
    newDivider = f1.divider * f2.divider;
    return Fraction(newDivisible, newDivider);
}

Fraction operator/(const Fraction &f1, const Fraction &f2) {
    int newDivisible, newDivider;
    newDivisible = f1.divisible * f2.divider;
    newDivider = f1.divider * f2.divisible;
    return Fraction(newDivisible, newDivider);
}

bool operator==(const Fraction &f1, const Fraction &f2) {
    return (f1.divisible == f2.divisible && f1.divider == f2.divider);
}

bool operator!=(const Fraction &f1, const Fraction &f2) {
    return !(f1 == f2);
}

bool operator<(const Fraction &f1, const Fraction &f2) {
    return (f1.divisible * f2.divider < f2.divisible * f1.divider);
}

bool operator>(const Fraction &f1, const Fraction &f2) {
    return (f1.divisible * f2.divider > f2.divisible * f1.divider);
}

bool operator<=(const Fraction &f1, const Fraction &f2) {
    return !(f1 > f2);
}

bool operator>=(const Fraction &f1, const Fraction &f2) {
    return !(f1 < f2);
}

/*4. Создать класс Card, описывающий карту в игре БлэкДжек. У этого класса должно быть три поля: масть, значение карты и
 * положение карты (вверх лицом или рубашкой). Сделать поля масть и значение карты типом перечисления (enum).
 * Положение карты - тип bool. Также в этом классе должно быть два метода:
метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.*/

class Card {
public:
    enum Suits {
        DIAMONDS,
        HEARTS,
        CLUBS,
        SPADES
    };
    enum Ranks {
        ACE = 1,
        KING = 10,
        QUEEN = 10,
        JACK = 10,
        TEN = 10,
        NINE = 9,
        EIGHT = 8,
        SEVEN = 7,
        SIX = 6,
        FIVE = 5,
        FOUR = 4,
        THREE = 3,
        TWO = 2
    };

    Card(Ranks r, Suits s, bool f) : cardRank(r), cardSuite(s), face(f) {}

    void flip() {
        face = !face;
    }

    int getValue() {
        switch (cardRank) {
            case ACE:
                return 1;
            case KING | QUEEN | JACK | TEN:
                return 10;
            case NINE:
                return 9;
            case EIGHT:
                return 8;
            case SEVEN:
                return 7;
            case SIX:
                return 6;
            case FIVE:
                return 5;
            case FOUR:
                return 4;
            case THREE:
                return 3;
            case TWO:
                return 2;
            default:
                cout << "Incorrect rank";
                return 0;
        }
    }

private:
    Ranks cardRank;
    Suits cardSuite;
    bool face;
};

int main() {
    cout << "First task:" << endl;
    Parallelogram p(3, 4);
    Circle c(2);
    Rectangle r(3, 5);
    Square s(6);
    Rhombus rh(2, 5);
    cout << "Parallelogram area = " << p.area() << endl
         << "Circle area = " << c.area() << endl
         << "Rectangle area = " << r.area() << endl
         << "Square area = " << s.area() << endl
         << "Rhombus area = " << rh.area() << endl;

    cout << endl << "Second task:" << endl;
    PassengerCar pc("BMW", "X5");
    Bus b("IVECO", "FBI 83 MR");
    Minivan m("Honda", "Odyssey");

    cout << endl << "Third task:" << endl;
    Fraction f1(1, 5);
    Fraction f2(2, 5);
    Fraction fResult = f1 / f2;
    fResult.printFraction();
    fResult = -fResult;
    fResult.printFraction();
    cout << "f1 = f2:  " << ((f1 == f2) ? "true" : "false") << endl;
    cout << "f1 != f2: " << ((f1 != f2) ? "true" : "false") << endl;
    cout << "f1 < f2:  " << ((f1 < f2) ? "true" : "false") << endl;
    cout << "f1 > f2:  " << ((f1 > f2) ? "true" : "false") << endl;
    cout << "f1 <= f2: " << ((f1 <= f2) ? "true" : "false") << endl;
    cout << "f1 >= f2: " << ((f1 >= f2) ? "true" : "false") << endl;

    cout << endl << "Fourth task:" << endl;
    Card card(Card::SIX, Card::CLUBS, true);
    cout << card.getValue() << endl;

    return 0;
}
