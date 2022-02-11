#include "myMesh.h"

namespace Polyhedron_Lightning
{

myMesh::myMesh(size_t k, int x, int y):
points(k, sf::VertexArray(sf::Triangles, 3)),
points3D(k),
mColor(sf::Color::Transparent),
x0(x),
y0(y),
scale(200),
PI(3.14159265358979f)
{
	using namespace std;
	float speed{PI/50};
	M_R_X_DOWN = std::array<std::array<float, 3>, 3>{{{1.f, 0.f, 0.f}, {0.f, cosf(speed), -sinf(speed)}, {0.f, sinf(speed), cosf(speed)}}};
	M_R_X_UP = std::array<std::array<float, 3>, 3>{{{1.f, 0.f, 0.f}, {0.f, cosf(speed), sinf(speed)}, {0.f, -sinf(speed), cosf(speed)}}};

	M_R_Y_RIGHT = std::array<std::array<float, 3>, 3>{{{cosf(speed), 0.f, sinf(speed)},{0.f, 1.f, 0.f}, {-sinf(speed),0.f,cosf(speed)}}};
	M_R_Y_LEFT = std::array<std::array<float, 3>, 3>{{{cosf(speed), 0.f, -sinf(speed)},{0.f, 1.f, 0.f}, {sinf(speed),0.f,cosf(speed)}}};

}

void myMesh::add(size_t index, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
	points3D[index][0] = x1;
	points3D[index][1] = y1;
	points3D[index][2] = z1;
	points3D[index][3] = x2;
	points3D[index][4] = y2;
	points3D[index][5] = z2;
	points3D[index][6] = x3;
	points3D[index][7] = y3;
	points3D[index][8] = z3;

	points[index][0].position.x = x1*scale + x0;
	points[index][0].position.y = -y1*scale + y0;
	points[index][1].position.x = x2*scale + x0;
	points[index][1].position.y = -y2*scale + y0;
	points[index][2].position.x = x3*scale + x0;
	points[index][2].position.y = -y3*scale + y0;

	points[index][0].color = mColor;
	points[index][1].color = mColor;
	points[index][2].color = mColor;


}

void myMesh::update()
{
	for (size_t i = 0, k = points3D.size(); i < k; ++i)
	{
		points[i][0].position.x = points3D[i][0]*scale + x0;
		points[i][0].position.y = -points3D[i][1]*scale + y0;
		points[i][1].position.x = points3D[i][3]*scale + x0;
		points[i][1].position.y = -points3D[i][4]*scale + y0;
		points[i][2].position.x = points3D[i][6]*scale + x0;
		points[i][2].position.y = -points3D[i][7]*scale + y0;
	}
}

void myMesh::active(size_t ind, float intens)
{
	points[ind][0].color = sf::Color(255*intens, 255*intens, 255*intens);
	points[ind][1].color = sf::Color(255*intens, 255*intens, 255*intens);;
	points[ind][2].color = sf::Color(255*intens, 255*intens, 255*intens);;
}

void myMesh::passive(size_t ind)
{
	points[ind][0].color = sf::Color::Transparent;
	points[ind][1].color = sf::Color::Transparent;
	points[ind][2].color = sf::Color::Transparent;
}


void myMesh::rotateSurface(std::array<std::array<float, 3>, 3>& MRX)
{
	for (auto& it: points3D)
	{
		for (size_t i = 0; i < 9; i+=3)
		{
			std::array<std::array<float, 1>, 3>  A = {{{it[i]}, {it[i+1]}, {it[i+2]}}};
			A = mult<3, 3, 1>(MRX, A);
			it[i] = A[0][0];
			it[i+1] = A[1][0];
			it[i+2] = A[2][0];
		}
	}
	update();
}

void myMesh::lightning()
{
	std::vector<std::array<float, 4>> volumeMatrix(points3D.size(), {{0.f, 0.f, 0.f, 0.f}});
	std::vector<std::array<float, 3>> centroidTriang(points3D.size(), {{0.f, 0.f, 0.f}});
	std::array<float, 3> insidePoint = {0.f, 0.f, 0.f};
	std::array<float, 4> viewPoint{{0.f, 0.f, 1.f, 0.f}};
	std::array<float, 3> lightPoint = normalize(0.f, 0.f, 1.f);
	std::vector<float> intens(points3D.size());

	for (size_t i = 0, k = points3D.size(); i < k; ++i)
	{
		volumeMatrix[i] = (getABCD(points3D[i][0], points3D[i][1], points3D[i][2],
				points3D[i][3], points3D[i][4], points3D[i][5],
					points3D[i][6], points3D[i][7], points3D[i][8]));

		centroidTriang[i][0] = (points3D[i][0] + points3D[i][3] + points3D[i][6])/3;
		centroidTriang[i][1] = (points3D[i][1] + points3D[i][4] + points3D[i][7])/3;
		centroidTriang[i][2] = (points3D[i][2] + points3D[i][5] + points3D[i][8])/3;
	}

	for (size_t i = 0, k = centroidTriang.size(); i < k; ++i)
	{
		insidePoint[0] += centroidTriang[i][0];
		insidePoint[1] += centroidTriang[i][1];
		insidePoint[2] += centroidTriang[i][2];
	}
	insidePoint[0] /= centroidTriang.size();
	insidePoint[1] /= centroidTriang.size();
	insidePoint[2] /= centroidTriang.size();

	for (size_t i = 0, k = volumeMatrix.size(); i < k; ++i)
	{
		if ((volumeMatrix[i][0]*insidePoint[0] + volumeMatrix[i][1]*insidePoint[1] +
				volumeMatrix[i][2]*insidePoint[2]+ volumeMatrix[i][3]) > 0)
		{
			volumeMatrix[i][0] *= -1;
			volumeMatrix[i][1] *= -1;
			volumeMatrix[i][2] *= -1;
			volumeMatrix[i][3] *= -1;
		}
	}

	for (size_t i = 0, k = volumeMatrix.size(); i < k; ++i)
	{

		float a = volumeMatrix[i][0];
		float b = volumeMatrix[i][1];
		float c = volumeMatrix[i][2];
		float d = volumeMatrix[i][3];

		if ((volumeMatrix[i][0]*viewPoint[0] + volumeMatrix[i][1]*viewPoint[1] +
				volumeMatrix[i][2]*viewPoint[2]+ volumeMatrix[i][3]*viewPoint[3]) > 0)
		{
			std::array<float, 3> arr = normalize(volumeMatrix[i][0], volumeMatrix[i][1], volumeMatrix[i][2]);
			if ((arr[0]*lightPoint[0]+arr[1]*lightPoint[1]+arr[2]*lightPoint[2])>0)
				active(i, arr[0]*lightPoint[0]+arr[1]*lightPoint[1]+arr[2]*lightPoint[2]);
		}
		else
		{
			passive(i);
		}
	}

}

std::array<float, 4> myMesh::getABCD(float x1, float y1,
        float z1, float x2,
        float y2, float z2,
        float x3, float y3, float z3)
{
    float a1 = x2 - x1;
    float b1 = y2 - y1;
    float c1 = z2 - z1;
    float a2 = x3 - x1;
    float b2 = y3 - y1;
    float c2 = z3 - z1;
    float a = b1 * c2 - b2 * c1;
    float b = a2 * c1 - a1 * c2;
    float c = a1 * b2 - b1 * a2;
    float d = (- a * x1 - b * y1 - c * z1);

	return std::array<float, 4>{{a, b, c, d}};
}

std::array<float, 3> myMesh::normalize(float a, float b, float c)
{
	float d = std::sqrt(std::pow(a, 2) + std::pow(b, 2) + std::pow(c, 2));
	return std::array<float, 3>{{a/d, b/d, c/d}};
}

void myMesh::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& triang: points)
	{
			target.draw(triang);
	}
}

myMesh::~myMesh() {

}

}
