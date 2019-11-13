/*
@file Shader.cpp
*/
#include "Shader.h"
#include "Geometry.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include <fstream>

/*
�V�F�[�_�[�Ɋւ���@�\���i�[���閼�O���
*/
namespace Shader
{
	/*
	�V�F�[�_�[�E�v���O�������R���p�C������

	@param type �V�F�[�_�[�̎��
	@param string �V�F�[�_�[�E�I�u�W�F�N�g�̍쐬�Ɏ��s
	*/

	GLuint Compile(GLenum type, const GLchar* string)
	{
		if (!string)
		{
			return 0;
		}
		//�V�F�[�_�[�E�I�u�W�F�N�g���쐬���Ă���
		GLuint shader = glCreateShader(type);
		//�V�F�[�_�[�E�I�u�W�F�N�g�ɃV�F�[�_�[�E�v���O�������֘A�t�����Ă���
		glShaderSource(shader, 1, &string, nullptr);
		//�V�F�[�_�[�E�v���O�������R���p�C������A�V�F�[�_�[�E�I�u�W�F�N�g�ɃZ�b�g�����
		glCompileShader(shader);
		GLint compiled = 0;
		//�V�F�[�_�[�E�I�u�W�F�N�g�̏�Ԃ��擾���Ă���
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		//�R���p�C���Ɏ��s�����ꍇ�A�������R���\�[���ɏo�͂���0��Ԃ�
		if (!compiled)
		{
			GLint infoLen = 0;
			//�ڍ׏��̃o�C�g�����擾���Ă���
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen)
			{
				//�ڍ׏����l�����邽�߂�vector���g���Ă���
				std::vector<char> buf;
				//std::vector�̃T�C�Y��ύX���Ă���
				buf.resize(infoLen);
				if (static_cast<int>(buf.size()) >= infoLen)
				{
					glGetShaderInfoLog(shader, infoLen, NULL, buf.data());
					std::cerr << "ERROR: �V�F�[�_�[�̃R���p�C���Ɏ��s.\n" << buf.data() << std::endl;
				}
			}
			//�G���[���������ꍇ�̓V�F�[�_�[�E�I�u�W�F�N�g���폜
			glDeleteShader(shader);
			return 0;
		}
		return shader;
	}

	/*
	�v���O�����E�I�u�W�F�N�g���쐬����

	@param vsCode ���_�V�F�[�_�[�E�v���O�����ւ̃|�C���^
	@param fsCode �t���O�����g�V�F�[�_�[�E�v���O�����ւ̃|�C���^

	@retval 0���傫��  �쐬�����v���O�����E�I�u�W�F�N�g
	@retval 0            �v���O�����E�I�u�W�F�N�g�̍쐬�Ɏ��s
	*/

	GLuint Build(const GLchar* vsCode, const GLchar* fsCode)
	{
		//�V�F�[�_�[�E�v���O��������V�F�[�_�[�E�I�u�W�F�N�g���쐬
		GLuint vs = Compile(GL_VERTEX_SHADER, vsCode);
		GLuint fs = Compile(GL_FRAGMENT_SHADER, fsCode);
		if (!vs || !fs)
		{
			return 0;
		}
		//�V�F�[�_�[�E�v���O�������쐬���Ă���
		GLuint program = glCreateProgram();
		//�V�F�[�_�[�E�I�u�W�F�N�g���V�F�[�_�[�E�v���O�����Ɋ��蓖�ĂĂ���
		glAttachShader(program, fs);
		glDeleteShader(fs);
		glAttachShader(program, vs);
		glDeleteShader(vs);
		//���蓖�Ă��V�F�[�_�[�E�v���O�������m�������N���Ă���
		glLinkProgram(program);
		GLint linkStatus = GL_FALSE;
		//�����N���ʂ��擾���Ă���
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE)
		{
			GLint infoLen = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen)
			{
				std::vector<char> buf;
				buf.resize(infoLen);
				if (static_cast<int>(buf.size()) >= infoLen)
				{
					glGetProgramInfoLog(program, infoLen, NULL, buf.data());
					std::cerr << "ERROR: �V�F�[�_�[�̃����N�Ɏ��s.\n" << buf.data() << std::endl;
				}
			}
			glDeleteShader(program);
			return 0;
		}
		return program;
	}

	/*
	�t�@�C����ǂݍ���

	@param path �ǂݍ��ރt�@�C����

	@retrun �ǂݍ��񂾃f�[�^
	*/
	std::vector<GLchar> ReadFile(const char* path)
	{
		std::basic_ifstream<GLchar> ifs;
		ifs.open(path, std::ios_base::binary);
		if (!ifs.is_open())
		{
			std::cerr << "ERROR : " << path << " ���J���܂���.\n";
			return{};
		}
		ifs.seekg(0, std::ios_base::end);
		const size_t length = (size_t)ifs.tellg();
		ifs.seekg(0, std::ios_base::beg);
		std::vector<GLchar> buf(length);
		ifs.read(buf.data(), length);
		buf.push_back('\0'); //�Ō��'\0'�����Ȃ���΂Ȃ�Ȃ�
		return buf;
	}

	/*
	�t�@�C������v���O�����E�I�u�W�F�N�g���쐬����

	@param vsPath ���_�f�[�^�E�t�@�C����
	@param fsPath �t���O�����g�V�F�[�_�[�E�t�@�C����

	@retrun �쐬�����v���O�����E�I�u�W�F�N�g
	*/
	GLuint BuildFromFile(const char* vsPath, const char* fsPath)
	{
		const std::vector<GLchar> vsCode = ReadFile(vsPath);
		const std::vector<GLchar> fsCode = ReadFile(fsPath);
		return Build(vsCode.data(), fsCode.data());
	}

	/*
	���C�g���X�g������������

	�S�Ă̖��邳��0�ɂ���
	*/
	void LightList::Init()
	{
		ambient.color = glm::vec3(0);
		directional.color = glm::vec3(0);
		for (int i = 0; i < 8; i++)
		{
			point.color[i] = glm::vec3(0);
		}
		for (int i = 0; i < 4; i++)
		{
			spot.color[i] = glm::vec3(0);
		}
	}

	/*
	�R���X�g���N�^
	*/
	Program::Program()
	{
		lights.Init();
	}

	/*
	�R���X�g���N�^

	@param programId �v���O�����E�I�u�W�F�N�g��ID
	*/
	Program::Program(GLuint programId):id(programId)
	{
		lights.Init();
		Reset(programId);
	}

	/*
	�f�X�g���N�^

	�v���O�����E�I�u�W�F�N�g���폜����
	*/
	Program::~Program()
	{
		if (id)
		{
			glDeleteProgram(id);
		}
	}

	/*
	�v���O�����E�I�u�W�F�N�g��ݒ肷��

	@param id �v���O�����E�I�u�W�F�N�g��ID
	*/
	void Program::Reset(GLuint programId)
	{
		glDeleteProgram(id);
		id = programId;
		if (id == 0)
		{
			locMatMVP = -1;
			locAmbLightCol = -1;
			locDirLightDir = -1;
			locDirLightCol = -1;
			locPointLightPos = -1;
			locPointLightCol = -1;
			locSpotLightDir = -1;
			locSpotLightPos = -1;
			locSpotLightCol = -1;
			return;
		}

		locMatMVP = glGetUniformLocation(id, "matMVP");
		locAmbLightCol = glGetUniformLocation(id, "ambientLight.color");
		locDirLightDir = glGetUniformLocation(id, "directionalLight.direction");
		locDirLightCol = glGetUniformLocation(id, "directionalLight.color");
		locPointLightPos = glGetUniformLocation(id, "pointLight.position");
		locPointLightCol = glGetUniformLocation(id, "pointLight.color");
		locSpotLightDir = glGetUniformLocation(id, "spotLight.direction");
		locSpotLightPos = glGetUniformLocation(id, "spotLight.posAndInnerCutOff");
		locSpotLightCol = glGetUniformLocation(id, "spotLight.color");
		

		const GLint texColorLoc = glGetUniformLocation(id, "texColor");
		if (texColorLoc >= 0)
		{
			glUseProgram(id);
			glUniform1i(texColorLoc, 0);
			glUseProgram(0);
		}
	}

	/*
	�v���O�����E�I�u�W�F�N�g���O���t�B�b�N�E�p�C�v���C���Ɋ��蓖�Ă�
	*/
	void Program::Use()
	{
		if (id)
		{
			glUseProgram(id);
		}
	}

	/*
	�`��Ɏg�p����e�N�X�`����ݒ肷��

	@param unitNo �ݒ肷��e�N�X�`���E�C���[�W�E���j�b�g�̔ԍ�(0�`)
	@param texId  �ݒ肷��e�N�X�`��ID
	*/
	void Program::BindTexture(GLuint unitNo, GLuint texId)
	{
		glActiveTexture(GL_TEXTURE0 + unitNo);
		glBindTexture(GL_TEXTURE_2D, texId);
	}

	/*
	�`��Ɏg���郉�C�g��ݒ肷��

	@param light �ݒ肷��
	*/
	void Program::SetLightList(const LightList& lights)
	{
		this->lights = lights;

		//���C�g�̐F����GPU�������ɓ]������
		if (locAmbLightCol >= 0)
		{
			glUniform3fv(locAmbLightCol, 1, &lights.ambient.color.x);
		}
		if (locDirLightCol >= 0)
		{
			glUniform3fv(locDirLightCol, 1, &lights.directional.color.x);
		}
		if (locPointLightCol >= 0)
		{
			glUniform3fv(locPointLightCol, 8, &lights.point.color[0].x);
		}
		if (locSpotLightCol >= 0)
		{
			glUniform3fv(locSpotLightCol, 4, &lights.spot.color[0].x);
		}
	}

	/*
	�`��Ɏg����r���[�E�v���W�F�N�V�����s���ݒ肷��

	@param matVP �ݒ肷��r���[�E�v���W�F�N�V�����s��
	*/
	void Program::SetViewProjectionMatrix(const glm::mat4& matVP)
	{
		this->matVP = matVP;
	}

	/*
	���b�V����`�悷��

	@param mesh �`�悷�郁�b�V��
	@param translate ���s�ړ���
	@param rotate ��]�p�x(���W�A��)
	@param scale �g��k����(1 =���{ , 0.5 = 1/2�{, 2.0 = 2�{)
	
	���̊֐����g���O�ɁAUse()�����s���Ă�������
	*/
	void Program::Draw(const Mesh& mesh,
		const glm::vec3& translate, const glm::vec3& rotate, const glm::vec3& scale)
	{
		if (id == 0)
		{
			return;
		}

		//���f���s����v�Z����
		const glm::mat4 matScale = glm::scale(glm::mat4(1), scale);
		const glm::mat4 matRotateY = glm::rotate(glm::mat4(1), rotate.y, glm::vec3(0, 1, 0));
		const glm::mat4 matRotateZY = glm::rotate(matRotateY, rotate.z, glm::vec3(0, 0, -1));
		const glm::mat4 matRotateXZY = glm::rotate(matRotateZY, rotate.x, glm::vec3(1, 0, 0));
		const glm::mat4 matTranslate = glm::translate(glm::mat4(1), translate);
		const glm::mat4 matModelTR = matTranslate * matRotateXZY;
		const glm::mat4 matModel = matModelTR * matScale;

		//���f���E�r���[�E�v���W�F�N�V�����s����v�Z���AGPU�������ɓ]������
		const glm::mat4 matMVP = matVP * matModel;
		//�V�F�[�_�[�ɕϊ��s���]�����Ă���
		/*
		�����P�E�E�E�]�����uniform�ϐ��̈ʒu
		�����Q�E�E�E�]������f�[�^�̐�
		�����R�E�E�E�s���]�u���邩�ǂ������w�肷��
		�����S�E�E�E�]������f�[�^�̃|�C���^(�s��̍ŏ��̗v�f�ւ̃|�C���^��n���Ă���)
		*/
		glUniformMatrix4fv(locMatMVP, 1, GL_FALSE, &matMVP[0][0]);

		//�w�������C�g�̌��������f�����W�n�ɕϊ�����GPU�������ɓ]������
		const glm::mat3 matInvRotate = glm::inverse(glm::mat3(matRotateXZY));
		if (locDirLightDir >= 0)
		{
			const glm::vec3 dirLightDirOnModel = matInvRotate * lights.directional.direction;
			glUniform3fv(locDirLightDir, 1, &dirLightDirOnModel.x);
		}

		//�|�C���g���C�g�̈ʒu�����f�����W�n�ɕϊ�����GPU�������ɓ]������
		const glm::mat4 matInvModel = glm::inverse(matModelTR);
		glm::vec3 pointLightPosOnModel[8];
		for (int i = 0; i < 8; i++)
		{
			pointLightPosOnModel[i] = matInvModel * glm::vec4(lights.point.position[i], 1);
		}
		glUniform3fv(locPointLightPos, 8, &pointLightPosOnModel[0].x);

		//�X�|�b�g���C�g�̈ʒu�����f�����W�n�ɕϊ�����GPU�������ɓ]������
		if (locSpotLightDir >= 0 && locSpotLightPos)
		{
			glm::vec4 spotLightDirOnModel[4];
			glm::vec4 spotLightPosOnModel[4];
			for (int i = 0; i < 4; i++)
			{
				const glm::vec3 invDir = matInvRotate * glm::vec3(lights.spot.dirAndCutoff[i]);
				spotLightDirOnModel[i] = glm::vec4(invDir, lights.spot.dirAndCutoff[i].w);
				const glm::vec3 pos = glm::vec3(lights.spot.posAndInnerCutOff[i]);
				spotLightPosOnModel[i] = matInvModel * glm::vec4(pos, 1);
				spotLightPosOnModel[i].w = lights.spot.posAndInnerCutOff[i].w;
			}
			glUniform4fv(locSpotLightDir, 4, &spotLightDirOnModel[0].x);
			glUniform4fv(locSpotLightPos, 4, &spotLightPosOnModel[0].x);
		}

		//���b�V����`�悷��
		/*
		�����P�E�E�E�v���~�e�B�u�̎�ނ��w�肷��
		�����Q�E�E�E�`�悷��C���f�b�N�X�̐�
		�����R�E�E�E�C���f�b�N�X�f�[�^�̌^���w�肷��
		�����S�E�E�E�C���f�b�N�X�f�[�^�̕`��J�n�I�t�Z�b�g��
		�@�@�@�@�@�@�C���f�b�N�X�f�[�^�̐擪����̃o�C�g�����w�肷��
		�����T�E�E�E�u�C���f�b�N�X��0�ԂƂ݂Ȃ����_�f�[�^�̈ʒu�v��ݒ肷��
		*/
		glDrawElementsBaseVertex(
		mesh.mode, mesh.count, GL_UNSIGNED_SHORT, mesh.indices, mesh.baseVertex);
	}
}
//Shader namespace