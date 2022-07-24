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
		rectangleBatch.UsedTextures = 0;
		
		for (auto& batchTexture : rectangleBatch.BatchTextures)
		{
			batchTexture->SetCurrentBatch(nullptr, NoTextureSlot);
		}
		rectangleBatch.BatchTextures.clear();
	}

	void OpenGLRenderer2D::RenderBatch()
	{
		const auto& shader =
			rectangleBatch.MaterialInstance->GetMaterial()->GetShader();

		shader->Bind();

		rectangleBatch.Vao->Bind();

		for (unsigned int i = 0; i < rectangleBatch.UsedTextures; i++)
		{
			rectangleBatch.BatchTextures[i]->GetTexture()->Bind(i);
		}

		if (rectangleBatch.UsedTextures)
		{
			shader->SetUniform("TextureSamplers",
				reinterpret_cast<int*>(rectangleBatch.TextureSlots.data()),
				rectangleBatch.UsedTextures);
		}

		shader->SetUniform("ViewProjection", viewProjectionMatrix);

		rectangleBatch.MaterialInstance->UploadData();

		ApplyMaterialFlags(rectangleBatch.MaterialInstance);

		rectangleBatch.Vbo->SetData(rectangleBatch.Vertices.data(),
			rectangleBatch.UsedVertices, RectangleVertex::Layout());

		glDrawElements(GL_TRIANGLES, rectangleBatch.UsedRectangles * 6, GL_UNSIGNED_INT, nullptr);
	}

	/*void OpenGLRenderer2D::Render(const Ref<VertexArray>& vao, const Transformation2D& transform)
	{
		const auto& shader = rectangleBatch.->GetMaterial()->GetShader();
		shader->Bind();
		vao->Bind();

		shader->SetUniform("ViewProjection", viewProjectionMatrix);
		shader->SetUniform("Transform", transform.ToMatrix());

		materialInstance->UploadData();

		ApplyMaterialFlags();

		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		
	}*/

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

		unsigned int textureSlot = NoTextureSlot;

		auto& batchTexture = sprite->GetBatchTexture();
		auto [batch, slot] = batchTexture->GetCurrentBatch();
		if (batch == &rectangleBatch.batch)
		{
			textureSlot = slot;
		}
		else
		{
			if (rectangleBatch.BatchTextures.size() == rectangleBatch.MaxTextures)
			{
				RenderBatch();
				NextBatch(rectangleBatch.MaterialInstance);
			}
			textureSlot = static_cast<unsigned int>(rectangleBatch.BatchTextures.size());
			rectangleBatch.BatchTextures.push_back(batchTexture);
			batchTexture->SetCurrentBatch(&rectangleBatch.batch, textureSlot);
		}

		rectangleBatch.UsedTextures = static_cast<unsigned int>(
			rectangleBatch.BatchTextures.size());

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
	
	/*void OpenGLRenderer2D::RenderRectangle(const Transformation2D& transform)
	{
		static Ref<VertexArray> rectangleVao;
		if (!rectangleVao)
		{
			Vertex vertices[] = {
			{ 1.f,  1.f, 0.0f},   // top right
			{ 1.f, -1.f, 0.0f },   // bottom right
			{ -1.f, -1.f, 0.0f },  // bottom left
			{ -1.f,  1.f, 0.0f }   // top left 
			};

			unsigned int indices[] = {
				0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
			};

			auto factory = GraphicsFactory::Get();

			const auto& layout = Vertex::Layout();

			auto vbo = factory->CreateVertexBuffer();
			vbo->SetVertices(vertices, 4, layout);

			auto ibo = factory->CreateIndexBuffer(indices, 6);

			rectangleVao = factory->CreateVertexArray(vbo, ibo);
		}

		Render(rectangleVao, transform);
	}*/

	void OpenGLRenderer2D::ApplyMaterialFlags(const Ref<MaterialInstance>& materialInstance)
	{
		const auto& flags = materialInstance->GetMaterial()->Flags;

		flags.EnableBlending ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
		flags.EnableDepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	OpenGLRenderer2D::RectangleBatchData::RectangleBatchData()
	{
		Vertices.resize(RectanglesCapacity * 4);
		auto factory = GraphicsFactory::Get();

		Vbo = factory->CreateVertexBuffer();
		Vbo->SetData(nullptr, static_cast<unsigned int>(Vertices.size()), RectangleVertex::Layout());
		
		std::vector<unsigned int> indices;
		indices.resize(RectanglesCapacity * 6);

		unsigned int pattern[6] = { 0, 1, 3, 1, 2, 3 };

		for (unsigned int i = 0; i < indices.size(); i++)
		{
			indices[i] = pattern[i % 6] + ((i / 6) * 4);
		}

		Ibo = factory->CreateIndexBuffer(indices.data(),
			static_cast<unsigned int>(indices.size()));

		Vao = factory->CreateVertexArray(Vbo, Ibo);

		BatchTextures.reserve(16);
		TextureSlots.resize(16);
		for (unsigned int i = 0; i < TextureSlots.size(); i++)
		{
			TextureSlots[i] = i;
		}
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