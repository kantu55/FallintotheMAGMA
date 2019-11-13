/*
@file MeshList.cpp
*/
#include "MeshList.h"
#include <fstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <iostream>

const Vertex vTree[] =
{
	{ { 0.00f, 5.0f,  0.00f },{ 0.5f, 0.8f, 0.3f, 1.0f },{ 0.0f,  1.0f },{ 0.00f, 1.0f,  0.00f } },
	{ { 0.00f, 1.5f, -1.10f },{ 0.1f, 0.3f, 0.0f, 1.0f },{ 0.0f,  0.0f },{ 0.00f, -0.49f, -0.87f } },
	{ { -0.75f, 1.5f,  0.40f },{ 0.1f, 0.3f, 0.0f, 1.0f },{ 0.0f,  0.0f },{ -0.76f, -0.49f, 0.43f } },
	{ { 0.75f, 1.5f,  0.40f },{ 0.1f, 0.3f, 0.0f, 1.0f },{ 0.5f,  0.0f },{ 0.76f, -0.49f, 0.43f } },
	{ { 0.00f, 4.0f,  0.00f },{ 0.2f, 0.1f, 0.0f, 1.0f },{ 1.0f,  1.0f },{ 0.00f,  1.00f, 0.00f } },
	{ { 0.00f, 0.0f, -0.37f },{ 0.5f, 0.3f, 0.2f, 1.0f },{ 0.0f,  0.0f },{ 0.00f, -0.49f, -0.87f } },
	{ { -0.25f, 0.0f,  0.13f },{ 0.5f, 0.3f, 0.2f, 1.0f },{ 0.5f,  0.0f },{ -0.76f, -0.49f, 0.43f } },
	{ { 0.25f, 0.0f,  0.13f },{ 0.5f, 0.3f, 0.2f, 1.0f },{ 1.0f,  0.0f },{ 0.76f, -0.49f, 0.43f } },
};

const GLushort iTree[] =
{
	0,1,2,0,2,3,0,3,1,1,2,3,
	4,5,6,4,6,7,4,7,5,
};

const Vertex vHouse[] =
{
	//0
	{ { 2.8f, 0.0f, 3.0f },{ 0.4f, 0.3f, 0.2f, 1.0f },{ 1.000, 0.00f },{-0.71f, 0.00f, 0.71f}},
	//1
	{ { 3.0f, 4.0f, 3.0f },{ 0.6f, 0.5f, 0.3f, 1.0f },{ 1.000, 0.69f },{ -0.71f, 0.00f, 0.71f } },
	//2
	{ { 0.0f, 6.0f, 3.0f },{ 0.5f, 0.4f, 0.2f, 1.0f },{ 0.875f, 1.00f },{ 0.00f, 0.71f, 0.71f} },
	//3
	{ { -3.0f, 4.0f, 3.0f },{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.750f, 0.69f },{  0.71f, 0.00f, 0.71f } },
	//4
	{ { -2.8f, 0.0f, 3.0f },{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.750f, 0.00f },{  0.71f, 0.00f, 0.71f} },
	//5
	{ { -2.8f, 0.0f, -3.0f },{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.500f, 0.00f },{  0.71f, 0.00f, -0.71f } },
	//6
	{ { -3.0f, 4.0f, -3.0f },{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.500f, 0.69f },{  0.71f, 0.00f, -0.71f } },
	//7
	{ { 0.0f, 6.0f, -3.0f },{ 0.5f, 0.4f, 0.2f, 1.0f },{ 0.375f, 1.00f },{  0.00f, 0.71f, -0.71f } },
	//8
	{ { 3.0f, 4.0f, -3.0f },{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.250f, 0.69f },{ -0.71f, 0.00f, -0.71f } },
	//9
	{ { 2.8f, 0.0f, -3.0f },{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.250f, 0.00f },{ -0.71f, 0.00f, -0.71f } },
	//10
	{ { 2.8f, 0.0f,  3.0f },{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.000f, 0.00f } },
	//11
	{ { 3.0f, 4.0f,  3.0f },{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.000f, 0.69f } },
	//12
	{ { 0.0f, 6.0f,  3.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.750f, 1.00f } },
	//13
	{ { 0.0f, 6.0f, -3.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.500f, 1.00f } },
	//14
	{ { 0.0f, 6.0f, -3.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.250f, 1.00f } },
	//15
	{ { 0.0f, 6.0f,  3.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.000f, 1.00f } },

};

const GLushort iHouse[] =
{
	0,1,3,3,4,0,1,2,3,
	5,6,8,8,9,5,6,7,8,
	9,8,11,11,10,9,
	4,3,6,6,5,4,
	3,12,13,13,6,3,
	8,14,15,15,11,8,
};

const Vertex vRock[] =
{
	{ { -1.0f, 3.0f,  1.5f },{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.0f,  2.0f } },
	{ { 1.0f, 3.0f,  1.5f },{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.0f,  2.0f } },
	{ { 3.0f, 0.0f,  1.5f },{ 0.5f, 0.4f, 0.2f, 1.0f },{ 0.0f,  2.0f } },
	{ { -3.0f, 0.0f,  1.5f },{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.0f,  2.0f } },
	
	{ { 1.0f, 3.0f, -1.5f },{ 0.4f, 0.3f, 0.2f, 1.0f },{ 0.0f,  2.0f } },
	{ { 3.0f, 0.0f, -1.5f },{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.0f,  2.0f } },
	{ { -1.0f, 3.0f, -1.5f },{ 0.5f, 0.4f, 0.2f, 1.0f },{ 0.0f,  2.0f } },
	{ { -3.0f, 0.0f, -1.5f },{ 0.6f, 0.5f, 0.3f, 1.0f },{ 0.0f,  2.0f } },

};

const GLushort iRock[] =
{
	3, 2, 1, 1, 0, 3,
	6, 4, 5, 5, 7, 6,
	0, 1, 4, 4, 6, 0,
	6, 7, 0, 7, 3, 0,
	1, 2, 5, 5, 4, 1,
};

const Vertex vGround[] =
{
	{ { -20.0f, 0.0f, 20.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { -10.0f, 0.0f, 20.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 0.0f, 0.0f, 20.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 10.0f, 0.0f, 20.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 20.0f, 0.0f, 20.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	
	
	
	{ { -20.0f, 0.0f, 10.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { -10.0f, 0.0f, 10.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 0.0f, 0.0f, 10.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 10.0f, 0.0f, 10.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 20.0f, 0.0f, 10.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	
	{ { -20.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { -10.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 0.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 10.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 20.0f, 0.0f, 0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	
	{ { -20.0f, 0.0f, -10.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { -10.0f, 0.0f, -10.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 0.0f, 0.0f, -10.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 10.0f, 0.0f, -10.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 20.0f, 0.0f, -10.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	
	{ { -20.0f, 0.0f, -20.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { -10.0f, 0.1f, -20.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 0.0f, 0.0f, -20.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 10.0f, 0.0f, -20.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
	{ { 20.0f, 0.0f, -20.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f,  2.0f },
	{ 0.00f, 1.0f,  0.00f } },
};

const GLushort iGround[] =
{
	0,1,6,6,5,0,
	1,2,7,7,6,1,
	2,3,8,8,7,2,
	3,4,9,9,8,3,

	5,6,11,11,10,5,
	6,7,12,12,11,6,
	7,8,13,13,12,7,
	8,9,14,14,13,8,

	10,11,16,16,15,10,
	11,12,17,17,16,11,
	12,13,18,18,17,12,
	13,14,19,19,18,13,

	15,16,21,21,22,15,
	16,17,22,22,21,16,
	17,18,23,23,22,17,
	18,19,24,24,23,18,
};

/*
Vertex Buffer Object���쐬����

�����_�f�[�^���i�[����I�u�W�F�N�g

@param size ���_�f�[�^�̃T�C�Y
@param data ���_�f�[�^�ւ̃|�C���^

@retrun �쐬����VBO
*/
GLuint CreateVBO(GLsizeiptr size, const GLvoid* data)
{
	GLuint vbo = 0;
	/*
	OpenGL���Ǘ����郁�����̈���Ǘ�����I�u�W�F�N�g���쐬����֐�
	�����P�F�쐬����o�b�t�@�E�I�u�W�F�N�g�̌�
	�����Q�F�쐬�����o�b�t�@�E�I�u�W�F�N�g���i�[����ϐ��̃|�C���^
	*/
	glGenBuffers(1, &vbo);
	//�o�b�t�@�E�I�u�W�F�N�g�����̗p�r�Ɋ��蓖�Ă�
	//�����͒��_�f�[�^�p�o�b�t�@�Ɏw�肵�Ă���
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//�o�b�t�@�E�I�u�W�F�N�g�Ƀf�[�^��]������
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	//������0��n���Ċ��蓖�Ă��������Ă���
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vbo;
}

/*
Index Buffer Object���쐬����

*�C���f�b�N�X�f�[�^���i�[����I�u�W�F�N�g

@param size �C���f�b�N�X�f�[�^�̃T�C�Y
@param data �C���f�b�N�X�f�[�^�ւ̃|�C���^

@return �쐬����IBO
*/
GLuint CreateIBO(GLsizeiptr size, const GLvoid* data)
{
	GLuint ibo = 0;
	//OpenGL���Ǘ�����̈���Ǘ�����I�u�W�F�N�g���쐬����֐�
	glGenBuffers(1, &ibo);
	//�o�b�t�@�E�I�u�W�F�N�g�����̗p�r�Ɋ��蓖�Ă�
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//�o�b�t�@�E�I�u�W�F�N�g�Ƀf�[�^��]������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	//���蓖�Ă��������Ă���
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return ibo;
}


/*
Vertex Array Object���쐬����

*�ǂ̒��_�A�g���r���[�g���o�C���f�B���O�E�|�C���g�Ɍ��т��邩��
 ���R�ɐݒ肷�邽�߂̃I�u�W�F�N�g

@param vbo VAO�Ɋ֘A�t������VBO
@param ibo VAO�Ɋ֘A�t������IBO

@retrun �쐬����VAO

*/

GLuint CreateVAO(GLuint vbo, GLuint ibo)
{
	GLuint vao = 0;
	//VAO���쐬���Ă���
	glGenVertexArrays(1, &vao);
	//�w�肳�ꂽVAO��OpenGL�́u���݂̏����Ώہv�ɐݒ肵�Ă���
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//�w�肳�ꂽ�o�C���f�B���O�E�|�C���g��L���ɂ���
	glEnableVertexAttribArray(0);
	//���_�A�g���r���[�g���o�C���f�B���O�E�|�C���g�Ɋ��蓖�Ă�
	/*
	�����P...�o�C���f�B���O�E�|�C���g�̈���
	�����Q...���̗v�f��
	�����R...���̌^
	�����S...���𐳋K�����邩�ǂ���
	�����T...���_�f�[�^�̃o�C�g��
	�����U...�u��񂪒��_�f�[�^�̐擪���牽�o�C�g�ڂɂ��邩�v��ݒ肵�Ă���
	*/
	glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(Vertex::texCoord) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, texCoord)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, sizeof(Vertex::normal) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, normal)));
	//�������u0�v�ɂ��āAVAO�̃o�C���h���������Ă���
	glBindVertexArray(0);
	//VBO���폜���Ă���
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	return vao;
}

/*
�R���X�g���N�^
*/
MeshList::MeshList()
{

}

/*
�f�X�g���N�^
*/
MeshList::~MeshList()
{
	Free();
}

/*
Mesh��ǉ�����

@param vBegin �ǉ����钸�_�f�[�^�z��̐�[
@param vEnd   �ǉ����钸�_�f�[�^�z��̏I�[
@param iBegin �ǉ�����C���f�b�N�X�f�[�^�z��̐�[
@param iEnd   �ǉ�����C���f�b�N�X�f�[�^�z��̏I�[
*/
void MeshList::Add(const Vertex* vBegin, const Vertex* vEnd,
	const GLushort* iBegin, const GLushort* iEnd)
{
	//���b�V���̒ǉ�
	Mesh m;
	m.mode = GL_TRIANGLES;
	m.count = iEnd - iBegin;
	m.indices = (const GLvoid*)(tmpIndices.size() * sizeof(GLushort));
	m.baseVertex = (GLint)tmpVertices.size();
	meshes.push_back(m);

	//���f���̃f�[�^��vector�ɃR�s�[
	tmpVertices.insert(tmpVertices.end(), vBegin, vEnd);
	tmpIndices.insert(tmpIndices.end(), iBegin, iEnd);
}

/*
OBJ�t�@�C�����烁�b�V����ǂݍ���

@param path �ǂݍ���OBJ�t�@�C����

@retval true  �ǂݍ��ݐ���
@retval false �ǂݍ��ݎ��s
*/
bool MeshList::AddFromObjFile(const char* path)
{
	//�t�@�C���J��
	std::ifstream ifs;
	ifs.open(path, std::ios::binary);
	if (!ifs.is_open())
	{
		std::cerr << "ERROR : " << path << "���J���܂���\n";
		return false;
	}

	//�f�[�^�ǂݎ��p�̕ϐ�������
	struct Face
	{
		int v;
		int vt;
		int vn;
	};
	std::vector<Face> faceList;
	std::vector<Vector3> positionList;
	std::vector<Vector2> texCoordList;
	std::vector<Vector3> normalList;
	faceList.reserve(1000);
	positionList.reserve(1000);
	texCoordList.reserve(1000);
	normalList.reserve(1000);

	//�t�@�C�����烂�f���̃f�[�^��ǂݍ���
	while (!ifs.eof())
	{
		std::string line;
		getline(ifs, line);

		//�ǂݎ�菈���p�̕ϐ����`����
		Vector3 v;
		Vector2 vt;
		Vector3 vn;
		Face f[3];

		//�f�[�^�𕶎��ɑΉ�����ϐ��ɑΉ�����
		//sscanf_s��[string scan format secure]�̗�
		if (sscanf_s(line.data(), "v %f %f %f", &v.x, &v.y, &v.z) == 3)
		{
			positionList.push_back(v);
		}
		else if (sscanf_s(line.data(), "vt %f %f", &vt.x, &vt.y) == 2)
		{
			texCoordList.push_back(vt);
		}
		else if (sscanf_s(line.data(), "vn %f %f %f", &vn.x, &vn.y, &vn.z) == 3)
		{
			const float length = sqrt(vn.x * vn.x + vn.y * vn.y + vn.z * vn.z);
			vn.x /= length;
			vn.y /= length;
			vn.z /= length;
			normalList.push_back(vn);
		}
		else if (sscanf_s(line.data(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
			&f[0].v, &f[0].vt, &f[0].vn,
			&f[1].v, &f[1].vt, &f[1].vn,
			&f[2].v, &f[2].vt, &f[2].vn) == 9)
		{
			faceList.push_back(f[0]);
			faceList.push_back(f[1]);
			faceList.push_back(f[2]);
		}
	}

	//�f�[�^�s���̏ꍇ�͍쐬���~
	if (positionList.empty())
	{
		std::cerr << "WARNING: " << path << "�ɂ͒��_���W�̒�`������܂���.\n";
		positionList.push_back({0, 0, 0});
	}
	if (texCoordList.empty())
	{
		std::cerr << "WARNING: " << path << "�ɂ̓e�N�X�`�����W�̒�`������܂���.\n";
		texCoordList.push_back({0, 0});
	}
	if (normalList.empty())
	{
		std::cerr << "WARNING: " << path << "�ɂ͖@���̒�`������܂���.\n";
		normalList.push_back({ 0, 0, 0 });
	}

	//���_�f�[�^�ƃC���f�b�N�X�f�[�^�p�̕ϐ�������
	std::vector<Vertex> vertices;
	std::vector<GLushort> indices;
	std::vector<Face> faceToVertexList;
	vertices.reserve(faceList.size());
	indices.reserve(faceList.size());
	faceToVertexList.reserve(faceList.size());

	//���f���̃f�[�^�𒸓_�f�[�^���C���f�b�N�X�f�[�^�ɕϊ�����
	for (size_t i = 0; i < faceList.size(); i++)
	{
		//�d�����钸�_�f�[�^�����邩���ׂ�
		size_t n = 0;

		for (; n < faceToVertexList.size(); n++)
		{
			if (faceToVertexList[n].v == faceList[i].v &&
				faceToVertexList[n].vt == faceList[i].vt &&
				faceToVertexList[n].vn == faceList[i].vn)
			{
				// �d�����钸�_�f�[�^��������
				break;
			}
		}

		if (n < faceToVertexList.size())
		{
			//�d�����钸�_�f�[�^������������A�����������_�f�[�^�̃C���f�b�N�X��ǉ�����
			indices.push_back((GLushort)n);
		}
		else
		{
			//�d�����钸�_�f�[�^��������Ȃ���΁A�V�������_�f�[�^���쐬���A���̃C���f�b�N�X��ǉ�����
			indices.push_back((GLushort)vertices.size());

			//�ʃf�[�^��ǉ�����
			faceToVertexList.push_back(faceList[i]);

			//���_�f�[�^��ǉ�����
			Vertex vertex;
			Color color = { 1, 1, 1, 1 };
			int v = faceList[i].v - 1;
			if (v < 0 || v >= (int)positionList.size())
			{
				color = { 0.5f, 0, 0, 1 };
				v = 0;
			}
			int vt = faceList[i].vt - 1;
			if (vt < 0 || vt >= (int)texCoordList.size())
			{
				color = { 0.5f, 0, 0, 1 };
				vt = 0;
			}
			int vn = faceList[i].vn - 1;
			if (vn < 0 || vn >= (int)faceList.size())
			{
				color = { 0.5f, 0, 0, 1 };
				vn = 0;
			}
			vertex.position = positionList[v];
			vertex.color = color;
			vertex.texCoord = texCoordList[vt];
			vertex.normal = normalList[vn];
			vertices.push_back(vertex);
		}
	}

	std::cout << "INFO: " << path <<
		"[���_��=" << vertices.size() << "�C���f�b�N�X��=" << indices.size() << "]\n";

	Add(vertices.data(), vertices.data() + vertices.size(),
		indices.data(), indices.data() + indices.size());

	return true;
}

/*
���f���f�[�^����Mesh�̃��X�g���쐬����

@retval true  �쐬����
@retval false �쐬���s
*/
bool MeshList::Allocate()
{
	//�e�ʂ�\��
	meshes.reserve(100);
	tmpVertices.reserve(10'000);
	tmpIndices.reserve(10'000);

	//���b�V����ǉ�
	AddFromObjFile("Res/obj/Human.obj");
	AddFromObjFile("Res/obj/Ground.obj");
	AddFromObjFile("Res/obj/Plane.obj");
	AddFromObjFile("Res/obj/Bullet2.obj");
	AddFromObjFile("Res/obj/Zombie.obj");

	//VAO���쐬����
	GLuint vbo = CreateVBO(tmpVertices.size() * sizeof(Vertex), tmpVertices.data());
	GLuint ibo = CreateIBO(tmpIndices.size() * sizeof(GLushort), tmpIndices.data());
	vao = CreateVAO(vbo, ibo);

	//vector�̃��������J������
	std::vector<Vertex>().swap(tmpVertices);
	std::vector<GLushort>().swap(tmpIndices);

	if (!vbo || !ibo || !vao)
	{
		std::cerr << "ERROR : VAO�̍쐬�Ɏ��s\n";
		return false;
	}
	return true;
}

/*
���b�V�����X�g��j������
*/
void MeshList::Free()
{
	glDeleteVertexArrays(1, &vao);
	vao = 0;
	std::vector<Mesh>().swap(meshes);
}

/*
�`��Ɏg�p����VAO��ݒ肷��
*/
void MeshList::BindVertexArray()
{
	glBindVertexArray(vao);
}

/*
���b�V�����擾����

@param index �擾���郁�b�V���̔ԍ�

@retrun index �Ԗڂ̃��b�V��
*/
const Mesh& MeshList::Get(size_t index) const
{
	return meshes[index];
}