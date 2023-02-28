#include <stdio.h>
#include <iostream>

class Triangle
{
protected:
	int a, b, c;
public:
	Triangle()
	{
		printf("Triangle()\n");
		a = 1;
		b = 1;
		c = 1;
	}
	Triangle(int a, int b, int c)
	{
		printf("Triangle(%d, %d, %d)\n", a, b, c);
		this->a = a;
		this->b = b;
		this->c = c;
	}
	Triangle(const Triangle& triangle)
	{
		printf("Triangle(сonst Triangle& triangle)\n");
		this->a = triangle.a;
		this->b = triangle.b;
		this->c = triangle.c;
	}
	~Triangle()
	{
		printf("~Triangle a=%d b=%d c=%d\n", a, b, c);
	}

	void Increase(int value)
	{
		printf("Вызван метод Increase(%d) a=%d, b=%d, c=%d\n", value, a, b, c);
		a += value;
		b += value;
		c += value;
	}

	void Perimeter();
};

void Triangle::Perimeter()
{
	printf("Вызван метод Perimeter(), a=%d, b=%d, c=%d\n", a, b, c);
	printf("Периметр равен %d\n", a + b + c);
}


class ColoredTriangle : public Triangle
{
private:
	int color;
public:
	ColoredTriangle() : Triangle()
	{
		printf("ColoredTriangle()\n");
		color = 1;
	}
	ColoredTriangle(int a, int b, int c, int color) : Triangle(a, b, c)
	{
		printf("ColoredTriangle(%d, %d, %d, %d)\n", a, b, c, color);
		this->color = color;
	}
	ColoredTriangle(const ColoredTriangle& coloredTriangle)
	{
		printf("ColoredTriangle(const ColoredTriangle& coloredTriangle)\n");
		this->a = coloredTriangle.a;
		this->b = coloredTriangle.b;
		this->c = coloredTriangle.c;
		this->color = coloredTriangle.color;
	}
	~ColoredTriangle()
	{
		printf("~ColoredTriangle a=%d b=%d c=%d color=%d\n", a, b, c, color);
	}

	void ChangeColor(int newColor)
	{
		printf("Вызван метод ChangeColor(%d) a=%d, b=%d, c=%d, color=%d\n", newColor, a, b, c, color);
		color = newColor;
	}
};


class Figure
{
protected:
	Triangle* tr1;
	Triangle* tr2;
public:
	Figure()
	{
		printf("Figure()\n");
		tr1 = new Triangle;
		tr2 = new Triangle;
	}
	Figure(int a1, int b1, int c1, int a2, int b2, int c2)
	{
		printf("Figure(%d, %d, %d, %d, %d, %d)\n", a1, b1, c1, a2, b2, c2);
		tr1 = new Triangle(a1, b1, c1);
		tr2 = new Triangle(a2, b2, c2);
	}
	Figure(const Figure& Figure)
	{
		printf("Figure(const Figure& Figure)\n");
		tr1 = new Triangle(*(Figure.tr1));
		tr2 = new Triangle(*(Figure.tr2));
	}
	~Figure()
	{
		delete tr1;
		delete tr2;
		printf("~Figure\n");
	}
};



int main()
{
	setlocale(LC_ALL, "Russian");
	printf("Статически созданные объекты:\n\n");
	{
		Triangle tr1;
		Triangle tr2(10, 15, 20);
		Triangle tr3(tr2);
		printf("\n");


		ColoredTriangle coltr1;
		ColoredTriangle coltr2(10, 15, 20, 100);
		ColoredTriangle coltr3(coltr2);
		printf("\n");
		printf("\nУдаление статически созданных объектов:\n");
	}


	printf("\nПрименение композиции (объекты создаются статистически):\n\n");
	{
		Figure f1;
		Figure f2(10, 15, 20, 25, 30, 40);
		Figure f3(f2);
		printf("\nУдаление статически созданных объектов:\n");
	}

	printf("\nДинамически созданные объекты:\n\n");

	Triangle* tr1 = new Triangle();
	Triangle* tr2 = new Triangle(10, 15, 20);
	Triangle* tr3 = new Triangle(*tr2);
	printf("\n");

	ColoredTriangle* coltr1 = new ColoredTriangle();
	ColoredTriangle* coltr2 = new ColoredTriangle(10, 15, 20, 100);
	ColoredTriangle* coltr3 = new ColoredTriangle(*coltr2);


	printf("\nВызов методов:\n\n");
	tr2->Perimeter();
	tr2->Increase(10);
	tr2->Perimeter();


	coltr2->ChangeColor(150);
	coltr2->Increase(10);

	printf("\nУдаление динамически созданных объектов:\n\n");
	delete tr1;
	delete tr2;
	delete tr3;


	delete coltr1;
	delete coltr2;
	delete coltr3;

	printf("\nПрименение композиции (объекты создаются динамически):\n\n");
	Figure* f1 = new Figure();
	Figure* f2 = new Figure(10, 15, 20, 25, 30, 40);
	Figure* f3 = new Figure(*f2);
	printf("\nУдаление динамически созданных объектов:\n\n");
	delete f1;
	delete f2;
	delete f3;
	return 0;
}