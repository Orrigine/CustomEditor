#pragma once
#include "Graphics/Render.h"
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
			void defineGeometries(std::list<Vertex> Point, std::list < float> DrawOrder);
			void triangle();
			void square();
			void cube();
		#pragma endregion
		#pragma region Return Points and Order
			std::list<Vertex> returnPoints();
			std::list<float> returnOrderDraw();
		#pragma endregion
	};
}