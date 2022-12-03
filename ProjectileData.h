#pragma once
class ProjectileData
{
public:
	ProjectileData(Position position, double age) {
		this->position = position;
		this->age = age;
	}
	Position position;
	double age;
};

