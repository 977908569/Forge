#pragma once
#include "Graphics/GraphicsRenderer.h"
#include "glad/glad.h"

namespace Forge
{

	class GLGraphicsRenderer : public GraphicsRenderer
	{
	private:
		
		uint clearMask = 0;
		float normalizedClearColor[4];

	public:
		GLGraphicsRenderer();
		~GLGraphicsRenderer();

		void PreDraw() override;
		void Draw(DrawBatch* batch) override;
		void PostDraw() override;

		void DrawToScreen() override;

		void Init(const Vector2i& windowSize) override;

		void SetSize(const Vector2i& newSize) override;
		void SetClearColorBuffer(bool value) override;
		void SetClearDepthBuffer(bool value) override;

		void BindFrameBuffer(GLuint bufferId);
		void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);
		void ClearFrameBuffer(const Color& color);
		void ClearDepthValue(float clearDepthValue);
		void SetDepthMask(bool value);


		
	};
}