//
// Project: fug
// File: VS_Sprite.glsl
//
// Copyright (c) 2021 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#version 420


layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 vPosition;
out vec2 vTexCoord;

uniform int windowWidth;
uniform int windowHeight;


void main() {
    vPosition = vec2(2.0*position.x/windowWidth - 1.0, 1.0 - 2.0*position.y/windowHeight);
    vTexCoord = texCoord;

    gl_Position = vec4(vPosition, 0.0, 1.0);
}