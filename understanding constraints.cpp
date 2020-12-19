// understanding constraints.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine.h"
#include "ParticleManager.h"


using olc::vf2d;

typedef vf2d v2;



struct pge;
void Input(pge*);
struct pge : olc::PixelGameEngine {

    ParticleManager PM;
    v2 MouseVec;

    bool OnUserCreate()
    {
        return true;
    }
    bool OnUserUpdate(float ft)
    {
        Clear(olc::BLACK);
        Input(this);
        PM.Update(ft);
        PM.Draw(this);
        return true;
    }

};


void Input(pge* scr)
{
    scr->MouseVec = { (float)scr->GetMouseX(), (float)scr->GetMouseY() };
    if (scr->GetMouse(0).bPressed)
    {
        

        if (scr->GetKey(olc::CTRL).bHeld)
        {
            scr->PM.AddParticle(scr->MouseVec,250, true);
        }
        else
        {
            scr->PM.AddParticle(scr->MouseVec,30, false);
            
        }


    }
    
    if (scr->GetMouse(1).bPressed)
    {

 
            scr->PM.SetSelected(scr->MouseVec);
 
        
    }

    if (scr->GetMouse(1).bHeld)
    {
        if (scr->PM.selected)
        {
            scr->PM.selected->p = scr->MouseVec;
            scr->PM.selected->v = { 0,0 };
        }
        
    }

    if (scr->GetMouse(1).bReleased)
    {
        scr->PM.selected = nullptr;
    }
    

   

}

int main()
{
    pge test;
    test.Construct(800, 800, 1, 1);
    test.Start();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
