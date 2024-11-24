#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include <limits>

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

double calculateIntersectionAreaMonteCarlo(const Circle &c1, const Circle &c2, const Circle &c3,
                                           int numPoints = 200000) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());

    // Пределы для генерации случайных чисел (прямоугольник).
    double minX = std::min(c1.center.x - c1.radius, std::min(c2.center.x - c2.radius, c3.center.x - c3.radius));
    double maxX = std::max(c1.center.x + c1.radius, std::max(c2.center.x + c2.radius, c3.center.x + c3.radius));
    double minY = std::min(c1.center.y - c1.radius, std::min(c2.center.y - c2.radius, c3.center.y - c3.radius));
    double maxY = std::max(c1.center.y + c1.radius, std::max(c2.center.y + c2.radius, c3.center.y + c3.radius));

    std::uniform_real_distribution<> randXGen(minX, maxX);
    std::uniform_real_distribution<> randYGen(minY, maxY);

    double sRect = (maxX - minX) * (maxY - minY);
    int insideAreaCnt = 0;

    for (int i = 0; i < numPoints; ++i) {
        Point randPoint = Point(randXGen(generator), randYGen(generator));
        if (c1.isInside(randPoint) && c2.isInside(randPoint) && c3.isInside(randPoint)) {
            ++insideAreaCnt;
        }
    }

    return (double)insideAreaCnt / numPoints * sRect;
}

int main() {
    double x;
    double y;
    double r;
    std::cin >> x >> y >> r;
    Circle c1(x, y, r);
    std::cin >> x >> y >> r;
    Circle c2(x, y, r);
    std::cin >> x >> y >> r;
    Circle c3(x, y, r);

    std::cout << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10);
    std::cout << calculateIntersectionAreaMonteCarlo(c1, c2, c3);
    return 0;
}