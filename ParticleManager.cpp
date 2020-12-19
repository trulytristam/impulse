#include "ParticleManager.h"
#include "olcPixelGameEngine.h"
#include <iostream>
#include "Manifold.h"
#include "Shapes.h"



using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;


void ParticleManager::Clean()
{
	for (auto p : vecParticles) {
		if (p->p.y > 800 || p->p.y < 0 || p->p.x > 800 || p->p.x < 0)
		{
			//cout << "Particle Deleted" << endl;
			p->toDelete = true;
		}
	}

	auto itter = remove_if(vecParticles.begin(), vecParticles.end(), [](shared_ptr<Particle> p) {return p->toDelete; });
	vecParticles.erase(itter, vecParticles.end());
}

void ParticleManager::Integrate(float ft)
{
	for (auto p : vecParticles) {



		v2 gravity = { 0,1200 };  //Gravity

		p->AddForce(gravity);
		//p->ConstrainToCircle({ 200,200 }, 50);

		p->Integrate(ft, gravity);

		
	}
}

void ParticleManager::Update(float ft)
{




	GenerateColliders();
	GenerateManifolds();

	ImpulseSolver(ft);

	Integrate(ft);


	Clean();
}

void ParticleManager::SetSelected(v2 point)
{
	for (auto& s : vecParticles)
	{
		if (s->PointIn(point))
		{
			selected = &*s;
		}


	}

}


void ParticleManager::ImpulseSolver(float ft)
{
	int N = 40;
	for (int i = 0; i < N; i++)
	{
		for (auto mani : vecManifolds)
		{

			v2 n = mani.normal;

			v2 col = mani.twoPoint + mani.normal * (mani.depth / 2);

			Particle* a = mani.one;
			Particle* b = mani.two;

			v2 aPoint = mani.onePoint;
			v2 bPoint = mani.twoPoint;

			v2 ap = col - aPoint;
			v2 bp = col - bPoint;


			v2 aVel = a->getPointVelocity(aPoint);
			v2 bVel = b->getPointVelocity(bPoint);

			v2 relativeVel = aVel - bVel;


			float relativeVelProj = relativeVel.dot(n);

			float rat = ap.cross(n);
			rat = rat * rat;
			float rbt = bp.cross(n);
			rbt = rbt* rbt;




			if (relativeVelProj > 0)
			{
				//positive to b and negative to a
				float am = (a->iM + b->iM);

				float B = mani.depth;
				float top = ((0.7) * relativeVelProj) -0.008 / ft * B ;
				float bot = am + (rat * a->iI + rbt * b->iI);
				float j = top / bot;

				v2 J = n * (j - B);

				a->AddImpulse(col, J * -1);
				b->AddImpulse(col, J);

			}

			if(i==N-1)
			{
				v2 t = relativeVel - relativeVel * relativeVel.dot(n);
				v2 tangent = t.norm();

				float relativeVelProjTan = relativeVel.dot(tangent);



				float ratT = ap.cross(tangent);
				ratT = ratT * ratT;
				float rbtT = bp.cross(tangent);
				rbtT = rbtT * rbtT;

				if (relativeVelProjTan > 0)
				{
					//positive to b and negative to a
					float am = (a->iM + b->iM);


					float top = (relativeVelProjTan);
					float bot = am + (ratT * a->iI + rbtT * b->iI);
					float j = top / bot;

					

					v2 J = -tangent * j *0.08;
					//cout << "JJ: "<< J.mag() << endl;

					a->AddImpulse(col, J);
					b->AddImpulse(col, J * -1);

				}
			}
			





			//if (!a->bStatic)
				//a->p += n * (mani.depth) * 0.04;

			//if (!b->bStatic)
				//b->p -= n * (mani.depth) * 0.04;
		}
	}
	
}


void ParticleManager::Draw(olc::PixelGameEngine* scr)
{


	//scr->DrawCircle({ 200,200 }, 50);

	for (auto& p : vecParticles) {

		
		p->Draw(scr);

		//cout << "Particle Drawn" << endl;

	}


	for (auto m : vecManifolds)
	{


		v2 point = m.onePoint;
		v2 point2 = m.twoPoint;


		//scr->FillCircle(point.x, point.y, 3, olc::RED);
		//scr->FillCircle(point2.x, point2.y, 3, olc::BLUE);


		//scr->DrawLine(point, point + m.normal * 15, olc::BLUE);


		
	}

}


void ParticleManager::AddParticle(v2 p,float s, bool stat = false)
{
	//cout << "Particle Added" << endl;
	

	vecParticles.push_back(make_shared<Particle>(p, Square, s, stat));

	//cout << "n particles: " << vecParticles.size() << endl;
}

void ParticleManager::GenerateColliders()
{
	for (auto& particle1 : vecParticles)
	{

		particle1->UpdateCollider();


	}
}

void ParticleManager::GenerateManifolds() {

	vecManifolds.clear();
	int s = vecParticles.size();

	for (int i = 0; i< s-1; i++)
	{
		
		shared_ptr<Particle> particle1 = vecParticles[i];
		for (int j = i+1; j < vecParticles.size(); j++)
		{
			shared_ptr<Particle> particle2 = vecParticles[j];

			if (&*particle1 != &*particle2)
			{
				Manifold tempMan;

				if (particle1->isCollidingWith(particle2, tempMan))
				{
					vecManifolds.push_back(tempMan);

				}
			}
		}
	}

}
