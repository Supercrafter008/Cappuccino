#!/bin/bash

echo "Assembling Shaders";

/d/WiiU/latte-assembler.exe assemble --vsh="./shaders/VertexShader.vsh" --psh="./shaders/TextureShader.psh" "./data/shaders/TextureShader.gsh"
/d/WiiU/latte-assembler.exe assemble --vsh="./shaders/VertexShader.vsh" --psh="./shaders/TextShader.psh" "./data/shaders/TextShader.gsh"
/d/WiiU/latte-assembler.exe assemble --vsh="./shaders/VertexShader.vsh" --psh="./shaders/ColorShader.psh" "./data/shaders/ColorShader.gsh"