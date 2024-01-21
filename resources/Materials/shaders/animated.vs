attribute vec2 w4_a_uv0;

uniform float countX;
uniform float countY;
uniform float frameNum;

varying vec2 vTexCoord;

void w4_main()
{
    gl_Position = w4_u_projectionView * w4_getVertexPosition();

    float frameX = min(mod(frameNum, countX), countX - 1.0);
    float frameY = floor(frameNum / countX);

    vTexCoord.x = (frameX + w4_a_uv0.x) / countX;
    vTexCoord.y = 1. -(frameY + w4_a_uv0.y) / countY;
}
