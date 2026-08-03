//this is probably gonna be broken, I'm just moving code into here

#include "Engine.h"
using namespace sr;
using namespace std;

vector<Vector2> points;
Input input;
Renderer renderer;

int draw() {
    //handle clicking points
    if (input.GetMousePressed(sr::Input::MouseButton::LEFT)) {
        if (points.empty()) {
            points.push_back(input.GetMousePos());
        }
        else {
            sr::Vector2 v = points.back() - input.GetMousePos();
            if (v.Length() > 10.0f) {
                points.push_back(input.GetMousePos());
            }
        }
    }

    //handle click and drag
    if (input.GetMouseDown(sr::Input::MouseButton::LEFT)) {
        sr::Vector2 v = points.back() - input.GetMousePos();
        if (v.Length() > 10.0f) {
            points.push_back(input.GetMousePos());
        }
    }

    //handle undo
    if (input.GetKeyDown(SDL_SCANCODE_LCTRL) && input.GetKeyPressed(SDL_SCANCODE_Z))
    {
        if (!points.empty()) { points.pop_back(); }
    }

    if (points.size() > 1) {
        for (int i = 0; i < (int)points.size() - 1; ++i) {
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
    }
    else if (points.size() == 1) {
        renderer.DrawRect(points[0].x - 5, points[0].y - 5, 10, 10);
    }
    return 0;
}