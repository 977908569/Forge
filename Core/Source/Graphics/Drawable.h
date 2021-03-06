#pragma once
#include "Material.h"
#include "Mesh.h"
#include "Math/Matrix3x4.h"

namespace Forge
{
	class Drawable
	{
	protected:
		Mesh* _mesh;
		Material* _material;
		const Matrix3x4* _worldTransform;
        bool _transparent = false;
        bool active = true;
	public:
		Drawable();
		~Drawable();

		const Matrix3x4* GetWorldPosition() const;
		Material& GetMaterial() const;
		Mesh& GetMesh() const;

		void SetWorldPosition(const Matrix3x4& newPosition);

        virtual void Draw() const;

		virtual void SetActive(bool state);
		bool IsActive() const { return active; }

        virtual bool IsTransparent() const { return _transparent; }
        virtual void SetTranparent(bool state) { _transparent = state; }
	};

}
