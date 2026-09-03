#ifndef CAMERA_H
#define CAMERA_H

#include "MEGEngine/Common.hpp"
#include "MEGEngine/Core/Entity.hpp"
#include "MEGEngine/Math/Mat4.hpp"


class ENGINE_API Camera : public Entity {
public:
	Camera(int width, int height);
	void updateCamMatrix();

	Mat4 camMatrix() const;

private:
	float _width;
	float _height;

	float _fov;
	float _nearZ;
	float _farZ;

	Mat4 _camMatrix = Mat4(1.0f);
};



#endif //CAMERA_H