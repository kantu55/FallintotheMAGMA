/*
@file GLFWE..cpp
*/

#include "GLFWEW.h"
#include <iostream>

//GLFW��GLEW�����b�v���邽�߂̖��O���
namespace GLFWEW
{

	/*
	GLFW����̃G���[�񍐂���������

	@param error  �G���[�ԍ�
	@param desc   �G���[�̓��e
	*/
	void ErrorCallback(int error, const char* desc)
	{
		std::cerr << "ERROR: " << desc << std::endl;
	}

	/*
	�V���O���g���C���X�^���X���擾����

	@return window�̃V���O���g���C���X�^���X
	*/

	Window& Window::Instance()
	{
		static Window instance;
		return instance;
	}

	/*
	�R���X�g���N�^
	*/
	Window::Window()
	{
	}

	/*
	�f�X�g���N�^
	*/
	Window::~Window()
	{
		if (isGLFWInitialized)
		{
			glfwTerminate();
		}
	}

	/*
	GLFW/GLEW�̏�����

	@param w �E�B���h�E�̕`��͈͂̕�(�s�N�Z��)
	@param h �E�B���h�E�̕`��͈͂̍���(�s�N�Z��)
	@param title �E�B���h�E�^�C�g��(UTF-8��0�I�[������)
	
	@retval true   ����������
	@retval false  ���������s
	*/

	bool Window::Init(int w, int h, const char* title)
	{
		if (isInitialized)
		{
			std::cerr << "ERROR: GLFWEW�͂��łɏ���������Ă��܂�." << std::endl;
			return false;
		}
		if (!isGLFWInitialized)
		{
			
			glfwSetErrorCallback(ErrorCallback);
			//OpenGL�y��GLFW�̏��������s��
			if (glfwInit() != GL_TRUE)
			{
				return false;
			}
			isGLFWInitialized = true;
		}

		if (!window)
		{
			//�O���t�B�b�N�`��p�̃E�B���h�E���쐬����
			window = glfwCreateWindow(w, h, title, nullptr, nullptr);
			if (!window)
			{
				return false;
			}
			//�w�肵���E�B���h�E�ɑΉ�����OpenGL�R���e�L�X�g��`��Ώۂɐݒ肷��
			glfwMakeContextCurrent(window);
		}

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "ERROR: GLEW�̏������Ɏ��s���܂���." << std::endl;
			return false;
		}

		//OpenGL�̏����R���\�[���E�B���h�E�֏o�͂���
		/*
		glGetString -> OpenGL�R���e�L�X�g�Ɋ֘A�t����Ă��������̏����擾����֐�
		GL_RENDERER�E�E�EOpenGL��`�悷��O���t�B�b�N�X�n�[�h�E�F�A���A�܂��̓h���C�o��
		*/
		const GLubyte* renderer = glGetString(GL_RENDERER);
		std::cout << "Renderer: " << renderer << std::endl;
		//GL_VERSION�E�E�E�O���t�B�b�N�X�n�[�h�E�F�A�A�܂��̓h���C�o���Ή�����ő��OpenGL
		const GLubyte* version = glGetString(GL_VERSION);
		std::cout << "Version: " << version << std::endl;

		isInitialized = true;
		return true;
	}

	/*
	�E�B���h�E�����ׂ������ׂ�

	@retval true   ����
	@retval false  ���Ȃ�
	*/
	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(window) != 0;
	}

	/*
	�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@��؂�ւ���
	�t�����g�o�b�t�@�͕\�����̃t���[���o�b�t�@
	�o�b�N�o�b�t�@�͕`�摤�̃t���[���o�b�t�@
	*/
	void Window::SwapBuffers() const
	{
		//GLFW��OS���瑗��ꂽ�C�x���g����������֐�
		glfwPollEvents();
		/*
		�t���[���o�b�t�@�̕`�摤(�o�b�N)�ƕ\����(�t�����g)�����ւ���
		�t���[���o�b�t�@�͊G��`�悷�邽�߂̃�����
		*/
		glfwSwapBuffers(window);
	}

	/*
	�L�[��������Ă��邩���ׂ�

	@param key ���ׂ����L�[�E�R�[�h(GLFW_KEY_A�Ȃ�)

	@retval true  �L�[��������Ă���
	@retval false �L�[��������Ă��Ȃ�

	�g�p�ł���L�[�E�R�[�h�ꗗ��glfw3.h�ɂ���܂�(�ukeyboard�v�Ō���)
	*/

	bool Window::IsKeyPressed(int key) const
	{
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	bool Window::IsMousePressed(int mouse) const
	{
		return glfwGetMouseButton(window, mouse) == GLFW_PRESS;
	}


	void Window::CursorPos(double mousex, double mousey) const
	{
		return glfwGetCursorPos(window, &mousex, &mousey);
	}

	/*
	�^�C�}�[������������
	*/
	void Window::InitTimer()
	{
		glfwSetTime(0.0);
		previousTime = 0.0;
		deltaTime = 0.0;
	}

	/*
	�^�C�}�[���X�V����
	*/
	void Window::UpdateTimer()
	{
		//�o�ߎ��Ԃ��v��
		const double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		//�o�ߎ��Ԃ������Ȃ肷���Ȃ��悤�ɒ���
		const float upperLimit = 0.25f; //�o�ߎ��ԂƂ��ċ��e�������
		if (deltaTime > upperLimit)
		{
			deltaTime = 0.1f;
		}
	}

	/*
	�o�ߎ��Ԃ��擾����

	@retrun ���O��2���UpdateTimer()�Ăяo���̊ԂɌo�߂�������
	*/
	double Window::DeltaTime() const
	{
		return deltaTime;
	}

}//namespace GLFWEW