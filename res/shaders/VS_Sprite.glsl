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
layout(location = 2) in vec3 color;

out vec2 vPosition;
out vec2 vTexCoord;
out vec3 vColor;

uniform int windowWidth;
uniform int windowHeight;

uniform mat3 viewport;


void main() {
    vec3 p = viewport * vec3(position, 1.0);
    vPosition = vec2(
        2.0*p.x/windowWidth - 1.0,
        1.0 - 2.0*p.y/windowHeight);
    vTexCoord = texCoord;
    vColor = color;

    gl_Position = vec4(vPosition, 0.0, 1.0);
}
