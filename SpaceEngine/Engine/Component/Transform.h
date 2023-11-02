#include "IComponent.hpp"

namespace SpaceEngine {
	class Transform : public IComponent
	{
	public:
		Transform();
		~Transform();
	private:
		std::shared_ptr<Vector3f> position;
		std::shared_ptr<Vector3f> rotation;
		std::shared_ptr<Vector3f> scale;
	};
}
