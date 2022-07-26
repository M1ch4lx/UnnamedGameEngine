#include "Pch.h"
#include "OpenGLRenderer2D.h"

namespace UEngine
{
	OpenGLRenderer2D::OpenGLRenderer2D(RenderContext* context) :
		context(context)
	{
		clearColor = Color(0.f, 0.f, 0.f);
		SetClearColor(clearColor);
	}

	void OpenGLRenderer2D::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer2D::SetClearColor(const Color3& Color)
	{
		clearColor = Color;
		glClearColor(Color.r, Color.g, Color.b, 1.f);
	}

	const Color3& OpenGLRenderer2D::GetClearColor() const
	{
		return clearColor;
	}

	void OpenGLRenderer2D::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	RenderContext* OpenGLRenderer2D::GetContext() const
	{
		return context;
	}

	void OpenGLRenderer2D::BeginScene(const Camera2D& camera)
	{
		viewProjectionMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix();
		const auto& vp = camera.GetViewport();

		const float width = static_cast<const float>(context->Width());
		const float height = static_cast<const float>(context->Height());
		
		DenormalizedViewport denormalizedVp(
			static_cast<int>(height * vp.Top),
			static_cast<int>(width * vp.Left),
			static_cast<int>(height * vp.Bottom),
			static_cast<int>(width * vp.Right));

		// Reduces redundant glViewport calling
		if (viewport != denormalizedVp)
		{
			viewport = denormalizedVp;

			glViewport(denormalizedVp.Left, denormalizedVp.Top,
				denormalizedVp.Right - denormalizedVp.Left,
				denormalizedVp.Bottom - denormalizedVp.Top);
		}
	}

	void OpenGLRenderer2D::EndScene()
	{
		// Do smth
	}

	void OpenGLRenderer2D::Display()
	{
		context->SwapBuffers();
	}

	void OpenGLRenderer2D::NextBatch(const Ref<MaterialInstance>& materialInstance)
	{
		rectangleBatch.MaterialInstance = materialInstance;

		rectangleBatch.UsedRectangles = 0;
		rectangleBatch.UsedVertices = 0;
		
		rectangleBatch.textureSlots.ClearTextures();
	}

	void OpenGLRenderer2D::RenderBatch()
	{
		const auto& shader =
			rectangleBatch.MaterialInstance->GetMaterial()->GetShader();

		shader->Bind();

		rectangleBatch.Vao->Bind();

		rectangleBatch.textureSlots.BindTextures();

		auto [textureSlots, usedSlots] = rectangleBatch.textureSlots.SlotsUsage();

		if (usedSlots)
		{
			shader->SetUniform("TextureSamplers",
				reinterpret_cast<const int*>(textureSlots),
				usedSlots);
		}

		shader->SetUniform("ViewProjection", viewProjectionMatrix);

		rectangleBatch.MaterialInstance->UploadData();

		ApplyMaterialFlags(rectangleBatch.MaterialInstance);

		rectangleBatch.Vbo->SetData(rectangleBatch.Vertices.data(),
			rectangleBatch.UsedVertices, RectangleVertex::Layout());

		glDrawElements(GL_TRIANGLES, rectangleBatch.UsedRectangles * 6, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderer2D::RenderRectangle(const Transformation2D& transform, const Color4& color)
	{
		struct Rectangle
		{
			RectangleVertex TopRight;
			RectangleVertex BottomRight;
			RectangleVertex BottomLeft;
			RectangleVertex TopLeft;
		};

		if (rectangleBatch.UsedRectangles == rectangleBatch.RectanglesCapacity)
		{
			RenderBatch();
			NextBatch(rectangleBatch.MaterialInstance);
		}

		auto& rectangle = reinterpret_cast<Rectangle&>(
			rectangleBatch.Vertices[rectangleBatch.UsedVertices]);

		rectangle.TopRight.ModelPosition = { 1.f * transform.Scale.x, 1.f * transform.Scale.y, transform.Depth };
		rectangle.TopRight.Translation = transform.Position;
		rectangle.TopRight.Rotation = Radians(transform.Rotation);
		rectangle.TopRight.Color = color;
		rectangle.TopRight.TexSlot = NoTextureSlot;

		rectangle.BottomRight.ModelPosition = { 1.f * transform.Scale.x, -1.f * transform.Scale.y, transform.Depth };
		rectangle.BottomRight.Translation = transform.Position;
		rectangle.BottomRight.Rotation = Radians(transform.Rotation);
		rectangle.BottomRight.Color = color;
		rectangle.BottomRight.TexSlot = NoTextureSlot;

		rectangle.BottomLeft.ModelPosition = { -1.f * transform.Scale.x, -1.f * transform.Scale.y, transform.Depth };
		rectangle.BottomLeft.Translation = transform.Position;
		rectangle.BottomLeft.Rotation = Radians(transform.Rotation);
		rectangle.BottomLeft.Color = color;
		rectangle.BottomLeft.TexSlot = NoTextureSlot;

		rectangle.TopLeft.ModelPosition = { -1.f * transform.Scale.x, 1.f * transform.Scale.y, transform.Depth };
		rectangle.TopLeft.Translation = transform.Position;
		rectangle.TopLeft.Rotation = Radians(transform.Rotation);
		rectangle.TopLeft.Color = color;
		rectangle.TopLeft.TexSlot = NoTextureSlot;

		rectangleBatch.UsedRectangles++;
		rectangleBatch.UsedVertices += 4;
	}

	void OpenGLRenderer2D::RenderSprite(const Transformation2D& transform, const Color4& color, const Ref<Sprite>& sprite)
	{
		struct Rectangle
		{
			RectangleVertex TopRight;
			RectangleVertex BottomRight;
			RectangleVertex BottomLeft;
			RectangleVertex TopLeft;
		};

		const auto& texture = sprite->GetTexture();
		const auto& textureCoords = sprite->GetTextureCoords();
		const auto& boundingRect = sprite->GetBoundingRect();

		unsigned int textureSlot = rectangleBatch.textureSlots.AddTexture(texture);
		if (textureSlot == TextureSlotsBuffer::InvalidTextureSlot)
		{
			RenderBatch();
			NextBatch(rectangleBatch.MaterialInstance);
		}
		textureSlot = rectangleBatch.textureSlots.AddTexture(texture);

		Transformation2D transformation = transform;
		transformation.Scale.x *= sprite->GetSize().x / 2.f;
		transformation.Scale.y *= sprite->GetSize().y / 2.f;

		RenderRectangle(transformation, color);

		auto& rectangle = reinterpret_cast<Rectangle&>(
			rectangleBatch.Vertices[rectangleBatch.UsedVertices - 4]);

		const auto& coords = sprite->GetTextureCoords();

		rectangle.TopRight.TexCoord = { coords.Right, coords.Top };
		rectangle.BottomRight.TexCoord = { coords.Right, coords.Bottom };
		rectangle.BottomLeft.TexCoord = { coords.Left, coords.Bottom };
		rectangle.TopLeft.TexCoord = { coords.Left, coords.Top };

		rectangle.TopRight.TexSlot = textureSlot;
		rectangle.BottomRight.TexSlot = textureSlot;
		rectangle.BottomLeft.TexSlot = textureSlot;
		rectangle.TopLeft.TexSlot = textureSlot;
	}

	void OpenGLRenderer2D::ApplyMaterialFlags(const Ref<MaterialInstance>& materialInstance)
	{
		const auto& flags = materialInstance->GetMaterial()->Flags;

		flags.EnableBlending ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
		flags.EnableDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	OpenGLRenderer2D::RectangleBatchData::RectangleBatchData() :
		shape(4, 6, { 0, 1, 3, 1, 2, 3 })
	{
		Vertices.resize(RectanglesCapacity * 4);
		auto factory = GraphicsFactory::Get();

		Vbo = factory->CreateVertexBuffer();
		Vbo->SetData(nullptr, static_cast<unsigned int>(Vertices.size()), RectangleVertex::Layout());
		
		std::vector<unsigned int> indices;
		indices.resize(RectanglesCapacity * 6);

		shape.IndexShapes(indices.data(), 0, RectanglesCapacity);

		Ibo = factory->CreateIndexBuffer(indices.data(),
			static_cast<unsigned int>(indices.size()));

		Vao = factory->CreateVertexArray(Vbo, Ibo);
	}

	const VertexLayout& RectangleVertex::Layout()
	{
		static const VertexLayout layout = {
			VertexElementType::Float3,
			VertexElementType::Float2,
			VertexElementType::Float,
			VertexElementType::Float4,
			VertexElementType::Float,
			VertexElementType::Float2
		};
		
		return layout;
	}
}