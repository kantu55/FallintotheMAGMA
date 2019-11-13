/*
@file Texture.h
*/

#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include <GL\glew.h>
#include<string>
#include<memory>

namespace Texture
{
	GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* data,
		GLenum format, GLenum type);
	GLuint LoadImage2D(const char* path);
	class Texture;
	typedef std::shared_ptr<Texture> TexturePtr; ///< �e�N�X�`���|�C���^.

	/*
	2D�e�N�X�`��
	*/
	class Image2D
	{
	public:
		//default...���̌��ʂ��ǂ̒l�Ƃ���v���Ȃ������Ƃ��̏���
		Image2D() = default;
		//explicit...�ÖٓI�ȕϊ���h�����Ƃ��ł���
		explicit Image2D(GLuint texId);
		~Image2D();

		void Reset(GLuint texId);
		bool IsNull() const;
		GLuint Get() const;

	private:
		GLuint id = 0;
	};
}

#endif // !TEXTURE_H_INCLUDED

