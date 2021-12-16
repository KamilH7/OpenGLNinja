#ifndef GAME_H
#define GAME_H

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"

#pragma once
class Game
{
	public:
		Game(ShaderProgram* shaderProgram);
		void Start();
		void Update();
		void Terminate();

	private:
		GLfloat vertices[];
		GLfloat vertices[]
		const char* popCatPath = "Resources/pop_cat.png";
		ShaderProgram* shaderProgram;
		Texture* popCat;
		VAO* VAO1;
		VBO* VBO1;
		EBO* EBO1;
};
#endif