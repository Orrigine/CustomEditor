#pragma once
#include "Tranform/Transform.h"
#include <list>

namespace Render
{
	class Geometries {
	private:
		std::list<Vertex> m_PointList;
		std::list <float> m_DrawOrder;
	public:
		#pragma region Create
			Geometries();
			~Geometries();
		#pragma endregion
		#pragma region Define
			void DefineGeometries(std::list<Vertex> Point, std::list < float> DrawOrder);
			void Triangle();
			void Square();
			void Cube();
		#pragma endregion
		#pragma region Return Points and Order
			std::list<Vertex> ReturnPoints();
			std::list<float> ReturnOrderDraw();
		#pragma endregion
	};
}