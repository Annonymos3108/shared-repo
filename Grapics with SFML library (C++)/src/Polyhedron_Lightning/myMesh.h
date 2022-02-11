#ifndef MYMESH_H_
#define MYMESH_H_

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <array>
#include <vector>

namespace Polyhedron_Lightning
{

class myMesh: public sf::Drawable, public sf::Transformable {
public:
	explicit myMesh(size_t, int, int);
	virtual ~myMesh();
	void add(size_t, float, float, float, float, float, float, float, float, float);
	sf::VertexArray get(size_t);
	std::vector<sf::VertexArray> getPt();
	sf::Color mColor;
	const float PI;
	void rotateSurface(std::array<std::array<float, 3>, 3>&);

	void lightning();
	std::array<float, 4> getABCD(float, float, float, float, float, float, float, float, float);

	std::array<std::array<float, 3>, 3> M_R_X_DOWN;
	std::array<std::array<float, 3>, 3> M_R_X_UP;
	std::array<std::array<float, 3>, 3> M_R_Y_LEFT;
	std::array<std::array<float, 3>, 3> M_R_Y_RIGHT;
	std::array<std::array<float, 3>, 3> matrixRotate;
	int offsetX;
	int offsetY;
	template<std::size_t N, std::size_t M, std::size_t P>
			std::array<std::array<float, P>, N> mult(std::array<std::array<float, M>, N> A, std::array<std::array<float, P>, M> B) {
			    static_assert(N > 0, "N must be greater than 0");
			    static_assert(M > 0, "M must be greater than 0");
			    static_assert(P > 0, "P must be greater than 0");

			    std::array<std::array<float, P>, N> C;

			    for (std::size_t n = 0; n < N; n++) {
			        for (std::size_t p = 0; p < P; p++) {
			            float res = 0;
			            for (std::size_t m = 0; m < M; m++) {
			            	res += A[n][m] * B[m][p];
			            }
			            C[n][p] = res;
			        }
			    }

			    return C;
			}

private:
	std::vector<sf::VertexArray> points;
	std::vector<std::array<float, 9>> points3D;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void active(size_t, float);
	void passive(size_t);
	std::array<float, 3> normalize(float, float, float);
	void update();
	float x0;
	float y0;
	int scale;
};
}

#endif /* MYMESH_H_ */
