#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include <fstream>
#include <numbers>

struct Point {
    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {}
};

struct Circle {
    Point center;
    double radius;

    Circle(Point center, double radius) : center(center), radius(radius) {}
    Circle(double x, double y, double radius) : center(x, y), radius(radius) {}

    bool isInside(Point p) const {
        return (std::pow(p.x - center.x, 2) + std::pow(p.y - center.y, 2) <= radius * radius);
    }
};

// Прямоугольник, представленный его границами.
struct RectangleRepresentation {
    double minX;
    double maxX;
    double minY;
    double maxY;
    double area;

    RectangleRepresentation(double minX, double maxX, double minY, double maxY) : minX(minX), maxX(maxX),
                                                                                  minY(minY), maxY(maxY) {
        area = (maxX - minX) * (maxY - minY);
    }
};

double calculateIntersectionAreaMonteCarlo(const Circle &c1, const Circle &c2, const Circle &c3,
                                           RectangleRepresentation rect, int numPoints = 200000) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());

    std::uniform_real_distribution<> randXGen(rect.minX, rect.maxX);
    std::uniform_real_distribution<> randYGen(rect.minY, rect.maxY);

    int insideAreaCnt = 0;

    for (int i = 0; i < numPoints; ++i) {
        Point randPoint(randXGen(generator), randYGen(generator));
        if (c1.isInside(randPoint) && c2.isInside(randPoint) && c3.isInside(randPoint)) {
            ++insideAreaCnt;
        }
    }

    return (double)insideAreaCnt / numPoints * rect.area;
}

int main() {
    // Описание окружностей.
    Circle c1(1, 1, 1);
    Circle c2(1.5, 2, std::sqrt(5) / 2);
    Circle c3(2, 1.5, std::sqrt(5) / 2);

    // Точная площадь пересечения.
    double exactArea = 0.25 * std::numbers::pi + 1.25 * std::asin(0.8) - 1;

    // Описание прямоугольников.
    // Границы примерные, взяты с небольшим запасом, поскольку точных координат вершин прямоугольников не дано.
    RectangleRepresentation bigRect(0, 3.2, 0, 3.2);
    RectangleRepresentation smallRect(0.8, 2.1, 0.8, 2.1);

    std::ofstream file1;
    std::ofstream file2;
    file1.open("../../data/big_rectangle_results_type_1.txt");
    file2.open("../../data/big_rectangle_results_type_2.txt");
    // Для большого прямоугольника.
    for (int numPoints = 100; numPoints < 100001; numPoints += 500) {
        double calculatedArea = calculateIntersectionAreaMonteCarlo(c1, c2, c3, bigRect, numPoints);
        file1 << numPoints << ' ' << calculatedArea << '\n';
        file2 << numPoints << ' ' << std::abs(exactArea - calculatedArea) << '\n';
    }
    file1.close();
    file2.close();

    file1.open("../../data/small_rectangle_results_type_1.txt");
    file2.open("../../data/small_rectangle_results_type_2.txt");
    // Для маленького прямоугольника.
    for (int numPoints = 100; numPoints < 100001; numPoints += 500) {
        double calculatedArea = calculateIntersectionAreaMonteCarlo(c1, c2, c3, smallRect, numPoints);
        file1 << numPoints << ' ' << calculatedArea << '\n';
        file2 << numPoints << ' ' << std::abs(exactArea - calculatedArea) << '\n';
    }
    file1.close();
    file2.close();

    std::cout << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10);
    std::cout << exactArea;
    return 0;
}