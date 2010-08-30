/*
 *  Shader.cpp
 *  RStation
 *
 *  Created by Colby Klein on 8/30/10.
 *  Copyright 2010 ssc. All rights reserved.
 *
 */

#include "Shader.h"

void Shader::Load(std::string _vs, std::string _fs)
{

}

void Shader::Load(GLuint _program)
{
	program = _program;
}

void Shader::Unload()
{

}

void Shader::Bind()
{

}

void Shader::Unbind()
{

}

GLuint Shader::GetProgram()
{
	return program;
}
