#include <iostream>
#include <type_traits>
#include <variant>
#include <vector>

template <typename T>
concept Shape = requires(T s) {
  { s.area() } -> std::floating_point;
  { s.perimeter() } -> std::floating_point;
};

template <Shape T>
void draw(const T& s) {
  std::cout << "Drawing a shape with area: " << s.area() << " and perimeter: " << s.perimeter() << std::endl;
}

struct Circle {
  double radius;

  double area() const {
    return 3.14 * radius * radius;
  }

  double perimeter() const {
    return 2 * 3.14 * radius;
  }
};

struct Square {
  double side;

  double area() const {
    return side * side;
  }

  double perimeter() const {
    return 4 * side;
  }
};

using ShapeVariant = std::variant<Circle, Square>;

int main() {
  std::vector<ShapeVariant> shapes;

  shapes.push_back(Circle{1.0});
  shapes.push_back(Square{2.0});

  for (const auto& shape : shapes) {
    std::visit([](const auto& s) { draw(s); }, shape);
  }

  return 0;
}
