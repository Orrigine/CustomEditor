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

		Geometries();
		~Geometries();

		void DefineGeometries(std::list<Vertex> Point, std::list < float> DrawOrder);
		void Triangle();
		void Square();
		void Cube();

		std::list<Vertex> ReturnPoints();
		std::list<float> ReturnOrderDraw();

		
	};
}