#include "AIE.h"
#include "glm.hpp"
#include <iostream>

static glm::vec2 Lerp(glm::vec2 a_Start, glm::vec2 a_End, float t);
static glm::vec2 CubBezier(glm::vec2 a_P0, glm::vec2 a_P1, glm::vec2 a_P2, glm::vec2 a_P3, float t);

//constant vars
static int SCREEN_MAX_X = 900, SCREEN_MAX_Y = 600;

int main( int argc, char* argv[] )
{	
	Initialise(SCREEN_MAX_X, SCREEN_MAX_Y, false, "My Awesome Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	unsigned int point = CreateSprite("images/crate_sideup.png", 10, 10, true);
	glm::vec2 start = glm::vec2((SCREEN_MAX_X / 5) * 1, (SCREEN_MAX_Y / 4) * 1);
	glm::vec2 end = glm::vec2((SCREEN_MAX_X / 5) * 4, (SCREEN_MAX_Y / 4) * 2);
	glm::vec2 mid1 = glm::vec2((SCREEN_MAX_X / 5) * 2, (SCREEN_MAX_Y / 4) * 3);
	glm::vec2 mid2 = glm::vec2((SCREEN_MAX_X / 5) * 4, (SCREEN_MAX_Y / 4) * 3);
	glm::vec2 pos = glm::vec2();
	float t = 0;
    //Game Loop
    do
	{
        ClearScreen();

		if (t < 1) {
			t += GetDeltaTime() / 2;
		} else {
			t = 1;
		}

		pos = CubBezier(start, mid2, end, mid1, t);

		MoveSprite(point, pos.x, pos.y);
		DrawSprite(point);

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}

static glm::vec2 Lerp(glm::vec2 a_Start, glm::vec2 a_End, float t) {
	return (1 - t) * a_Start + t * a_End;
}

static glm::vec2 CubBezier(glm::vec2 a_P0, glm::vec2 a_P1, glm::vec2 a_P2, glm::vec2 a_P3, float t) {
	return Lerp(Lerp(a_P0, a_P1, t), Lerp(a_P2, a_P3, t), t);
}
