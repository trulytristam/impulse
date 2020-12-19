#pragma once
#include "Particle.h"
#include <vector>
#include "Manifold.h"

using std::vector;
using std::shared_ptr;

class ParticleManager
{
	vector<shared_ptr<Particle>> vecParticles;
	vector<Manifold> vecManifolds;
public:
	Particle* selected = nullptr;

public:
	void Update(float);

	void Draw(olc::PixelGameEngine*);

	void AddParticle(v2,float, bool);

	void GenerateColliders();
	void GenerateManifolds();


	void ImpulseSolver(float);
	void SetSelected(v2);


	void Integrate(float);

	void Clean();







};

