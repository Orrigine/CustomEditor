#include"Headers/Geometries.h"

Render::Geometries::Geometries()
{
}
Render::Geometries::~Geometries()
{
}

void Render::Geometries::DefineGeometries(std::list <Vertex> Point, std::list <float> DrawOrder)
{
	this->m_PointList = Point;
	this->m_DrawOrder = DrawOrder;

}

void Render::Geometries::Triangle()
{
	this->m_PointList = {
		{{-1,0,0},{0,0,0,0}},
		{{1,0,0},{0,0,0,0}},
		{{0,1,0},{0,0,0,0}}
	};
	this->m_DrawOrder = {
		{0,1,2},
	};
}
void Render::Geometries::Square()
{
	this->m_PointList = {
		{{-1,1,0},{0,0,0,0}},
		{{1,1,0},{0,0,0,0}},
		{{-1,-1,0},{0,0,0,0}},
		{{1,-1,0},{0,0,0,0}},
	};
	this->m_DrawOrder = {
		{
			0,1,2,
			1,3,2
		},
	};
}
void Render::Geometries::Cube()
{
	this->m_PointList = {
	{	{-1, 1, 0.5f}	,	{0,0,0,0}	},
	{	{ 1, 1, 0.5f}	,	{0,0,0,0}	},
	{	{-1,-1, 0.5f}	,	{0,0,0,0}	},
	{	{ 1,-1, 0.5f}	,	{0,0,0,0}	},				

	{	{-1, 1, -0.5f}	,	{0,0,0,0}	},
	{	{ 1, 1, -0.5f}	,	{0,0,0,0}	},
	{	{-1,-1, -0.5f}	,	{0,0,0,0}	},
	{	{ 1,-1, -0.5f}	,	{0,0,0,0}	},

	};
	this->m_DrawOrder = {
		{
			0,1,2,
			1,3,2,   //z = 0.5f

			4,5,6,
			5,7,6,	// z =-0.5f

			0,1,4,
			2,5,4,	// y = 1

			2,3,6,
			3,7,6,	// y = -1

			1,3,5,
			3,7,5, // x = 1

			0,2,4,
			2,6,4, //x = -1
		}
	};
}


std::list<Vertex> Render::Geometries::ReturnPoints()
{
	return this->m_PointList;
}
std::list<float> Render::Geometries::ReturnOrderDraw()
{
	return this->m_DrawOrder;
}