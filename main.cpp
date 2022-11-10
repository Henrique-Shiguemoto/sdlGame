#include "main.h"

//Globals
bool g_IsRunning{true};
Player g_Flower{};
Enemy g_Enemies[MAX_ENEMIES]{};
SDL_Window* g_Window{nullptr};
SDL_Surface* g_WindowSurface{nullptr};
SDL_Surface* g_BackgroundSurface{nullptr};

int main(int, char*[]){

	//Initializing SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Setting seed for pseudo random number generator
	srand(time(0));

	//Setting up window
	g_Window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
								windowWidth, windowHeight, 0);

	//Setting up player
	InitializeEntity(&g_Flower);

	//Setting up enemies
	for(int i = 0; i < MAX_ENEMIES; i++){
		InitializeEntity(&g_Enemies[i]);
	}

	//Setting up background
	g_BackgroundSurface = SDL_LoadBMP("assets/texture/background_1280x720.bmp");

	//Hiding the cursor
	SDL_ShowCursor(SDL_DISABLE);

	unsigned int numberOfFramesPassed = 0;

	const int frameDelay = 1000 / TARGET_FPS;
	unsigned int frameStart;
	int frameTime;
	unsigned int cumulativeFrameTime = 0;
	while(g_IsRunning){
		frameStart = SDL_GetTicks();
		
		ProcessInput();
		SimulateWorld();
		RenderGraphics();

		frameTime = SDL_GetTicks() - frameStart;
		cumulativeFrameTime += frameTime;
		std::cout << frameTime << " ms" << std::endl;
		
		if(frameDelay > frameTime){
			SDL_Delay(frameDelay - frameTime);
		}

		numberOfFramesPassed++;
		if(numberOfFramesPassed == 5*TARGET_FPS){
			g_IsRunning = false;
		}
	}

	//Showing frame time average
	std::cout << "Frame Time Average: " << cumulativeFrameTime / numberOfFramesPassed << " ms" << std::endl;

	//Freeing memory
	for(int i = 0; i < MAX_ENEMIES; i++){
		SDL_FreeSurface(g_Enemies[i].imageSurface);
	}
	SDL_FreeSurface(g_Flower.imageSurface);
	SDL_FreeSurface(g_WindowSurface);
	SDL_FreeSurface(g_BackgroundSurface);
	SDL_DestroyWindow(g_Window);
	SDL_Quit();
	return EXIT_SUCCESS;
}

void InitializeEntity(Player* p){
	p->rect = {windowWidth / 2.0f, windowHeight / 2.0f, (float)tileWidth, (float)tileHeight};
	p->imageSurface = SDL_LoadBMP("assets/texture/flower_64x64.bmp");
	p->speed = 2.0f;
}

void printEntityPosition(Player* p){
	std::cout << "(" << p->rect.x << ", " << p->rect.y << ")" << std::endl;
}

void InitializeEntity(Enemy* e){
	float speedScale = 0.01f;
	e->rect = {(float)(rand() % windowWidth), (float)(rand() % windowHeight), (float)tileWidth, (float)tileHeight};
	e->imageSurface = SDL_LoadBMP("assets/texture/bee_64x64.bmp");
	e->speedX = RandomSign()*speedScale*RandomInRange(5, 9);
	e->speedY = RandomSign()*speedScale*RandomInRange(5, 9);
}

void printEntityPosition(Enemy* e){
	std::cout << "(" << e->rect.x << ", " << e->rect.y << ")" << std::endl;
}

void ProcessInput(){
	SDL_Event event;
	while(SDL_PollEvent(&event) != 0){
		switch (event.type) {
			case SDL_QUIT: {
				g_IsRunning = false;
				break;
			}
			case SDL_KEYDOWN:{
				//Closing game with escape key
				if(event.key.keysym.sym == SDLK_ESCAPE){
					g_IsRunning = false;
				}
				break;
			}
			case SDL_MOUSEMOTION:{
				int x, y;
				SDL_GetMouseState(&x, &y);
				g_Flower.rect.x = x;
				g_Flower.rect.y = y;
				break;
			}
		}
	}
}

void SimulateWorld(){
	//Updating enemies
	for(int i = 0; i < MAX_ENEMIES; i++){
		//Update enemies positions
		g_Enemies[i].rect.x += g_Enemies[i].speedX;
		g_Enemies[i].rect.y += g_Enemies[i].speedY;
		
		//Checking boundaries, reflect speed
		if(g_Enemies[i].rect.x <= 0 || g_Enemies[i].rect.x > windowWidth - g_Enemies[i].rect.w){
			g_Enemies[i].speedX = (-1)*g_Enemies[i].speedX;
		}
		else if(g_Enemies[i].rect.y <= 0 || g_Enemies[i].rect.y > windowHeight - g_Enemies[i].rect.h){
			g_Enemies[i].speedY = (-1)*g_Enemies[i].speedY;
		}
	}

	//Checking if enemies touched the player (AABB)
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if(IsColliding(g_Enemies[i].rect, g_Flower.rect)){
			g_IsRunning = false;
			break;
		}
	}
}

void RenderGraphics(){
	//Getting window surface so we can blit stuff on it
	g_WindowSurface = SDL_GetWindowSurface(g_Window);

	//Blitting background
	SDL_BlitSurface(g_BackgroundSurface, NULL, g_WindowSurface, NULL);

	//Blitting enemies
	for(int i = 0; i < MAX_ENEMIES; i++){
		SDL_Rect auxRect = {(int)g_Enemies[i].rect.x, (int)g_Enemies[i].rect.y, (int)g_Enemies[i].rect.w, (int)g_Enemies[i].rect.h};
		SDL_BlitSurface(g_Enemies[i].imageSurface, NULL, g_WindowSurface, &auxRect);
	}

	//Blitting player
	SDL_Rect auxRect = {(int)g_Flower.rect.x, (int)g_Flower.rect.y, (int)g_Flower.rect.w, (int)g_Flower.rect.h};
	SDL_BlitSurface(g_Flower.imageSurface, NULL, g_WindowSurface, &auxRect);

	//Updating window
	SDL_UpdateWindowSurface(g_Window);
}

char RandomSign() {
    return ((rand() % 2 == 0) == true) ? 1 : -1;
}

unsigned int RandomInRange(unsigned int min, unsigned int max) {
    return rand() % (max - min) + min;
}

bool IsColliding(Rect object1, Rect object2) {
    //aabb
    if ((object1.x <= object2.x + object2.w) &&
        (object1.x + object1.w >= object2.x) &&
        (object1.y <= object2.y + object2.h) &&
        (object1.y + object1.h >= object2.y))
    {
        return true;
    }
    return false;
}
