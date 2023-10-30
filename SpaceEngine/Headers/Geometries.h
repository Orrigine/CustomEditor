#pragma once

#include "Tranform/Transform.h"


namespace Render
{
	class Geometries {
	
	private:
		DirectX::XMFLOAT3 m_PosOrigin;
		DirectX::XMMATRIX m_rotation;
		


		OrderDraw m_DrawOrder [MAX_POINT];
		Vertex m_PointList[MAX_POINT] = {NULLVERTEX};
	
	public:

		Geometries(TRANSFORM );
		~Geometries();
		void AddPoint(Vertex newPoint[]);
		void ChangeDrawOrdeer(int Line1, int Line2);
		void ChangeLineInDraw(OrderDraw newOrder, int Line);

		void TransformGeometries(TRANSFORM Transformation);
		#pragma region OtherTransform

		void TransformGeometries(DirectX::XMFLOAT3 Translation);
		void TransformGeometries(DirectX::XMMATRIX Translation);
		
		void TransformGeometries(DirectX::XMFLOAT3 Scale);
		void TransformGeometries(DirectX::XMMATRIX Scale);

		void TransformGeometries(DirectX::XMMATRIX RotationMatrix);

#pragma endregion

		DirectX::XMMATRIX GetRotationMatrix();
		DirectX::XMFLOAT3 GetPosOrigin();
	};
}