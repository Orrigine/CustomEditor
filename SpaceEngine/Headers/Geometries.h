#pragma once

#include "Tranform/Transform.h"

namespace Render
{
	class Geometries {
	
	private:
		OrderDraw m_DrawOrder [MAX_POINT];
		Vertex m_PointList[] ;
	
	public:

		Geometries();
		~Geometries();

		void DefineGeometries(Vertex Point[], OrderDraw DrawOrder[]);

		void Triangle();
		void Triangle(DirectX::XMFLOAT3 x, DirectX::XMFLOAT3 y, DirectX::XMFLOAT3 z);
		
		void Square();
		void Square(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c, DirectX::XMFLOAT3 d);

		void Cube();
		void Cube(
			DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c, DirectX::XMFLOAT3 d,
			DirectX::XMFLOAT3 e, DirectX::XMFLOAT3 f, DirectX::XMFLOAT3 g, DirectX::XMFLOAT3 h);
		
	};
}