#pragma once

#include "../Utility/Vector2D.h"

class Player
{
private:
	Vector2D location;
	Vector2D direction;
	float radius;

public:
	Player();
	Player(float x, float y);
	Player(Vector2D location);
	~Player();

	void Update();
	void Draw() const;

	void SetLocation(float x, float y);
	void SetLocation(Vector2D location);
	Vector2D GetLocation() const;
	float GetRadius();

private:
	void Movement();
};