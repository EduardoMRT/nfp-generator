#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/minkowski_sum_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel> Polygon_with_holes_2;

std::vector<sf::Vertex> polygonToVertices(const Polygon_2& poly, sf::Color color, float scale, sf::Vector2f offset) {
    std::vector<sf::Vertex> vertices;
    for (const auto& pt : poly) {
        float x = static_cast<float>(CGAL::to_double(pt.x())) * scale + offset.x;
        float y = static_cast<float>(CGAL::to_double(pt.y())) * scale + offset.y;
        vertices.emplace_back(sf::Vector2f(x, y), color);
    }
    if (!vertices.empty()) {
        vertices.push_back(vertices.front());
    }
    return vertices;
}

void getPolygonInput(Polygon_2& polygon) {
    int numVertices;
    std::cout << "Informe o numero de vertices do poligono: ";
    std::cin >> numVertices;

    std::cout << "Informe os vertices do poligono (x y):\n";
    for (int i = 0; i < numVertices; ++i) {
        float x, y;
        std::cin >> x >> y;
        polygon.push_back(Point_2(x, y));
    }
}

int main() {
    Polygon_2 moving; // polígono fixo
    std::cout << "Digite os vertices do poligono fixo\n";
    getPolygonInput(moving);

    Polygon_2 fixed; // polígono móvel
    std::cout << "Digite os vertices do poligono movel\n";
    getPolygonInput(fixed);

    // Escolher primeiro vértice de B como ponto de referência
    Point_2 refB = moving[0];

    // Criar polígono refletido relativo ao ponto de referência
    Polygon_2 reflected;
    for (const auto& p : moving)
        reflected.push_back(Point_2(-(p.x() - refB.x()), -(p.y() - refB.y()))); // centralizar em refB

    if (fixed.orientation() != CGAL::COUNTERCLOCKWISE)
        fixed.reverse_orientation();
    if (reflected.orientation() != CGAL::COUNTERCLOCKWISE)
        reflected.reverse_orientation();

    Polygon_with_holes_2 nfp = CGAL::minkowski_sum_2(fixed, reflected);

    // Setup SFML
    const unsigned window_width = 1000;
    const unsigned window_height = 800;
    sf::RenderWindow window(sf::VideoMode({window_width, window_height}), "NFP");

    // Bounding box do NFP
    Kernel::FT min_x = nfp.outer_boundary()[0].x(), max_x = min_x;
    Kernel::FT min_y = nfp.outer_boundary()[0].y(), max_y = min_y;
    for (const auto& p : nfp.outer_boundary()) {
        if (p.x() < min_x) min_x = p.x();
        if (p.x() > max_x) max_x = p.x();
        if (p.y() < min_y) min_y = p.y();
        if (p.y() > max_y) max_y = p.y();
    }

    float poly_width = static_cast<float>(CGAL::to_double(max_x - min_x));
    float poly_height = static_cast<float>(CGAL::to_double(max_y - min_y));

    float margin = 40.0f;
    float scale_x = (window_width - margin * 2) / poly_width;
    float scale_y = (window_height - margin * 2) / poly_height;
    float scale = std::min(scale_x, scale_y);

    float cx = static_cast<float>(CGAL::to_double((min_x + max_x) / 2));
    float cy = static_cast<float>(CGAL::to_double((min_y + max_y) / 2));
    sf::Vector2f offset(window_width / 2.f - cx * scale, window_height / 2.f - cy * scale);

    // Fonte
    sf::Font font;
    if (!font.openFromFile(R"(C:\Windows\Fonts\arial.ttf)")) return -1;
    sf::Text text(font, "", 12);
    text.setFillColor(sf::Color::White);

    auto nfpVerts = polygonToVertices(nfp.outer_boundary(), sf::Color::White, scale, offset);


    // Ponto de referência de B
    sf::CircleShape refBPoint(5);
    refBPoint.setFillColor(sf::Color::Blue);
    // coordenadas relativas ao NFP
    float refB_x = static_cast<float>(CGAL::to_double(refB.x())) * scale + offset.x;
    float refB_y = static_cast<float>(CGAL::to_double(refB.y())) * scale + offset.y;
    refBPoint.setPosition(sf::Vector2f(refB_x - refBPoint.getRadius(), refB_y - refBPoint.getRadius()));
    sf::Text textRefB(font, "Ref B", 14);
    textRefB.setFillColor(sf::Color::Blue);
    textRefB.setPosition(sf::Vector2f(refB_x + 8, refB_y - 8));

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }


        window.clear(sf::Color::Black);
        window.draw(nfpVerts.data(), nfpVerts.size(), sf::PrimitiveType::LineStrip);

        // Desenha NFP coordenadas
        for (const auto& pt : nfp.outer_boundary()) {
            float x = static_cast<float>(CGAL::to_double(pt.x()));
            float y = static_cast<float>(CGAL::to_double(pt.y()));
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2)
                << CGAL::to_double(x) << ", " << CGAL::to_double(-y);
            text.setString(oss.str());
            text.setPosition(sf::Vector2f(x * scale + offset.x, y * scale + offset.y));
            window.draw(text);
        }

        // Desenha pontos de referência
        window.draw(refBPoint);
        window.draw(textRefB);

        window.display();
    }

    return 0;
}
