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
Vertex Buffer Objectを作成する

＊頂点データを格納するオブジェクト

@param size 頂点データのサイズ
@param data 頂点データへのポインタ

@retrun 作成したVBO
*/
GLuint CreateVBO(GLsizeiptr size, const GLvoid* data)
{
	GLuint vbo = 0;
	/*
	OpenGLが管理するメモリ領域を管理するオブジェクトを作成する関数
	引数１：作成するバッファ・オブジェクトの個数
	引数２：作成したバッファ・オブジェクトを格納する変数のポインタ
	*/
	glGenBuffers(1, &vbo);
	//バッファ・オブジェクトを特定の用途に割り当てる
	//引数は頂点データ用バッファに指定している
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//バッファ・オブジェクトにデータを転送する
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	//引数に0を渡して割り当てを解除している
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vbo;
}

/*
Index Buffer Objectを作成する

*インデックスデータを格納するオブジェクト

@param size インデックスデータのサイズ
@param data インデックスデータへのポインタ

@return 作成したIBO
*/
GLuint CreateIBO(GLsizeiptr size, const GLvoid* data)
{
	GLuint ibo = 0;
	//OpenGLが管理する領域を管理するオブジェクトを作成する関数
	glGenBuffers(1, &ibo);
	//バッファ・オブジェクトを特定の用途に割り当てる
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//バッファ・オブジェクトにデータを転送する
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	//割り当てを解除している
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return ibo;
}


/*
Vertex Array Objectを作成する

*どの頂点アトリビュートをバインディング・ポイントに結びつけるかを
 自由に設定するためのオブジェクト

@param vbo VAOに関連付けられるVBO
@param ibo VAOに関連付けられるIBO

@retrun 作成したVAO

*/

GLuint CreateVAO(GLuint vbo, GLuint ibo)
{
	GLuint vao = 0;
	//VAOを作成している
	glGenVertexArrays(1, &vao);
	//指定されたVAOをOpenGLの「現在の処理対象」に設定している
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//指定されたバインディング・ポイントを有効にする
	glEnableVertexAttribArray(0);
	//頂点アトリビュートをバインディング・ポイントに割り当てる
	/*
	引数１...バインディング・ポイントの引数
	引数２...情報の要素数
	引数３...情報の型
	引数４...情報を正規化するかどうか
	引数５...頂点データのバイト数
	引数６...「情報が頂点データの先頭から何バイト目にあるか」を設定している
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
	//引数を「0」にして、VAOのバインドを解除している
	glBindVertexArray(0);
	//VBOを削除している
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	return vao;
}

/*
コンストラクタ
*/
MeshList::MeshList()
{

}

/*
デストラクタ
*/
MeshList::~MeshList()
{
	Free();
}

/*
Meshを追加する

@param vBegin 追加する頂点データ配列の先端
@param vEnd   追加する頂点データ配列の終端
@param iBegin 追加するインデックスデータ配列の先端
@param iEnd   追加するインデックスデータ配列の終端
*/
void MeshList::Add(const Vertex* vBegin, const Vertex* vEnd,
	const GLushort* iBegin, const GLushort* iEnd)
{
	//メッシュの追加
	Mesh m;
	m.mode = GL_TRIANGLES;
	m.count = iEnd - iBegin;
	m.indices = (const GLvoid*)(tmpIndices.size() * sizeof(GLushort));
	m.baseVertex = (GLint)tmpVertices.size();
	meshes.push_back(m);

	//モデルのデータをvectorにコピー
	tmpVertices.insert(tmpVertices.end(), vBegin, vEnd);
	tmpIndices.insert(tmpIndices.end(), iBegin, iEnd);
}

/*
OBJファイルからメッシュを読み込む

@param path 読み込むOBJファイル名

@retval true  読み込み成功
@retval false 読み込み失敗
*/
bool MeshList::AddFromObjFile(const char* path)
{
	//ファイル開く
	std::ifstream ifs;
	ifs.open(path, std::ios::binary);
	if (!ifs.is_open())
	{
		std::cerr << "ERROR : " << path << "を開けません\n";
		return false;
	}

	//データ読み取り用の変数を準備
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

	//ファイルからモデルのデータを読み込む
	while (!ifs.eof())
	{
		std::string line;
		getline(ifs, line);

		//読み取り処理用の変数を定義する
		Vector3 v;
		Vector2 vt;
		Vector3 vn;
		Face f[3];

		//データを文字に対応する変数に対応する
		//sscanf_sは[string scan format secure]の略
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

	//データ不足の場合は作成中止
	if (positionList.empty())
	{
		std::cerr << "WARNING: " << path << "には頂点座標の定義がありません.\n";
		positionList.push_back({0, 0, 0});
	}
	if (texCoordList.empty())
	{
		std::cerr << "WARNING: " << path << "にはテクスチャ座標の定義がありません.\n";
		texCoordList.push_back({0, 0});
	}
	if (normalList.empty())
	{
		std::cerr << "WARNING: " << path << "には法線の定義がありません.\n";
		normalList.push_back({ 0, 0, 0 });
	}

	//頂点データとインデックスデータ用の変数を準備
	std::vector<Vertex> vertices;
	std::vector<GLushort> indices;
	std::vector<Face> faceToVertexList;
	vertices.reserve(faceList.size());
	indices.reserve(faceList.size());
	faceToVertexList.reserve(faceList.size());

	//モデルのデータを頂点データをインデックスデータに変換する
	for (size_t i = 0; i < faceList.size(); i++)
	{
		//重複する頂点データがあるか調べる
		size_t n = 0;

		for (; n < faceToVertexList.size(); n++)
		{
			if (faceToVertexList[n].v == faceList[i].v &&
				faceToVertexList[n].vt == faceList[i].vt &&
				faceToVertexList[n].vn == faceList[i].vn)
			{
				// 重複する頂点データを見つけた
				break;
			}
		}

		if (n < faceToVertexList.size())
		{
			//重複する頂点データが見つかったら、見つかった頂点データのインデックスを追加する
			indices.push_back((GLushort)n);
		}
		else
		{
			//重複する頂点データが見つからなければ、新しい頂点データを作成し、そのインデックスを追加する
			indices.push_back((GLushort)vertices.size());

			//面データを追加する
			faceToVertexList.push_back(faceList[i]);

			//頂点データを追加する
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
		"[頂点数=" << vertices.size() << "インデックス数=" << indices.size() << "]\n";

	Add(vertices.data(), vertices.data() + vertices.size(),
		indices.data(), indices.data() + indices.size());

	return true;
}

/*
モデルデータからMeshのリストを作成する

@retval true  作成成功
@retval false 作成失敗
*/
bool MeshList::Allocate()
{
	//容量を予約
	meshes.reserve(100);
	tmpVertices.reserve(10'000);
	tmpIndices.reserve(10'000);

	//メッシュを追加
	AddFromObjFile("Res/obj/Human.obj");
	AddFromObjFile("Res/obj/Ground.obj");
	AddFromObjFile("Res/obj/Plane.obj");
	AddFromObjFile("Res/obj/Bullet2.obj");
	AddFromObjFile("Res/obj/Zombie.obj");

	//VAOを作成する
	GLuint vbo = CreateVBO(tmpVertices.size() * sizeof(Vertex), tmpVertices.data());
	GLuint ibo = CreateIBO(tmpIndices.size() * sizeof(GLushort), tmpIndices.data());
	vao = CreateVAO(vbo, ibo);

	//vectorのメモリを開放する
	std::vector<Vertex>().swap(tmpVertices);
	std::vector<GLushort>().swap(tmpIndices);

	if (!vbo || !ibo || !vao)
	{
		std::cerr << "ERROR : VAOの作成に失敗\n";
		return false;
	}
	return true;
}

/*
メッシュリストを破棄する
*/
void MeshList::Free()
{
	glDeleteVertexArrays(1, &vao);
	vao = 0;
	std::vector<Mesh>().swap(meshes);
}

/*
描画に使用するVAOを設定する
*/
void MeshList::BindVertexArray()
{
	glBindVertexArray(vao);
}

/*
メッシュを取得する

@param index 取得するメッシュの番号

@retrun index 番目のメッシュ
*/
const Mesh& MeshList::Get(size_t index) const
{
	return meshes[index];
}