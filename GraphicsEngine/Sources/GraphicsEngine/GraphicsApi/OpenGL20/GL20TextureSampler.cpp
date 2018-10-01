#include "GL20TextureSampler.h"
//#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngineContext.h"


GL20TextureSampler::GL20TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode)
{
	SetFilterMode( filterMode );
	SetWrapMode  ( wrapMode );
}

GL20TextureSampler::~GL20TextureSampler()
{

}

void GL20TextureSampler::SetFilterMode(TextureFilterMode filterMode)
{
	// http://www.learnopengles.com/android-lesson-six-an-introduction-to-texture-filtering/
	// https://www.opengl.org/wiki/Sampler_Object
	// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
	// http://opengl-master.ru/view_post.php?id=78
	// http://www.araku.ac.ir/~d_comp_engineering/88892/1323108/OpenGL%20Game%20Development.pdf

	if (filterMode == TEXTURE_FILTER_MODE_POINT)
	{
		// TODO: Task05_01
	}
	else if (filterMode == TEXTURE_FILTER_MODE_BILINEAR)
	{
		// TODO: Task05_01
	}
	else if (filterMode == TEXTURE_FILTER_MODE_TRILINEAR)
	{
		// TODO: Task05_01
	}
	else if (filterMode == TEXTURE_FILTER_MODE_ANISOTROPIC)
	{
		// TODO: Task05_01
	}
}

void GL20TextureSampler::SetWrapMode(TextureWrapMode wrapMode)
{
	// http://gamedev.stackexchange.com/questions/62548/what-does-changing-gl-texture-wrap-s-t-do

	if (wrapMode == TEXTURE_WRAP_MODE_CLAMP)
	{
		// TODO: Task05_01
	}
	else if (wrapMode == TEXTURE_WRAP_MODE_REPEAT)
	{
		// TODO: Task05_01
	}
}

void GL20TextureSampler::PassParamsToShader(int textureRegister, bool toPixelShader) const
{
	// TODO: Task05_01

	// Set wrap mode (Clamp, Repeat).
	// TODO: Task05_01
		
	// Set filter mode (Point, Bilinear, Trilinear, Anisotropic).
	// TODO: Task05_01
	
	// Enable/disable anisotropic filter.
	if (m_useAniso)
	{
		// TODO: Task05_01
	}
	else
	{
		// TODO: Task05_01
	}
}
