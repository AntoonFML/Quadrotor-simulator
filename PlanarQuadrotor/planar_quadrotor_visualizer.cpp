#include "planar_quadrotor_visualizer.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int QUADROTOR_WIDTH = 80;
const int QUADROTOR_HEIGHT = 80;
const int PROPELLER_WIDTH = 30;
const int PROPELLER_HEIGHT = 5;
const int centerX = SCREEN_WIDTH / 2;
const int centerY = SCREEN_HEIGHT / 2;

PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualisation
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers
 */

void PlanarQuadrotorVisualizer::drawPropeller(std::shared_ptr<SDL_Renderer> &gRenderer, int x, int y, float angle){
    SDL_Rect propellerRect;
    propellerRect.x = x - PROPELLER_WIDTH / 2;
    propellerRect.y = y - PROPELLER_HEIGHT / 2;
    propellerRect.w = PROPELLER_WIDTH;
    propellerRect.h = PROPELLER_HEIGHT;

    SDL_SetRenderDrawColor(gRenderer.get(), 255, 0, 0, 255); 
    SDL_Point center = { propellerRect.w / 2, propellerRect.h / 2 };
    SDL_RenderFillRect(gRenderer.get(), &propellerRect);

    SDL_Texture* texture = SDL_CreateTexture(gRenderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, PROPELLER_WIDTH, PROPELLER_HEIGHT);
    SDL_SetRenderTarget(gRenderer.get(), texture);
    SDL_SetRenderDrawColor(gRenderer.get(), 255, 0, 0, 255);
    SDL_RenderClear(gRenderer.get());
    SDL_RenderFillRect(gRenderer.get(), &propellerRect);
    SDL_SetRenderTarget(gRenderer.get(), nullptr);
    SDL_RenderCopyEx(gRenderer.get(), texture, nullptr, &propellerRect, 90, &center, SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
}

void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {


     Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x = state[0];
    float q_y = state[1];
    float q_theta = state[2];


    SDL_Rect quadrotorRect;
    quadrotorRect.x = centerX + q_x - QUADROTOR_WIDTH / 2;
    quadrotorRect.y = centerY - q_y - QUADROTOR_HEIGHT / 2;
    quadrotorRect.w = QUADROTOR_WIDTH;
    quadrotorRect.h = QUADROTOR_HEIGHT;

    SDL_SetRenderDrawColor(gRenderer.get(), 0, 0, 255, 255);
    SDL_RenderFillRect(gRenderer.get(), &quadrotorRect);

    drawPropeller(gRenderer, quadrotorRect.x, quadrotorRect.y + QUADROTOR_HEIGHT, q_theta);
    drawPropeller(gRenderer, quadrotorRect.x + QUADROTOR_WIDTH, quadrotorRect.y + QUADROTOR_HEIGHT, q_theta);
    drawPropeller(gRenderer, quadrotorRect.x, quadrotorRect.y, q_theta);
    drawPropeller(gRenderer, quadrotorRect.x + QUADROTOR_WIDTH, quadrotorRect.y, q_theta);
}

